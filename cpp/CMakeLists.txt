
cmake_minimum_required(VERSION 3.4.1)

project(NativeLib)

add_library(
        native-lib
        SHARED
        native-lib.cpp
)

# Set your OpenCV path correctly
set(OpenCV_DIR "C:/Users/OpenCV-android-sdk/sdk/native/jni")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(
        native-lib
        ${OpenCV_LIBS}
        log
        android
)

