################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
CodeStartBranch.obj: D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/CodeStartBranch.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --optimize_with_debug --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --diag_warning=225 -k --asm_listing --output_all_syms --preproc_with_compile --preproc_dependency="CodeStartBranch.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

IQsample.obj: D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --optimize_with_debug --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" --include_path="/packages/ti/xdais" --include_path="D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --diag_warning=225 -k --asm_listing --output_all_syms --preproc_with_compile --preproc_dependency="IQsample.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


