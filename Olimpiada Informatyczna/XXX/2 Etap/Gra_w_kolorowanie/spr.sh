g++ wzo.cpp -o wzo.e 
g++ brut.cpp -o brut.e 
g++ gen.cpp -o gen.e 

for i in {1..1000}
{
    ./gen.e > test.in;
    ./wzo.e < test.in > wzo.out;
    ./brut.e < test.in > brut.out;

    printf "$i: ";
    cmp -s wzo.out brut.out || {
        printf "Error\n";
        break;
    }
    printf "OK\n";
}
