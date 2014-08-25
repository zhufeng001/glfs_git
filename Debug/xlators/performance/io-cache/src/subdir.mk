################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/performance/io-cache/src/io-cache.c \
../xlators/performance/io-cache/src/ioc-inode.c \
../xlators/performance/io-cache/src/page.c 

OBJS += \
./xlators/performance/io-cache/src/io-cache.o \
./xlators/performance/io-cache/src/ioc-inode.o \
./xlators/performance/io-cache/src/page.o 

C_DEPS += \
./xlators/performance/io-cache/src/io-cache.d \
./xlators/performance/io-cache/src/ioc-inode.d \
./xlators/performance/io-cache/src/page.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/performance/io-cache/src/%.o: ../xlators/performance/io-cache/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


