#!/bin/bash

#!/usr/bin/bash

#-------------------
#Description: Given a folder with a movie, subtitles and script, extracts the audio files associated with each character
#Argument 1: The movie folder
#------------------------

aligner="../build/ssa"
audio_extracter="bash ./audio_extractor.sh"
extraction_folder="/ffs/tmp/patrick/extracted-audio"

movie_folder=$1

#get the paths
get_file_from_extension "$movie_folder" mp4
movie=$ret_var
get_file_from_extension "$movie_folder" txt
script=$ret_var
get_file_from_extension "$movie_folder" srt
subtitle=$ret_var

movie_name=$(basename "$movie_folder")
mkdir "$extraction_folder/$movie_name"

echo "-- Aligning --"
eval $aligner "\"$script\""  "\"$subtitle\""  >"$extraction_folder/$movie_name/alignment_results.txt"

echo "-- Extracting Audio --"
eval $audio_extracter "\"$extraction_folder/$movie_name/alignment_results.txt\"" "\"$movie\"" "\"$extraction_folder/$movie_name/\""