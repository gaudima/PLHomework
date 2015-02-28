#Conway's Game of Life

##Dependencies:
To compile this application you will need to install **SFML v2.1 (it is important)** and its dependencies.

###On Ubuntu:
Simply type `sudo apt-get install libsfml-dev` in terminal.

###On Windows:
You can [download SFML v2.1](http://www.sfml-dev.org/download/sfml/2.1/) and put it in `./SFML` folder, or put it anywhrere else and launch **cmake** with `-DSFML_ROOT=path_to_sfml`

##Compilation

###On Ubuntu
```
mkdir build
cd build
cmake ..
make
```

###On Windows (MinGW)
```
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
```
 