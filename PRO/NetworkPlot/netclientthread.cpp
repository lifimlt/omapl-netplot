#include "netclientthread.h"

#define             RING_BUFFER_SIZE    19200ul
#define             pow(x) x*x
NetClientThread::NetClientThread( QString server_ip, quint16 server_port )
{

    socket = new QTcpSocket();
    server = new QTcpServer();
    data_packet = (struct data_packet_t*)malloc(sizeof(struct data_packet_t));
    file_ctr = new FileManager();
    array_length = 0;
    mutex = new QMutex();
    count = 0;
    is_head = false;
    packet_number = 0;
    kcount = 0;
    isEnableSave = false;
    is_enable_socket_read = false;
    left_length = 0;
    array_rom.clear();
    connect( this, SIGNAL(net_data_save_to_disk(quint8*,quint64) ),(QObject*)this->file_ctr ,SLOT(on_save_data_to_disk(quint8*,quint64)));
    connect( (QObject*)this->file_ctr, SIGNAL(file_manager_add_file_name(QString)), this, SLOT(on_file_manager_add_doc_list(QString)) );
    connect( (QObject*)this->file_ctr, SIGNAL(file_manager_file_size(double)), this, SLOT(on_file_manager_file_size(double)));

}
// not use
bool NetClientThread::set_connect(QString server_ip, quint16 server_port)
{
    qDebug() << "netclientread@set_connect() >: seting the connection to " <<  server_ip;
    socket->connectToHost( QHostAddress(server_ip), server_port , QIODevice::ReadWrite );
    if( !socket->waitForConnected(500) ) {
        qDebug() << socket->error();
        qDebug("netclientread@set_connect() >: socket Connection failed!!");
        return false;
    }else {
        QObject::connect((QObject*) socket,SIGNAL(readyRead()),(QObject*)this,SLOT(on_read_message()));
        qDebug("netclientread@set_connect() >: socket conncetion succussful.");
        return true;
    }
}
void NetClientThread::set_disconnet()
{
    socket->flush();
    socket->close();
}

float NetClientThread::bcd_decoding(uint8_t *dHandle)
{
    float *df;
    uint32_t temp;

    for ( int i = 0; i < 4; i ++ ) {
        temp |= *(dHandle + 4 - i) & 0xFF;
        temp = temp << 8;
    }
    df = (float *)&temp;
    return *df;
}

void NetClientThread::bcd_encoding(float df, uint8_t *distChar)
{
    uint8_t* dHandle;

    dHandle = (uint8_t *)&df;
    *distChar = *dHandle & 0xFF;
    *(distChar + 1) = *(dHandle + 1) & 0xFF ;
    *(distChar + 2) = *(dHandle + 2) & 0xFF ;
    *(distChar + 3) = *(dHandle + 3) & 0xFF ;
}

void NetClientThread::send_cmd_close_app()
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(0xAA);
    cmd.append(0xBB);
    cmd.append(0x01);
    cmd.append(0x01);
    cmd.append(0xFF);
    cmd.append(0xAA^0xBB^0x01^0x01^0xFF);
    socket->write(cmd);
    socket->flush();
    //1//xqDebug() << "netclientread@send_cmd_close_app() >: close remote...." ;
}

void NetClientThread::send_cmd_to_remote(uint8_t *users, quint16 length)
{
    QByteArray cmd;
    quint8  checkSum = 0;
    union {
        struct {
            uint8_t bit0_8;
            uint8_t bit8_16;
        } bits;
        uint16_t all;
    } lengthCmd;

    cmd.clear();
    cmd.append(CMD_HEADER_1);
    cmd.append(CMD_HEADER_2);
    /* cmd length not contains cmd headers(0xAA 0xBB) and length byte. */
    lengthCmd.all = length - 1;
    cmd.append( lengthCmd.bits.bit8_16);
    cmd.append( lengthCmd.bits.bit0_8);
    for (int i = 0; i < length; i ++)
        cmd.append(users[i]);
    //1//xqDebug() << "send :" << cmd;
    socket->write(cmd);
    socket->flush();
    //1//xqDebug() << "netclientread@send_cmd_close_app() >: send to remote...." ;
}
// socket ascii stream.
// [0xAD 0xAC] : 2bytes frame heads.
// [0xLL 0xLL 0xLL 0xLL] : 4bytes data number.
// 500 x [0xQQ 0xQQ 0xQQ 0xTT | 0xQQ 0xQQ 0xQQ 0xTT | 0xQQ 0xQQ 0xQQ 0xTT | 0xQQ 0xQQ 0xQQ 0xTT] : 500*16 adc datas
// [0xEE 0xEE 0xEE 0xEE] : 4bytes end flags.
void NetClientThread::run()
{

}
void NetClientThread::on_read_message()
{
    if (socket->bytesAvailable() < ONE_PACKET_LENGTH)
        return;
    array_rom.append(socket->read(ONE_PACKET_LENGTH));
    if (isEnableSave == true)
        emit net_data_save_to_disk((quint8*)array_rom.data(), array_rom.length());
    qDebug() << array_rom.indexOf("abcd");
    qDebug() << array_rom.indexOf("cdab");
    check_packet(array_rom);
    array_rom.clear();
}

QByteArray NetClientThread::check_packet(QByteArray array)
{
    QByteArray left;
    QByteArray true_packet;
    left.clear();
    true_packet.clear();

    if (array.contains("abcd") && array.contains("cdab") && \
        (array.indexOf("abcd") < array.indexOf("cdab")) ) {
        true_packet = array.mid(array.indexOf("abcd") , array.indexOf("cdab")+4);
        deal_true_packet(true_packet);
        qDebug() << "found a true packet.";
    }else  {
        qDebug() << "found a error packet.";
    }
    left = array;
    return left;

}
bool NetClientThread::deal_true_packet(QByteArray array)
{
    int header_count = 0;
    int tail_count = 0;
    float f_buffer[3000];
    quint64 packet_number;
    quint64 data_length;

    union result {
        quint64 u_64;
        float f_64;
        char c_8[8];
    } r;

    header_count = array.count("abcd");
    tail_count = array.count("cdab");
    QByteArray *seper_array = new QByteArray[header_count];

    if ( (header_count != tail_count) | (header_count < 1) ){
         qDebug() << "head and tail count not equals";
         qDebug() << "header : " << header_count ;
         qDebug() << "tail :" << tail_count;
         return false;
    }

    qDebug() << "include " << header_count << " packet;";

    int count = 0;
    while (!array.isEmpty()) {
        seper_array[count].append( array.mid(array.indexOf("abcd") + 4, array.indexOf("cdab") ) );
        array.remove(0,array.indexOf("cdab") + 4);
        count ++;
        //qDebug() << "deal " << count << " packet; length is :" << seper_array[0].length();
    }
    socket_buffer = (quint8*)malloc(sizeof(quint8)*seper_array[0].length()*8);
    for (quint64 i = 0; i < seper_array[0].length(); i ++) {
        socket_buffer[i] =  seper_array[0].at(i);
    }

    free(socket_buffer);
    for (quint64 i = 0; i < (seper_array[0].length() - 20) / 8; i ++) {
        for (quint64 j = 0; j < 8; j ++)
            r.c_8[j]  = seper_array[0].at(i*8 + j);
        if (i == 0) {
            packet_number = r.u_64;
            qDebug() << "packet number :" << packet_number;
        }
        if (i == 1) {
            data_length = r.u_64;
        }
        if (i >= 2) {
            f_buffer[i - 2] = r.f_64;
            if (i > 2048) {
                break;
            }
        }
    }
    delete seper_array;
    emit net_data_plot(f_buffer, 2048);
    // process the data;
}

qint8 NetClientThread::check_packet(quint8* array, quint64 length)
{
    quint16 header_vector_table[9999];
    quint32 vec_counter = 0;


    memset(header_vector_table,0xff,9999);

    header_vector_table[0] = 0xF;
    for (quint32 i = 0; i < length - 1; i ++) {
        if ( ((array[i] & 0xFF)  == 0xad) && (((array[i+1] & 0xFF) == 0xac)) ) {
            header_vector_table[vec_counter] = i;
            vec_counter ++;
        }
    }
    if (vec_counter > 9999) {
        //xqDebug() << "@check_packet: over the length "<< vec_counter;
    }
    // case 1;
    if ((header_vector_table[0] == 0) && (length%ONE_PACKET_LENGTH == 0)) {
        is_head = true;
        return 1;
    }
    // case 2;
    if ((header_vector_table[0] == 0) && (length%ONE_PACKET_LENGTH != 0)) {
        is_head = true;
        return 2;
    }
    // case 3;
    if ((header_vector_table[0] != 0) && (is_head == true)) {
        return 3;
    }
    // case 4;
    if ((header_vector_table[0] != 0) && (is_head == false)) {
        is_head = true;
        return 4;
    }

    return -1;
}
void NetClientThread::case_1(quint8 *buffer,  quint64 length, quint32 vector_counter)
{
    case_1(buffer, length);
}

void NetClientThread::case_1(quint8 *buffer,  quint64 length)
{

    //xqDebug() << "do case 1";
    qint64 count = 0;
    qint32 length_d = (qint32)length;
    qint32 pac_num = 8010;
    quint32 da,db,dc,dd,d_len;
    count = (length_d / 8010);
    ////1//xqDebug() << "emit net data save to disk singal.";


    kcount ++;
    //1//xqDebug() << "@case_1 : count is :" << count;
    // plot data
    if (kcount % 12 == 0) {
        kcount = 0;
        memset(channel_data,0,2000);
        quint32 uh = 0, h = 0, l = 0, ul = 0;

        for (quint64 i = 0 ; i < 500*16; i ++) {
            plot_buffer[i] = buffer[i+6];
        }

        uh = (plot_buffer[2] << 24) & 0xFF000000;
        h  = (plot_buffer[3] << 16) & 0x00FF0000;
        l  = (plot_buffer[4] << 8)  & 0x0000FF00;
        ul = (plot_buffer[5] << 0)  & 0X000000FF;
        d_len = uh | h | l | ul;

        for (quint64 i = 0; i < 500; i ++) {

            uh = (plot_buffer[16*i + 2] << 16) & 0x00FF0000;
            h  = (plot_buffer[16*i + 1] << 8)  & 0x0000FF00;
            l  = (plot_buffer[16*i + 0] << 0)  & 0x000000FF;
            ul = (plot_buffer[16*i + 3] << 0)  & 0X000000FF;

            da = uh | h | l;

            uh = (plot_buffer[16*i + 6] << 16) & 0x00FF0000;
            h  = (plot_buffer[16*i + 5] << 8)  & 0x0000FF00;
            l  = (plot_buffer[16*i + 4] << 0)  & 0x000000FF;
            ul = (plot_buffer[16*i + 7] << 0)  & 0X000000FF;

            db = uh | h | l;

            uh = (plot_buffer[16*i + 10] << 16) & 0x00FF0000;
            h  = (plot_buffer[16*i + 9] << 8)  & 0x0000FF00;
            l  = (plot_buffer[16*i + 8] << 0)  & 0x000000FF;
            ul = (plot_buffer[16*i + 11] << 0)  & 0X000000FF;

            dc = uh | h | l;

            uh = (plot_buffer[16*i + 14] << 16) & 0x00FF0000;
            h  = (plot_buffer[16*i + 13] << 8)  & 0x0000FF00;
            l  = (plot_buffer[16*i + 12] << 0)  & 0x000000FF;
            ul = (plot_buffer[16*i + 15] << 0)  & 0X000000FF;

            dd = uh | h | l;

            channel_data[i] = da;
            channel_data[500 + i] = db;
            channel_data[1000 + i] = dc;
            channel_data[1500 + i] = dd;
        }
        ////1//xqDebug() << "emit net data plot signal.";
       //emit net_data_plot(channel_data, 2000);
    }


}
void NetClientThread::case_2(quint8 *socket_buffer, quint64 length, quint8 *left_buffer, quint64 *left_length)
{
    //xqDebug() << "do case 2";
    quint32 final_head_index = 0;
    // step 1: save left buffer data.

    for (quint64 i = length; i > 0; i --) {
        if ( socket_buffer[i-1] == 0xAC && socket_buffer[i-2] == 0xAD ) {
            final_head_index = i - 2;
            break;
        }
    }
    *left_length = length - final_head_index;
    // positive direction save.
    for (quint64 i = 0; i < *left_length; i ++) {
        *(left_buffer + i) = *(socket_buffer + final_head_index + i);
    }

    // step 2: save complete data packet.
    //xqDebug() << "case 2 join case 1";
    //case_1(left_buffer, final_head_index);
}

void NetClientThread::case_3(quint8 *socket_buffer, quint64 length, quint8 *right_buffer, quint64 right_length)
{
    //xqDebug() << "do case 3";
    quint64 first_header_index = 0;
    quint32 header_vector_table[100];
    quint64 header_number = 0;
    quint8 *unknown_buffer = new quint8[ONE_PACKET_LENGTH*100];
    quint32 unknown_length = 0;
    quint32 surplus_len = 0;
    quint32 refresh_len = 0;

    quint8 *fresh_buffer = (quint8* )malloc(sizeof(quint8) * (100*ONE_PACKET_LENGTH + 1));
    quint8 *a_full_packet_buffer = new quint8[ONE_PACKET_LENGTH*5];
    // STEP1 : abstract the the data in front of the first head.
    memset(header_vector_table,0,100);
    for (quint64 i = 0; i < length; i ++) {
        if ( (*(socket_buffer + i) == 0xAD) && (*(socket_buffer + i + 1) == 0xAC) ) {
            header_vector_table[header_number] = i;
            header_number ++;
        }
    }
    header_number -= 1;
    memcpy(a_full_packet_buffer, right_buffer, right_length);
    memcpy(a_full_packet_buffer, socket_buffer, header_vector_table[0]);
    // now a full packet mix succuss, the length is 8010.
    // save the a_full_packet_buffer.
    //case_1(a_full_packet_buffer, ONE_PACKET_LENGTH);

    // STEP2 : give the surplus data to check.
    refresh_len =  length - header_vector_table[0];
    memcpy(fresh_buffer, socket_buffer + header_vector_table[0], refresh_len);
    int ret = check_packet(fresh_buffer, refresh_len);

    if (ret == 1) {
        //xqDebug() << "case 3 join case 1";
        //case_1(fresh_buffer, refresh_len);
    }else if( ret == 2 ) {
        //xqDebug() << "case 3 join case 2";
        //case_2(fresh_buffer, refresh_len, left_rom, &left_length);
    }else{
        //xqDebug() << "You are wrong about case not 1 or 2 what else?";
    }
#if 0
    // deal with last right surplus.
    ////xqDebug() << "@case3:vector:" << vector_count;

    memcpy(all_buffer, right_buffer, right_length);
    memcpy(all_buffer + right_length, socket_buffer, length);
    unknown_length = length + right_length;
    memcpy(unknown_buffer, all_buffer, unknown_length);

    memcpy(all_buffer + right_length, socket_buffer, header_vector_table[vector_count]);
    finish_len = right_length + header_vector_table[vector_count];
    // deal with right surplus
    surplus_len = length - (header_vector_table[vector_count] + 1) - 1;

    if ((surplus_len < ONE_PACKET_LENGTH - 2)) {
        // the case 3 packet right data is not full.
        memcpy(right_buffer, socket_buffer + (header_vector_table[vector_count]), surplus_len);
    }else if (surplus_len == ONE_PACKET_LENGTH - 2){
        memcpy(all_buffer + right_length + surplus_len, socket_buffer + header_vector_table[vector_count], ONE_PACKET_LENGTH);
        finish_len += ONE_PACKET_LENGTH;
    }else {
        //xqDebug() << "@case 3: error no case;";
    }

    ////xqDebug() << "join case1!";
    case_1(all_buffer, finish_len);

    int ret = check_packet(unknown_buffer,unknown_length);
    if (ret == 1) {
        //xqDebug() << "join case 1";
        case_1(unknown_buffer,unknown_length);
    }else if( ret == 2 ) {
        //xqDebug() << "join case 2";
        case_2(unknown_buffer, unknown_length, left_rom, &left_length);
    }else{
        //xqDebug() << "You are wrong about case not 1 or 2 what else?";
    }
#endif
    delete a_full_packet_buffer;
    free(unknown_buffer);
    delete fresh_buffer;
}

void NetClientThread::case_4(quint8 *socket_buffer, quint64 length)
{
    //xqDebug() << "do case 4";
    quint64 first_header_index = 0;
    quint8 *unknown_buffer = new quint8[ONE_PACKET_LENGTH*100];
    quint32 unknown_length = 0;
    quint32 unknown_pac_num = 0;

    for (quint64 i = 0; i < length; i ++) {
        if ( (*(socket_buffer + i) == 0xAD) && (*(socket_buffer + i + 1) == 0xAC) ) {
            first_header_index = i;
            break;
        }
    }
    quint8 *all_buffer = (quint8* )malloc(sizeof(quint8) * (100*ONE_PACKET_LENGTH + 1));

    memcpy(all_buffer, socket_buffer + first_header_index, length - first_header_index + 1);

    int ret = check_packet(unknown_buffer, unknown_length);
    if (ret == 1) {
        //xqDebug() << "case 4 join case 1";
        //case_1(unknown_buffer,unknown_length);
    }else if( ret == 2 ) {
        //xqDebug() << "case 4 join case 2";
        //case_2(unknown_buffer, unknown_length, left_rom, &left_length);
    }else{
        //xqDebug() << "You are wrong about case not 1 or 2 what else?";
    }
    free(all_buffer);
    delete unknown_buffer;
}



void NetClientThread::on_net_close_file()
{
    if (file_ctr->file->isOpen()) {
        file_ctr->fileClose();
    }
}

void NetClientThread::on_net_enable_save(bool state)
{
    isEnableSave = state;
    if (file_ctr->file->isOpen() && isEnableSave == false) {
        file_ctr->fileClose();
    }

    if (!file_ctr->file->isOpen() && isEnableSave == true) {
    }
}

void NetClientThread::on_file_manager_add_doc_list(QString filename)
{
    emit net_add_doc_list(filename);
}

void NetClientThread::on_file_manager_file_size(double percent)
{
    emit net_file_size(percent);
}

void NetClientThread::stop()
{
    stop();
}

void NetClientThread::enable_socket_read(bool state)
{
    is_enable_socket_read = state;
}

QString NetClientThread::gethostMac()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();
    int nCnt = nets.count();
    QString strMacAddr = "";
    for(int i = 0; i < nCnt; i ++) {
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning)
                && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            strMacAddr = nets[i].hardwareAddress();
            break;
        }
    }
    return strMacAddr;

}
NetClientThread::~NetClientThread()
{
    delete this->file_ctr;
}
