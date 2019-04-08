add_executable(NBTTester src/main.cpp)

include_directories("C:/Users/User/Documents/SDK & libs/rapidjson/include")
target_link_libraries(NBTTester NBTLite)