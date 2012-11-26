#!/bin/bash

module="scull_driver"
device="scull_driver"
mode="664"

echo "Loading driver: $module"
/sbin/insmod ./$module.ko $* || exit 1

echo "Removing stale nodes for $device"
rm -rf /dev/${device}*

major=$(awk "\$2==\"$module\" {print \$1}" /proc/devices)

echo "mknod for $device with $major major"
mknod /dev/${device} c $major 0

group="staff"
grep -q '^staff:' /etc/group || group="wheel"

chgrp $group /dev/${device}
chmod $mode /dev/${device}
