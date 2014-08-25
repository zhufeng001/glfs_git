################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../contrib/fuse-util/fusermount.c \
../contrib/fuse-util/mount_util.c 

OBJS += \
./contrib/fuse-util/fusermount.o \
./contrib/fuse-util/mount_util.o 

C_DEPS += \
./contrib/fuse-util/fusermount.d \
./contrib/fuse-util/mount_util.d 


# Each subdirectory must supply rules for building sources it contributes
contrib/fuse-util/%.o: ../contrib/fuse-util/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


