#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

#define int long long
constexpr int maxn=5e5+7;

int n,d;
int x;
int tab[maxn];

vector<int>skalowanie;

map<int,int> skal;

priority_queue<pair<int,int>>pq;

vector<int>kosz[maxn];

int dp[maxn];

int rep[maxn];
int prawo[maxn];

void set_rep()
{
    for(int i=0;i<maxn;++i)
    {
        rep[i]=i;
        prawo[i]=i;
    }
}

int Find(int x)
{
    if(rep[x]==x) return x;
    else return rep[x]=Find(rep[x]);
}

void Union(int a, int b)
{
    a=Find(a);
    b=Find(b);
    if(a>b) swap(a,b);

    rep[b]=rep[a];
    prawo[a]=max(prawo[a],prawo[b]);
}

vector<int>del[maxn];
multiset<int> solves[maxn];
int wynik[maxn];
int solv=0;

//drzewo dziala
constexpr int M=(1<<20);
int tree[2*M];
void set_tree(int poz, int val)
{
    poz=poz+M-1;

    tree[poz]=val;
    poz/=2;

    while(poz>0)
    {
        tree[poz]=max(tree[2*poz],tree[2*poz+1]);
        poz/=2;
    }
}

int get_tree(int a, int b, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) 
        return 0;
    if(a<=l && r<=b)
        return tree[v];
    int mid=(l+r)/2;
    return max(get_tree(a,b,2*v,l,mid),get_tree(a,b,2*v+1,mid+1,r));
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>d;

    for(int i=1;i<=n;i++)
    {
        cin>>tab[i];
        skalowanie.push_back(tab[i]);
    }

    int war=0;
    sort(skalowanie.begin(), skalowanie.end());
    for(int i=0;i<n;i++) if(skal[skalowanie[i]]==0) skal[skalowanie[i]] = ++war;
    for(int i=1;i<=n;i++)
    {
        tab[i]=skal[tab[i]];
        kosz[tab[i]].push_back(i);
    }

    //dziala

    set_rep();
    set<int> idx;
    for(int i=1;i<=n;i++)
    {
        // cout<<"i: "<<i<<endl;
        for(auto &u: kosz[i])
        {
            idx.insert(u);
            auto it = idx.find(u);

            // cout<<*it<<endl;

            //dziala

            // cout<<*it<<" "<<u<<endl;
            if(it!=idx.begin())// && 
            {
                it--; 
                if(abs(u - (*it))<=d)
                {
                    // cout<<"Union("<<u<<", "<<*it<<")"<<endl;
                    Union(u, *it);
                }
                it++;
            }
            it++;
            if(it!=idx.end() && abs(u - (*it))<=d)
            {
                // cout<<"Union2("<<u<<", "<<*it<<")"<<endl;
                Union(u, *it);
            }
        }
        // cout<<endl;
        for(auto &u: kosz[i])
            dp[u] = min(n+1, prawo[Find(u)] + d);
    }

    // cout<<"dp: "<<endl;
    // for(int i=1;i<=n;i++)
    //     cout<<dp[i]<<endl;

    // // for(int i=1;i<=n;i++)
    // //     cout<<dp[i]<<' ';
    // // cout<<endl;

    for(int i=1;i<=n;i++)
    {
        for(auto &u: del[i])
        {
            solves[tab[u]].erase(solves[tab[u]].find(wynik[u]));
            if(solves[tab[u]].empty())
                set_tree(tab[u], 0);
            else
                set_tree(tab[u], *solves[tab[u]].rbegin());
        }
        int odp=1;
        if(1<=tab[i]-1) odp += get_tree(1, tab[i]-1);
        wynik[i] = odp;
        solv=max(solv, odp);
        solves[tab[i]].insert(odp);
        set_tree(tab[i], *solves[tab[i]].rbegin());
        del[dp[i] + 1].push_back(i);
    }

    cout<<solv;
    return 0;
}