#!/bin/bash

read str

if [ $str ]
	then
	if [ -z $str ]
		then
		echo "Het is een palindroom"
	else
		length=`expr length $str`
		if [ $length == 1 ]
			then
			echo "De string: \"$str\" is een palindroom"
		else
			i=$length
			while [ $i -ge 0 ]
			do
				tmp="${str:i:1}"
				new="$new$tmp"
				i=`expr $i - 1`
			done
			if [ $str = $new ]
				then
				echo "De string: \"$str\" is een palindroom"
			else
				echo "De string: \"$str\" is geen palindroom"
			fi
		fi
	fi
else
	echo "Error wrong usage"
fi