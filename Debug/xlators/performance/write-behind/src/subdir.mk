################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/performance/write-behind/src/write-behind.c 

OBJS += \
./xlators/performance/write-behind/src/write-behind.o 

C_DEPS += \
./xlators/performance/write-behind/src/write-behind.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/performance/write-behind/src/%.o: ../xlators/performance/write-behind/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


