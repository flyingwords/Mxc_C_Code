#!/bin/bash
#测试：测试使用shift指令偏移参数
#测试命令：./shift_paras.sh    000 111 222 333 444

echo "Total parameter number is ==> $#"
echo "Your whole parameter is ==> '$@'"

shift # 进行第一次『一个变量的 shift 』
echo "Total parameter number is ==> $#"
echo "Your whole parameter is ==> '$@'"

shift 3 # 进行第二次『三个变量的 shift 』
echo "Total parameter number is ==> $#"
echo "Your whole parameter is ==> '$@'"
