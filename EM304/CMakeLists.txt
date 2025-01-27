# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(EM304 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(EM304 EM304.c initialise_functions.c)

pico_set_program_name(EM304 "EM304")
pico_set_program_version(EM304 "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(EM304 0)
pico_enable_stdio_usb(EM304 1)

# Add the standard library to the build
target_link_libraries(EM304
        pico_stdlib
        )

# Add the standard include files to the build
target_include_directories(EM304 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)



# Add the directory containing btstack_config.h
target_include_directories(EM304 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/btstackconfig)

message(STATUS "Include directories: ${CMAKE_CURRENT_LIST_DIR}/btstackconfig")


# Add any user requested libraries
target_link_libraries(EM304 
        pico_stdlib
        pico_btstack_ble
        pico_btstack_cyw43
        hardware_i2c
        hardware_interp
        hardware_timer
        hardware_watchdog
        hardware_clocks
        pico_cyw43_arch_none
        )

target_compile_definitions(EM304 PRIVATE ENABLE_BLE)

# BTstack Root
set(BTSTACK_ROOT "C:/Users/fares/.pico-sdk/sdk/2.1.0/lib/btstack")

# BTstack include directories
target_include_directories(EM304 PRIVATE
        ${BTSTACK_ROOT}/src
        ${BTSTACK_ROOT}/platform/embedded
        ${BTSTACK_ROOT}/3rd-party/rijndael  # Added this line
        ${BTSTACK_ROOT}/3rd-party/lc3-google/include  # Added this line
)

# BTstack source files
file(GLOB BTSTACK_SRC "${BTSTACK_ROOT}/src/*.c")
file(GLOB BTSTACK_PLATFORM_SRC "${BTSTACK_ROOT}/platform/embedded/*.c")

# Link BTstack library
add_library(btstack STATIC ${BTSTACK_SRC} ${BTSTACK_PLATFORM_SRC})

target_include_directories(btstack PRIVATE ${CMAKE_CURRENT_LIST_DIR}/btstackconfig)

# Link BTstack with the executable
target_link_libraries(EM304 btstack)

pico_add_extra_outputs(EM304)

