# halide-SSCAL


To run the sctipt correctly :

1- suppsose that the script is in /Myfolder/ and Halide binaries is in /Myfolder/halide/

2- run the commande : g++ exo.cpp -g -fpermissive -I ./halide/include -L ./halide/bin -lHalide -lpthread -ldl -o exo -std=c++11

3- run the commande : LD_LIBRARY_PATH=./halide/bin ./exo
