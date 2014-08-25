################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/storage/posix/src/posix-aio.c \
../xlators/storage/posix/src/posix-handle.c \
../xlators/storage/posix/src/posix-helpers.c \
../xlators/storage/posix/src/posix.c 

OBJS += \
./xlators/storage/posix/src/posix-aio.o \
./xlators/storage/posix/src/posix-handle.o \
./xlators/storage/posix/src/posix-helpers.o \
./xlators/storage/posix/src/posix.o 

C_DEPS += \
./xlators/storage/posix/src/posix-aio.d \
./xlators/storage/posix/src/posix-handle.d \
./xlators/storage/posix/src/posix-helpers.d \
./xlators/storage/posix/src/posix.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/storage/posix/src/%.o: ../xlators/storage/posix/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


