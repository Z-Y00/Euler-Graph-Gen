#!/bin/bash
# first test if we have two param, todo

#if fine, then run it
./gen $1 
chmod 777 ./*.dat
mkdir -p $2/1/ $2/2/ $2/4/ $2/8/
mv ./1-0.dat $2/1/
mv ./2-*.dat $2/2/
mv ./4-*.dat $2/4/
mv ./8-*.dat $2/8/
