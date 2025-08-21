// XXXI Olimpiada Informatyczna - 1 Etap
// Mateusz Woloszyk
// Solution for 100/100 pkt
#include<bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=100000+7;
constexpr int maxm=500000+7;
constexpr int inf=1e9;


int n,m;
int r,c;
pair<int,int> spr[maxm];//[numer przycisku] = jego r i c 
bool szukam_parzystych;
queue<int>przyciski;//odpowiedz

vector<pair<int,pair<int,int>>>p;
//.f=y .s.f=x .s.s=id

int x[maxn];
int y[maxn];

int parzystosc_x[maxn];
int parzystosc_y[maxn];

set<pair<int,pair<int,int>>>elementy_x[maxn];
set<pair<int,pair<int,int>>>elementy_y[maxn];

constexpr int M=262144;

int tree[2*M];
void prepere_tree()
{
    for(int i=0;i<2*M;i++)
        tree[i]=inf;
}
void set_tree(int v, int x, char f)
{
    if(f=='y')
        v+=n;
    v=v+M-1;
    if(tree[v]==inf)
        tree[v]=x;
    else
        tree[v]+=x;
    if(tree[v]==0)
        tree[v]=inf;
    while(v/2>0)
    {
        v/=2;
        tree[v]=min(tree[2*v],tree[2*v+1]);
    }
}
pair<int,int> find_tree()
{
    int v=1;
    while(2*v+1<=2*M)
    {
        if(tree[2*v]<=tree[2*v+1])
            v=2*v;
        else
            v=2*v+1;
    }
    return {tree[v],v-M+1};
}

int rep[maxm];//znany algorytm Find&Union
void set_rep()//znany algorytm Find&Union
{
    for(int i=0;i<maxm;++i)
        rep[i]=i;
}
int Find(int x)//znany algorytm Find&Union
{
    if(rep[x]==x) return x;
    else return rep[x]=Find(rep[x]);
}

void Union(int a, int b)//znany algorytm Find&Union
{
    rep[Find(a)]=rep[Find(b)];
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

    set_rep();
    prepere_tree();
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>r>>c;
        spr[i]={r,c};
        elementy_x[c].insert({c,{r,i}});
        set_tree(c,1,'x');
        elementy_y[r].insert({c,{r,i}});
        set_tree(r,1,'y');
        p.push_back({r,{c,i}});
    }

    sort(p.begin(),p.end());
    //.f=y .s.f=x .s.s=id
    for(int i=0;i<p.size();i++)
    {
        if(y[p[i].f]!=0 && x[p[i].s.f]!=0 && Find(y[p[i].f])==Find(x[p[i].s.f]))
        {
            Union(y[p[i].f],p[i].s.s);
            Union(x[p[i].s.f],p[i].s.s);
            szukam_parzystych=true;
            prepere_tree();
            for(int i=1;i<=n;i++)
            {
                elementy_x[i].clear();
                elementy_y[i].clear();
            }
            int o=Find(p[i].s.s);
            for(int i=1;i<=m;i++)
            {
                if(Find(i)==o)
                {
                    elementy_x[spr[i].s].insert({spr[i].s,{spr[i].f,i}});
                    set_tree(spr[i].s,1,'x');
                    elementy_y[spr[i].f].insert({spr[i].s,{spr[i].f,i}});
                    set_tree(spr[i].f,1,'y');
                }
            }
            break;
        }
        if(y[p[i].f]!=0)
            Union(y[p[i].f],p[i].s.s);
            
        if(x[p[i].s.f]!=0)
            Union(x[p[i].s.f],p[i].s.s);
        y[p[i].f]=p[i].s.s;
        x[p[i].s.f]=p[i].s.s;
    }
    while(true)
    {
        pair<int,int> ostatni=find_tree();
        if(ostatni.f==inf)
            break;
        if(ostatni.f==2)
            break;
        if(ostatni.s<=n)
        {
            pair<int,pair<int,int>> top=*elementy_x[ostatni.s].begin();
            elementy_x[top.f].erase(top);
            set_tree(top.f,-1,'x');
            elementy_y[top.s.f].erase(top);
            set_tree(top.s.f,-1,'y');
            if(parzystosc_x[top.f]==0)
            {
                przyciski.push(top.s.s);
                parzystosc_x[top.f]=1;
                parzystosc_y[top.s.f]=(parzystosc_y[top.s.f]+1)%2;
            }
        }
        else
        {
            ostatni.s-=n;
            pair<int,pair<int,int>> top=*elementy_y[ostatni.s].begin();
            elementy_x[top.f].erase(top);
            set_tree(top.f,-1,'x');
            elementy_y[top.s.f].erase(top);
            set_tree(top.s.f,-1,'y');
            if(parzystosc_y[top.s.f]==0)
            {
                przyciski.push(top.s.s);
                parzystosc_x[top.f]=(parzystosc_x[top.f]+1)%2;
                parzystosc_y[top.s.f]=1;
            }
        }
    }
    if(szukam_parzystych)
    {
        while(!przyciski.empty())
            przyciski.pop();
        for(int i=1;i<=n;i++)
        {
            for(auto u: elementy_x[i])
                przyciski.push(u.s.s);
        }
    }
    else
    {
        for(int i=1;i<=n;i++)
        {
            if(parzystosc_x[i]==0 || parzystosc_y[i]==0)
            {
                cout<<"NIE\n";
                return 0;
            }
        }
    }
    cout<<"TAK\n";
    cout<<przyciski.size()<<'\n';
    while(!przyciski.empty())
    {
        cout<<przyciski.front()<<' ';
        przyciski.pop();
    }
    return 0;
}