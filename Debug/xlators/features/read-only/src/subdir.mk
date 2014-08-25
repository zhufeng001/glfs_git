################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/features/read-only/src/read-only-common.c \
../xlators/features/read-only/src/read-only.c \
../xlators/features/read-only/src/worm.c 

OBJS += \
./xlators/features/read-only/src/read-only-common.o \
./xlators/features/read-only/src/read-only.o \
./xlators/features/read-only/src/worm.o 

C_DEPS += \
./xlators/features/read-only/src/read-only-common.d \
./xlators/features/read-only/src/read-only.d \
./xlators/features/read-only/src/worm.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/features/read-only/src/%.o: ../xlators/features/read-only/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


