################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/cluster/stripe/src/stripe-helpers.c \
../xlators/cluster/stripe/src/stripe.c 

OBJS += \
./xlators/cluster/stripe/src/stripe-helpers.o \
./xlators/cluster/stripe/src/stripe.o 

C_DEPS += \
./xlators/cluster/stripe/src/stripe-helpers.d \
./xlators/cluster/stripe/src/stripe.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/cluster/stripe/src/%.o: ../xlators/cluster/stripe/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


