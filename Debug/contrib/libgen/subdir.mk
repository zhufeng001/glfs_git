################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../contrib/libgen/basename_r.c \
../contrib/libgen/dirname_r.c 

OBJS += \
./contrib/libgen/basename_r.o \
./contrib/libgen/dirname_r.o 

C_DEPS += \
./contrib/libgen/basename_r.d \
./contrib/libgen/dirname_r.d 


# Each subdirectory must supply rules for building sources it contributes
contrib/libgen/%.o: ../contrib/libgen/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


