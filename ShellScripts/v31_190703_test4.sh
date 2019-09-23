#!/bin/bash

ver1="190703_temp_v31_uncorrectedEt"
ver2="190625_temp_v29_uncorrectedEt"

root -l -b -q 'results/getRawDist_v7_test.C++("'$ver1'",1,1)' >& log/getRawDist_v7_'$ver1'.log & sleep 20 
root -l -b -q 'results/getRawDist_v7_test2.C++("'$ver2'",1,1)' >& log/getRawDist_v7_'$ver2'.log & sleep 20 
