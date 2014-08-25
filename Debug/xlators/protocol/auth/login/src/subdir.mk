################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/protocol/auth/login/src/login.c 

OBJS += \
./xlators/protocol/auth/login/src/login.o 

C_DEPS += \
./xlators/protocol/auth/login/src/login.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/protocol/auth/login/src/%.o: ../xlators/protocol/auth/login/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


