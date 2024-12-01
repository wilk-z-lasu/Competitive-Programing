#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=200*200+7;
int n,m;
int a,b;

int nr(int x, int y)
{
    return (y-1)*n + x;
}

bool check(int val)
{
    if(val < 1 || val>n) return 0;
    else return 1;
}

bool blocked[207][207];

vector<int>vec[maxn];

int timer=0;
int partner[maxn];
int vis[maxn];

bool connect(int v)
{
    vis[v]=timer;
    for(auto &u: vec[v])
    {
        if(partner[u]==0)
        {
            partner[u]=v;
            return true;
        }
    }

    for(auto &u: vec[v])
    {
        if(vis[partner[u]]!=timer && connect(partner[u]))
        {
            partner[u]=v;
            return true;
        }
    }
    return false;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>a>>b;
        blocked[a][b]=1;
    }

    for(int y=1;y<=n;y++)
    {
        for(int x=1;x<=n;x++)
        {
            if(blocked[x][y]) continue;
            for(int add1: {-1,-2,1,2})
            {
                for(int add2: {-1,-2,1,2})
                {
                    if(abs(add1)==abs(add2)) continue;
                    if(check(y+add1) && check(x+add2) && !blocked[x+add2][y+add1])
                    {
                        vec[nr(x,y)].push_back(nr(x+add2, y+add1));
                        // cout<<nr(x,y)<<" -> "<<nr(x+add2, y+add1)<<endl;
                    }
                }
            }
        }
    }

    for(int y=1;y<=n;y++)
    {
        for(int x=1;x<=n;x++)
        {
            if((x+y)%2==0)
            {
                timer++;
                connect(nr(x,y));
            }
        }
    }

    int max_matching=0;
    for(int y=1;y<=n;y++)
        for(int x=1;x<=n;x++)
            if((x+y)%2==1 && partner[nr(x,y)]!=0)
                max_matching++;
    // cout<<n*n<<" - "<<m<<" - "<<max_matching<<endl; 
    cout<<n*n - m - max_matching;
    return 0;
}