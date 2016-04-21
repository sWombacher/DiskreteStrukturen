include_directories(include)
file(GLOB HEADER include/*.h include /*.hpp)
file(GLOB SOURCE src/*.c src/*.cpp)
add_executable(p3 main.cpp ${HEADER} ${SOURCE})
