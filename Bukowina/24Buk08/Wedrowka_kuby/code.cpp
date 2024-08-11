#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=4e3+7;
constexpr int inf=1e9+7;


int n,m;
int a,b;
char c;

vector<pair<pair<int,int>,int>>vec;

int odl[maxn];
bool belman()
{
    for(int i=1;i<=n;i++)
        odl[i]=inf;
    odl[1]=0;
    for(int tura=1;tura<=n-1;tura++)
        for(auto &u: vec)
            odl[u.f.s]=min(odl[u.f.s], odl[u.f.f]+u.s);
    for(auto &u: vec)
        if(odl[u.f.s] > odl[u.f.f]+u.s)
            return 1;
    return 0;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;

    for(int i=1;i<=m;i++)
    {
        cin>>a>>b>>c;
        if(c=='(')
            vec.push_back({{a,b},1});
        else
            vec.push_back({{a,b},-1});
    }

    bool minus=belman();
    for(auto &u: vec)
        u.s=-u.s;
    bool plus=belman();

    if((minus^plus)==0)
        cout<<"TAK";
    else
        cout<<"NIE";
    return 0;
}