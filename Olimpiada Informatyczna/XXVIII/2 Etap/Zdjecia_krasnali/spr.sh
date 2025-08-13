# take into consideration there are multiple correct outputs, but You can check TAK/NIE part of output
g++ wzo.cpp -o wzo.e 
g++ brut.cpp -o brut.e 
g++ gen.cpp -o gen.e 

for i in {1..100}
{
    ./gen.e > test.in;
    ./wzo.e < test.in > wzo.out;
    ./brut.e < test.in > brut.out;

    printf "$i: ";
    cmp -s brut.out wzo.out || {
        printf "ERROR\n";
        break;
    }
    printf "OK\n";
}