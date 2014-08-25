################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/features/marker/utils/src/gsyncd.c \
../xlators/features/marker/utils/src/procdiggy.c 

OBJS += \
./xlators/features/marker/utils/src/gsyncd.o \
./xlators/features/marker/utils/src/procdiggy.o 

C_DEPS += \
./xlators/features/marker/utils/src/gsyncd.d \
./xlators/features/marker/utils/src/procdiggy.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/features/marker/utils/src/%.o: ../xlators/features/marker/utils/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


