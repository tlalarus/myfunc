#!/bin/bash

for (( i=81; i<90; i++ ));
do
  if (( ${i} < 10 )); then
    diridx="0${i}"
  else
    diridx="${i}"
  fi


  dname="shot${diridx}"
  echo "Dir: ${dname}"

  ./rename_.sh ${dname}
done

