# Project generated with [Templi](https://github.com/RickaPrincy/Templi)

#cpp_inquirer :memo:

C++ inquirer

# Installation :seedling:

- Archlinux

```bash
yay -Sy cpp_inquirer 
```
For the moment, you have to build templi to use it if you use another system (not archlinux)

- Dependancies
    - CMake (Version 3.18 or later)
    - C++ Compiler with C++17 support

- Build manually

```bash
git clone -b v0.0.1 https://github.com/RickaPrincy/cpp-inquirer 

cd cpp_inquirer 

mkdir build

cd build

cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .

sudo make install
```
#### :warning: If some libs are not found after building manually

Identify the installation path of the missing library. For example, let's assume the library is installed in `/usr/local/lib` (on linux it should be there).

If you are using Linux, add the following code to your `~/.zshrc` or `~/.bashrc` based on what you use (replacing `/usr/local/lib` with the actual installation path):

```bash
export LD_LIBRARY_PATH=/usr/local/lib:\$LD_LIBRARY_PATH
```

# Create tar release to pin on your release
```bash
cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build

# a scripts create_release.sh will be created
chmod +x create_release.sh 
create_release
# a release folder will be created
```
