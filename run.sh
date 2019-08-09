#!/bin/bash
# first test if we have two param, todo

#if fine, then run it
./gen $1  $2.dat
chmod 744 $2.dat
