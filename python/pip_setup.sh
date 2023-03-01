#!/bin/bash
echo "Current working directory: ${PWD}"
echo "Current python info"
which python # should return /usr/local/bin/python
python --version

# Setup python 3.8.12
pushd /usr/src/
wget -P /usr/src/ https://www.python.org/ftp/python/3.8.12/Python-3.8.12.tgz
tar xvfz Python-3.8.12.tgz
Python-3.8.12/configure
make
sudo make install
popd

python --version

# virtual env 
python3 -3.8 -m venv env_clf
source env_clf/bin/activate

python --version

pip3 install --upgrade pip3
# requirements.txt 생성
echo -e "scikit-learn\nseaborn==0.11.0\nsquarify==0.4.3\nipykernel\npandas\nnumpy\ndask[complete]\ndask-ml[complete]\nplotly\npython-kaleido" > requirements.txt
pip3 install -r requirements.txt
pip3 install dask-cuda

