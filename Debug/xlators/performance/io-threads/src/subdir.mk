################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/performance/io-threads/src/io-threads.c 

OBJS += \
./xlators/performance/io-threads/src/io-threads.o 

C_DEPS += \
./xlators/performance/io-threads/src/io-threads.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/performance/io-threads/src/%.o: ../xlators/performance/io-threads/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


