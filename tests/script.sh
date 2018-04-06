#!/bin/bash

CNF_files="f_CNF_files"
Solver_output="f_Solver_output"
Solver_time="f_Solver_time"

mkdir $CNF_files
mkdir $Solver_output
mkdir $Solver_time

clauses=$1
variables=$2
iterations=$3

fileNumber=1

echo "" >> output.csv
echo "" >> "$Solver_output"/solve.out
echo "" >> "$Solver_output"/glu.out

i=0
while [ $i -lt $iterations ]
do
	#aux=`/usr/bin/time -f '%S' echo "uou" >> teste`
	#echo "$aux"
	echo "iteration $i"

	CNF="$CNF_files"/"$fileNumber".cnf
	./gerador -f "$CNF" -u "$clauses" "$variables" "$i"
	#outputSolver=`/usr/bin/time ./solver "$CNF_files"/"$fileNumber".cnf >> "$Solver_output"/solve.out`
	#outputGlucose=`/usr/bin/time -f '%S' ./glucose "$CNF_files"/"$fileNumber".cnf >> "$Solver_output"/glu.out`

	outputGlucose=`/usr/bin/time -f '%S' ./glucose CNF > glu.out`

	echo "$i outputSolver $outputGlucose" > output.csv

	i=$[$i + 1]
	fileNumber=$[$fileNumber + 1]
done