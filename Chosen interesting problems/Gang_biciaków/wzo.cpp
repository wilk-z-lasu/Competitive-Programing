#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int maxn=1e5+7;
constexpr int maxm=15e4+7;
constexpr int SQRT=450;

int n,m,z;
int a,b,c;
vector<pair<int,pi>> vec[maxn];
char Z;
pair<char,pi> queries[maxm];

vector<int>orginal;
int Start[maxn];
int End[maxn];
pi ID_to_edge[maxn];
void dfs(int v=1, int ojciec=1)
{
    for(auto &u: vec[v])
    {
        if(u.f!=ojciec)
        {
            Start[u.f]=sz(orginal);
            ID_to_edge[u.s.s].f=Start[u.f];
            orginal.pb(u.s.f);
            dfs(u.f,v);
            End[u.f]=sz(orginal);
            ID_to_edge[u.s.s].s=End[u.f];
            orginal.pb(-u.s.f);
        }
    }
}

int akt[2*maxn];
pi Comp[maxm];
int Uses[maxm];
int wynik=0;
void Use(int val)
{
    // cout<<"Use("<<val<<")\n";
    if(val>0)
    {
        if(Uses[val]==0) ++wynik;
        Uses[val]++;
    }
    else
    {
        val = -val;
        Uses[val]--;
        if(Uses[val]==0) --wynik;
    }
}

int it=0;
void Move(int poz)
{
    while(it+1<=poz)
    {
        ++it;
        Use(akt[it]);
    }
    while(it-1>=poz)
    {
        Use(-akt[it]);
        --it;
    }
}
int solv[maxm];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m>>z;
    for(int i=1;i<=n-1;i++)
    {
        cin>>a>>b>>c;
        vec[a].pb({b,{c,i}});
        vec[b].pb({a,{c,i}});
    }
    for(int i=1;i<=z;++i)
    {
        cin>>Z;
        if(Z=='Z')
        {
            cin>>a;
            queries[i]={Z,{a,0}};
        }
        else
        {
            cin>>a>>b;
            queries[i]={Z,{a,b}};
        }
    }
    orginal.pb(0);
    dfs();

    int max_Comp=0;
    for(int i=0;i*SQRT+1<=sz(orginal)-1;i++)
    {
        int l=i*SQRT+1;
        int r=(i+1)*SQRT;
        r = min(r, sz(orginal)-1);
        Comp[i]={l,r};
        max_Comp=i;
    }

    for(int i=0;i<=max_Comp;++i)
    {
        int l=Comp[i].f; int r=Comp[i].s;
        //wstępne obliczenia dla bloku
        for(int i=0;i<sz(orginal);++i) akt[i]=orginal[i];
        Move(l-1);

        for(int i=1;i<=z;++i)
        {
            if(queries[i].f=='Z')
            {
                if(Start[queries[i].s.f]<l || Start[queries[i].s.f]>r)
                    continue;
                Move(Start[queries[i].s.f]);
                solv[i]=wynik;
                // cout<<"Move("<<Start[queries[i].s.f]<<") = "<<wynik<<'\n';
            }
            else
            {
                int ID = queries[i].s.f;
                int new_color = queries[i].s.s;
                
                int S = ID_to_edge[ID].f;
                int E = ID_to_edge[ID].s;
                if(S<=it && E>it)
                {
                    Use(-akt[S]);
                    Use(new_color);
                }
                akt[S] = new_color;
                akt[E] = -new_color;
            }
        }
        Move(0);
    }
    for(int i=1;i<=z;++i)
    {
        if(queries[i].f=='Z')
            cout<<solv[i]<<'\n';
    }
    return 0;
}