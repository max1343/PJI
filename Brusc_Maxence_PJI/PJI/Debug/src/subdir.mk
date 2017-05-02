################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Appariement.cpp \
../src/Catalogue.cpp \
../src/DetectionExp.cpp \
../src/DetectionGenre.cpp \
../src/DetectionVisage.cpp \
../src/Main.cpp \
../src/Person.cpp 

OBJS += \
./src/Appariement.o \
./src/Catalogue.o \
./src/DetectionExp.o \
./src/DetectionGenre.o \
./src/DetectionVisage.o \
./src/Main.o \
./src/Person.o 

CPP_DEPS += \
./src/Appariement.d \
./src/Catalogue.d \
./src/DetectionExp.d \
./src/DetectionGenre.d \
./src/DetectionVisage.d \
./src/Main.d \
./src/Person.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/opencv2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


