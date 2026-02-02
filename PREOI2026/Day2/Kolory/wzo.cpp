#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=1e5+7;
constexpr int maxq=2e5+7;
constexpr int inf=1e9+7;

int Z;
int n,m,q;
int color[maxn];
vector<int> poz[maxn];

vector<int>L[maxn];
vector<int>R[maxn];
void preproces()
{
    for(int iter=1;iter<=m;++iter)
    {
        L[iter].resize(sz(poz[iter]));
        for(int i=0;i<sz(poz[iter]);++i)
        {
            if(i==0)
                L[iter][i]=0;
            else
                L[iter][i] = L[iter][i-1] + (poz[iter][i] - poz[iter][i-1])*i;
        }

        R[iter].resize(sz(poz[iter]));
        for(int i=sz(poz[iter])-1;i>=0;--i)
        {
            if(i==sz(poz[iter])-1)
                R[iter][i]=0;
            else
                R[iter][i] = R[iter][i+1] + (poz[iter][i+1] - poz[iter][i])*(sz(poz[iter])-1 - i);
        }
    }
}

int solv(int a, int b)
{
    if(sz(poz[a]) > sz(poz[b])) swap(a,b);
    int solv = 0;
    for(auto &x : poz[a])
    {
        auto it = upper_bound(poz[b].begin(), poz[b].end(), x);
        if(it != poz[b].end())
        {
            int ile = poz[b].end() - it;
            solv += (*it-x)*ile + R[b][it - poz[b].begin()];
        }
        
        if(it != poz[b].begin()) 
        {
            --it;
            int ile = it-poz[b].begin()+1;
            solv += (x - *it)*ile + L[b][it - poz[b].begin()];
        }
    }
    return solv;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>Z;
    while(Z--)
    {
        cin>>n>>m>>q;
        for(int i=1;i<=m;++i)
            poz[i].clear();
        for(int i=1;i<=n;++i)
        {
            cin>>color[i];
            poz[color[i]].push_back(i);
        }
        preproces();
        for(int i=1;i<=q;++i)
        {
            int a,b;
            cin>>a>>b;
            cout<<solv(a,b)<<"\n";
        }
    }


    return 0;
}