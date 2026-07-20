echo "cur path is: ${PWD}"

path="${PWD}"

cd ${path}

# cmake . -G "MinGW Makefiles"  -B  build
# 通常包含OpenCVConfig.cmake文件的路径类似：
cmake -G "MinGW Makefiles"                                 \
      -DCMAKE_C_COMPILER=E:/software/HS/mingw64posix_1120/bin/gcc.exe    \
      -DCMAKE_CXX_COMPILER=E:/software/HS/mingw64posix_1120/bin/g++.exe  \
      -DCMAKE_MAKE_PROGRAM=E:/software/HS/mingw64posix_1120/bin/mingw32-make.exe \
      -DCMAKE_BUILD_TYPE=Debug                             \
      -DCMAKE_CXX_FLAGS="-g -O0 -Wall"                     \
      -DCMAKE_C_FLAGS="-g -O0 -Wall"                       \
      -B build .


path="${PWD}/build/src"

echo "new path is: ${path}"
cd ${path}

mingw32-make

exe="ZWO_SRC"
chmod +x ${exe}
./"${exe}"