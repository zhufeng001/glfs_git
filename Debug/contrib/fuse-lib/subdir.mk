################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../contrib/fuse-lib/misc.c \
../contrib/fuse-lib/mount-common.c \
../contrib/fuse-lib/mount.c 

OBJS += \
./contrib/fuse-lib/misc.o \
./contrib/fuse-lib/mount-common.o \
./contrib/fuse-lib/mount.o 

C_DEPS += \
./contrib/fuse-lib/misc.d \
./contrib/fuse-lib/mount-common.d \
./contrib/fuse-lib/mount.d 


# Each subdirectory must supply rules for building sources it contributes
contrib/fuse-lib/%.o: ../contrib/fuse-lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


