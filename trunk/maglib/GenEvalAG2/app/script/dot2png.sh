#!/bin/bash

	######### MAGLIB #########
# Convert dot's file to png's file.


# Use:
# "./dot2png.sh [SOURCE] [TARGET]"
# Where:
#	SOURCE----> Source directory of files to convert
#	TARGET----> Target directory.

# Observation: 
#	if not SOURCE and not TARGET then uses actual directory ("./").
#	if not TARGET then uses directory source and target directory to SOURCE.


source="./"
target="./"
if [ $# -gt 2 ]; then
    echo "Wrong use.
  Use: ./dot2png.sh [SOURCE] [TARGET] 
   	Where:
    	SOURCE----> Source directory of files to convert
    	TARGET----> Target directory."
else
    if [ $# == 1 ]; then
		source=$1
		target=$1
    else
    	source=$1
        target=$2
    fi
	if [ -d $source ]; then
		if [ -d $target ]; then
			check_=${target##*/}

			if [ ${#check_} -gt 0 ]; then
				target=$target/
			fi
			echo "Convirtiendo..."

			for archivo in $source*
			do
				if [ -f $archivo ]; then
					file=${archivo##*/}
					filename=${file%.*}
					extension=${file#*.}
					ext="dot"
    				if [ $extension == $ext ]; then
    					echo $archivo 
			    		dot -Tpng $archivo -o $target$filename.png
			    		echo $target$filename.png
			    	fi
			 	fi				   
			done
		else
			echo "Path target non exists." $target
		fi
	else
		echo "Path source non exists." $source
	fi
fi

