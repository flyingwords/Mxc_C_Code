#!/bin/bash
#测试：输入两个数字进行四项运算
#说明：
#在数值的运算上，使用   var=$((运算内容)) 进行运算。
#bash shell里头预设仅支持到整数的数据而已，如果你想要计算含有小数点的数据时，其实可以透过 bc 这个指令的协助。

echo "input 2 numbers to operate"
read -p "first number: " firstnu
read -p "second number: " secnu
multi=$((${firstnu}*${secnu}))
div=$((${firstnu}/${secnu}))
sub=$((${firstnu}-${secnu}))
sum=$((${firstnu}+${secnu}))


echo "${firstnu} x ${secnu} is ==> ${multi}"
echo "${firstnu} / ${secnu} is ==> ${div}"
echo "${firstnu} - ${secnu} is ==> ${sub}"
echo "${firstnu} + ${secnu} is ==> ${sum}"



