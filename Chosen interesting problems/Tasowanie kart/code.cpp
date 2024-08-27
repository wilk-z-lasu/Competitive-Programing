#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=2e5+7;
constexpr int maxq=1000000+7;
constexpr int inf=1e9+7;

int n,q;
int tab[maxn];

int poz[maxn];
int last[maxn];

vector<pair<int,int>>S;
int get(int add, int poz) {
    while(!S.empty() && S.back().f<add)
        S.pop_back();
    S.push_back({add,poz});
    if(S.size()==1)
        return n;
    else return S[S.size()-2].s-1;
}

constexpr int M=(1<<18);
int tree[2*M];
void set_tree(int poz, int val)
{
    poz=poz+M-1;
    tree[poz]=val;
    poz/=2;
    while(poz)
    {
        tree[poz]=tree[2*poz]+tree[2*poz+1];
        poz/=2;
    }
}
int get_sum(int a, int b, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return 0;
    if(a<=l && r<=b) return tree[v];
    int mid=(l+r)/2;
    return get_sum(a,b, 2*v, l,mid) + get_sum(a,b, 2*v+1, mid+1,r);
}
int get_tree(int v, int k)//last segment started before k
{
    int l=2*v;
    int r=2*v+1;
    if(M<=v) return v-M+1;
    if(k <= tree[l])
        return get_tree(l,k);
    else
        return get_tree(r,k-tree[l]);
}

int get_k_th_element(int k)
{
    int rep = get_tree(1,k);
    int need = k - get_sum(1,rep-1) - 1; 
    return tab[poz[rep]+need];
}

void update(int a, int b)
{
    for(int i=a; i<=b; i++)
    {
        int next=min(last[i], b);
        set_tree(tab[i], next-i+1);
        i=next;
    }
}

vector<pair<int,int>>vec[maxn];//.f-ktory .s-id
int solv[maxq];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>tab[i];

    for(int i=n;i>=1;i--)
        last[i]=get(tab[i],i);

    for(int i=1;i<=n;i++)
        poz[tab[i]]=i;

    update(1,n);

    for(int i=1;i<=q;i++)
    {
        int t,x;
        cin>>t>>x;
        vec[min(t,n+1)].push_back({x,i});
    }

    for(int i=0;i<=n+1;i++)//n
    {
        for(auto &u: vec[i])
            solv[u.s]=get_k_th_element(u.f);

        //simulate sort
        int rep = get_tree(1,n/2);
        int new_last = get_k_th_element(n/2);
        int dl=get_sum(rep,rep);
        set_tree(rep, poz[new_last] - poz[rep] + 1);
        update(poz[new_last]+1, poz[rep]+dl-1);
    }

    for(int i=1;i<=q;i++)
        cout<<solv[i]<<'\n';

    return 0;
}