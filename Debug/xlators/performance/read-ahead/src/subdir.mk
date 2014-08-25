################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/performance/read-ahead/src/page.c \
../xlators/performance/read-ahead/src/read-ahead.c 

OBJS += \
./xlators/performance/read-ahead/src/page.o \
./xlators/performance/read-ahead/src/read-ahead.o 

C_DEPS += \
./xlators/performance/read-ahead/src/page.d \
./xlators/performance/read-ahead/src/read-ahead.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/performance/read-ahead/src/%.o: ../xlators/performance/read-ahead/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


