################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Teensy3/arduino/hardware/teensy/avr/libraries/Wire/utility/twi.c 

C_DEPS += \
.\libraries\Wire\utility\twi.c.d 

LINK_OBJ += \
./libraries/Wire/utility/twi.c.o 


# Each subdirectory must supply rules for building sources it contributes
libraries/Wire/utility/twi.c.o: C:/Teensy3/arduino/hardware/teensy/avr/libraries/Wire/utility/twi.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-gcc" -c -O3 -g -Wall -ffunction-sections -fdata-sections -nostdlib -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -D__MK66FX1M0__ -DTEENSYDUINO=136 -DARDUINO=10609 -DF_CPU=180000000 -DUSB_SERIAL -DLAYOUT_PORTUGUESE_BRAZILIAN  -I"C:\Teensy3\arduino\hardware\teensy\avr\cores\teensy3" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SerialFlash" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SPI" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


