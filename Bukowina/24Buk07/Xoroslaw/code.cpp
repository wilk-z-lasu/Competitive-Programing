#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=100000+7;
constexpr int inf=1e9+7;

constexpr int LOG=31;

int n;
int a;

map<int,int>input;

priority_queue<pair<pair<int,int>,int>>pq;

pair<int,int> xor_base[LOG];

int significant_bit(int x)
{
    int odp=0;
    while (x >>= 1)
        odp++;
    return odp;
}

void wrzuc_do_bazy(int val, int time, int curent_time)
{
    if(val==0) return;

    int msc = significant_bit(val);
    if(xor_base[msc].f==0 || xor_base[msc].s<curent_time)
    {
        xor_base[msc]={val,time};
        return;
    }
    if(time > xor_base[msc].s)
    {
        pair<int,int> tmp_base=xor_base[msc];
        xor_base[msc]={val,time};
        val=tmp_base.f;
        time=tmp_base.s;
    }
    val^=xor_base[msc].f;
    wrzuc_do_bazy(val,time,curent_time);
}

int odp_z_bazy(int time)
{
    int odp=0;
    for(int i=LOG-1; i>=0; i--)
    {
        if(xor_base[i].s <= time)
        {
            xor_base[i]={0,0};
            continue;
        }

        if((odp^xor_base[i].f) > odp)
            odp^=xor_base[i].f;
    }
    return odp;
}


int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a;
        if(a>0)
            input[a]=i;
        else
        {
            // input[-a] - i a
            int p=input[-a];
            int k=i;
            int val=-a;
            pq.push({{-p,-k},val});
            pq.push({{-k,0},0});
            input.erase(-a);
        }
    }

    for(auto &u: input)
        pq.push({{-u.s,-inf},u.f});

    while(!pq.empty())
    {
        auto top = pq.top();
        pq.pop();

        wrzuc_do_bazy(top.s, -top.f.s, -top.f.f);

        cout<<odp_z_bazy(-top.f.f)<<'\n';
    }

    return 0;
}