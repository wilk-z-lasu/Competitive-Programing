#include <bits/stdc++.h>
using namespace std;
// #define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)(A.size())

constexpr int maxn=1e6+7;

int n;

int up[maxn];
int paid[maxn];
int start;

vector<int>vec[maxn];

bool allowed[maxn];
bool used[maxn];
vector<int>p;

void allow(int v) {
    int ile=0;
    int next=0;
    for(auto &u: vec[v])
    {
        if(paid[u]==0)
        {
            next=u;
            ile++;
        }
    }
    if(ile==1)
    {
        allowed[next]=1;
        allow(next);
    }
}

void preproces() {
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>up[i]>>paid[i];
        if(up[i]==i) start=i;
        else vec[up[i]].pb(i);
    }
    paid[start]=n;
    for(int i=1;i<=n;++i)
        used[paid[i]]=1;
    for(int i=n;i>=1;--i)
        if(!used[i])
            p.pb(i);
    for(int i=1;i<=n;++i)
        if(paid[i]!=0)
            allowed[i]=1;
    for(int i=1;i<=n;++i)
        if(paid[i]!=0)
            allow(i);
}
//TO JEST GIT ^^^^^^^^

vector<pi>e;
int where[maxn];
bool blocked_num[maxn];

int licz(int v)
{
    int odp=1;
    for(auto &u: vec[v])
        if(paid[u]==0)
            odp += licz(u);
    return odp;
}

void oznacz(int num) {
    for(int i=1;i<=num;++i)
        blocked_num[p[sz(p)-i]]=1;
}

void koloruj(int v)
{
    for(auto &u: vec[v])
        if(paid[u]==0)
            koloruj(u);
    if(paid[v]==0)
    {
        paid[v]=p.back();
        p.pop_back();
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    
    preproces();

    for(int i=1;i<=n;++i)
    {
        if(paid[i]!=0)
        {
            int l = licz(i) - 1;
            if(l!=0)
            {
                e.pb({paid[i], l});
                where[paid[i]]=i;
            }
        }
    }

    sort(e.begin(), e.end());
    for(auto &u: e)
    {
        int limit = u.f;
        int num = u.s;

        int last=sz(p);
        while(last-1>=0 && p[last-1] < limit)
            last--;

        int p_num = sz(p)-last;

        if(p_num == num)
            koloruj(where[limit]);
        else if(p_num > num)
        {
            oznacz(p_num);
            koloruj(where[limit]);
        }
    }

    for(int i=1;i<=n;++i)
    {
        if(!blocked_num[paid[i]] && allowed[i]) // <- I can get deterministic answers on simple paths with one possible answer 
            cout<<paid[i]<<'\n';
        else
            cout<<0<<'\n';
    }
    return 0;
}