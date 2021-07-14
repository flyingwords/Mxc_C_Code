#!/bin/bash
# 测试：测试for循环
users=$(cut -d ':' -f1 /etc/passwd) # 撷取账号名称
for username in ${users} # 开始循环进行！
do
id ${username}
done
