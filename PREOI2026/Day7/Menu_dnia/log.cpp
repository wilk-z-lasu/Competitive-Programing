#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=150007;

constexpr int M=(1<<18);
int tree[2*M];

void add_tree(int poz, int val)
{
    poz+=M-1;
    tree[poz]=max(tree[poz], val);
    while(poz>1)
    {
        poz/=2;
        tree[poz]=max(tree[2*poz], tree[2*poz+1]);
    }
}
int get_max(int a, int b, int v=1, int l=1, int r=M)
{
    if(a > b) return 0;
    if(r<a || b<l) return 0;
    if(a<=l && r<=b) return tree[v];
    int mid=(l+r)/2;
    return max(get_max(a,b,2*v,l,mid), get_max(a,b,2*v+1,mid+1,r));
}

int n,m;
int A,W;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    cin>>m;
    for(int i=1;i<=n;++i)
    {
        cin>>A>>W;
        int odp = max(get_max(1,A-1), get_max(A+1,m)) + W;
        add_tree(A, odp);
    }

    cout<<get_max(1,m)<<"\n";
    return 0;
}