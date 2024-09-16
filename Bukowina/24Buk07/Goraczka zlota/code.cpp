#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=2000+7;

int n;

struct pkt
{
    int x,y,w;
}punkty[maxn];

bool punkty_cmp(const pkt& p1, const pkt& p2)
{
    if(p1.x!=p2.x) return p1.x<p2.x;
    else return p1.y>p2.y;
}

constexpr int M=(1<<12);
struct Node
{
    int wynik, prefix, sufix, suma;
};

struct drzewo
{
    Node tree[2*M];
    void update(int poz, int val)
    {
        poz=poz+M;
        tree[poz]={val,val,val,val};
        poz/=2;
        while(poz)
        {
            tree[poz].prefix=max({tree[2*poz].prefix, tree[2*poz].suma+tree[2*poz+1].prefix});
            tree[poz].sufix=max({tree[2*poz+1].sufix, tree[2*poz+1].suma+tree[2*poz].sufix});
            tree[poz].suma=tree[2*poz].suma+tree[2*poz+1].suma;
            tree[poz].wynik=max({tree[2*poz].wynik, tree[2*poz+1].wynik, tree[poz].prefix, tree[poz].sufix, tree[2*poz].sufix+tree[2*poz+1].prefix});
            poz/=2;
        }
    }
}SegTree;

struct odcinek
{
    int roznica_x, roznica_y, id1, id2;
};
vector<odcinek>odcinki;
int punkt_na_drzewie[maxn];

bool cmp_odcinki(const odcinek& a, const odcinek& b)
{
    if(a.roznica_y*b.roznica_x == b.roznica_y*a.roznica_x)
    {
        if(a.id1==b.id1)
            return a.id2<b.id2;
        else return a.id1<b.id1;
    }
    return a.roznica_y*b.roznica_x < b.roznica_y*a.roznica_x;
}

int solv;

void swap_tree(int a, int b)
{
    int a_drzewo=punkt_na_drzewie[a];
    int b_drzewo=punkt_na_drzewie[b];

    int a_val=SegTree.tree[M+a_drzewo].suma;
    int b_val=SegTree.tree[M+b_drzewo].suma;

    SegTree.update(a_drzewo,b_val);
    SegTree.update(b_drzewo,a_val);
    swap(punkt_na_drzewie[a],punkt_na_drzewie[b]);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for (int i = 1; i <= n; ++i)
        cin>>punkty[i].x>>punkty[i].y>>punkty[i].w;

    if(n==1)
    {
        cout<<max((int)0,punkty[1].w);
        return 0;
    }

    sort(&punkty[1],&punkty[n+1], punkty_cmp);

    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            pkt a=punkty[i];
            pkt b=punkty[j];
            int roz_y=b.y-a.y;
            int roz_x=b.x-a.x;
            int idxa=i;
            int idxb=j;

            if(roz_x<0 || (roz_x==0 && roz_y>0))
            {
                swap(a,b);
                swap(idxa,idxb);
            }

            odcinki.push_back({b.x-a.x,b.y-a.y,idxa,idxb});
        }   
    }

    for (int i = 1; i <= n; ++i)
    {
        SegTree.update(i,punkty[i].w);
        punkt_na_drzewie[i]=i;
    }

    sort(odcinki.begin(), odcinki.end(), cmp_odcinki);

    solv=SegTree.tree[1].wynik;

    swap_tree(odcinki[0].id1, odcinki[0].id2);

    for(int i=1;i<odcinki.size();i++)
    {
        if(odcinki[i].roznica_y*odcinki[i-1].roznica_x != odcinki[i-1].roznica_y*odcinki[i].roznica_x)
            solv=max(solv,SegTree.tree[1].wynik);

        swap_tree(odcinki[i].id1, odcinki[i].id2);
    }

    solv=max(solv,SegTree.tree[1].wynik);

    cout<<solv;

    return 0;
}