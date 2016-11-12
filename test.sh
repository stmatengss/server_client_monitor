#!/bin/bash
set -x

get_url="166.111.131.132:8080/CCSP.zip"
root_dir=`pwd`
work_dir=$1
driver_dir=$2
wget  ${get_url}
curl -O ${get_url} #choose wget or curl to get the data

if [ $? -eq 0 ]; then
	file_name=`ls *.zip`
	file_dir=${file_name%.zip} # get the dir's name
	
	if [ "$file_dir" == "" ]; then
		echo "error"
	fi

	#if [ ! -d ${work_dir}/${file_dir} ]; then
	#	mkdir ${work_dir}/${file_dir}
	#fi
	
	#cp ${file_name} ${work_dir}/${file_dir}  
	#user_name=${}	
	cp ${file_name} ${work_dir}
	
	cd ${work_dir}
	unzip -q -o ${file_name}
	rm -rf ${file_name}
	/bin/cp -r -f ${driver_dir} . 	
	cd ${file_dir}
	make > make.log # compile project
	if [ $? -ne 0 ]; then # error occur
		echo "error"
	else
		echo "success"
	fi
	cd ${root_dir} # return root_dir
else
	echo "error"
fi
