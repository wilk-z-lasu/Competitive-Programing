#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
 
int n,k,q;
int a,b;

map<int,pair<int,int>>m;

void mark(int v, int cost=0)
{
    // cout<<"v: "<<v<<' '<<cost<<endl;
    m[v]={cost,q};
    int ansestor=(v - 2) / k + 1;
    if(ansestor != v) mark(ansestor, cost + 1);
}
int solv(int v, int cost=0)
{
    // cout<<"s: "<<v<<' '<<cost<<endl;
    if(m.find(v)!=m.end() && m[v].s==q) return cost + m[v].f;
    else return solv((v - 2) / k + 1, cost + 1);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    cin>>n>>k>>q;

    if(k==1)
    {
        while(q--)
        {
            cin>>a>>b;
            cout<<abs(a-b)<<'\n';
        }
        return 0;
    }
    
    while(q--)
    {
        cin>>a>>b;
        mark(a);
        cout<<solv(b)<<'\n';
    }
    return 0;
}