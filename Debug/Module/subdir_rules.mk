################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Module/%.obj: ../Module/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -O3 --opt_for_speed=3 --include_path="C:/WorkSpace/GitHub/BLDC_Motor28335" --include_path="C:/WorkSpace/GitHub/BLDC_Motor28335/Inc" --include_path="C:/WorkSpace/GitHub/math/FPUfastRTS/V100/include" --include_path="C:/WorkSpace/GitHub/F2833x/v141/DSP2833x_headers/include" --include_path="C:/WorkSpace/GitHub/F2833x/v141/DSP2833x_common/include" --include_path="C:/WorkSpace/GitHub/math/IQmath/v160/include" --include_path="C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS/include" --advice:performance=all --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Module/$(basename $(<F)).d_raw" --obj_directory="Module" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


