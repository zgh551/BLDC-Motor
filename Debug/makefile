################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./Module/CRC.obj" \
"./Module/Control.obj" \
"./Module/Digital_IO.obj" \
"./Module/ExternalInterrupt.obj" \
"./Module/Led.obj" \
"./Module/PID.obj" \
"./Module/Relay.obj" \
"./Module/SelfCheck.obj" \
"./Module/State_Machine.obj" \
"./Module/SteeringEngine.obj" \
"./Module/Steering_ADC.obj" \
"./Module/Steering_SCI.obj" \
"./Module/Steering_SPI.obj" \
"./Module/Steering_XINTF.obj" \
"./Src/DSP2833x_ADC_cal.obj" \
"./Src/DSP2833x_Adc.obj" \
"./Src/DSP2833x_CodeStartBranch.obj" \
"./Src/DSP2833x_CpuTimers.obj" \
"./Src/DSP2833x_DMA.obj" \
"./Src/DSP2833x_DefaultIsr.obj" \
"./Src/DSP2833x_EPwm.obj" \
"./Src/DSP2833x_GlobalVariableDefs.obj" \
"./Src/DSP2833x_Gpio.obj" \
"./Src/DSP2833x_MemCopy.obj" \
"./Src/DSP2833x_PieCtrl.obj" \
"./Src/DSP2833x_PieVect.obj" \
"./Src/DSP2833x_Sci.obj" \
"./Src/DSP2833x_Spi.obj" \
"./Src/DSP2833x_SysCtrl.obj" \
"./Src/DSP2833x_Xintf.obj" \
"./Src/DSP2833x_usDelay.obj" \
"../28335_RAM_lnk.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Module/subdir_vars.mk
-include Src/subdir_vars.mk
-include subdir_rules.mk
-include Module/subdir_rules.mk
-include Src/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
BLDC_Motor.out \

EXE_OUTPUTS__QUOTED += \
"BLDC_Motor.out" \

BIN_OUTPUTS += \
BLDC_Motor.hex \

BIN_OUTPUTS__QUOTED += \
"BLDC_Motor.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "BLDC_Motor.out"

# Tool invocations
BLDC_Motor.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi -z -m"BLDC_Motor.map" --stack_size=0x300 --warn_sections -i"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS/lib" -i"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="BLDC_Motor_linkInfo.xml" --rom_model -o "BLDC_Motor.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

BLDC_Motor.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS/bin/hex2000"  -o "BLDC_Motor.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "Module\CRC.obj" "Module\Control.obj" "Module\Digital_IO.obj" "Module\ExternalInterrupt.obj" "Module\Led.obj" "Module\PID.obj" "Module\Relay.obj" "Module\SelfCheck.obj" "Module\State_Machine.obj" "Module\SteeringEngine.obj" "Module\Steering_ADC.obj" "Module\Steering_SCI.obj" "Module\Steering_SPI.obj" "Module\Steering_XINTF.obj" "Src\DSP2833x_ADC_cal.obj" "Src\DSP2833x_Adc.obj" "Src\DSP2833x_CodeStartBranch.obj" "Src\DSP2833x_CpuTimers.obj" "Src\DSP2833x_DMA.obj" "Src\DSP2833x_DefaultIsr.obj" "Src\DSP2833x_EPwm.obj" "Src\DSP2833x_GlobalVariableDefs.obj" "Src\DSP2833x_Gpio.obj" "Src\DSP2833x_MemCopy.obj" "Src\DSP2833x_PieCtrl.obj" "Src\DSP2833x_PieVect.obj" "Src\DSP2833x_Sci.obj" "Src\DSP2833x_Spi.obj" "Src\DSP2833x_SysCtrl.obj" "Src\DSP2833x_Xintf.obj" "Src\DSP2833x_usDelay.obj" 
	-$(RM) "main.d" "Module\CRC.d" "Module\Control.d" "Module\Digital_IO.d" "Module\ExternalInterrupt.d" "Module\Led.d" "Module\PID.d" "Module\Relay.d" "Module\SelfCheck.d" "Module\State_Machine.d" "Module\SteeringEngine.d" "Module\Steering_ADC.d" "Module\Steering_SCI.d" "Module\Steering_SPI.d" "Module\Steering_XINTF.d" "Src\DSP2833x_Adc.d" "Src\DSP2833x_CpuTimers.d" "Src\DSP2833x_DMA.d" "Src\DSP2833x_DefaultIsr.d" "Src\DSP2833x_EPwm.d" "Src\DSP2833x_GlobalVariableDefs.d" "Src\DSP2833x_Gpio.d" "Src\DSP2833x_MemCopy.d" "Src\DSP2833x_PieCtrl.d" "Src\DSP2833x_PieVect.d" "Src\DSP2833x_Sci.d" "Src\DSP2833x_Spi.d" "Src\DSP2833x_SysCtrl.d" "Src\DSP2833x_Xintf.d" 
	-$(RM) "Src\DSP2833x_ADC_cal.d" "Src\DSP2833x_CodeStartBranch.d" "Src\DSP2833x_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

