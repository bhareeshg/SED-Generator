#!/bin/bash
# My first script
cc ganKDTree.c -lm
./a.out
cd output/
sort -k1 SEDoutput.tsv > SEDoutputsorted.tsv
python plotSEDsWE.py
