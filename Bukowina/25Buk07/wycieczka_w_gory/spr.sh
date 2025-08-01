g++ brut64.cpp -o brut.e
g++ try.cpp -o try.e
g++ gen.cpp -o gen.e

for i in {1..100}
{
    ./gen.e > test.in;
    ./brut.e < test.in > brut.out;
    ./try.e < test.in > try.out;

    cmp -s brut.out try.out || {
        printf "ERROR\n";
        break;
    }
    printf "OK\n";
}
