#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=2e5+7;
constexpr int mod=1e9+7;

int n;
int tab[maxn];
int tmp_tab[maxn];

int inwersje[maxn];
bool check()
{
    for(int i=1;i<=n;++i)
        inwersje[i]=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=i+1;j<=n;++j)
        {
            if(tmp_tab[i]>tmp_tab[j])
                inwersje[i]++;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(inwersje[i]>1)
            return false;
    }
    return true;
}


int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i = 1; i <= n; ++i)
        cin>>tab[i];

    int solv = n*n+7;
    for(int mask=0;mask<pow(n,10);++mask)
    {
        int tmp=mask;
        for(int i=1;i<=n;++i)
            tmp_tab[i]=tab[i];
        int moves=0;
        for(int i=1;i<=n*n;++i)
        {
            int ruch = tmp%n;
            tmp/=n;
            if(ruch==0) continue;
            moves++;
            swap(tmp_tab[ruch],tmp_tab[ruch+1]);
            // cout<<"Swap "<<ruch<<" "<<ruch+1<<"\n";
        }
        if(check())
            solv = min(solv,moves);
    }
    cout<<solv;
    return 0;
}