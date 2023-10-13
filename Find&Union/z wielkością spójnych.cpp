//Find&Union z wielkością spójnych
constexpr int maxn=1e5+2137;//największy elemnet do Find&Union

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
