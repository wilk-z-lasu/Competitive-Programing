#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=500000+7;

int n;
string w;
int P[maxn];
int s;
int v;
int z[maxn];
int sb[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>w;
    n=w.size();
    w="#"+w;

    for(int i=2;i<=n;i++)
    {
        s=P[i-1];
        while(s>0 && w[s+1]!=w[i])
            s=P[s];
        if(w[s+1]==w[i])
            s++;
        P[i]=s;
    }

    for(int i=1;i<=n;i++) z[i]=i;

    for(int i=2;i<=n;i++)
    {
        s=P[i];
        v=sb[s];
        if(s>0 && z[v]>=i-s)
        {
            z[v]=i;
            sb[i]=v;
        }
        else
            sb[i]=i;
    }
    cout<<sb[n];
    return 0;
}