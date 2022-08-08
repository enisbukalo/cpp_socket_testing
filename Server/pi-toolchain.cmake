# the name of the target operating system
set(CMAKE_SYSTEM_NAME RaspberryPi_3B)

# which compilers to use for C and C++
set(CMAKE_C_COMPILER   gcc-arm-linux-gnueabihf)
set(CMAKE_CXX_COMPILER gcc-arm-linux-gnueabihf)

# where is the target environment located
set(CMAKE_FIND_ROOT_PATH  ~/usr/gcc-arm-linux-gnueabihf)