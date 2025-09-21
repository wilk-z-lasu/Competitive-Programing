//works for 50/100 points, because it doesn't have BIG numbers implementation
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long A; // number of offers
    if(!(cin >> A)) return 0;
    long long B,C,D; // minimal price thresholds in respective units
    cin >> B >> C >> D;
    long long threshold = max({B, 2*C, 100*D});

    long long bestValue = -1; // in spinacze
    for(long long i=0;i<A;i++){
        long long N,K,L; // N spinaczy, K ziaren, L gabek
        cin >> N >> K >> L;
        long long value = N + 2*K + 100*L; // convert everything to spinacze
        if(value % 6 == 0 || value % 7 == 0) continue; // skip divisible by 6 or 7
        if(value > threshold){
            if(value > bestValue) bestValue = value;
        }
    }

    if(bestValue == -1){
        cout << "Brak opłacalnych ofert\n";
        return 0;
    }

    long long g = bestValue / 100; // gabki
    long long rem = bestValue % 100;
    long long z = rem / 2; // ziarna
    long long s = rem % 2; // spinacze

    // Output order: spinacze, ziarna, gabki (minimal total count representation)
    cout << s << ' ' << z << ' ' << g << '\n';
    return 0;
}
