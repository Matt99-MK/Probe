#!/bin/bash

for i in $@
do
    echo "Matching the pattern: $i"
       FILES=()
    while read -rd '' file
    do
        FILES+=("$file")
        echo "  $file"
    done < <(find . -depth -iname "$i" -print0)

    if [  -z "$FILES" ]
    then
	   
	    echo "Nothing found"
	    continue
    fi

#Process Substitution - from stackoverflow "The -print0 will use the NULL as a file separator instead of a newline and the -d $'\0' will use NULL as the separator while reading."
 read -p "Delete ALL? <y/N> " variable

 if [[ $variable == "y" || $variable == "Y" ]] 
 	then
	       	for files in "${FILES[@]}"
		 do
			 if rm "$files";
			 then
				 echo " Deleting file: $files OK"
			 else
				 echo " Deleting file: $files FAIL"
			 fi
		 done
echo $FILES
	 else

echo "    Nothing deleted"    
fi

done
