echo "cur path is: ${PWD}"

path="${PWD}"

cd ${path}

cmake . -G "MinGW Makefiles"  -B  build

path="${PWD}/build"

echo "new path is: ${path}"
cd ${path}

make

exe="SOCKET_CLIENT"
chmod +x ${exe}
./"${exe}"

