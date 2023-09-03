constexpr int maxn = 200000+2137;// maksymalny number elementow które będziemy łączyć

int rep[maxn];

void set_rep()
{
    for(int i=0;i<maxn;++i)
        rep[i]=i;
}

int Find(int x)
{
    if(rep[x]==x) return x;
    else return rep[x]=Find(rep[x]);
}

void Union(int a, int b)
{
    rep[Find(a)]=rep[Find(b)];
}
