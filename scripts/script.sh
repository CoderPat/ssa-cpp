#!/usr/bin/bash

#-------------------
#Description: script that extracts audio from the movie based on the aligment results
#Argument 1: the name of the file with the alignement reuslts
#Argument 2: the name of the movie file
#------------------------

results=$1
movie=$2
alignements=0
validpair=1
mode=1
numpair=0
while read line
do

    if [ "$alignements" -eq 1 ]; then
        line=${line#*:}
        #check for a valid pair
        if [ "$mode" -eq 0 ]; then
           (( mode++ ))
        elif [ "$mode" -eq 1 ]; then
            if [ "$line" == " GAP" ];then
                validpair=0
            else
                tmp=${line#*[}
                name=${tmp%]*}
            fi
            (( mode++ ))
        elif [ "$mode" -eq 2 ]; then
            if [ "$line" == " GAP" ];then
                validpair=0
            fi
        #if it is a valid pair
            if [ "$validpair" -eq 1 ];then
                mkdir scriptresults
                ffmpeg -i $movie -ss "${line:1:12}" -to "${line:18:12}" -vn -acodec copy scriptresults/"$name${numpair}".m4a -nostdin
                (( numpair++ ))
            fi
            mode=0
            validpair=1
        fi
    else
        if [ "$line" == "Pairs:" ];then
            alignements=1;
        fi
    fi
done < $results
exit 0