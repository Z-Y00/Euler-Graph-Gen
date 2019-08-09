#!/bin/bash
# first test if we have two param, todo

#if fine, then run it
cat $1 | ./gen  $2.bin
