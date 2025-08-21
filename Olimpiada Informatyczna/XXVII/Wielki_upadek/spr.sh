#!/bin/bash
# Sprawdzarka dla checker.cpp i brut.cpp
# Kompiluje, generuje testy, uruchamia i porównuje wyniki

g++ checker.cpp -o checker.e || { echo "Błąd kompilacji checker.cpp"; exit 1; }
g++ brut.cpp -o brut.e || { echo "Błąd kompilacji brut.cpp"; exit 1; }
g++ gen.cpp -o gen.e || { echo "Błąd kompilacji gen.cpp"; exit 1; }

for i in {1..1000}
do
    ./gen.e > test.in
    ./checker.e < test.in > checker.out
    ./brut.e < test.in > brut.out

    printf "$i: "
    cmp -s checker.out brut.out || {
        printf "Error\n"
        break
    }
    printf "OK\n"
done
