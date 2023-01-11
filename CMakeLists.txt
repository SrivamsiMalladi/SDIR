cmake_minimum_required(VERSION 3.14)
project(sdri_ctrl2019)

set(CMAKE_CXX_STANDARD 11)

include_directories(postype src/ctrl/postypes)
include_directories(json include/json)
include_directories(vrep include/vrep)
add_definitions(-DNON_MATLAB_PARSING)
add_definitions(-DMAX_EXT_API_CONNECTIONS=255)
add_definitions(-DDO_NOT_USE_SHARED_MEMORY)
if (UNIX)
    SET(CMAKE_CXX_FLAGS -pthread)
    #run apt-get install libpthread-stubs0-dev
endif (UNIX)

add_executable(sdri_ctrl2019 src/main.cpp
        src/ctrl/sdir_ctrl.cpp
        src/ctrl/sdir_ctrl.h
        src/ctrl/pathplanner/ptp/ptp.cpp
        src/ctrl/pathplanner/ptp/ptp.h
        src/ctrl/pathplanner/lin/lin.cpp
        src/ctrl/pathplanner/lin/lin.h
        src/ctrl/postypes/Trajectory.cpp
        src/ctrl/postypes/Trajectory.h
        src/ctrl/postypes/Configuration.cpp
        src/ctrl/postypes/Configuration.h
        src/ctrl/postypes/SixDPos.cpp
        src/ctrl/postypes/SixDPos.h
        src/ctrl/postypes/TMatrix.cpp
        src/ctrl/postypes/TMatrix.h
        include/json/json-forwards.h
        include/json/json.h
        src/ctrl/com/jsoncpp.cpp
        src/ctrl/com/remoteApi/extApi.c
        src/ctrl/com/remoteApi/extApi.h
        src/ctrl/com/remoteApi/extApiInternal.h
        src/ctrl/com/remoteApi/extApiPlatform.c
        src/ctrl/com/remoteApi/extApiPlatform.h
        src/ctrl/com/jsoncpp.cpp
        src/ctrl/com/json_handler.cpp
        src/ctrl/com/json_handler.h
        src/ctrl/com/opmode_enum.h
        src/ctrl/kinematics/inverse/inverse_kinematics.cpp
        src/ctrl/kinematics/inverse/inverse_kinematics.h
        src/ctrl/kinematics/direct/fw_kinematics.cpp
        src/ctrl/kinematics/direct/fw_kinematics.h
        )