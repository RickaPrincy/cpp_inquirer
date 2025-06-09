#! /bin/bash
git clone -b v0.0.1 https://github.com/RickaPrincy/cpp_inquirer 
cd cpp_inquirer 
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .
sudo make install
cd ../..
rm -rf cpp_inquirer 
