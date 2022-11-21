cmake_minimum_required(VERSION 3.20)

set(TARGET_GROUP test CACHE STRING "Group to build")

if(TARGET_GROUP STREQUAL production)
    # Use AVR GCC toolchain
    set(CMAKE_SYSTEM_NAME Generic)
    set(CMAKE_CXX_COMPILER avr-g++)
    set(CMAKE_C_COMPILER avr-gcc)
    set(CMAKE_ASM_COMPILER avr-gcc)
elseif(TARGET_GROUP STREQUAL test)
    # Use default GCC on the OS
    set(CMAKE_CXX_COMPILER clang++)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_ASM_COMPILER clang)
else()
    message(FATAL_ERROR "Please specify either production or test")
endif()

# Project name
project("Kabeltester")

# Product filename
set(PRODUCT_NAME kabeltester_fw)

## AVR Chip Configuration
# 8Mhz, this should match the crystal on your board,
set(F_CPU 8000000UL)
# CPU, you can find the list here:
# https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html
set(MCU atmega2560)
# Default Baudrate for UART, read avr include/util/setbaud.h for usage
set(BAUD 9600)
# The programmer to use, read avrdude manual for list
set(PROG_TYPE avrisp2)
# Target device 
set(TARGET_DEVICE /dev/cu.usbmodem1101)

# AVR Fuses, must be in concordance with your hardware and F_CPU
# http://eleccelerator.com/fusecalc/fusecalc.php?chip=atmega2560
set(E_FUSE 0xFF)
set(H_FUSE 0x99)
set(L_FUSE 0x42)
set(LOCK_BIT 0xFF)

# Pass defines to compiler
add_definitions(
    -DF_CPU=${F_CPU}
    -DBAUD=${BAUD}
)
# mmcu MUST be passed to bot the compiler and linker, this handle the linker
set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})

if(TARGET_GROUP STREQUAL production)
    add_compile_options(
        -mmcu=${MCU} # MCU
        -std=gnu99 # C99 standard
        -Os # optimize
        -Wall # enable warnings
        -Wno-main
        -Wundef
        -pedantic
        -Wstrict-prototypes
        -Werror
        -Wfatal-errors
        -Wl,--relax,--gc-sections
        -g
        -gdwarf-2
        -funsigned-char # a few optimizations
        -funsigned-bitfields
        -fpack-struct
        -fshort-enums
        -ffunction-sections
        -fdata-sections
        -fno-split-wide-types
        -fno-tree-scev-cprop
    )
elseif(TARGET_GROUP STREQUAL test)
    add_compile_options(
        -g
        -DTEST
    )
endif()

# Libraries
add_subdirectory(gpio)
add_subdirectory(serial)
add_subdirectory(interrupt)
add_subdirectory(tester)
#add_subdirectory(twi)

if(TARGET_GROUP STREQUAL production)
    # Executable
    add_subdirectory(src)
elseif(TARGET_GROUP STREQUAL test)
    # Tests
    include(CTest)
    add_subdirectory(extern)
    add_subdirectory(hardware)
    add_subdirectory(tests)
else()
    message(FATAL_ERROR "Please specify either production or test")
endif()
# Clean extra files
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PRODUCT_NAME}")
