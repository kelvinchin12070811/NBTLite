add_executable(NBTTester src/main.cpp)

include_directories("${SDK_DIR}/rapidjson/include")
target_link_libraries(NBTTester NBTLite)