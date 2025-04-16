# Get the current directory
set(CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Define the output directory
set(OUTPUT_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data")

# Get all files in the current directory except this CMakeLists.txt
file(GLOB_RECURSE FILES_TO_COPY
    RELATIVE ${CURRENT_DIR}
    ${CURRENT_DIR}/*
)
list(FILTER FILES_TO_COPY EXCLUDE REGEX "CMakeLists\\.txt$")

# Copy each file to the output directory
foreach(FILE ${FILES_TO_COPY})
    configure_file(${CURRENT_DIR}/${FILE} ${OUTPUT_DIR}/${FILE} COPYONLY)
endforeach()