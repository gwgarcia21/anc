################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Teensy3/arduino/hardware/teensy/avr/libraries/SD/File.cpp \
C:/Teensy3/arduino/hardware/teensy/avr/libraries/SD/SD.cpp \
C:/Teensy3/arduino/hardware/teensy/avr/libraries/SD/cache_t3.cpp \
C:/Teensy3/arduino/hardware/teensy/avr/libraries/SD/card_t3.cpp \
C:/Teensy3/arduino/hardware/teensy/avr/libraries/SD/dir_t3.cpp \
C:/Teensy3/arduino/hardware/teensy/avr/libraries/SD/fat_t3.cpp \
C:/Teensy3/arduino/hardware/teensy/avr/libraries/SD/file_t3.cpp \
C:/Teensy3/arduino/hardware/teensy/avr/libraries/SD/init_t3.cpp 

LINK_OBJ += \
./libraries/SD/File.cpp.o \
./libraries/SD/SD.cpp.o \
./libraries/SD/cache_t3.cpp.o \
./libraries/SD/card_t3.cpp.o \
./libraries/SD/dir_t3.cpp.o \
./libraries/SD/fat_t3.cpp.o \
./libraries/SD/file_t3.cpp.o \
./libraries/SD/init_t3.cpp.o 

CPP_DEPS += \
.\libraries\SD\File.cpp.d \
.\libraries\SD\SD.cpp.d \
.\libraries\SD\cache_t3.cpp.d \
.\libraries\SD\card_t3.cpp.d \
.\libraries\SD\dir_t3.cpp.d \
.\libraries\SD\fat_t3.cpp.d \
.\libraries\SD\file_t3.cpp.d \
.\libraries\SD\init_t3.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/SD/File.cpp.o: C:/Teensy3/arduino/hardware/teensy/avr/libraries/SD/File.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-g++" -c -O3 -g -Wall -ffunction-sections -fdata-sections -nostdlib -fno-exceptions -felide-constructors -std=gnu++0x -fno-rtti -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -D__MK66FX1M0__ -DTEENSYDUINO=136 -DARDUINO=10609 -DF_CPU=180000000 -DUSB_SERIAL -DLAYOUT_PORTUGUESE_BRAZILIAN  -I"C:\Teensy3\arduino\hardware\teensy\avr\cores\teensy3" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SerialFlash" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SPI" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/SD/SD.cpp.o: C:/Teensy3/arduino/hardware/teensy/avr/libraries/SD/SD.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-g++" -c -O3 -g -Wall -ffunction-sections -fdata-sections -nostdlib -fno-exceptions -felide-constructors -std=gnu++0x -fno-rtti -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -D__MK66FX1M0__ -DTEENSYDUINO=136 -DARDUINO=10609 -DF_CPU=180000000 -DUSB_SERIAL -DLAYOUT_PORTUGUESE_BRAZILIAN  -I"C:\Teensy3\arduino\hardware\teensy\avr\cores\teensy3" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SerialFlash" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SPI" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/SD/cache_t3.cpp.o: C:/Teensy3/arduino/hardware/teensy/avr/libraries/SD/cache_t3.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-g++" -c -O3 -g -Wall -ffunction-sections -fdata-sections -nostdlib -fno-exceptions -felide-constructors -std=gnu++0x -fno-rtti -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -D__MK66FX1M0__ -DTEENSYDUINO=136 -DARDUINO=10609 -DF_CPU=180000000 -DUSB_SERIAL -DLAYOUT_PORTUGUESE_BRAZILIAN  -I"C:\Teensy3\arduino\hardware\teensy\avr\cores\teensy3" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SerialFlash" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SPI" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/SD/card_t3.cpp.o: C:/Teensy3/arduino/hardware/teensy/avr/libraries/SD/card_t3.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-g++" -c -O3 -g -Wall -ffunction-sections -fdata-sections -nostdlib -fno-exceptions -felide-constructors -std=gnu++0x -fno-rtti -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -D__MK66FX1M0__ -DTEENSYDUINO=136 -DARDUINO=10609 -DF_CPU=180000000 -DUSB_SERIAL -DLAYOUT_PORTUGUESE_BRAZILIAN  -I"C:\Teensy3\arduino\hardware\teensy\avr\cores\teensy3" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SerialFlash" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SPI" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/SD/dir_t3.cpp.o: C:/Teensy3/arduino/hardware/teensy/avr/libraries/SD/dir_t3.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-g++" -c -O3 -g -Wall -ffunction-sections -fdata-sections -nostdlib -fno-exceptions -felide-constructors -std=gnu++0x -fno-rtti -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -D__MK66FX1M0__ -DTEENSYDUINO=136 -DARDUINO=10609 -DF_CPU=180000000 -DUSB_SERIAL -DLAYOUT_PORTUGUESE_BRAZILIAN  -I"C:\Teensy3\arduino\hardware\teensy\avr\cores\teensy3" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SerialFlash" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SPI" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/SD/fat_t3.cpp.o: C:/Teensy3/arduino/hardware/teensy/avr/libraries/SD/fat_t3.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-g++" -c -O3 -g -Wall -ffunction-sections -fdata-sections -nostdlib -fno-exceptions -felide-constructors -std=gnu++0x -fno-rtti -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -D__MK66FX1M0__ -DTEENSYDUINO=136 -DARDUINO=10609 -DF_CPU=180000000 -DUSB_SERIAL -DLAYOUT_PORTUGUESE_BRAZILIAN  -I"C:\Teensy3\arduino\hardware\teensy\avr\cores\teensy3" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SerialFlash" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SPI" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/SD/file_t3.cpp.o: C:/Teensy3/arduino/hardware/teensy/avr/libraries/SD/file_t3.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-g++" -c -O3 -g -Wall -ffunction-sections -fdata-sections -nostdlib -fno-exceptions -felide-constructors -std=gnu++0x -fno-rtti -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -D__MK66FX1M0__ -DTEENSYDUINO=136 -DARDUINO=10609 -DF_CPU=180000000 -DUSB_SERIAL -DLAYOUT_PORTUGUESE_BRAZILIAN  -I"C:\Teensy3\arduino\hardware\teensy\avr\cores\teensy3" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SerialFlash" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SPI" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/SD/init_t3.cpp.o: C:/Teensy3/arduino/hardware/teensy/avr/libraries/SD/init_t3.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Teensy3/arduino/hardware/teensy/../tools/arm/bin/arm-none-eabi-g++" -c -O3 -g -Wall -ffunction-sections -fdata-sections -nostdlib -fno-exceptions -felide-constructors -std=gnu++0x -fno-rtti -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -D__MK66FX1M0__ -DTEENSYDUINO=136 -DARDUINO=10609 -DF_CPU=180000000 -DUSB_SERIAL -DLAYOUT_PORTUGUESE_BRAZILIAN  -I"C:\Teensy3\arduino\hardware\teensy\avr\cores\teensy3" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Audio\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SerialFlash" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SPI" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\Wire\utility" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD" -I"C:\Teensy3\arduino\hardware\teensy\avr\libraries\SD\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


