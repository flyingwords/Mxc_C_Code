#!/bin/bash
# 测试：检测端口运行脚本
echo "Now, I will detect your Linux server's services!"
echo -e "The www, ftp, ssh, and mail(smtp) will be detect! \n"
testfile=./netstat_checking.txt

netstat -tuln > ${testfile} # 先转存数据到内存当中！不用一直执行 netstat
testing=$(grep ":80 " ${testfile}) # 侦测看 port 80 在否？
if [ "${testing}" != "" ]; then
echo "WWW is running in your system."
fi
testing=$(grep ":22 " ${testfile}) # 侦测看 port 22 在否？
if [ "${testing}" != "" ]; then
echo "SSH is running in your system."
fi
testing=$(grep ":21 " ${testfile}) # 侦测看 port 21 在否？
if [ "${testing}" != "" ]; then
echo "FTP is running in your system."
fi
testing=$(grep ":25 " ${testfile}) # 侦测看 port 25 在否？
if [ "${testing}" != "" ]; then
echo "Mail is running in your system."
fi
rm ${testfile} -rf
