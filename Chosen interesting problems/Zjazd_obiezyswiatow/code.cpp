#include<bits/stdc++.h>
using namespace std;

#define int long long

constexpr int maxn = 250+7;

int n,m,k;
int a,b;
int s[maxn];

struct matrix
{
    vector<vector<bool>>m;
    void make() { //make sure matrx is cleaned
        m.resize(maxn);
        for(int i=0;i<maxn;++i)
            m[i].resize(maxn);
        for(int i=0;i<maxn;++i)
            for(int j=0;j<maxn;++j)
                m[i][j]=0;
    }
    matrix operator *(matrix& x) { //fast matrix multiplying in n^3/64
        matrix odp;
        odp.make();
        bitset<maxn>A[maxn];
        bitset<maxn>B[maxn];

        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                A[i][j] = m[i][j];
                B[i][j] = x.m[j][i];
            }
        }
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                if((A[i]&B[j]).any())
                    odp.m[i][j]=1;
        return odp;
    }

    void wypisz() { //for debug reasons
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
                cout<<m[i][j]<<' ';
            cout<<endl;
        }
    }
    
} vec;

matrix sym(matrix a, int p)
{
    matrix odp;
    odp.make();
    for(int i=1;i<=n;++i)
        odp.m[i][i]=1;
    while(p)
    {
        if(p&1)
            odp = odp* a;
        a = a*a;
        p/=2;
    }
    return odp;
} 

int vis[maxn];
bool check(int mid)
{
    matrix odp = sym(vec, mid);
    for(int i=1;i<=n;++i)
        vis[i]=0;

    for(int i=1;i<=k;++i)
        for(int j=1;j<=n;++j)
            if(odp.m[s[i]][j])
                ++vis[j];

    for(int i=1;i<=n;++i)
        if(vis[i]==k)
            return 1;
    return 0;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

    cin>>n>>m>>k;

    for(int i=1;i<=k;++i)
        cin>>s[i];

    vec.make();
    for(int i=1;i<=m;++i)
    {
        cin>>a>>b;
        vec.m[a][b]=1;
    }

    int l=0; int r = n*n; int mid;
    while(l<r)
    {
        mid = (l+r)/2;
        if(check(mid))//possible
            r=mid;
        else//not possoible
            l=mid+1;
    }

    //print solution
    if(l == n*n)
        cout<<"NIE\n";
    else
    {
        cout<<"TAK\n";
        cout<<l<<'\n';
    }
    return 0;
}