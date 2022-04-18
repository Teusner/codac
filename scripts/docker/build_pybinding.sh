#!/bin/bash

set -e -x

cd /io
for PYBIN in /opt/python/cp3*/bin; do
  
  #if [ "${PYBIN}" = "/opt/python/cp310-cp310/bin" ]; then
  #  continue
  #fi

  "${PYBIN}/python" -m pip install --upgrade pip
  #"${PYBIN}/python" -m pip install --upgrade pyibex
  #"${PYBIN}/python" -m pip install pyibex==1.9.2
  mkdir -p build_dir && cd build_dir
  cmake -DPYTHON_EXECUTABLE=${PYBIN}/python -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON -DWITH_TUBE_TREE=OFF -DWITH_CAPD=OFF -DWITH_PYTHON=ON -DCMAKE_CXX_FLAGS="-fPIC" ..
  make api
  # Again for doxygen2docstring:
  cmake -DPYTHON_EXECUTABLE=${PYBIN}/python -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON -DWITH_TUBE_TREE=OFF -DWITH_CAPD=OFF -DWITH_PYTHON=ON -DCMAKE_CXX_FLAGS="-fPIC" ..
  make -j2

  #make test ARGS="-V"s
  make pip_package
  echo "copy wheel and clean build_dir"
  for whl in *.whl; do
    auditwheel repair "$whl" -w /io/wheelhouse/
  done
  
  "${PYBIN}/python" -m pip install codac --no-deps --no-index -f /io/wheelhouse
  #(cd "$HOME"; "${PYBIN}/python" -m unittest discover codac.tests)
  cd /io
  rm -fr build_dir

done