#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#

unexport MAKEFILE_LIST
MK_NOGENDEPS := $(filter clean,$(MAKECMDGOALS))
override PKGDIR = configuro
XDCINCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(XPKGPATH))))
XDCCFGDIR = package/cfg/

#
# The following dependencies ensure package.mak is rebuilt
# in the event that some included BOM script changes.
#
ifneq (clean,$(MAKECMDGOALS))
/opt/ti/xdctools_3_25_03_72/packages/xdc/utils.js:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/utils.js
/opt/ti/xdctools_3_25_03_72/packages/xdc/xdc.tci:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/xdc.tci
/opt/ti/xdctools_3_25_03_72/packages/xdc/template.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/template.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/om2.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/om2.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/xmlgen.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/xmlgen.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/xmlgen2.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/xmlgen2.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/Warnings.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/Warnings.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/IPackage.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/IPackage.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/package.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/package.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/services/global/Clock.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/services/global/Clock.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/services/global/Trace.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/services/global/Trace.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/bld/bld.js:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/bld/bld.js
/opt/ti/xdctools_3_25_03_72/packages/xdc/bld/BuildEnvironment.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/bld/BuildEnvironment.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/bld/PackageContents.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/bld/PackageContents.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/bld/_gen.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/bld/_gen.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/bld/Library.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/bld/Library.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/bld/Executable.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/bld/Executable.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/bld/Repository.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/bld/Repository.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/bld/Configuration.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/bld/Configuration.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/bld/Script.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/bld/Script.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/bld/Manifest.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/bld/Manifest.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/bld/Utils.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/bld/Utils.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/bld/ITarget.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/bld/ITarget.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/bld/ITarget2.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/bld/ITarget2.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/bld/ITarget3.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/bld/ITarget3.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/bld/ITargetFilter.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/bld/ITargetFilter.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/bld/package.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/bld/package.xs
package.mak: config.bld
/home/delvis/script/ad7606_dsp/shared/config.bld:
package.mak: /home/delvis/script/ad7606_dsp/shared/config.bld
/opt/ti/xdctools_3_25_03_72/packages/ti/targets/ITarget.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/ti/targets/ITarget.xs
/opt/ti/xdctools_3_25_03_72/packages/ti/targets/C28_large.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/ti/targets/C28_large.xs
/opt/ti/xdctools_3_25_03_72/packages/ti/targets/C28_float.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/ti/targets/C28_float.xs
/opt/ti/xdctools_3_25_03_72/packages/ti/targets/package.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/ti/targets/package.xs
/opt/ti/xdctools_3_25_03_72/packages/ti/targets/elf/ITarget.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/ti/targets/elf/ITarget.xs
/opt/ti/xdctools_3_25_03_72/packages/ti/targets/elf/package.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/ti/targets/elf/package.xs
package.mak: package.bld
/opt/ti/xdctools_3_25_03_72/packages/xdc/tools/configuro/template/compiler.opt.xdt:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/tools/configuro/template/compiler.opt.xdt
/opt/ti/xdctools_3_25_03_72/packages/xdc/services/io/File.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/services/io/File.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/services/io/package.xs:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/services/io/package.xs
/opt/ti/xdctools_3_25_03_72/packages/xdc/tools/configuro/template/compiler.defs.xdt:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/tools/configuro/template/compiler.defs.xdt
/opt/ti/xdctools_3_25_03_72/packages/xdc/tools/configuro/template/custom.mak.exe.xdt:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/tools/configuro/template/custom.mak.exe.xdt
/opt/ti/xdctools_3_25_03_72/packages/xdc/tools/configuro/template/package.xs.xdt:
package.mak: /opt/ti/xdctools_3_25_03_72/packages/xdc/tools/configuro/template/package.xs.xdt
endif

ti.targets.elf.C674.rootDir ?= /opt/ti/ccsv5/tools/compiler/c6000_7.4.4
ti.targets.elf.packageBase ?= /opt/ti/xdctools_3_25_03_72/packages/ti/targets/elf/
.PRECIOUS: $(XDCCFGDIR)/%.oe674
.PHONY: all,e674 .dlls,e674 .executables,e674 test,e674
all,e674: .executables,e674
.executables,e674: .libraries,e674
.executables,e674: .dlls,e674
.dlls,e674: .libraries,e674
.libraries,e674: .interfaces
	@$(RM) $@
	@$(TOUCH) "$@"

.help::
	@$(ECHO) xdc test,e674
	@$(ECHO) xdc .executables,e674
	@$(ECHO) xdc .libraries,e674
	@$(ECHO) xdc .dlls,e674


all: .executables 
.executables: .libraries .dlls
.libraries: .interfaces

PKGCFGS := $(wildcard package.xs) package/build.cfg
.interfaces: package/package.xdc.inc package/package.defs.h package.xdc $(PKGCFGS)

-include package/package.xdc.dep
package/%.xdc.inc package/%_configuro.c package/%.defs.h: %.xdc $(PKGCFGS)
	@$(MSG) generating interfaces for package configuro" (because $@ is older than $(firstword $?))" ...
	$(XSRUN) -f xdc/services/intern/cmd/build.xs $(MK_IDLOPTS) -m package/package.xdc.dep -i package/package.xdc.inc package.xdc

.dlls,e674 .dlls: dsp.pe674

-include package/cfg/dsp_pe674.mak
-include package/cfg/dsp_pe674.cfg.mak
ifeq (,$(MK_NOGENDEPS))
-include package/cfg/dsp_pe674.dep
endif
dsp.pe674: package/cfg/dsp_pe674.xdl
	@


ifeq (,$(wildcard .libraries,e674))
dsp.pe674 package/cfg/dsp_pe674.c: .libraries,e674
endif

package/cfg/dsp_pe674.c package/cfg/dsp_pe674.h package/cfg/dsp_pe674.xdl: override _PROG_NAME := dsp.xe674
package/cfg/dsp_pe674.c: package/cfg/dsp_pe674.cfg

clean:: clean,e674
	-$(RM) package/cfg/dsp_pe674.cfg
	-$(RM) package/cfg/dsp_pe674.dep
	-$(RM) package/cfg/dsp_pe674.c
	-$(RM) package/cfg/dsp_pe674.xdc.inc

clean,e674::
	-$(RM) dsp.pe674
.executables,e674 .executables: dsp.xe674

dsp.xe674: |dsp.pe674

-include package/cfg/dsp.xe674.mak
dsp.xe674: package/cfg/dsp_pe674.oe674 
	$(RM) $@
	@$(MSG) lnke674 $@ ...
	$(RM) $(XDCCFGDIR)/$@.map
	$(ti.targets.elf.C674.rootDir)/bin/lnk6x -w -q -u _c_int00 -fs $(XDCCFGDIR)$(dir $@)  -q -o $@ package/cfg/dsp_pe674.oe674   package/cfg/dsp_pe674.xdl --abi=eabi -c -m $(XDCCFGDIR)/$@.map -l $(ti.targets.elf.C674.rootDir)/lib/libc.a
	
dsp.xe674: export C_DIR=
dsp.xe674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

dsp.test test,e674 test: dsp.xe674.test

dsp.xe674.test:: dsp.xe674
ifeq (,$(_TESTLEVEL))
	@$(MAKE) -R -r --no-print-directory -f $(XDCROOT)/packages/xdc/bld/xdc.mak _TESTLEVEL=1 dsp.xe674.test
else
	@$(MSG) running $<  ...
	$(call EXEC.dsp.xe674, ) 
endif

clean,e674::
	-$(RM) .tmp,dsp.xe674,0,*


clean:: clean,e674

clean,e674::
	-$(RM) dsp.xe674
clean:: 
	-$(RM) package/cfg/dsp_pe674.pjt
%,copy:
	@$(if $<,,$(MSG) don\'t know how to build $*; exit 1)
	@$(MSG) cp $< $@
	$(RM) $@
	$(CP) $< $@
dsp_pe674.oe674,copy : package/cfg/dsp_pe674.oe674
dsp_pe674.se674,copy : package/cfg/dsp_pe674.se674

$(XDCCFGDIR)%.c $(XDCCFGDIR)%.h $(XDCCFGDIR)%.xdl: $(XDCCFGDIR)%.cfg .interfaces $(XDCROOT)/packages/xdc/cfg/Main.xs
	@$(MSG) "configuring $(_PROG_NAME) from $< ..."
	$(CONFIG) $(_PROG_XSOPTS) xdc.cfg $(_PROG_NAME) $(XDCCFGDIR)$*.cfg $(XDCCFGDIR)$*

.PHONY: release,configuro
configuro.tar: package/package.bld.xml
configuro.tar: package/build.cfg
configuro.tar: package/package.xdc.inc
ifeq (,$(MK_NOGENDEPS))
-include package/rel/configuro.tar.dep
endif
package/rel/configuro/configuro/package/package.rel.xml: .force
	@$(MSG) generating external release references $@ ...
	$(XS) $(JSENV) -f $(XDCROOT)/packages/xdc/bld/rel.js $(MK_RELOPTS) . $@

configuro.tar: package/rel/configuro.xdc.inc package/rel/configuro/configuro/package/package.rel.xml
	@$(MSG) making release file $@ "(because of $(firstword $?))" ...
	-$(RM) $@
	$(call MKRELTAR,package/rel/configuro.xdc.inc,package/rel/configuro.tar.dep)


release release,configuro: all configuro.tar
clean:: .clean
	-$(RM) configuro.tar
	-$(RM) package/rel/configuro.xdc.inc
	-$(RM) package/rel/configuro.tar.dep

clean:: .clean
	-$(RM) .libraries .libraries,*
clean:: 
	-$(RM) .dlls .dlls,*
#
# The following clean rule removes user specified
# generated files or directories.
#

ifneq (clean,$(MAKECMDGOALS))
ifeq (,$(wildcard package))
    $(shell $(MKDIR) package)
endif
ifeq (,$(wildcard package/cfg))
    $(shell $(MKDIR) package/cfg)
endif
ifeq (,$(wildcard package/lib))
    $(shell $(MKDIR) package/lib)
endif
ifeq (,$(wildcard package/rel))
    $(shell $(MKDIR) package/rel)
endif
ifeq (,$(wildcard package/internal))
    $(shell $(MKDIR) package/internal)
endif
endif
clean::
	-$(RMDIR) package

include custom.mak
clean:: 
	-$(RM) package/configuro.pjt
