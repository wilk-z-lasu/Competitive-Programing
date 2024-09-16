#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=2e5+7;

int n,m;

int a[maxn];
int b[maxn];

void not_possible()
{
    cout<<"NIE";
    exit(0);
}

constexpr int M=(1<<18);

struct node
{
    int max, push;
} tree[2*M];

inline void Push(int v)
{
    if(tree[v].push == 0) return;
    int l=2*v;
    int r=2*v+1;

    tree[l].max+=tree[v].push;
    tree[l].push+=tree[v].push;

    tree[r].max+=tree[v].push;
    tree[r].push+=tree[v].push;
    
    tree[v].push=0;
}

// int get_element(int poz, int v=1, int l=1, int r=M)
// {
//     int mid;
//     while(l != r)
//     {
//         Push(v);
//         mid = (l+r)/2;
//         if(poz<=mid)
//         {
//             v=2*v;
//             r=mid;
//         }
//         else
//         {
//             v=2*v+1;
//             l=mid+1;
//         }
//     }
//     return tree[v].max;
// }

inline int get_element(int poz, int v=1, int l=1, int r=M)
{
    if(l==r)
        return tree[v].max;
    Push(v);

    int mid=(l+r)/2;
    int odp;
    if(poz<=mid)
        odp = get_element(poz, 2*v, l,mid);
    else
        odp = get_element(poz, 2*v+1, mid+1,r);
    tree[v].max = max(tree[2*v].max, tree[2*v+1].max);
    return odp;
}

inline void add(int a, int b, int val, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        tree[v].max += val;
        tree[v].push += val;
        return;
    }
    Push(v);
    int mid=(l+r)/2;
    add(a,b,val, 2*v, l,mid);
    add(a,b,val, 2*v+1, mid+1,r);
    tree[v].max = max(tree[2*v].max, tree[2*v+1].max);
}

inline int get_last_bigger(int val, int v=1, int l=1, int r=M)
{
    if(l==r)
        return l;
    int mid=(l+r)/2;
    Push(v);
    // cout<<l<<" "<<r<<endl;
    int odp;
    if(tree[2*v+1].max > val)
        odp = get_last_bigger(val, 2*v+1, mid+1,r);
    else
        odp = get_last_bigger(val, 2*v, l,mid);
    tree[v].max = max(tree[2*v].max, tree[2*v+1].max);
    return odp;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];

    for(int i=1;i<=m;i++)
        cin>>b[i];

    sort(&a[1], &a[n+1], greater<int>());
    sort(&b[1], &b[n+1], greater<int>());

    for(int i=1; i<=n; i++)
        tree[i+M-1].max=a[i];

    for(int i=M-1;i>=1;i--)
        tree[i].max = max(tree[2*i].max, tree[2*i+1].max);

    for(int i=1; i<=m; i++)
    {
        int element = get_element(b[i]);
        if(element == 0)
            not_possible();
        if(element == get_element(1))
        {
            int end_rel = get_last_bigger(element-1);
            int need_rel = b[i];
            int start_rel = end_rel-need_rel+1;
            add(start_rel, end_rel, -1);
            continue;
        }
        int end1 = get_last_bigger(element);
        add(1, end1, -1);
        int need = b[i] - end1;
        int end2 = get_last_bigger(element-1);
        add(end2-need+1, end2, -1);
    }
    cout<<"TAK\n";
    return 0;
}