#!/bin/bash
# Author           : Tamara Mruk ( mruktamara64@gmail.com )
# Created On       : 01.05.2024
# Last Modified By : Tamara Mruk ( mruktamara64@gmail.com )
# Last Modified On : 08.05.2024
# Version          : 1.0
#
# Description      : mp3finder is a script made for sorting and finding mp3 files by tags in the current folder, the results are also color coded by query match percentage
#
# Licensed under GPL (see /usr/share/common-licenses/GPL for more details
# or contact # the Free Software Foundation for a copy)


while getopts "h" arg; do

  case $arg in
    h)
	echo "Open mp3finder manual to learn more about the script and what it does!"
	exit 1;;
    *)
	echo "Invalid option";;
  esac
  
done


data=`zenity --forms --title="MP3 file finder" --text="insert tags" --separator="," --add-entry="Artist" --add-entry="Album" --add-entry="Title" --add-entry="Genre"`

artist=`echo $data | cut -d "," -f 1`
album=`echo $data | cut -d "," -f 2`
title=`echo $data | cut -d "," -f 3`
genre=`echo $data | cut -d "," -f 4`

filtered_files=()

for file in *".mp3"; do

	METADATA=$(ffprobe -v error -show_entries format_tags=title:format_tags=artist:format_tags=album:format_tags=genre -of default=noprint_wrappers=1:nokey=1 "$file")

    	ALBUM=$(echo "$METADATA" | sed -n '1p')
    	ARTIST=$(echo "$METADATA" | sed -n '2p')
    	GENRE=$(echo "$METADATA" | sed -n '3p')
    	TITLE=$(echo "$METADATA" | sed -n '4p')

	matching=0

	if [[ -n "$artist" && "$ARTIST" == *"$artist"* ]]; then
        	((matching++))
    	fi

    	if [[ -n "$album" && "$ALBUM" == *"$album"* ]]; then
        	((matching++))
    	fi

    	if [[ -n "$genre" && "$GENRE" == *"$genre"* ]]; then
        	((matching++))
    	fi

	if [[ -n "$title" && "$TITLE" == *"$title"* ]]; then
		((matching++))
	fi
	
	filtered_files+=("$matching $file")
	matching=0
	
done

IFS=$'\n' filtered_files=($(sort -nr <<<"${filtered_files[*]}"))
unset IFS

for file_info in "${filtered_files[@]}"; do

    	matching="${file_info%% *}"

    	file="${file_info#* }"

    	if [ "$matching" -eq 4 ]; then
        	echo -e "\e[1;32m$file\e[0m"

    	elif [ "$matching" -eq 3 ]; then
        	echo -e "\e[92m$file\e[0m"

    	elif [ "$matching" -eq 2 ]; then
        	echo -e "\e[1;33m$file\e[0m"

	elif [ "$matching" -eq 1 ]; then
		echo -e "\e[34m$file\e[0m"
	else
		echo -e "\e[31m$file\e[0m"
	fi

done