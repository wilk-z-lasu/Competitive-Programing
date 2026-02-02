g++ wzo.cpp -o wzo.e
g++ brut.cpp -o brut.e 
g++ gen.cpp -o gen.e 
for i in {1..10000}
{
    printf "$i: "
    ./gen.e > test.in;
    ./wzo.e < test.in > wzo.out;
    ./brut.e < test.in > brut.out;
    cmp -s wzo.out brut.out || {
        printf "ERROR\n";
        break;
    }
    printf "OK\n";
}