#!/bin/bash

makefile="Makefile"

function arrayContains {
	local match="$1"
	shift
	local arr="$@"
	for str in $arr; do
		if [[ "$str" == "$match" ]]; then
			return 1
		fi
	done
	return 0
}

function getIncludeName {
	local inc="$1"
	local inclen=${#inc}
	inc=${inc:10:(($inclen - 11))}
}

function printMake {
	echo -e "$1" >> "$makefile"
}


echo "C = g++" > Makefile
printMake "CFLAGS = -Wall"
printMake "LFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf"
printMake ""
printMake "TARGET = JAM"
printMake ""
objList="OBJS = "
objRules=()
ruleNum=0

for cppFile in ../src/*.cpp; do
	name=${cppFile%.*p}
	name=${name:7}
	hFile="../src/$name.hpp"
	obj="$name.o"
	objList+="$obj "
	objRule="$obj : "
	linenum=0
	if [[ -a "$hFile" ]]; then
		incs[$linenum]="$hFile"
		((linenum++))
		while read -r line ; do
			incs[$linenum]=$(getIncludeName "$line")
			((linenum++))
		done < <(grep "#include \"" $hFile)
	fi
	incs[$linenum]=$cppFile
	((linenum++))
	while read -r line; do
		incFile=$(getIncludeName "$line")
		arrayContains "$incFile" "${incs[@]}"
		result=$?
		if [[ $result == 0 ]]; then
			incs[$linenum]="$incFile"
			((linenum++))
		fi
	done < <(grep "#include \"" $cppFile)
	for inc in ${incs[@]}; do
		objRule+="$inc "	
	done
	objRule="${objRule: : -1}"
	objRules[$ruleNum]="$objRule"
	((ruleNum++))
done

printMake "${objList: : -1}"
printMake ""

printMake 'all : game\n'

printMake 'game : $(OBJS)'
printMake '\t$(C) $(CFLAGS) -o $(TARGET) $^ $(LFLAGS)'
printMake "\trm ../src/*.gch"
printMake ""

for rule in "${objRules[@]}"; do
	printMake "$rule"
	printMake '\t$(C) $(CFLAGS) -c -g $^ $(LFLAGS)' #-o $@ $(LFLAGS)'
	printMake ""
done

printMake 'clean :'
printMake "\trm ./*.o"
printMake "\trm ../src/*.gch"
printMake ""

make all
