#!/bin/bash
# 测试：输入参数简单测试case
case ${1} in
"hello")
echo "Hello, how are you ?"
;;
"")
echo "You MUST input parameters, ex> {${0} someword}"
;;
*) # 其实就相当于通配符， 0~无穷多个任意字符之意，必须放在最后面
echo "Usage ${0} {hello}"
;;
esac
