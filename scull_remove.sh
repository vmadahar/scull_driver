#!/bin/bash

module="scull_driver"
device="scull_driver"

echo "Removing $module driver"
/sbin/rmmod $module

echo "Removing $device nodes"
rm -rf /dev/${device}*
