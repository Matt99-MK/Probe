#!/bin/bash

Info()
{
  cat <<EOF
*UpDownLoader*
Description: Uploading and downloading files from the command line.
Usage: updowloader [flag] [args]  
 No Args - Upload a single file
 -d Compress and Upload directory 
 -F Upload multiple files 
  Examples:
 updownloader.sh /home/Mateusz/scrip1.sh
 updownloader.sh -d /home/Mateusz/dumps
 updownloader.sh 'file1.sh' 'file2.sh' 'file3.sh'
EOF
}

if ! [ $(command -v curl) ]
then
	echo "curl is not installed!" 
fi

if [ "$#" -eq 0 ]
then
Info

elif [ "$#" -eq 1 ]
then
	if ! [ -f "$1" ] 
	then 
		echo "File not exist"! 

	else
	basenamefile=$(basename $1)
	curl -o /tmp/progress.tmp -# https://bashupload.com/$basenamefile --data-binary @/$1 && cat /tmp/progress.tmp && rm /tmp/progress.tmp
	
	fi	

elif [ "$#" -eq 2 ] && [ "$1" = "-d" ]
then
        if ! [ -d "$2" ]
        then 
                echo "Directory not exist"! 

        else
		basenamedirectory=$(basename $2)	
		tar -czvf /tmp/$basenamedirectory.tgz -C $2 . && curl -o /tmp/progress.tmp -#   https://bashupload.com/$basenamedirectory.tgz --data-binary @/tmp/$basenamedirectory.tgz && cat /tmp/progress.tmp && rm /tmp/progress.tmp  || { echo Something went wrong!; }
       rm -r /tmp/$basenamedirectory.tgz
	fi
elif [ "$#" -eq 2 ]
then
	Info
elif [ "$#" -gt 2 ]
then
	for variable in "$@"
	do
	variable1="$(echo $variable | cut -d'=' -f 2)"
	if ! [ -f "$variable1" ]
	then
		echo "File $variable1 not exist"
		echo "Terminate executing the script"
		exit 1

	fi
	done
	curl https://bashupload.com/ -F $1 -F $2 -F $3 -F $4
fi























