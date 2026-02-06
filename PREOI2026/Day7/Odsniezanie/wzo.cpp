#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=1e6+7;

int N,S;
int Y,X;

vector<int> kol[maxn];
vector<pair<pi,pair<vector<int>, int>>> wyn[maxn];

void get_data()
{
    cin>>N>>S;
    for(int i=1;i<=S;++i)
    {
        cin>>Y>>X;
        kol[X].pb(Y);
    }

    for(int i=1;i<=N;++i)
    {
        if(kol[i].empty()) continue;
        sort(kol[i].begin(), kol[i].end());
        for(int s=0;s<sz(kol[i]);++s)
        {
            int k = s;
            while(k+1 < sz(kol[i]) && kol[i][k]+1 == kol[i][k+1])
                ++k;
            wyn[i].pb({{kol[i][s], kol[i][k]}, {{}, 0}});
            s = k;
        }
    }
}

pi leftH[maxn];
void calculate_left(int p, int k, int column, vector<int>& v)
{
    for(int i=p;i<=k;++i)
    {
        if(leftH[i].s!=column-1) leftH[i] = {1, column};
        else leftH[i] = {leftH[i].f+1, column};
        v[i-p] = leftH[i].f;
    }
}
pi rightH[maxn];
void calculate_right(int p, int k, int column, vector<int>& v)
{
    for(int i=p;i<=k;++i)
    {
        if(rightH[i].s!=column+1) rightH[i] = {1, column};
        else rightH[i] = {rightH[i].f+1, column};
        v[i-p] = rightH[i].f-1;
    }
}

void przelicz()
{
    for(int column=1;column<=N;++column)
    {
        for(auto& x:wyn[column])
        {
            // x.f <-> x.s
            vector<int>solv_pref(sz(x.s.f));
            vector<int>solv_sufi(sz(x.s.f));

            vector<pi> stack;
            for(int i=0;i<sz(x.s.f);++i)
            {
                while(!stack.empty() && stack.back().f >= x.s.f[i])
                    stack.pop_back();
                int Prev = stack.empty() ? -1 : stack.back().s;
                solv_pref[i] = x.s.f[i]*(i-Prev);
                if(Prev >= 0)
                    solv_pref[i] += solv_pref[Prev];
                stack.pb({x.s.f[i], i});
            }

            stack.clear();
            for(int i=sz(x.s.f)-1;i>=0;--i)
            {
                while(!stack.empty() && stack.back().f >= x.s.f[i])
                    stack.pop_back();
                int Next = stack.empty() ? sz(x.s.f) : stack.back().s;
                solv_sufi[i] = x.s.f[i]*(Next-i);
                if(Next < sz(x.s.f))
                    solv_sufi[i] += solv_sufi[Next];
                stack.pb({x.s.f[i], i});
            }
            int maxi = 0;
            for(int i=0;i<sz(x.s.f);++i)
                maxi = max(maxi, solv_pref[i]+solv_sufi[i]-x.s.f[i]);
            x.s.s += maxi;
        }
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    get_data();

    for(int column=1;column<=N;++column)
    {
        for(auto& x:wyn[column])
        {
            // x.f <-> x.s
            x.s.f.resize(x.f.s-x.f.f+1);
            calculate_left(x.f.f, x.f.s, column, x.s.f);
        }
    }
    przelicz();

    for(int column=N;column>=1;--column)
    {
        for(auto& x:wyn[column])
        {
            // x.f <-> x.s
            x.s.f.resize(x.f.s-x.f.f+1);
            calculate_right(x.f.f, x.f.s, column, x.s.f);
        }
    }
    przelicz();

    // for(int column=1;column<=N;++column)
    // {
    //     cout<<"---- "<<column<<" ----\n";
    //     for(auto& x:wyn[column])
    //     {
    //         // x.f <-> x.s
    //         cout<<x.f.f<<" <-> "<<x.f.s<<" : ";
    //         for(auto &u: x.s.f)
    //             cout<<u<<" ";
    //         cout<<"\n";
    //     }
    // }

    int odp = 0;
    for(int column=1;column<=N;++column)
    {
        for(auto& x:wyn[column])
        {
            // x.f <-> x.s
            odp = max(odp, x.s.s);
        }
    }
    
    cout<<odp<<"\n";
    return 0;
}