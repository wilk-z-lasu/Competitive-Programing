#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long

constexpr int mod = 1001;
constexpr int inf = 1e19;

int N,D,A,B;
unordered_map<int,int> memory;
inline int solv(int n)
{
    if(n == 1) return 0;
    if(memory.find(n)!=memory.end())
        return memory[n];

    int a=n/2;
    int b=n-a;

    int odp = inf;
    while(a>0 && b-a <= D)
    {
        odp = min(odp, solv(a) + solv(b) + min((a*A + b*B)%mod, (b*A + a*B)%mod));
        --a; ++b;
    }
    return memory[n]=odp;
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>N>>D>>A>>B;
    cout<<solv(N);
}