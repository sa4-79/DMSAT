################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/core/Controller.cpp \
../src/core/JobController.cpp 

CC_SRCS += \
../src/core/Main.cc \
../src/core/Solver.cc 

OBJS += \
./src/core/Controller.o \
./src/core/JobController.o \
./src/core/Main.o \
./src/core/Solver.o 

CC_DEPS += \
./src/core/Main.d \
./src/core/Solver.d 

CPP_DEPS += \
./src/core/Controller.d \
./src/core/JobController.d 


# Each subdirectory must supply rules for building sources it contributes
src/core/%.o: ../src/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/n1ge/include/ -I/home/sasghar/Zeromq/zmq/include/ -I/usr/local/boost/include -O3 -g0 -g -Wall -c -fmessage-length=0 -D __STDC_LIMIT_MACROS -D __STDC_FORMAT_MACROS -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/core/%.o: ../src/core/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/n1ge/include/ -I/home/sasghar/Zeromq/zmq/include/ -I/usr/local/boost/include -O3 -g0 -g -Wall -c -fmessage-length=0 -D __STDC_LIMIT_MACROS -D __STDC_FORMAT_MACROS -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


