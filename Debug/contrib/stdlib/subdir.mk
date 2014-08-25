################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../contrib/stdlib/gf_mkostemp.c 

OBJS += \
./contrib/stdlib/gf_mkostemp.o 

C_DEPS += \
./contrib/stdlib/gf_mkostemp.d 


# Each subdirectory must supply rules for building sources it contributes
contrib/stdlib/%.o: ../contrib/stdlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


