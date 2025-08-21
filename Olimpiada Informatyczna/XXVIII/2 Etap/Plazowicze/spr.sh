g++ try.cpp -o try.e
g++ wzo.cpp -o wzo.e
g++ gen.cpp -o gen.e

for i in {1..100}
{
    printf "$i: ";
    ./gen.e > test.in;
    ./wzo.e < test.in > wzo.out;
    ./try.e < test.in > try.out;

    cmp -s wzo.out try.out || {
        printf "ERROR\n";
        break;
    }
    printf "OK\n";
}