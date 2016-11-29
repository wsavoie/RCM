#!/bin/bash
exePath="D:/RCMcode/RCM/Release/RCM.exe"


#varying LW
#lwArr=(1.4 1.3 1.2 1.1 1.0 0.9 0.8 0.7 0.6 0.5 0.4 0.3 0.2 0.1 0.0);
#a1Arr=(70 70 70 70 70 70 70 70 70 70 70 70 70 70 70);
#a2Arr=(70 70 70 70 70 70 70 70 70 70 70 70 70 70 70);
#boxSizeArr=(122 122 122 122 122 122 122 122 122 122 122 122 122 122 122);

# lwVals=(1.4 1.3 1.2 1.1 1.0 0.9 0.8 0.7 0.6 0.5 0.4 0.3 0.2 0.1 0.0);
lwVals=(0.1 0.5 0.9 1.4 1.3 1.2 1.1 1.0 0.9 0.8 0.7 0.6 0.5 0.4 0.3 0.2 0.1 0.0);
for z in `seq 0 2`; do
	for b in `seq 0 14`; do
	  lwArr[$b]=${lwVals[$z]};
	done;
	#lwArr=(0.0 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7);
	# a1Arr=(0 10 20 30 40 50 60 70 80 90 100 110 120);
	# a2Arr=(0 10 20 30 40 50 60 70 80 90 100 110 120);
	a1Arr=(90);
	a2Arr=(90);
	boxSizeArr=(140 100);
	angsL=${#a1Arr[@]};
	((angsLen=angsL-1));
	cd D:/RCMcode/RCM/Results;
	# foldName=AngleChangeLW=${lwArr[$z]};
	foldName=ushape2
	mkdir $foldName
	for i in `seq 0 ${angsLen}`; do
	  SECONDS=0;
	  printf '\n%s\n' "$i"
	  #a=./$foldName/${lwArr[$i]}-${a1Arr[$i]}-${a2Arr[$i]}-$(date '+%Y%m%d-%H%M%S')
	  a=./$foldName/${lwArr[$z]}-${a1Arr[$i]}-${a2Arr[$i]}-${boxSizeArr[1]}
	  mkdir $a
	  cd $a
	  $exePath ${a1Arr[$i]} ${a2Arr[$i]} ${lwVals[$z]} ${boxSizeArr[1]};
	  printf '\nSim Time=%ds\n' "$SECONDS"
	  cd ../..;
	done;
done;