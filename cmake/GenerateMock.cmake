# Generate cmock for provided header file.
# Based on Nordic nRF Connect SDK Unity integration
find_program(RUBY_EXECUTABLE ruby)
get_property(CMOCK_DIR GLOBAL PROPERTY CMOCK_DIR)
set(MOCK_PREFIX mock_)

function(cmock_generate_mock header_path dst_path)
  get_filename_component(file_name "${header_path}" NAME_WE)
  set(MOCK_FILE ${dst_path}/${MOCK_PREFIX}${file_name}.c)

  file(MAKE_DIRECTORY "${dst_path}")

  add_custom_command(OUTPUT ${MOCK_FILE}
    COMMAND ${RUBY_EXECUTABLE}
    ${CMOCK_DIR}/lib/cmock.rb
    --mock_prefix=${MOCK_PREFIX}
    --mock_path=${dst_path}
    -o${UNITY_CONFIG_FILE}
    ${header_path}
    DEPENDS ${header_path} ${UNITY_CONFIG_FILE}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )

  target_sources(app PRIVATE ${MOCK_FILE})
endfunction()
