#!/bin/bash

if test $# = 3 ; then
	if [ -e "$1" ] ; then
		if [ -e "$2" ] ; then
			if [ -e "$3" ] ; then

				cat $1 $2 > tmp

				./prog2 < tmp > $3

				rm tmp

			fi
		fi
	fi
else
	echo "Il faut 3 arguments"
fi
