################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ClusterMonitor/OGEmonitor.cpp 

OBJS += \
./src/ClusterMonitor/OGEmonitor.o 

CPP_DEPS += \
./src/ClusterMonitor/OGEmonitor.d 


# Each subdirectory must supply rules for building sources it contributes
src/ClusterMonitor/%.o: ../src/ClusterMonitor/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/n1ge/include/ -I/home/sasghar/Zeromq/zmq/include/ -I/usr/local/boost/include -O3 -g0 -g -Wall -c -fmessage-length=0 -D __STDC_LIMIT_MACROS -D __STDC_FORMAT_MACROS -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


