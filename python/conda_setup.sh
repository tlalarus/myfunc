#!/bin/bash
echo "Current working directory: ${PWD}"
echo "Current python info"
which python # should return /usr/local/bin/python
python --version

env PYTHONPATH # /env/python
env -u PYTHONPATH

# Setup python 3.8.12
pushd /usr/src/
wget -P /usr/src/ https://www.python.org/ftp/python/3.8.12/Python-3.8.12.tgz
tar xvfz Python-3.8.12.tgz
Python-3.8.12/configure
make
sudo make install
popd

python --version


################################################################################
# INSTALL CONDA ON GOOGLE COLAB
################################################################################
wget https://repo.anaconda.com/miniconda/Miniconda3-py38_4.12.0-Linux-x86_64.sh
chmod +x Miniconda3-py38_4.12.0-Linux-x86_64.sh
bash ./Miniconda3-py38_4.12.0-Linux-x86_64.sh -b -f -p /usr/local

# import sys
# sys.path.append('/usr/local/lib/python3.8/site-packages/')

which conda  # should return /usr/local/bin/conda
conda --version
python --version

# 구글 코랩이 설치된 폴더 안의 파일, 패키지 리스트
echo "@@ Show packages in colab"
ls /usr/local/lib/python3.8/site-packages

# requirements.txt 생성
echo -e "scikit-learn\nseaborn==0.11.0\nsquarify==0.4.3\nipykernel\npandas\nnumpy\ndask\ndask-ml\nplotly\npython-kaleido" > requirements.txt

echo "@@ Show package install list"
cat requirements.txt

conda update --all -y
conda install --channel conda-forge --file requirements.txt --yes
conda install -c rapidsai -c nvidia -c conda-forge dask-cuda cudatoolkit=11.2 --yes
conda update --all -y
conda update --all -y

echo "conda setup done."