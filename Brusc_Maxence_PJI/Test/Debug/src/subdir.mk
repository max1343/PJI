################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Test.cpp 

OBJS += \
./src/Test.o 

CPP_DEPS += \
./src/Test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -Iopencv_calib3d -Iopencv_core -Iopencv_features2d -Iopencv_flann -Iopencv_highgui -Iopencv_imgcodecs -Iopencv_imgproc -Iopencv_ml -Iopencv_objdetect -Iopencv_photo -Iopencv_shape -Iopencv_stitching -Iopencv_superres -Iopencv_video -Iopencv_videoio -Iopencv_videostab -include/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


