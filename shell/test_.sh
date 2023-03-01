#!/bin/bash


# 샷 인덱스 범위 지정
for (( i=1; i<90; i++ ));
do
  if (( ${i} < 10 )); then
    shotidx="0${i}"
  else
    shotidx="${i}"
  fi

  dname="shot${shotidx}"

  input_path="/home/minkyung/spin-storage/test/${dname}/"
  echo "Test ${input_path}"

  fname_console_log="console${shotidx}.txt"
  ./spin-sensor-cli --save --mode=debug ${input_path} >> "${fname_console_log}"

  echo -e "${dname} test done. \n\n"
done
