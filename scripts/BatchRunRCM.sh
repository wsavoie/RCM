#!/bin/bash
exePath="D:/RCMcode/RCM/Release/RCM.exe"


#varying LW
#lwArr=(1.4 1.3 1.2 1.1 1.0 0.9 0.8 0.7 0.6 0.5 0.4 0.3 0.2 0.1 0.0);
#a1Arr=(70 70 70 70 70 70 70 70 70 70 70 70 70 70 70);
#a2Arr=(70 70 70 70 70 70 70 70 70 70 70 70 70 70 70);
#boxSizeArr=(122 122 122 122 122 122 122 122 122 122 122 122 122 122 122);

lwVals=(1.4 1.3 1.2 1.1 0.9 0.8 0.7 0.6 0.5 0.4 0.3 0.2 0.1 0.0);
# lwVals=(0.1 0.5 0.9 1.4 1.3 1.2 1.1 1.0 0.9 0.8 0.7 0.6 0.5 0.4 0.3 0.2 0.1 0.0);
its=1000000
mainFold="test"
boxSize=150;
printPos=0;
mkdir D:/RCMcode/RCM/Results/${mainFold};
for z in `seq 0 13`; do
	# a1Arr=(-120 -110 -100 -90 -80 -70 -60 -50 -40 -30 -20 -10 0 10 20 30 40 50 60 70 80 90 100 110 120);
	# a2Arr=(-120 -110 -100 -90 -80 -70 -60 -50 -40 -30 -20 -10 0 10 20 30 40 50 60 70 80 90 100 110 120);
	a1Arr=(90);
	a2Arr=(90);
	angsL=${#a1Arr[@]};
	((angsLen=angsL-1));
	cd D:/RCMcode/RCM/Results/${mainFold};
	# foldName=AngleChangeLW=${lwArr[$z]};
	foldName="lw=${lwVals[$z]}"
	mkdir $foldName
	for i in `seq 0 ${angsLen}`; do
		for j in `seq 0 ${angsLen}`; do
		  SECONDS=0;
		  printf '\n%s\n' "$i"
		  #a=./$foldName/${lwVals[$i]}-${a1Arr[$i]}-${a2Arr[$i]}-$(date '+%Y%m%d-%H%M%S')
		  a=./$foldName/${lwVals[$z]}_${a1Arr[$i]}_${a2Arr[$j]}_${boxSize}
		  mkdir $a
		  cd $a
		  $exePath ${a1Arr[$i]} ${a2Arr[$j]} ${lwVals[$z]} ${boxSize} ${its} ${printPos}
		  printf '\nSim Time=%ds\n' "$SECONDS"
		  cd ../..;
		done;
	done;
done;