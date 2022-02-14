## Ubuntu Version

Ubuntu 16.04.1 LTS xenial i686


## Kernel Version

4.4.0-91-generic


## Authorization to Execute Make Command

Make sure that you have root's authorization before run make command.

su -  
make  


## Log

/var/log/kern.log


## Header

/usr/src/linux-headers-4.4.0-36/Documentation  
/usr/include/asm-generic/ioctl.h  
/usr/include/asm-generic/ioctls.h  
#include <linux/XXX>  
/usr/src/linux-headers-4.4.0-59-generic/include/linux/XXX  


## Insert and Remove A Module

/sbin/insmod ./sample.ko  
/sbin/lsmod | grep sample  
sample                 16384  0  
cat /proc/devices | grep devone  
246 devone  
/bin/mknod /dev/devone c 246 0  
ls -l /dev/devone  
crw-r--r-- 1 root root 246, 0 Dec  4 19:09 /dev/devone  
/bin/mknod --mode=666 /dev/devone c \`grep devone /proc/devices | awk '{print $1;}'\` 0  
ls -l /dev/devone  
crw-rw-rw- 1 root root 246, 0 Dec  4 19:12 /dev/devone  
rm /dev/devone  
/sbin/rmmod sample.ko  


## Terminal Tool

tmux


## VirtualBox VM Network Setting

Host
```
C:\Users\BOSS>ipconfig  
Windows IP 設定  
無線區域網路介面卡 無線網路連線:  
連線特定 DNS 尾碼 . . . . . . . . :  
連結-本機 IPv6 位址 . . . . . . . : fe80::6055:a2ae:1d6b:936d%13  
IPv4 位址 . . . . . . . . . . . . : 192.168.0.104  
子網路遮罩 . . . . . . . . . . . .: 255.255.255.0  
預設閘道 . . . . . . . . . . . . .: 192.168.0.1  
```
   
VM
```
vim /etc/network/interfaces  
iface enp0s3 inet static  
address 192.168.0.200  
netmask 255.255.255.0  
```

Commands
```
機器->設定值->網路>附加到(A): 橋接介面卡  
ifdown enp0s3  
ifup enp0s3  
service networking restart  
```
