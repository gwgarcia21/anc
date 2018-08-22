################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
../anc_fxnlms_sim.ino 

CPP_SRCS += \
../.ino.cpp \
../ringbuffer.cpp 

C_SRCS += \
../arm_fxlms_norm_f32.c 

C_DEPS += \
.\arm_fxlms_norm_f32.c.d 

LINK_OBJ += \
./.ino.cpp.o \
./arm_fxlms_norm_f32.c.o \
./ringbuffer.cpp.o 

INO_DEPS += \
.\anc_fxnlms_sim.ino.d 

CPP_DEPS += \
.\.ino.cpp.d \
.\ringbuffer.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ../.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-g++" -c -O3 -g -Wall -ffunction-sections -fdata-sections -nostdlib -fno-exceptions -felide-constructors -std=gnu++0x -fno-rtti -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -D__MK66FX1M0__ -DTEENSYDUINO=136 -DARDUINO=10609 -DF_CPU=180000000 -DUSB_SERIAL -DLAYOUT_PORTUGUESE_BRAZILIAN  -I"C:\Teensy3\arduino\hardware\teensy\avr\cores\teensy3" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SerialFlash" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SPI" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

anc_fxnlms_sim.o: ../anc_fxnlms_sim.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-g++" -c -O3 -g -Wall -ffunction-sections -fdata-sections -nostdlib -fno-exceptions -felide-constructors -std=gnu++0x -fno-rtti -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -D__MK66FX1M0__ -DTEENSYDUINO=136 -DARDUINO=10609 -DF_CPU=180000000 -DUSB_SERIAL -DLAYOUT_PORTUGUESE_BRAZILIAN  -I"C:\Teensy3\arduino\hardware\teensy\avr\cores\teensy3" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SerialFlash" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SPI" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

arm_fxlms_norm_f32.c.o: ../arm_fxlms_norm_f32.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-gcc" -c -O3 -g -Wall -ffunction-sections -fdata-sections -nostdlib -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -D__MK66FX1M0__ -DTEENSYDUINO=136 -DARDUINO=10609 -DF_CPU=180000000 -DUSB_SERIAL -DLAYOUT_PORTUGUESE_BRAZILIAN  -I"C:\Teensy3\arduino\hardware\teensy\avr\cores\teensy3" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SerialFlash" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SPI" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

ringbuffer.cpp.o: ../ringbuffer.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-g++" -c -O3 -g -Wall -ffunction-sections -fdata-sections -nostdlib -fno-exceptions -felide-constructors -std=gnu++0x -fno-rtti -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -D__MK66FX1M0__ -DTEENSYDUINO=136 -DARDUINO=10609 -DF_CPU=180000000 -DUSB_SERIAL -DLAYOUT_PORTUGUESE_BRAZILIAN  -I"C:\Teensy3\arduino\hardware\teensy\avr\cores\teensy3" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SerialFlash" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SPI" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


