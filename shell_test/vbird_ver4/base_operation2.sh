#!/bin/bash
#测试：输入两个数字进行四项运算
#说明：
#在数值的运算上，可以使用declare -i total=${firstnu}*${secnu} 进行运算

echo "input 2 numbers to operate"
read -p "first number: " firstnu
read -p "second number: " secnu
declare -i multi=${firstnu}*${secnu}
declare -i div=${firstnu}/${secnu}
declare -i sub=${firstnu}-${secnu}
declare -i sum=${firstnu}+${secnu}

echo "${firstnu} x ${secnu} is ==> ${multi}"
echo "${firstnu} / ${secnu} is ==> ${div}"
echo "${firstnu} - ${secnu} is ==> ${sub}"
echo "${firstnu} + ${secnu} is ==> ${sum}"

