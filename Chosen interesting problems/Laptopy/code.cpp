#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long

#define f first
#define s second
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int inf=1e18+7;
constexpr int maxn=3e4+7;

//INPUT DATA
ll n,q,d,l,w;
ll k,p;
ll m;

pi convert(int odl)
{
    return {odl/d, odl%d};
}

vector<int>vec[maxn];
vector<int>extra_seats[maxn];//when given number of students to move

int dp[2][maxn];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>q>>d>>l>>w;
    for(int i=1;i<=n;i++)
    {
        cin>>k>>p;
        vec[k].push_back(p);
    }

    for(int i=1;i<=l;i++)
    {
        // cout<<"---------"<<i<<"---------"<<endl;
        vec[i].push_back(-d);
        sort(vec[i].begin(), vec[i].end());
        int N = sz(vec[i]);

        vector<pi>backpack(N);
        for(int j=1;j<N;j++)
        {
            for(int x=j;x>=0;x--)
            {
                backpack[x] = max(backpack[x], {convert(vec[i][j] - (vec[i][j-1] + d) + backpack[x].s).f + backpack[x].f, 0});
                if(x >= 1)
                {
                    pi add = convert(backpack[x-1].s + (vec[i][j] - vec[i][j-1]));
                    backpack[x] = max(backpack[x], {backpack[x-1].f + add.f, add.s});
                }
            }
        }
        for(int x=0;x<N;x++)
        {
            backpack[x].s += w-(vec[i][N-1] + d);
            extra_seats[i].push_back(backpack[x].f + backpack[x].s/d);
        }
    }
    // for(int i=1;i<=l;i++)
    // {
    //     for(auto &u: extra_seats[i])
    //         cout<<u<<' ';
    //     cout<<endl;
    // }

    for(int i=1;i<=l;i++)
    {
        for(int x=0;x<=n;x++)
            dp[i%2][x]=0;
        for(int j=0;j<extra_seats[i].size();j++)
            for(int x=j;x<=n;x++)
                dp[i%2][x] = max(dp[i%2][x], dp[(i-1)%2][x-j]+extra_seats[i][j]);
    }
    // for(int x=0;x<=n;x++)
    //     cout<<dp[l%2][x]<<' ';

    while(q--)
    {
        cin>>m;
        bool possible=0;
        for(ll x=0;x<=n;x++)
        {
            if(dp[l%2][x] >= m+x)
            {
                cout<<x<<'\n';
                possible=1;
                break;
            }
        }
        if(!possible)
            cout<<-1<<'\n';
    }
    return 0;
}