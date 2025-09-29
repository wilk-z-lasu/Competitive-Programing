#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)A.size()

constexpr int maxn = 1e5+7;
constexpr int mod = 1e9+7;

int N;
int H[maxn], W[maxn];
int R[maxn];
int L[maxn];

vector<pair<int,pi>>vec;

int prefix[maxn];
void prepere_prefix()
{
    prefix[0] = 0;
    for(int i=1;i<=N;++i)
        prefix[i] = (prefix[i-1]+W[i])%mod;
}
int get_sum(int a, int b)
{
    return (prefix[b]-prefix[a-1]+mod)%mod;
}

int solv = 0;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>N;
    for(int i=1;i<=N;++i)
        cin>>H[i];
    for(int i=1;i<=N;++i)
        cin>>W[i];

    vector<int>S;
    for(int i=1;i<=N+1;++i)
    {
        while(!S.empty() && H[S.back()]>H[i]) 
        {
            R[S.back()] = i-1;
            S.pop_back();
        }
        S.pb(i);
    }
    for(int i=N;i>=0;--i)
    {
        while(!S.empty() && H[S.back()]>=H[i]) 
        {
            L[S.back()] = i+1;
            S.pop_back();
        }
        S.pb(i);
    }

    prepere_prefix();
    for(int i=1;i<=N;++i)
    {
        int l = L[i];
        int r = R[i];

        int width1 = get_sum(l, i-1);
        int width2 = get_sum(i+1, r);

        int Width = 0;
        Width += width1 * width2;
        Width %= mod;
        Width += width1 * W[i];
        Width %= mod;
        Width += width2 * W[i];
        Width %= mod;
        Width += W[i] * (W[i] + 1) / 2;
        Width %= mod;
        int Hight = H[i]*(H[i]+1)/2;
        Hight %= mod;
        solv += (Width * Hight)%mod;
        solv %= mod;
    }
    cout<<solv;
    return 0;
}