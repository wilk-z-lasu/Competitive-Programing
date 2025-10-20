//Find & Union
//Bin search po wyniku dla wszytskich naraz jak w Meteorach
//Tworzymy drzewo, bo krawedzi miedzy polaczonymi wierzcholkami o wiekszej wadze niz te polaczenia sa nieuzywane nigdy
//n*log(n) liczymy od nowa w najgorszym wypadku
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=1e5+2137;

struct e
{
	int l,r;
	int u,v;
	int z;
	int id;
};

int n,m;
int a,b,c;
int t;

pair<int,int>con[maxn];
queue<e>vec[maxn];

int rep[maxn];
int siz[maxn];
//find&union
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
    // siz[a]+=siz[b];
    siz[b]+=siz[a];
}
void prepere()
{
    for(int i=0;i<maxn;i++)
    {
        rep[i]=i;
        siz[i]=1;
    }
}

int solv[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    prepere();

    int n,m;cin>>n>>m;

    for(int i=1;i<=m;i++)
    {
    	cin>>a>>b;
    	if(Find(a)!=Find(b))
    	{
    		Union(a,b);
    		con[i]={a,b};
    	}
    }
    
    cin>>t;
    for(int i=1;i<=t;i++)
    {
    	cin>>a>>b>>c;
    	vec[(1+m)/2].push({1,m,a,b,c,i});
    }

    for(int j=1;j<=ceil(log2(m));j++)
    {
        prepere();

        for(int i=1;i<=m;i++)
        {
            Union(con[i].f,con[i].s);
            //rozwazam
            while(!vec[i].empty())
            {
                e top = vec[i].front();
                vec[i].pop();
                // cout<<top.id<<": "<<top.l<<" "<<top.r<<endl;
                if(top.l==top.r)
                {
                    // cout<<top.l<<": "<<top.u<<" "<<top.v<<endl;
                    solv[top.id]=top.l;
                    continue;
                }
                int rozmiar;
                //sprawdzam rozmiar tych dwoch spojnych
                if(Find(top.u)==Find(top.v))
                    rozmiar=siz[Find(top.u)];
                else
                    rozmiar=siz[Find(top.u)]+siz[Find(top.v)];
                if(rozmiar>=top.z)
                    top.r=i;
                else
                    top.l=i+1;
                vec[(top.l+top.r)/2].push(top);
            }
        }
    }

    for(int i=1;i<=t;i++)
    	cout<<solv[i]<<'\n';

    return 0;
}