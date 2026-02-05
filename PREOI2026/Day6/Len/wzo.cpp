#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=2e5+7;
constexpr int mod=1e9+7;

int n;
int tab[maxn];

bool taken[maxn];

int poz[maxn];

constexpr int M=(1<<18);
int tree[2*M];

int get_tree(int poz)
{
    poz+=M-1;
    int res=0;
    while(poz)
    {
        res+=tree[poz];
        poz/=2;
    }
    return res;
}
void add_tree(int a, int b, int val, int v=1, int l=1, int r=M)
{
    if(r<a || b<l)
        return;
    if(a<=l && r<=b)
    {
        tree[v]+=val;
        return;
    }
    int mid=(l+r)/2;
    add_tree(a,b,val,2*v,l,mid);
    add_tree(a,b,val,2*v+1,mid+1,r);
    return;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i = 1; i <= n; ++i)
    {
        cin>>tab[i];
        poz[tab[i]]=i;
    }

    for(int i = 1; i <= n; ++i)
        add_tree(i,i,i);

    int solv=0;

    int ile=0;
    int maxi = n;
    set<int>S;
    for(int i=1;i<=n;++i) S.insert(i);

    while(!S.empty())
    {
        auto it = --S.end();
        int i = (*it);
        if(ile>=1 && tab[i]!=maxi)
        {
            int start=get_tree(poz[maxi]);
            int end=get_tree(i);

            solv += (end-start);

            add_tree(poz[maxi], i, -1);

            it = S.find(poz[maxi]);
            i = (*it);
        }
        taken[tab[i]]=1;
        if(tab[i]<=maxi) ++ile;

        while(taken[maxi])
        {
            --maxi;
            --ile;
        }
        S.erase(i);
    }
    cout<<solv;
    return 0;
}