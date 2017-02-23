#! /bin/bash

testerDirectory="/home/ssdavis/40/p5/Testing"

if [ $# -ne 1 ]; then
  echo "usage Tester.sh: $testerDirectory/Tester.sh CPU.out_directory" 1>&2
  exit
fi

if [[ $1 =~ Testing ]]; then # Use from this directory is not allowed
  echo "You may not use Testing as your own source directory!"  1>&2
  exit
fi

if [[ ! -e $1/CPU.out ]]; then # CPU.out not found
  echo "CPU.out not found in $1!"  1>&2
  exit
fi

cd $1

fileNum=5
opScore=0
echo Operation testing:  1>&2

while [[ $fileNum -lt 9 ]]; do
  echo $fileNum  1>&2
  echo "File#: $fileNum" >> operationsResults.txt
  rm -f out$fileNum.txt  
  (CPU.out $testerDirectory/test$fileNum.s > out$fileNum.txt )&
  sleep 1
  pkill CPU.out &> /dev/null
  if [[ -s out$fileNum.txt ]]; then
    rm students*.txt mine*.txt &> /dev/null
   
    awk -F: '{printf "%d:%s\n", NR, $1}' out$fileNum.txt > students.txt
    awk -F: '{printf "%d:%s\n", NR, $1}' $testerDirectory/out$fileNum.txt > mine.txt

    echo -n "Instruction string values without spaces (1 point): " >> operationsResults.txt
    cat students.txt | tr -d " " > studentString.txt
    cat mine.txt | tr -d " " > SeansString.txt
    grep -F -v -f studentString.txt SeansString.txt > misMatchedStrings.txt
    
    if [[ -s misMatchedStrings.txt ]]; then
      misMatchCount=$(( `cat misMatchedStrings.txt | wc -l` ))
      if [ $misMatchCount -gt 1 ]; then
        misMatchCount=1
      fi
      
      (( opScore += 1 - $misMatchCount ))
      echo "Not OK" >> operationsResults.txt
      echo "Mismatched strings:" >> operationsResults.txt
      cat misMatchedStrings.txt >> operationsResults.txt 
    else
      echo "OK" >> operationsResults.txt
      (( opScore += 1 ))
    fi

    awk -F: '{printf "%d:%s %s %s %s\n", NR, $2, $3, $4, $5}' out$fileNum.txt > students.txt
    awk -F: '{printf "%d:%s %s %s %s\n", NR, $2, $3, $4, $5}' $testerDirectory/out$fileNum.txt > mine.txt
    studentSpaceCount=$(( `fgrep -o " " students.txt | wc -l` ))
    SeansSpaceCount=$(( `fgrep -o " " mine.txt | wc -l` ))

    echo -n "Register string spacing (1 point): "  >> operationsResults.txt
    if [[ $studentSpaceCount -eq $SeansSpaceCount ]]; then
      (( opScore += 1 ))
      echo "OK" >> operationsResults.txt
    else
      echo "Not OK: Your space count: $studentSpaceCount Sean's: $SeansSpaceCount" >> operationsResults.txt
    fi

    
    echo -n "Register values without spaces (4 points): " >> operationsResults.txt
    cat students.txt | tr -d -c "\n:0-9" > studentValues.txt
    cat mine.txt | tr -d -c "\n:0-9" > SeansValues.txt
    grep -F -v -f studentValues.txt SeansValues.txt > misMatchedValues.txt

    if [[ -s misMatchedValues.txt ]]; then
      misMatchCount=$(( `cat misMatchedValues.txt | wc -l` ))

      if [ $misMatchCount -gt 4 ]; then
        misMatchCount=4
      fi

      (( opScore += 4 - $misMatchCount ))
      echo "Not OK" >> operationsResults.txt
      echo "Mismatched values:" >> operationsResults.txt
      cat misMatchedValues.txt >> operationsResults.txt
    else
      echo "OK" >> operationsResults.txt
      (( opScore += 4 ))
    fi
  else
    echo "No output created so zero for operation." >> operationsResults.txt
  fi

  fileNum=$((fileNum + 1))
done  # while less than 2 for now

rm core  &> /dev/null
echo $opScore   # this is the only line that goes to stdout