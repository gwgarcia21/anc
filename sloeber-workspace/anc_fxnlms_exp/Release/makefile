################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := del 

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries\Wire\utility/subdir.mk
-include libraries\Wire/subdir.mk
-include libraries\SerialFlash/subdir.mk
-include libraries\SPI/subdir.mk
-include libraries\SD\utility/subdir.mk
-include libraries\SD/subdir.mk
-include libraries\Audio\utility/subdir.mk
-include libraries\Audio/subdir.mk
-include core\core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
C:/Teensy3/tcc-workspace/anc_fxnlms_exp/Release/arduino.ar \

ELF += \
anc_fxnlms_exp.elf \

HEX += \
anc_fxnlms_exp.hex \


# All Target
all: anc_fxnlms_exp

# Tool invocations
anc_fxnlms_exp: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-size" -A "C:/Teensy3/tcc-workspace/anc_fxnlms_exp/Release/anc_fxnlms_exp.elf"
	@echo 'Finished building target: $@'
	@echo ' '

C:/Teensy3/tcc-workspace/anc_fxnlms_exp/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-gcc-ar" rcs    C:/Teensy3/tcc-workspace/anc_fxnlms_exp/Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

anc_fxnlms_exp.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-gcc" -O3 -Wl,--gc-sections,--relax,--defsym=__rtc_localtime=1526335952 "-TC:/Teensy3/arduino/hardware/teensy/avr/cores/teensy3/mk66fx1m0.ld" -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -o "C:/Teensy3/tcc-workspace/anc_fxnlms_exp/Release/anc_fxnlms_exp.elf"   $(LINK_OBJ) $(AR)   C:/Teensy3/tcc-workspace/anc_fxnlms_exp/Release/arduino.ar  "-LC:/Teensy3/tcc-workspace/anc_fxnlms_exp/Release" -larm_cortexM4lf_math -lm
	@echo 'Finished building: $@'
	@echo ' '

anc_fxnlms_exp.hex: $(ELF)
	@echo 'Create eeprom image'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	${A.RECIPE.OBJCOPY.HEX.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
