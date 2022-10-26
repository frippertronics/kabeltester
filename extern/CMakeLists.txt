set(LIBRARY_FILENAME unity)

add_library(${LIBRARY_FILENAME} STATIC CMock/vendor/unity/src/unity.c)

target_include_directories(${LIBRARY_FILENAME} PUBLIC CMock/vendor/unity/src)
