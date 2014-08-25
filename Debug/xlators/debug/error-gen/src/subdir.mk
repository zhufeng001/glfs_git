################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/debug/error-gen/src/error-gen.c 

OBJS += \
./xlators/debug/error-gen/src/error-gen.o 

C_DEPS += \
./xlators/debug/error-gen/src/error-gen.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/debug/error-gen/src/%.o: ../xlators/debug/error-gen/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


