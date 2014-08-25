################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/features/marker/src/marker-common.c \
../xlators/features/marker/src/marker-quota-helper.c \
../xlators/features/marker/src/marker-quota.c \
../xlators/features/marker/src/marker.c 

OBJS += \
./xlators/features/marker/src/marker-common.o \
./xlators/features/marker/src/marker-quota-helper.o \
./xlators/features/marker/src/marker-quota.o \
./xlators/features/marker/src/marker.o 

C_DEPS += \
./xlators/features/marker/src/marker-common.d \
./xlators/features/marker/src/marker-quota-helper.d \
./xlators/features/marker/src/marker-quota.d \
./xlators/features/marker/src/marker.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/features/marker/src/%.o: ../xlators/features/marker/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


