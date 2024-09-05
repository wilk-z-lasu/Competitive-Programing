//no idea how to get P in f() in linear time
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=2e5+7;
constexpr int inf=1e9+7;

int n,q;
int x[maxn];
int a,b;

constexpr int LOG=19;
int up[maxn][LOG];
void make_bin_lifting()
{
    for(int jump=1; jump<LOG; jump++)
        for(int i=1;i<=n+1;i++)
            up[i][jump] = up[up[i][jump-1]][jump-1];
}

int pref[maxn];
inline int get_sum(int p, int k)
{
    return pref[k]-pref[p-1];
}

int pref_tree[maxn];
vector<pair<int,int>>largest;
void add(int war, int poz)
{
    while(largest.back().f <= war)
        largest.pop_back();
    // cout<<poz<<" -> "<<largest.back().s<<endl;
    up[poz][0]=largest.back().s;
    pref_tree[poz] = pref_tree[largest.back().s] + (largest.back().s - poz - 1) * x[poz] - get_sum(poz+1, largest.back().s-1);
    // cout<<"pref_tree["<<poz<<"]= "<<pref_tree[poz]<<endl;
    largest.push_back({war,poz});
}

int f(int start, int end)
{
    int odp=0;
    int P = start;

    for(int jump=LOG-1;jump>=0;jump--)
        if(up[P][jump] <= end)
            P=up[P][jump];

    // cout<<"P: "<<P<<endl;

    odp+=pref_tree[start]-pref_tree[P];
    odp += (end - P)*x[P] - get_sum(P+1, end);
    return odp;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>x[i];

    for(int i=1;i<=n;i++)
        pref[i]=pref[i-1]+x[i];

    up[n+1][0]=n+1;
    largest.push_back({inf,n+1});
    for(int i=n;i>=1;i--)
        add(x[i],i);

    make_bin_lifting();

    for(int i=1;i<=q;i++)
    {
        cin>>a>>b;
        cout<<f(a,b)<<'\n';
    }
    return 0;
}