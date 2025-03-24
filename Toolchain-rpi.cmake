# Define our host system
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)

# Define the cross compiler locations
SET(CMAKE_C_COMPILER   /home/azureuser/opt/x-tools/aarch64-rpi3-linux-gnu/bin/aarch64-rpi3-linux-gnu-gcc)
SET(CMAKE_CXX_COMPILER /home/azureuser/opt/x-tools/aarch64-rpi3-linux-gnu/bin/aarch64-rpi3-linux-gnu-g++)

# Define the sysroot path for the Raspberry Pi distribution in our tools folder 
SET(CMAKE_FIND_ROOT_PATH /home/azureuser/opt/x-tools/aarch64-rpi3-linux-gnu/aarch64-rpi3-linux-gnu/sysroot)     

# Use our definitions for compiler tools
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Search for libraries and headers in the target directories only
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Add some compiler flags
add_definitions(-Wall -std=c11)
