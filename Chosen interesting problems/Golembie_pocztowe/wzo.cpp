#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define f first
#define s second

constexpr int maxn=1e6+7;

int n;
int mx,my;
int x,y;

//.f=x .s=y
set<pair<int,int>>pg;
set<pair<int,int>>lg;
set<pair<int,int>>ld;
set<pair<int,int>>pd;
//.f=y .s=x
vector<pair<int,int>>pg_vec;
vector<pair<int,int>>lg_vec;
vector<pair<int,int>>ld_vec;
vector<pair<int,int>>pd_vec;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    cin>>mx>>my;
    for(int i=1;i<=n;i++)
    {
        cin>>x>>y;
        x-=mx;
        y-=my;
        if(x>0 && y>0)
            pg_vec.push_back({-y,x});
        if(x<0 && y>0)
            lg_vec.push_back({-y,-x});
        if(x<0 && y<0)
            ld_vec.push_back({y,-x});
        if(x>0 && y<0)
            pd_vec.push_back({y,x});
    }

    sort(pg_vec.begin(),pg_vec.end(),greater<pair<int,int>>());
    sort(lg_vec.begin(),lg_vec.end(),greater<pair<int,int>>());
    sort(ld_vec.begin(),ld_vec.end(),greater<pair<int,int>>());
    sort(pd_vec.begin(),pd_vec.end(),greater<pair<int,int>>());

    // cout<<"pg\n";
    for(auto u:pg_vec)
    {
        // cout<<u.f<<" "<<u.s<<endl;
        pg.insert({u.s,u.f});
        auto wzk = pg.lower_bound({u.s,u.f});
        if(wzk!=pg.begin())
        {
            wzk--;
            pg.erase(wzk);
        }
    }
    // cout<<"lg\n";
    for(auto u:lg_vec)
    {
        // cout<<u.f<<" "<<u.s<<endl;
        lg.insert({u.s,u.f});
        auto wzk = lg.lower_bound({u.s,u.f});
        if(wzk!=lg.begin())
        {
            wzk--;
            lg.erase(wzk);
        }
    }
    // cout<<"ld\n";
    for(auto u:ld_vec)
    {
        // cout<<u.f<<" "<<u.s<<endl;
        ld.insert({u.s,u.f});
        auto wzk = ld.lower_bound({u.s,u.f});
        if(wzk!=ld.begin())
        {
            wzk--;
            ld.erase(wzk);
        }
    }
    // cout<<"pd\n";
    for(auto u:pd_vec)
    {
        // cout<<u.f<<" "<<u.s<<endl;
        pd.insert({u.s,u.f});
        auto wzk = pd.lower_bound({u.s,u.f});
        if(wzk!=pd.begin())
        {
            wzk--;
            pd.erase(wzk);
        }
    }
    cout<<pd.size()+ld.size()+lg.size()+pg.size();

    return 0;
}