################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/performance/md-cache/src/md-cache.c 

OBJS += \
./xlators/performance/md-cache/src/md-cache.o 

C_DEPS += \
./xlators/performance/md-cache/src/md-cache.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/performance/md-cache/src/%.o: ../xlators/performance/md-cache/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


