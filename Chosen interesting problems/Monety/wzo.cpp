#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=107;
constexpr int inf=1e9+7;

int n;
int tab[maxn];
vector<int> X;

bool is_prime(int x)
{
    if(x<=2) return false;
    for(int i=2;i*i<=x;++i)
        if(x%i==0)
            return false;
    return true;
}

vector<int> group1;
vector<int> group2;
vector<int> vec[maxn];
int rep[maxn];
int vis[maxn];
int turn=1;

bool make_match(int v)
{
    vis[v]=turn;
    for(auto &u: vec[v])
    {
        if(rep[u]==0)
        {
            rep[u]=v;
            return 1;
        }
    }
    for(auto &u: vec[v])
    {
        if(vis[rep[u]]!=turn && make_match(rep[u]))
        {
            rep[u]=v;
            return 1;
        }
    }
    return 0;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>tab[i];

    for(int i=1;i<=n;++i)
    {
        if(!X.empty() && X.back()==tab[i])
            X.pop_back();
        else
            X.pb(tab[i]);
        X.pb(tab[i]+1);
    }

    for(auto &u: X)
    {
        if(u%2==0)
            group1.pb(u);
        else
            group2.pb(u);
    }

    for(int i1=0;i1<sz(group1);++i1)
    {
        for(int i2=0;i2<sz(group2);++i2)
        {
            int u1 = group1[i1];
            int u2 = group2[i2];

            if(is_prime(abs(u2-u1)))
                vec[i1+1].pb(i2+1);
        }
    }

    for(int i=1;i<=sz(group1);++i)
    {
        make_match(i);
        ++turn;
    }
    int connections=0;
    for(int i=1;i<=sz(group2);++i)
        if(rep[i]!=0)
            ++connections;
            
    int solv=connections;

    int free1=sz(group1)-connections;
    int free2=sz(group2)-connections;

    solv+=2*(free1/2); free1%=2;
    solv+=2*(free2/2); free2%=2;

    if(free1==1 && free2==1)
        solv+=3;
    
    cout<<solv<<"\n";
    return 0;
}