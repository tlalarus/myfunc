#!/bin/bash

dirname=${1}
pushd ${dirname}

# 현재 경로의 파일 목록을 저장할 임시파일명 지정
tmpflist="ls.tmp"

# ls 명령어로 파일 목록 출력후 임시파일로 리다이렉션
ls -l | awk 'NR>=2 {print $9}' > "$tmpflist"

# 임시파일 목록 순회
cnt=1

while read cur_fname
do
  # 확장자 검사
  if [[ "$cur_fname" == *.png ]]; then
    if [[  "$cur_fname" == ready* ]]; then
      new_fname="0.png"
    else
      new_fname="${cnt}.png"
    fi

    echo "rename ${cur_fname} ${new_fname}"
    
    mv ${cur_fname} ${new_fname}
    (( cnt="${cnt}" + 1 ))
  fi
done < "$tmpflist"

rm -f "${tmpflist}"

popd