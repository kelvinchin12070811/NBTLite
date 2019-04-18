add_library(NBTLite INTERFACE)

include_directories("${SDK_DIR}/rapidjson/include")
target_include_directories(NBTLite INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")