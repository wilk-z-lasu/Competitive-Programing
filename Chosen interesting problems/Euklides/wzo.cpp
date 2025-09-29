#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long

#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)A.size()

constexpr int maxn=1e6+7;

int dziel[maxn];
void sito()
{
    for(int i=2;i<maxn;++i)
        if(dziel[i]==0)
            for(int j=2*i;j<maxn;j+=i)
                dziel[j]=i;
}
int n,p;
int A[maxn];
// vector<pi> B[maxn];
vector<int>C[maxn];
ll solv=1;
int pot(int x, int k)
{
    int odp = 1;
    while(k)
    {
        if(k&1) 
            odp = ((ll)odp * x) % p;
        x = ((ll)x * x) % p;
        k /= 2;
    }
    return odp;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>p;
    for(int i=1;i<=n;++i)
        cin>>A[i];

    sito();
    for(int i=1;i<=n;++i)
    {
        int x=A[i];
        while(dziel[x]!=0)
        {
            int ile = 0;
            int d = dziel[x];
            while(x%d==0)
            {
                ile++;
                x/=d;
            }
            // B[i].pb({d, ile});
            C[d].pb(ile);
        }
        if(x>1)
        {
            // B[i].pb({x, 1});
            C[x].pb(1);
        }

    }
    for(int j = 2; j < maxn; ++j)
    {
        vector<int> &u = C[j];
        sort(u.begin(), u.end(), greater<int>());
        int m = sz(u);
        for(int i=0;i<m;++i)
            solv = (solv * pot(pot(j, u[i]), i)) % p;
    }
    cout<<solv;
    return 0;
}