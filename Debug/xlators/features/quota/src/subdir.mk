################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/features/quota/src/quota.c 

OBJS += \
./xlators/features/quota/src/quota.o 

C_DEPS += \
./xlators/features/quota/src/quota.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/features/quota/src/%.o: ../xlators/features/quota/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


