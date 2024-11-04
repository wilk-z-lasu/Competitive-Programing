#include <bits/stdc++.h>
using namespace std;


constexpr int maxn=2e5+7;
int n,k,r;
int p,q;
int tab[maxn];
int need[maxn];
int have[maxn];
int already_did;

int solv=maxn;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>k>>r;

    for(int i=1;i<=n;i++)
        cin>>tab[i];

    for(int i=1;i<=r;i++)
    {
        cin>>p>>q;
        need[p]=q;
    }

    int i=0;
    for(int j=1;j<=n;j++)
    {
        while(already_did<r && i+1<=n)
        {
            i++;
            if(have[tab[i]]+1==need[tab[i]])
                already_did++;
            have[tab[i]]++;
        }
        if(already_did==r)
            solv=min(solv, i-j+1);
        if(have[tab[j]]==need[tab[j]])
            already_did--;
        have[tab[j]]--;
    }
    if(solv==maxn)
        cout<<"impossible";
    else
        cout<<solv;
    return 0;
}