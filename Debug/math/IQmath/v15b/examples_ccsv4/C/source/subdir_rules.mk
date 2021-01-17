################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
math/IQmath/v15b/examples_ccsv4/C/source/%.obj: ../math/IQmath/v15b/examples_ccsv4/C/source/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/WorkSpace/GitHub/BLDC_Motor28335" --include_path="C:/WorkSpace/GitHub/BLDC_Motor28335/Inc" --include_path="C:/WorkSpace/GitHub/BLDC_Motor28335/math/FPUfastRTS/V100/include" --include_path="C:/WorkSpace/GitHub/BLDC_Motor28335/F2833x/v141/DSP2833x_headers/include" --include_path="C:/WorkSpace/GitHub/BLDC_Motor28335/F2833x/v141/DSP2833x_common/include" --include_path="C:/WorkSpace/GitHub/BLDC_Motor28335/math/IQmath/v160/include" --include_path="C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="math/IQmath/v15b/examples_ccsv4/C/source/$(basename $(<F)).d_raw" --obj_directory="math/IQmath/v15b/examples_ccsv4/C/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

math/IQmath/v15b/examples_ccsv4/C/source/%.obj: ../math/IQmath/v15b/examples_ccsv4/C/source/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/WorkSpace/GitHub/BLDC_Motor28335" --include_path="C:/WorkSpace/GitHub/BLDC_Motor28335/Inc" --include_path="C:/WorkSpace/GitHub/BLDC_Motor28335/math/FPUfastRTS/V100/include" --include_path="C:/WorkSpace/GitHub/BLDC_Motor28335/F2833x/v141/DSP2833x_headers/include" --include_path="C:/WorkSpace/GitHub/BLDC_Motor28335/F2833x/v141/DSP2833x_common/include" --include_path="C:/WorkSpace/GitHub/BLDC_Motor28335/math/IQmath/v160/include" --include_path="C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="math/IQmath/v15b/examples_ccsv4/C/source/$(basename $(<F)).d_raw" --obj_directory="math/IQmath/v15b/examples_ccsv4/C/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


