#include <bits/stdc++.h>
using namespace std;

#define int long long

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int maxn=500007;

int N,S;
int tab[maxn];
map<int,vector<int>>M;
vector<int>solv;
set<pi>SET;
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>N>>S;
    for(int i=1;i<=N;++i)
    {
        cin>>tab[i];
        tab[i]++;
    }
    for(int i=1;i<=N;++i)
        tab[i]%=S;
    for(int i=1;i<=N;++i)
        M[tab[i]].pb(i);

    int akt=0;
    int odp=0;
    for(auto &u: M)
        SET.insert({sz(u.s), u.f});

    while(!SET.empty())
    {
        auto it = *(--SET.end());
        if((akt + it.s)%S == S-1)
        {
            if(sz(SET)>1)
                it = *(--(--SET.end()));
        }
        akt+=it.s;
        akt%=S;
        solv.pb(M[it.s].back()); //add element to solution
        M[it.s].pop_back(); //remove added element from map
        
        SET.erase(it); //remove old information
        it.f--;
        if(it.f>0) SET.insert(it); //add new information if it exists
        
        if(akt==S-1 && sz(solv)!=N)
        {
            ++odp;
            akt=0;
        }
    }
    cout<<odp<<'\n';
    for(auto &u: solv)
        cout<<u<<' ';
    return 0;
}