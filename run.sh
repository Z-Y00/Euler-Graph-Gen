#!/bin/bash
# first test if we have two param, todo

#if fine, then run it
./gen $1  $2.bin
chmod 744 $2.bin
