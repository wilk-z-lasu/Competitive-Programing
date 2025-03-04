#include<bits/stdc++.h>
using namespace std;
#define f first
#define s second

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

constexpr int maxn=300007;
constexpr int inf=1e9+7;
constexpr int LOG=20;

void ogranicz(int &x)
{
    if(x>inf) x = inf;
}

int n,m;
int x;
int need[maxn];
int k;

vector<int> mines[maxn];

struct deszcz
{
    int l,r,a;
} deszcze[maxn];

int L[maxn], R[maxn];
vector<int>vec[maxn];
int solv[maxn];

constexpr int M = (1<<19);
int tree[2*M];

void prepere()
{
    for(int i=0;i<2*M;++i)
        tree[i]=0;
}
inline void add_tree(int a, int b, int val, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        tree[v] += val;
        ogranicz(tree[v]);
        return;
    }
    int mid=(l+r)/2;
    add_tree(a,b,val, 2*v, l, mid);
    add_tree(a,b,val, 2*v+1, mid+1, r);
}
inline int get_tree(int poz)
{
    int odp = 0;
    poz = poz + M - 1;
    while(poz)
    {
        odp += tree[poz];
        ogranicz(odp);
        if(odp==inf) break;
        poz/=2;
    }
    return odp;
}
void sym_deszcz(int i)
{
    if(deszcze[i].l<=deszcze[i].r)
        add_tree(deszcze[i].l, deszcze[i].r, deszcze[i].a);
    else
    {
        add_tree(1, deszcze[i].r, deszcze[i].a);
        add_tree(deszcze[i].l, m, deszcze[i].a);
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

    cin>>n>>m;
    for(int i=1;i<=m;++i)
    {
        cin>>x;
        mines[x].push_back(i);
    }
    for(int i=1;i<=n;++i)
        cin>>need[i];

    cin>>k;
    for(int i=1;i<=k;++i)
        cin>>deszcze[i].l>>deszcze[i].r>>deszcze[i].a;
    deszcze[k+1] = {1,m,inf};

    for(int i=1;i<=n;++i)
    {
        vec[(k+2)/2].push_back(i);
        L[i] = 1;
        R[i] = k+1;
    }

    for(int iter=1; iter<=LOG; ++iter)
    {
        prepere();
        for(int i=1;i<=k+1;++i)
        {
            sym_deszcz(i);

            while(!vec[i].empty())
            {
                int id = vec[i].back();
                vec[i].pop_back();
                
                int sum = 0;
                for(auto &u: mines[id])
                {
                    sum += get_tree(u);
                    ogranicz(sum);
                    if(sum==inf) break;
                }

                if(sum >= need[id])
                    R[id] = i;
                else
                    L[id] = i + 1;

                if(L[id]==R[id])
                    solv[id] = L[id];
                else
                    vec[(L[id]+R[id])/2].push_back(id);
            }
        }
    }

    for(int i=1;i<=n;++i)
    {
        if(solv[i]==k+1)
            cout<<"NIE\n";
        else
            cout<<solv[i]<<'\n';
    }
}