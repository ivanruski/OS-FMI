#!/bin/bash

function participants {
    while read line; do

        if grep -q "^CALLSIGN:" $line; then
            echo $(basename $line)
        fi

    done < <(find "${1}" -type f)
}


function outliers {
    declare -A map
    declare -A result
    while read participant; do
        map[$participant]="1"
    done < <(participants "${1}")

    while read file; do
        
        while read col; do
            if [[ ! ${map[$col]+_} ]] && [[ ! ${result[$col]+_} ]]; then
                result[$col]="1"
            fi
       
        done < <(cat $file | tr -s ' ' | cut -d ' ' -f9 | egrep "^([0-9A-Z])+$")
        
    done < <(find "${1}" -type f)

    for r in "${!result[@]}";do
        echo $r
    done
}

function unique {
    declare -A result

    while read file; do
        
        while read col; do
            if [[ ! ${result[$col]+_} ]]; then
                result[$col]="1"
            else
                incr="${result[$col]}"
                result[$col]=$(( incr+=1 ))
            fi
       
        done < <(cat $file | tr -s ' ' | cut -d ' ' -f9 | egrep "^([0-9A-Z])+$")
        
    done < <(find "${1}" -type f)

    for r in "${!result[@]}";do
        if [[ ${result[$r]} -le 3 ]]; then
            echo $r
        fi
    done
}

function participants_log_files {
    
    while read line; do

        if grep -q "^CALLSIGN:" $line; then
            echo "$line"
        fi

    done < <(find "${1}" -type f)
}

function cross_check {

   while read log_file;do
       while read log_line; do
           p_name=$(cut -d ' ' -f9 <(echo ${log_line}))

           if [[ -n ${p_name} ]] && [[ -e "${1}/${p_name}" ]] && ! grep -q "$(basename ${log_file})" "${1}/${p_name}" 2> ../../../dev/null; then
               echo "${log_line}"
           fi

        done < <(cat "${log_file}" | egrep "^QSO: ")   
   done < <(participants_log_files "${1}")
}


#####Bonus

function get_time_in_sec_epoch {
# $1 yy-mm-dd
# $2 HH-MM
  dt=`date --date="${1} ${2}" +%s`
  echo "${dt}"  
}
 
function get_lower_range {
  time="$(get_time_in_sec_epoch ${1} ${2})"
  lower_range="$(( $time-180 ))"
  echo "${lower_range}"
}

function get_upper_range {
  time="$(get_time_in_sec_epoch ${1} ${2})"
  upper_range="$(( $time+180 ))"
  echo "${upper_range}"
}


function bonus {
while read log_file; do
	while read line; do
	    date="$(cut -d ' ' -f4 <(echo ${line}))"
	    hour="$(cut -d ' ' -f5 <(echo ${line}))"
	    cross_file="$(cut -d ' ' -f9 <(echo ${line}))"
          
	    l_range=$(cat <(get_lower_range ${date} ${hour}))
	    u_range=$(cat <(get_upper_range ${date} ${hour}))

      
       if [[ -n ${cross_file} ]] && [[ -e "${1}/${cross_file}" ]] && ! grep -q "$(basename ${log_file})" "${1}/${cross_file}" 2> ../../../dev/null; then
            echo "${line}"
       else
           match_line="$(grep $(basename ${log_file}) ${1}/${cross_file} 2> ../../../dev/null)"
          
           if [[ -n ${match_line} ]]; then
           
	            cross_date="$(cut -d ' ' -f4 <(echo ${match_line}))"
	            cross_hour="$(cut -d ' ' -f5 <(echo ${match_line}))"
	            cross_epoch=$(cat <(get_time_in_sec_epoch ${cross_date} ${cross_hour}))
	  
	            if [[ ${l_range} -gt ${cross_epoch} ]] || [[ ${u_range} -lt ${cross_epoch} ]]; then
	                echo "${line}"
	                #echo "cross ${match_line}"
	            fi
           fi
       fi
	
	done < <(cat "${log_file}" | egrep "^QSO: ")

done < <(participants_log_files "${1}")

}
#####End

if [[ $# -ne 2 ]]; then 
    echo "Usage: <path-to-dir> <function>"
    exit 1
fi

if [[ ! -d ${1} ]]; then 
    echo "Directory not found"
    exit 2
fi

if [[ ${2} = "participants" ]]; then 
    participants "${1}"
elif [[ ${2} = "outliers" ]]; then
    outliers "${1}"
elif [[ ${2} = "unique" ]]; then
    unique "${1}"
elif [[ ${2} = "cross_check" ]]; then
    cross_check "${1}"
elif [[ ${2} = "bonus" ]]; then
    bonus "${1}"
else
   echo "Function not found"
   echo "Options: participants\noutliers\nunique\ncross_check\nbonus"
fi 























