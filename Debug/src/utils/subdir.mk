################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/utils/Options.cc \
../src/utils/System.cc 

OBJS += \
./src/utils/Options.o \
./src/utils/System.o 

CC_DEPS += \
./src/utils/Options.d \
./src/utils/System.d 


# Each subdirectory must supply rules for building sources it contributes
src/utils/%.o: ../src/utils/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/n1ge/include/ -I/usr/local/boost/include -O3 -g0 -g -Wall -c -fmessage-length=0 -D __STDC_LIMIT_MACROS -D __STDC_FORMAT_MACROS -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


