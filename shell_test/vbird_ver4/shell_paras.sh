#!/bin/bash
# 测试：shell脚本传参测试
# 总结；
#	$0、$1、$2、$3	依次表示文件名、参数1、参数2、参数3
#	$@  代表『 "$1" "$2" "$3" "$4" 』之意，每个变量是独立的(用双引号括起来)；
#	$#	表示调用该shell时传参的个数，不包括$0 （即程序名） 
# 注意：$# 计算参数个数的时候，不包括$0 即文件名参数，而C语言的argc则是包括程序名参数在内的

echo "The script name is ==> ${0}"
echo "Total parameter number is ==> $#"
[ "$#" -lt 2 ] && echo "The number of parameter is less than 2. Stop here." && exit 0
echo "Your whole parameter is ==> '$@'"
echo "The 1st parameter ==> ${1}"
echo "The 2nd parameter ==> ${2}"
