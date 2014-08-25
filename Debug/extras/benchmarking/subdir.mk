################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../extras/benchmarking/glfs-bm.c \
../extras/benchmarking/rdd.c 

OBJS += \
./extras/benchmarking/glfs-bm.o \
./extras/benchmarking/rdd.o 

C_DEPS += \
./extras/benchmarking/glfs-bm.d \
./extras/benchmarking/rdd.d 


# Each subdirectory must supply rules for building sources it contributes
extras/benchmarking/%.o: ../extras/benchmarking/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


