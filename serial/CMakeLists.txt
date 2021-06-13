# Define the output library name. Use this name when referencing the library
# in the app and test CMakeLists
set(LIBRARY_FILENAME serial)

# Include the header file(s) for the library
set (headers ${CMAKE_SOURCE_DIR}/include/kabeltester/serial.h)

# Create a library for the non-executable library
add_library(${LIBRARY_FILENAME} serial.c ${headers})

# Make sure the compiler can include files for the library in other parts of the project
target_include_directories (${LIBRARY_FILENAME} PUBLIC ../include)