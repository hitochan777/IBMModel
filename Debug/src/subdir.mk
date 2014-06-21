################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/IBM1.cpp \
../src/IBM2.cpp \
../src/driver.cpp 

OBJS += \
./src/IBM1.o \
./src/IBM2.o \
./src/driver.o 

CPP_DEPS += \
./src/IBM1.d \
./src/IBM2.d \
./src/driver.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


