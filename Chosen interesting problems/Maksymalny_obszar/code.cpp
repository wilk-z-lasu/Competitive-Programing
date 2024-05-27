#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
 
constexpr int maxn=1e6+7;

int n;
int d[maxn];

vector<pair<int,int>>vec;

//Find&Union z wielkością spójnych
int rep[maxn];
int siz[maxn];
//find&union
int Find(int x)
{
    if(rep[x]==x) return x;
    return rep[x]=Find(rep[x]);
}
void Union(int a,int b)
{
    a=Find(a);
    b=Find(b);
    rep[a]=rep[b];
    siz[b]+=siz[a];
}
void prepere()
{
    for(int i=0;i<maxn;i++)
    {
        rep[i]=i;
        siz[i]=1;
    }
}

int solv;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    prepere();
 
    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>d[i];
        vec.push_back({d[i],i});
    }

    sort(vec.begin(), vec.end(), greater<pair<int,int>>());

    for(auto &u: vec)
    {
        int i=u.s;
        if(d[i-1]>=d[i] && Find(i-1)!=Find(i))
            Union(i-1,i);
        if(d[i+1]>=d[i] && Find(i+1)!=Find(i))
            Union(i+1,i);
        solv=max(solv,d[i]*siz[Find(i)]);
    }
    cout<<solv;
    return 0;
}