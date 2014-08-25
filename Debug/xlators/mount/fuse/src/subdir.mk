################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/mount/fuse/src/fuse-bridge.c \
../xlators/mount/fuse/src/fuse-helpers.c \
../xlators/mount/fuse/src/fuse-resolve.c 

OBJS += \
./xlators/mount/fuse/src/fuse-bridge.o \
./xlators/mount/fuse/src/fuse-helpers.o \
./xlators/mount/fuse/src/fuse-resolve.o 

C_DEPS += \
./xlators/mount/fuse/src/fuse-bridge.d \
./xlators/mount/fuse/src/fuse-helpers.d \
./xlators/mount/fuse/src/fuse-resolve.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/mount/fuse/src/%.o: ../xlators/mount/fuse/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


