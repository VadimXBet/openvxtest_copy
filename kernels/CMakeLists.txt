file(GLOB SRCS src/*.c src/*.cpp)
add_library(kernels ${SRCS} "src/findMoments.c"  "include/detail/momentsStruct.h" "src/findHuMoments.c")
target_include_directories(kernels PUBLIC include)
