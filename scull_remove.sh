#!/bin/bash
module="scull_driver"
device="scull_driver"

/sbin/rmmod $module

rm -rf /dev/${device}*
