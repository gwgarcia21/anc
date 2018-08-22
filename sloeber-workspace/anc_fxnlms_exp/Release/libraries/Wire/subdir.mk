################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Teensy3/arduino/hardware/teensy/avr/libraries/Wire/Wire.cpp \
C:/Teensy3/arduino/hardware/teensy/avr/libraries/Wire/WireKinetis.cpp 

LINK_OBJ += \
./libraries/Wire/Wire.cpp.o \
./libraries/Wire/WireKinetis.cpp.o 

CPP_DEPS += \
.\libraries\Wire\Wire.cpp.d \
.\libraries\Wire\WireKinetis.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/Wire/Wire.cpp.o: C:/Teensy3/arduino/hardware/teensy/avr/libraries/Wire/Wire.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-g++" -c -O3 -g -Wall -ffunction-sections -fdata-sections -nostdlib -fno-exceptions -felide-constructors -std=gnu++0x -fno-rtti -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -D__MK66FX1M0__ -DTEENSYDUINO=136 -DARDUINO=10609 -DF_CPU=180000000 -DUSB_SERIAL -DLAYOUT_PORTUGUESE_BRAZILIAN  -I"C:\Teensy3\arduino\hardware\teensy\avr\cores\teensy3" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SerialFlash" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SPI" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/Wire/WireKinetis.cpp.o: C:/Teensy3/arduino/hardware/teensy/avr/libraries/Wire/WireKinetis.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-g++" -c -O3 -g -Wall -ffunction-sections -fdata-sections -nostdlib -fno-exceptions -felide-constructors -std=gnu++0x -fno-rtti -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -D__MK66FX1M0__ -DTEENSYDUINO=136 -DARDUINO=10609 -DF_CPU=180000000 -DUSB_SERIAL -DLAYOUT_PORTUGUESE_BRAZILIAN  -I"C:\Teensy3\arduino\hardware\teensy\avr\cores\teensy3" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SerialFlash" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SPI" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


