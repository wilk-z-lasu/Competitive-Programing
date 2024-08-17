#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=2e5+7;
constexpr int inf=1e9+7;


int n,m;
int H,R;

constexpr int M=(1<<18);
int tree[2*M];
void set_tree(int poz, int val)
{
    poz=poz+M-1;
    tree[poz]=val;
    poz/=2;
    while(poz)
    {
        tree[poz]=max(tree[2*poz], tree[2*poz+1]);
        poz/=2;
    }
}
int get_max(int a, int b, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return 0;
    if(a<=l && r<=b) return tree[v];
    int mid=(l+r)/2;
    return max(get_max(a,b,2*v,l,mid), get_max(a,b,2*v+1,mid+1,r));
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>H;
        set_tree(i,H);
    }
    set_tree(n+1,inf);

    while(m--)
    {
        cin>>R;
        int l=1, p=n+1;
        while(l<p)
        {
            int mid=(l+p)/2;
            if(get_max(1,mid)>=R)
                p=mid;
            else
                l=mid+1;
        }
        if(l==n+1)
            cout<<0<<' ';
        else
        {
            cout<<l<<' ';
            set_tree(l,get_max(l,l)-R);
        }

    }
    return 0;
}