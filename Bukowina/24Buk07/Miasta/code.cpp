#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=2e5+7;
constexpr int maxm=2e5+7;
int n,m;
int q;

int solv[maxn];
vector<pair<pair<int,int>,pair<int,int>>>vec;//.f.f-w .f.s-id .s.f-v .s.s-u

//Find&Union z wielkością spójnych
int rep[maxn];
bool sigma[maxn];//indicates silna spojna sigmowa
int out[maxn];
bool ss_out[maxn];
int Find(int x)
{
    if(rep[x]==x) return x;
    return rep[x]=Find(rep[x]);
}
void Union(int a,int b)
{
    a=Find(a);
    b=Find(b);
    rep[a]=rep[b];
    ss_out[b]+=ss_out[a];
    if(sigma[a] || sigma[b])
        sigma[b]=1;
}
void prepere()
{
    for(int i=0;i<maxn;i++)
    {
        rep[i]=i;
        sigma[i]=0;
        out[i]=0;
        ss_out[i]=0;
    }
}

int l,r;
int mid;

struct kosz
{
    int lewo, prawo, id, u, v;
};
vector<kosz>basket[maxm];
queue<pair<int,kosz>> basket_h;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;

    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        u++; v++;
        vec.push_back({{w,i},{v,u}});
    }

    sort(vec.begin(),vec.end());

    cin>>q;
    l=0;r=m-1;
    mid=(l+r)/2;
    for(int i=1;i<=q;i++)
    {
        int v,u;
        cin>>v>>u;
        v++; u++;
        basket[mid].push_back({l, r, i, v, u});
    }

    for(int log=1;log<=18;log++)
    {
        prepere();
        for(int i=0;i<vec.size();i++)
        {
            // cout<<"i: "<<i+1<<endl;
            // cout<<vec[i].s.f<<" <-> "<<vec[i].s.s<<endl;
            if(Find(vec[i].s.f)!=Find(vec[i].s.s))
            {
                out[vec[i].s.f]++; if(out[vec[i].s.f]>=3) ss_out[Find(vec[i].s.f)]=1;
                out[vec[i].s.s]++; if(out[vec[i].s.s]>=3) ss_out[Find(vec[i].s.s)]=1;
                Union(vec[i].s.f, vec[i].s.s);
            }
            else
                sigma[Find(vec[i].s.f)]=1;

            for(auto &u: basket[i])
            {
                if(u.lewo>=u.prawo)
                {
                    if(Find(u.v)==Find(u.u) && (sigma[Find(u.v)] || ss_out[Find(u.v)]))
                        solv[u.id]=vec[i].f.f;
                    else
                        solv[u.id]=-1;
                    continue;
                }

                if(Find(u.v)==Find(u.u) && (sigma[Find(u.v)] || ss_out[Find(u.v)]))
                {
                    l=u.lewo;
                    r=i;
                }
                else
                {
                    l=i+1;
                    r=u.prawo;
                }
                mid=(l+r)/2;
                basket_h.push({mid,{l, r, u.id, u.u, u.v}});
            }
            basket[i].clear();
            while(!basket_h.empty())
            {
                basket[basket_h.front().f].push_back(basket_h.front().s);
                basket_h.pop();
            }
        }
    }
    for(int i=1;i<=q;i++)
        cout<<solv[i]<<endl;

    return 0;
}