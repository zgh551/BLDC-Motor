################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../F2833x/v141/DSP2833x_common/source/DSP2833x_ADC_cal.asm \
../F2833x/v141/DSP2833x_common/source/DSP2833x_CSMPasswords.asm \
../F2833x/v141/DSP2833x_common/source/DSP2833x_CodeStartBranch.asm \
../F2833x/v141/DSP2833x_common/source/DSP2833x_DBGIER.asm \
../F2833x/v141/DSP2833x_common/source/DSP2833x_DisInt.asm \
../F2833x/v141/DSP2833x_common/source/DSP2833x_usDelay.asm 

C_SRCS += \
../F2833x/v141/DSP2833x_common/source/DSP2833x_Adc.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_CpuTimers.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_DMA.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_DefaultIsr.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_ECan.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_ECap.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_EPwm.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_EQep.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_Gpio.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_I2C.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_Mcbsp.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_MemCopy.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_PieCtrl.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_PieVect.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_SWPrioritizedDefaultIsr.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_SWPrioritizedPieVect.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_Sci.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_Spi.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_SysCtrl.c \
../F2833x/v141/DSP2833x_common/source/DSP2833x_Xintf.c 

C_DEPS += \
./F2833x/v141/DSP2833x_common/source/DSP2833x_Adc.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_CpuTimers.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_DMA.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_DefaultIsr.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_ECan.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_ECap.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_EPwm.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_EQep.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_Gpio.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_I2C.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_Mcbsp.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_MemCopy.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_PieCtrl.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_PieVect.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_SWPrioritizedDefaultIsr.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_SWPrioritizedPieVect.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_Sci.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_Spi.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_SysCtrl.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_Xintf.d 

OBJS += \
./F2833x/v141/DSP2833x_common/source/DSP2833x_ADC_cal.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_Adc.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_CSMPasswords.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_CodeStartBranch.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_CpuTimers.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_DBGIER.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_DMA.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_DefaultIsr.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_DisInt.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_ECan.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_ECap.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_EPwm.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_EQep.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_Gpio.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_I2C.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_Mcbsp.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_MemCopy.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_PieCtrl.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_PieVect.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_SWPrioritizedDefaultIsr.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_SWPrioritizedPieVect.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_Sci.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_Spi.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_SysCtrl.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_Xintf.obj \
./F2833x/v141/DSP2833x_common/source/DSP2833x_usDelay.obj 

ASM_DEPS += \
./F2833x/v141/DSP2833x_common/source/DSP2833x_ADC_cal.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_CSMPasswords.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_CodeStartBranch.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_DBGIER.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_DisInt.d \
./F2833x/v141/DSP2833x_common/source/DSP2833x_usDelay.d 

OBJS__QUOTED += \
"F2833x\v141\DSP2833x_common\source\DSP2833x_ADC_cal.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_Adc.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_CSMPasswords.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_CodeStartBranch.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_CpuTimers.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_DBGIER.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_DMA.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_DefaultIsr.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_DisInt.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_ECan.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_ECap.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_EPwm.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_EQep.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_Gpio.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_I2C.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_Mcbsp.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_MemCopy.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_PieCtrl.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_PieVect.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_SWPrioritizedDefaultIsr.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_SWPrioritizedPieVect.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_Sci.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_Spi.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_SysCtrl.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_Xintf.obj" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_usDelay.obj" 

C_DEPS__QUOTED += \
"F2833x\v141\DSP2833x_common\source\DSP2833x_Adc.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_CpuTimers.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_DMA.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_DefaultIsr.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_ECan.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_ECap.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_EPwm.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_EQep.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_Gpio.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_I2C.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_Mcbsp.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_MemCopy.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_PieCtrl.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_PieVect.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_SWPrioritizedDefaultIsr.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_SWPrioritizedPieVect.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_Sci.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_Spi.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_SysCtrl.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_Xintf.d" 

ASM_DEPS__QUOTED += \
"F2833x\v141\DSP2833x_common\source\DSP2833x_ADC_cal.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_CSMPasswords.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_CodeStartBranch.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_DBGIER.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_DisInt.d" \
"F2833x\v141\DSP2833x_common\source\DSP2833x_usDelay.d" 

ASM_SRCS__QUOTED += \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_ADC_cal.asm" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_CSMPasswords.asm" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_CodeStartBranch.asm" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_DBGIER.asm" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_DisInt.asm" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_usDelay.asm" 

C_SRCS__QUOTED += \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_Adc.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_CpuTimers.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_DMA.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_DefaultIsr.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_ECan.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_ECap.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_EPwm.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_EQep.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_Gpio.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_I2C.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_Mcbsp.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_MemCopy.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_PieCtrl.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_PieVect.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_SWPrioritizedDefaultIsr.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_SWPrioritizedPieVect.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_Sci.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_Spi.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_SysCtrl.c" \
"../F2833x/v141/DSP2833x_common/source/DSP2833x_Xintf.c" 


