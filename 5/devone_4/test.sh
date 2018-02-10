#!/bin/bash

insmod sample.ko

mknod --mode=666 /dev/devone0 c `grep devone /proc/devices | awk '{print $1;}'` 0
mknod --mode=666 /dev/devone1 c `grep devone /proc/devices | awk '{print $1;}'` 1
mknod --mode=666 /dev/devone2 c `grep devone /proc/devices | awk '{print $1;}'` 2
ls -l /dev/devone*

cat /dev/devone0
dmesg | tail

cat /dev/devone1
dmesg | tail

cat /dev/devone2
dmesg | tail

rm /dev/devone0
rm /dev/devone1
rm /dev/devone2

rmmod sample.ko
