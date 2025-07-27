#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn = 1e3+7;
constexpr int inf = 1e9+7;


int n;
pi w[maxn];

int Area(pi a, pi b, pi c)
{
    return abs(a.f*(b.s-c.s) + b.f*(c.s-a.s) + c.f*(a.s-b.s));
}

map<pair<pi,int>,vector<int>>m;
map<pi, int>point;
map<pi, int>sum[3][2];
vector<pair<pi, int>>vec;

int Licz(vector<int> N) {
    int odp=0;
    for(int j=0;j<3;++j)
        for(int i=0;i<2;++i)
            sum[j][i].clear();
    sum[0][0][{0,0}]=1;
    for(int i=0;i<sz(N);++i)
    {
        for(int j=i+1;j<sz(N);++j)
        {
            odp += sum[2][0][{3*w[N[i]].f - w[N[j]].f, 3*w[N[i]].s - w[N[j]].s}];
            odp += sum[2][0][{3*w[N[j]].f - w[N[i]].f, 3*w[N[j]].s - w[N[i]].s}];
            odp += sum[2][1][{-w[N[i]].f - w[N[j]].f, -w[N[i]].s - w[N[j]].s}];
        }
        for(int j=1;j>=0;--j)
        {
            vec.clear();
            for(auto &u: sum[j][0])
                vec.pb({u.f, u.s});
            for(auto &u: vec)
            {
                sum[j+1][0][{u.f.f + w[N[i]].f, u.f.s + w[N[i]].s}] += u.s;
                sum[j+1][1][{u.f.f -3*w[N[i]].f, u.f.s -3*w[N[i]].s}] += u.s;
            }
            vec.clear();
            for(auto &u: sum[j][1])
                vec.pb({u.f, u.s});
            for(auto &u: vec)
                sum[j+1][1][{u.f.f + w[N[i]].f, u.f.s + w[N[i]].s}] += u.s;
        }
    }
    return odp;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>w[i].f>>w[i].s;
        point[{w[i].f*(int)3, w[i].s*(int)3}]=i;
    }

    for(int i=1;i<=n;++i)
        for(int j=i+1;j<=n;++j)
        {
            int top = w[i].f-w[j].f;
            int bot = w[i].s-w[j].s;
            if(top==0)
            {
                m[{{inf,1},abs(bot)}].pb(w[i].f);
                continue;
            }
            if(bot==0)
            {
                m[{{-inf,1},abs(top)}].pb(w[i].s);
                continue;
            }

            int dl = top*top+bot*bot;
            if(bot<0)
            {
                top*= -1;
                bot*= -1;
            }

            int GCD = __gcd(abs(top), abs(bot));
            top/=GCD;
            bot/=GCD;
            m[{{top,bot},dl}].pb(w[i].s*top - w[i].f*bot);
        }
    
    int solv=0;
    for(auto &u: m)
    {
        sort(u.s.begin(), u.s.end());
        int prev=0;
        int obc=1;

        for(int i=1;i<sz(u.s);++i)
        {
            if(u.s[i]!=u.s[i-1])
            {
                prev+=obc;
                obc=0;
            }
            ++obc;
            solv += prev;
        }
    }
    solv*=2;
        
    vector<int> All;
    for(int i=1;i<=n;++i)
        All.pb(i);
    solv += Licz(All);
    
    m.clear();
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i==j) continue;
            int top = w[i].f-w[j].f;
            int bot = w[i].s-w[j].s;
            if(top==0)
            {
                m[{{inf,1},w[i].f}].pb(i);
                continue;
            }
            if(bot==0)
            {
                m[{{-inf,1},w[i].s}].pb(i);
                continue;
            }
            if(bot<0)
            {
                top*= -1;
                bot*= -1;
            }

            int GCD = __gcd(abs(top), abs(bot));
            top/=GCD;
            bot/=GCD;

            m[{{top,bot},w[i].s*top - w[i].f*bot}].pb(i);
        }
    }

    for(auto &u: m)
    {
        if(sz(u.s)<4) continue;
        set<int> h;
        for(auto &x: u.s)
            h.insert(x);
        if(sz(h)<4) continue;

        vector<int>h2;
        for(auto &x: h)
            h2.pb(x);
        solv -= Licz(h2);
    }
    cout<<solv;
}