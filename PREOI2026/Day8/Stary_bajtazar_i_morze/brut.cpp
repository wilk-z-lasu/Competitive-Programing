#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=1507;

int n,m,q;
char znak[maxn][maxn];

int cord_to_id(int y, int x)
{
    if(x<1 || x>m || y<1 || y>n) return 0;
    return (y-1)*m+x;
}

constexpr int maxi=maxn*maxn;
int Next[maxi];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            cin>>znak[i][j];
            int v=cord_to_id(i,j);
            int u;
            if(znak[i][j]=='^')
            {
                u = cord_to_id(i-1,j);
            }
            else if(znak[i][j]=='v')
            {
                u = cord_to_id(i+1,j);
            }
            else if(znak[i][j]=='>')
            {
                u = cord_to_id(i,j+1);
            }
            else if(znak[i][j]=='<')
            {
                u = cord_to_id(i,j-1);
            }

            Next[v] = u;
        }
    }
    cin>>q;
    for(int iter=1;iter<=q;++iter)
    {
        int a,b,c,d;
        char Z;
        cin>>a>>b>>c>>d>>Z;
        int v=cord_to_id(a,b);
        int x=cord_to_id(c,d);
        int z;
        if(Z=='^')
            z = cord_to_id(c-1,d);
        else if(Z=='v')
            z = cord_to_id(c+1,d);
        else if(Z=='>')
            z = cord_to_id(c,d+1);
        else if(Z=='<')
            z = cord_to_id(c,d-1);

        int last = Next[x];
        Next[x] = z;

        int k = n*m+1;
        int ruchy=0;
        while(k--)
        {
            if(v==0)
                break;
            v = Next[v];
            ruchy++;
        }
        if(v==0)
            cout<<ruchy<<"\n";
        else
            cout<<"0\n";
        Next[x] = last;
    }
    return 0;
}