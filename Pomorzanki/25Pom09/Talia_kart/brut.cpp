#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define ld long double

#define pi pair<int,int>
#define f first
#define s second
#define pb push_back
#define sz(A) (int)A.size()

constexpr int inf = 1e9+7;
constexpr int maxn = 17;

int n;
char C[maxn];
int R[maxn];
int B[maxn];
vector<int>vec;
int solv = inf;

int f(vector<int> &x)
{
    int hR=0;
    int hB=0;
    int costR=0, costB=0;
    for(auto &i: x)
    {
        costR += max((int)0, R[i] - hR);
        costB += max((int)0, B[i] - hB);
        if(C[i]=='R')
            ++hR;
        else
            ++hB;
    }
    return n+max(costR, costB);
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>C[i]>>R[i]>>B[i];
    
    for(int i=1;i<=n;++i)   
        vec.pb(i);

    do 
    {
        solv = min(solv, f(vec));
    }
    while (std::next_permutation(vec.begin(), vec.end()));
    cout<<solv;
    return 0;
}