//I should use vector instead of priority_queue for faster code
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
#define f first
#define s second

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

constexpr int maxn=300007;

int n,m;
int k;
int akt;//aktualny deszcz

vector<int> mines[maxn];
int need[maxn];

struct deszcz
{
    int l,r,a;
} deszcze[maxn];

int dol=524288;
int tree[1048576];

inline void add(int l,int r, int64_t x, int v=1, int a=1, int b=dol)
{
    if(r<a || b<l) return;
    else if(l<=a && b<=r)
    {
        tree[v]+=x;
        return;
    }

    int mid=(a+b)/2;
    add(l,r,x,v*2,a,mid);
    add(l,r,x,v*2+1,mid+1,b);
}

inline int read(int indeks)
{
    indeks+=dol;
    indeks--;

    int odp=0;
    while(indeks!=0)
    {
        odp+=tree[indeks];
        indeks/=2;
    }
    return odp;
}

inline void sym_deszcz(int numer, bool status)//deszcze indeksuje od 1 //status=1-dodaje status=0-odejmuje
{
    int l=deszcze[numer].l;
    int r=deszcze[numer].r;
    int64_t a;
    if(status) a=deszcze[numer].a;
    else a=-deszcze[numer].a;

    if(l<=r)
    {
        add(l,r,a);
    }
    else if(l>r)
    {
        add(1,r,a);
        add(l,m,a);
    }
    
    if(status) akt++;
    else akt--;
}

inline int zlicz_zebrane(int panstwo)
{
    int odp=0;
    for(auto u: mines[panstwo])
    {
        odp+=read(u);
    }
    return odp;
}

inline void make_opad(int cel)
{
    while(akt!=cel)
    {
        if(akt<cel) 
        {
            for(int i=akt+1;i<=cel;i++)
            {
                sym_deszcz(i,1);
            }
        }
        else if(akt>cel) 
        {
            for(int i=akt;i>cel;i--)
            {
                sym_deszcz(i,0);
            }
        }
    }
}

int odp[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

    cin>>n>>m;

    int x; 
    for(int i=1;i<=m;i++)
    {
        cin>>x;
        mines[x].push_back(i);
    }
    
    for(int i=1;i<=n;i++)
    {
        cin>>need[i];
    }

    cin>>k;

    for(int i=1;i<=k;i++)
    {
        cin>>deszcze[i].l>>deszcze[i].r>>deszcze[i].a;
    }
    deszcze[k+1].l=1;
    deszcze[k+1].r=m;

    deszcze[k+1].a=1000000000;//1e9 jesli tu sie zatrzyma bin search to wyswietl nie

    priority_queue<pair<int,pair<int,pair<int,int>>>>pq;//.f=pozycja w binary searchu .s.f=numer panstwa .s.s.f=poczatek .s.s.s=koniec

    //bin search po falach meteorow(wyniki) od 1 do k+1, gdzie k+1 znaczy ze nie da sie otrzymac probek

    for(int i=1;i<=n;i++)
    {
        pq.push({(1+k+1)/2,{i,{1,k+1}}});
    }

    pair<int,pair<int,pair<int,int>>> top;
    while(!pq.empty())
    {
        queue<pair<int,pair<int,pair<int,int>>>>przepisz;

        make_opad(pq.top().f);

        do
        {
            top=pq.top();
            pq.pop();

            if(top.s.s.f==top.s.s.s)
                odp[top.s.f]=top.s.s.f;
            else if(zlicz_zebrane(top.s.f)<need[top.s.f])
                przepisz.push({(top.f+1+top.s.s.s)/2,{top.s.f,{top.f+1,top.s.s.s}}});
            else
                przepisz.push({(top.s.s.f+top.f)/2,{top.s.f,{top.s.s.f,top.f}}});
        } while(top.f==pq.top().f && !pq.empty());

        while(!przepisz.empty())
        {
            pq.push(przepisz.front());
            przepisz.pop();
        }
        
    }

    for(int i=1;i<=n;i++)
    {
        if(odp[i]==k+1 || odp[i]==0) cout<<"NIE \n";
        else cout<<odp[i]<<'\n';
    }

}