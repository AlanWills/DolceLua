cmake_minimum_required(VERSION 3.6)

##---------------------------- Globals ----------------------------##
project(Dolce)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
IF(NOT DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
ENDIF()

##---------------------------- end Globals ----------------------------##


##------------------------------ Dolce ------------------------------##
set(DOLCE_PROJECT_NAME Dolce)
set(DOLCE_BUILDS_DIR ${PROJECT_SOURCE_DIR}/Build/${CMAKE_VS_PLATFORM_NAME})
set(DOLCE_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SOURCE_FILES ${DOLCE_PROJECT_DIR}/Source/*.c ${DOLCE_PROJECT_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${DOLCE_PROJECT_DIR}/Include/*.h ${DOLCE_PROJECT_DIR}/Include/*.hpp)

source_group(TREE ${DOLCE_PROJECT_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${DOLCE_PROJECT_DIR} FILES ${HEADER_FILES})
source_group(TREE ${DOLCE_PROJECT_DIR} FILES ${RES_FILES})

add_library(${DOLCE_PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${DOLCE_PROJECT_NAME} PROPERTIES 
    FOLDER ${DOLCE_PROJECT_NAME}
    CXX_STANDARD 17)

target_include_directories(${DOLCE_PROJECT_NAME} PUBLIC ${DOLCE_PROJECT_DIR}/Include ${DOLCE_HEADER_DIRS})
target_link_directories(${DOLCE_PROJECT_NAME} PUBLIC ${DOLCE_LIB_DIRS})
target_link_libraries(${DOLCE_PROJECT_NAME} PUBLIC ${DOLCE_LIBS})

target_compile_options(${DOLCE_PROJECT_NAME} PRIVATE /MP4 /W4 /WX)