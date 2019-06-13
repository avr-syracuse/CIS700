# Ensembler
Ensembler is a tool designed to read in multiple (2 or more) classifier perdition csv files and make a single voted output file.

## Build
the program is a single file with no dependancies and can be built via cmake or command line very easily
### Cmake Build
```BASH
$ mkdir build
$ cd build
$ cmake ..
$ make 
```
### g++ direct build
```BASH
$ g++ ensembler_main.cpp -o Ensembler
```

## Arguments
### -i <path to input file>
this can be repeated multiple time until all files are added
### -o <path to directory to write output csv>
Directory path to write the resulting output file
### -w x
[Optional] when used will read the weight value in the second column of the csv file on an instance-by-instance basis
this value is used as classifiers voting weight.