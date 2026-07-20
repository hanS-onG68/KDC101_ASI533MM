echo "cur path is: ${PWD}"

path="${PWD}/build"

if [ -d ${path} ]; then
    echo "Enter into ${path}"
    rm -rf ${path}
fi
echo "Clean is finished!"