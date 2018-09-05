Ubuntu Version<br>
Ubuntu 16.04.1 LTS xenial i686

Kernel Version<br>
4.4.0-91-generic

Make sure that you have root's authorization before run make command.<br>
su -<br>
make

Log<br>
/var/log/kern.log

Header<br>
/usr/src/linux-headers-4.4.0-36/Documentation<br>
/usr/include/asm-generic/ioctl.h<br>
/usr/include/asm-generic/ioctls.h<br>
#include <linux/XXX><br>
/usr/src/linux-headers-4.4.0-59-generic/include/linux/XXX<br>

Insert and Remove A Module<br>
/sbin/insmod ./sample.ko<br>
/sbin/lsmod | grep sample<br>
sample                 16384  0<br>
cat /proc/devices | grep devone<br>
246 devone<br>
/bin/mknod /dev/devone c 246 0<br>
ls -l /dev/devone<br>
crw-r--r-- 1 root root 246, 0 Dec  4 19:09 /dev/devone<br>
/bin/mknod --mode=666 /dev/devone c `grep devone /proc/devices  | awk '{print $1;}'` 0<br>
ls -l /dev/devone<br>
crw-rw-rw- 1 root root 246, 0 Dec  4 19:12 /dev/devone<br>
rm /dev/devone<br>
/sbin/rmmod sample.ko<br>

Terminal Tool
tmux
