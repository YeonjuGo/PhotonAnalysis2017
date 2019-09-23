#!/bin/bash
    
ptBins=(20 25 30 40 50 60 80 100 300)
length=${#ptBins[@]}
current=0
centBins=(0 10 30 50 100)

for ((p=0; p< ${#ptBins[@]};p++))
do
    current=$((current+1))
    if [[ "$current" -eq "$length" ]]
    then 
        true
    else
        for ((j=0; j< ${#centBins[@]};j++))
        do
            if [[ "${centBins[$((j))]}" -eq "100" ]]
            then
                true
            else
                echo "${ptBins[$((p))]}" - "${ptBins[$((p+1))]}" - "${centBins[$((j))]}" 
            fi
        done
    fi
done
current=0
echo "$current"
