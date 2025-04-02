cmake_minimum_required(VERSION 3.28)
project(TP3)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/..")

set(template_Inc_directory "inc")
set(template_Src_directory "src")

file(GLOB_RECURSE SOURCES
        "${template_Src_directory}/**.cpp"
        "${template_Src_directory}/*.h")

include_directories("inc")

add_executable(${PROJECT_NAME} ${SOURCES})
# GLOB_RECURSE Pour voyager entre fichier
# rm -r */ ONLY DO IN \build
#cmake -G "MinGW Makefiles" ..
#cmake --build .
#PS D:\Session_2\INF147\INF147\TP1\build> mkdir build     
#D:\Session_2\INF147\INF147\TP1\build> cd build   
#D:\Session_2\INF147\INF147\TP1\build> cmake -G "MinGW Makefiles" .. 
#D:\Session_2\INF147\INF147\TP1\build> cmake --build .