################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../argp-standalone/argp-ba.c \
../argp-standalone/argp-eexst.c \
../argp-standalone/argp-fmtstream.c \
../argp-standalone/argp-help.c \
../argp-standalone/argp-parse.c \
../argp-standalone/argp-pv.c \
../argp-standalone/argp-pvh.c \
../argp-standalone/mempcpy.c \
../argp-standalone/strcasecmp.c \
../argp-standalone/strchrnul.c \
../argp-standalone/strndup.c \
../argp-standalone/vsnprintf.c 

OBJS += \
./argp-standalone/argp-ba.o \
./argp-standalone/argp-eexst.o \
./argp-standalone/argp-fmtstream.o \
./argp-standalone/argp-help.o \
./argp-standalone/argp-parse.o \
./argp-standalone/argp-pv.o \
./argp-standalone/argp-pvh.o \
./argp-standalone/mempcpy.o \
./argp-standalone/strcasecmp.o \
./argp-standalone/strchrnul.o \
./argp-standalone/strndup.o \
./argp-standalone/vsnprintf.o 

C_DEPS += \
./argp-standalone/argp-ba.d \
./argp-standalone/argp-eexst.d \
./argp-standalone/argp-fmtstream.d \
./argp-standalone/argp-help.d \
./argp-standalone/argp-parse.d \
./argp-standalone/argp-pv.d \
./argp-standalone/argp-pvh.d \
./argp-standalone/mempcpy.d \
./argp-standalone/strcasecmp.d \
./argp-standalone/strchrnul.d \
./argp-standalone/strndup.d \
./argp-standalone/vsnprintf.d 


# Each subdirectory must supply rules for building sources it contributes
argp-standalone/%.o: ../argp-standalone/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


