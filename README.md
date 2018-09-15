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
/bin/mknod --mode=666 /dev/devone c `grep devone /proc/devices | awk '{print $1;}'` 0  
ls -l /dev/devone  
crw-rw-rw- 1 root root 246, 0 Dec  4 19:12 /dev/devone  
rm /dev/devone  
/sbin/rmmod sample.ko  


## Terminal Tool

tmux


## VirtualBox VM Network Setting

虛擬網路要有DHCP分配的機制，例如：接到分享器或無線網路等等  
   
VM
```
機器->設定值->網路>附加到(A): 橋接介面卡  
機器->設定值->網路>名稱(N): 選Host的有線/無線網卡
```
```
vim /etc/network/interfaces  

iface enp0s3 inet dhcp  
```
```
ifdown enp0s3  
ifup enp0s3  
service networking restart  
```
