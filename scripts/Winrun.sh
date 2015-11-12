#!/bin/bash
exePath="D:/RCMcode/RCM/Release/RCM.exe"
foldName=UShape
#lwArr=(1.0 0.9 0.8 0.7 0.6 0.5);
lwArr=(1.0 1.0 1.0 1.0 1.0 1.0);
a1Arr=(9 90 90 90 90 90);
a2Arr=(0 90 90 90 90 90);
boxSizeArr=(122 92 102 112 122 132);
cd D:/RCMcode/RCM/Results;
mkdir $foldName
for i in `seq 0 0`; do
  printf '\n%s\n' "$i"
  #a=./$foldName/${lwArr[$i]}-${a1Arr[$i]}-${a2Arr[$i]}-$(date '+%Y%m%d-%H%M%S')
  a=./$foldName/${lwArr[$i]}-${a1Arr[$i]}-${a2Arr[$i]}-${boxSizeArr[$i]}
  mkdir $a
  cd $a
  $exePath ${a1Arr[$i]} ${a2Arr[$i]} ${lwArr[$i]} ${boxSizeArr[$i]};
  cd ../..;
done;