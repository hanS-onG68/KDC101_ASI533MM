echo "cur path is: ${PWD}"

path="${PWD}"

cd ${path}

cmake . -G "MinGW Makefiles"  -B  build

path="${PWD}/build/src"

echo "new path is: ${path}"
cd ${path}

make

exe="KDC101_SOCKET"
chmod +x ${exe}
./"${exe}"