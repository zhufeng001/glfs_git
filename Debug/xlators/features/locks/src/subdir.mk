################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/features/locks/src/clear.c \
../xlators/features/locks/src/common.c \
../xlators/features/locks/src/entrylk.c \
../xlators/features/locks/src/inodelk.c \
../xlators/features/locks/src/posix.c \
../xlators/features/locks/src/reservelk.c 

OBJS += \
./xlators/features/locks/src/clear.o \
./xlators/features/locks/src/common.o \
./xlators/features/locks/src/entrylk.o \
./xlators/features/locks/src/inodelk.o \
./xlators/features/locks/src/posix.o \
./xlators/features/locks/src/reservelk.o 

C_DEPS += \
./xlators/features/locks/src/clear.d \
./xlators/features/locks/src/common.d \
./xlators/features/locks/src/entrylk.d \
./xlators/features/locks/src/inodelk.d \
./xlators/features/locks/src/posix.d \
./xlators/features/locks/src/reservelk.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/features/locks/src/%.o: ../xlators/features/locks/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


