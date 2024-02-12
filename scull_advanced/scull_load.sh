#!/bin/sh

module="scull"
device="scull"
mode="066"

if [ "$1" = "ins" ]; then
/sbin/insmod ./$module.ko || exit 1

rm -f /dev/${device}[0-3]

major=$(cat /proc/devices | grep $module | head -1 | awk '{print $1}')

mknod /dev/${device}0 c $major 0
mknod /dev/${device}1 c $major 1
mknod /dev/${device}2 c $major 2
mknod /dev/${device}3 c $major 3

group="staff"
grep -q "^staff:" /etc/group || group="wheel"

chgrp $group /dev/${device}[0-3]
chmod $mode /dev/${device}[0-3]
elif [ "$1" = "rem" ]; then
	rm -f /dev/${device}[0-3]
	rmmod $module
fi
