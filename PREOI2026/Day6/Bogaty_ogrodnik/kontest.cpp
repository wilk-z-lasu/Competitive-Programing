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

int n,m;
priority_queue<int>Free;
priority_queue<int>Used;
char tab[maxn];

int last_Used[maxn];

vector<pi>C;
vector<pi>Z;
int rep[maxn];

int pot(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1) res=(res*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return res;
}
int silnia[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    silnia[0]=1;
    for(int i=1;i<maxn;++i)
        silnia[i]=(silnia[i-1]*i)%mod;

    cin>>n>>m;
    for(int i=1;i<=m;++i)
        cin>>tab[i];
    for(int i=1;i<=n;++i)
        Free.push(i);
    
    int solv1=0;

    int akt_do=0;
    int akt_wait=0;

    tab[0]=tab[1];
    for(int i=1;i<=m;++i)
    {
        rep[i]=sz(C);
        
        if(tab[i]!=tab[i-1])
        {
            if(tab[i-1]=='C')
                C.pb({akt_do,akt_wait});
            else
                Z.pb({akt_do,akt_wait});
            akt_do=0;
            akt_wait=0;
        }
        if(tab[i]=='C')
        {
            if(!Free.empty())
            {
                ++akt_do;
                int x=Free.top();
                Free.pop();
                Used.push(x);
                last_Used[x]=i;
            }
            else
                ++akt_wait;
        }
        if(tab[i]=='Z')
        {
            if(!Used.empty())
            {
                ++akt_do;
                int x=Used.top();
                solv1+=x;
                Used.pop();
                Free.push(x);
            }
            else
                ++akt_wait;
        }
    }
    if(tab[m]=='C')
        C.pb({akt_do,akt_wait});
    else
        Z.pb({akt_do,akt_wait});
    
    while(!Used.empty())
    {
        int x=Used.top();
        Used.pop();

        int poz = last_Used[x];
        C[rep[poz]].f--;
        C[rep[poz]].s++;
        // cout<<x<<" "<<last_Used[x]<<endl;
    }
    int solv2=1;
    for(auto x:C)
    {
        // cout<<"Debug: "<<x.f<<' '<<x.s<<'\n';
        solv2 = (solv2*silnia[x.f+x.s])%mod;
        solv2 = (solv2*pot(silnia[x.s],mod-2))%mod;
    }
    for(auto x:Z)
    {
        // cout<<"Debug: "<<x.f<<' '<<x.s<<'\n';
        solv2 = (solv2*silnia[x.f+x.s])%mod;
        solv2 = (solv2*pot(silnia[x.s],mod-2))%mod;
    }
    if(solv1==0) solv2=1;
    cout<<solv1<<' '<<solv2<<'\n';
    return 0;
}