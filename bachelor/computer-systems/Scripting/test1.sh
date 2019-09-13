#!/bin/bash

searchdirectory() {
	dir=$1
	searchString=$2

	for file in $dir/*
	do
		echo "$file"
		if [ -d "$file" ]
			then
			searchdirectory "$file" "$searchString"
		else
			if [ -f "$file" ]
				then
				searchfile "$file" "$searchString"
			fi
		fi
	done
}

searchfile() {
	file=$1
	searchString=$2

	tempString=`grep "$searchString" $file`

	if [[ $tempString == *$searchString* ]]
		then
		echo "$file bevat $searchString"
	else
		echo "$file bevat $searchString niet"
	fi
}

if [ $# -eq 0 -o $# -eq 1 ]
	then
	echo "Invalid usage"
else
	searchString=$1
	echo "We zoeken: $searchString"
	shift 1
		
	for file in $@
	do
		if [ -d $file ]
			then
			searchdirectory "$file" "$searchString"
		else
			searchfile "$file" "$searchString"
		fi
	done
fi


