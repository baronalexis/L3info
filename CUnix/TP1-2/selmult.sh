#!/bin/bash

read sub

while [ $sub != 0 ]
do
	echo $sub > tmp1
	cat tmp1 $1 > tmp2
	./prog2 < tmp2	
	read sub
done
rm tmp1 tmp2 
