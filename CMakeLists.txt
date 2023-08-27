cmake_minimum_required(VERSION 3.26)
project(bulk_server VERSION 0.1.0 LANGUAGES C CXX)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project (${PROJECT_NAME} VERSION ${PROJECT_VERSION})

set (CMAKE_CXX_STANDARD 20) 

add_executable(${PROJECT_NAME} 
src/main.cpp
server/session.hpp
server/server.hpp
server/classTest.hpp)

#NOTE include Ws2_32.lib wsock32
if(WIN32)
  target_link_libraries(${PROJECT_NAME} -lws2_32 -lwsock32)
endif()

target_include_directories(${PROJECT_NAME}
    PRIVATE
    includes/
)

#FIXME Need delete or comment out for push GitHub
set (BOOST_ROOT "C:/boost")

find_package (Boost REQUIRED system REQUIRED)

if (Boost_FOUND)
    include_directories (SYSTEM ${Boost_INCLUDE_DIR})    
    target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES}) 
endif ()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()