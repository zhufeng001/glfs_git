################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/system/posix-acl/src/posix-acl-xattr.c \
../xlators/system/posix-acl/src/posix-acl.c 

OBJS += \
./xlators/system/posix-acl/src/posix-acl-xattr.o \
./xlators/system/posix-acl/src/posix-acl.o 

C_DEPS += \
./xlators/system/posix-acl/src/posix-acl-xattr.d \
./xlators/system/posix-acl/src/posix-acl.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/system/posix-acl/src/%.o: ../xlators/system/posix-acl/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


