#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=1e5+7;
int n;
int tab[2*maxn];
bool skip[2*maxn];
int x;

long long solv;

queue<int>m[2*maxn];

constexpr int M=(1<<18);

int tree[2*M];
int get_in_range(int a, int b, int v=1, int l=1, int r=M)
{
    if(b<l || r<a)
        return 0;
    if(a<=l && r<=b)
        return tree[v];
    int mid=(l+r)/2;
    return get_in_range(a,b,2*v,l,mid) + get_in_range(a,b,2*v+1,mid+1,r);
}
void set_to_one(int poz)
{
    poz=poz+M-1;
    while(poz>0)
    {
        tree[poz]++;
        poz/=2;
    }
}
void set_to_zero(int poz)
{
    poz=poz+M-1;
    while(poz>0)
    {
        tree[poz]--;
        poz/=2;
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;

    for(int i=1;i<=2*n;i++)
    {
        cin>>tab[i];
        m[maxn+tab[i]].push(i);
    }

    for(int i=1;i<=2*n;i++)
        set_to_one(i);

    for(int i=1;i<=2*n;i++)
    {
        if(skip[i]) continue;
        
        x=tab[i];
        int j=m[maxn-x].front();

        skip[i]=1;
        skip[j]=1;


        solv+=get_in_range(i+1,j-1);
        if(tab[i]>tab[j]) solv++;

        set_to_zero(i);
        set_to_zero(j);

        m[maxn-x].pop();
        m[maxn+x].pop();
    }

    cout<<solv;
    return 0;
}