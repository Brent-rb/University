#!/bin/bash
read input
str=
while [ $input -ne 1 -a $input -ne 0 ]
do
	temp=`expr $input / 2`
	str="`expr $input % 2`$str"
	input=$temp
done

echo $input$str