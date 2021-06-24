#!/bin/bash
##测试：读取用户名输入并打印
read -p "Please input your first name: " firstname # 提示使用者输入
read -p "Please input your last name: " lastname # 提示使用者输入
echo  "Your full name is: ${firstname} ${lastname}" # 结果由屏幕输出
