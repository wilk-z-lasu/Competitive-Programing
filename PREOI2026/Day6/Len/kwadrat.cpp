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

int inwersje[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i = 1; i <= n; ++i)
        cin>>tab[i];
    
    for(int i=1;i<=n;++i)
    {
        for(int j=i+1;j<=n;++j)
        {
            if(tab[i]>tab[j])
                inwersje[i]++;
        }
    }

    int solv=0;
    int start=n;
    while(start>0)
    {
        if(inwersje[start]>1)
        {
            int tmp=start;
            while(inwersje[tmp]>1)
            {
                ++solv;
                if(tab[tmp]<tab[tmp+1])
                    inwersje[tmp+1]++;
                else
                    inwersje[tmp]--;
                swap(tab[tmp],tab[tmp+1]);
                swap(inwersje[tmp],inwersje[tmp+1]);
                tmp++;
            }
        }
        else
            start--;
    }
    cout << solv;
    return 0;
}