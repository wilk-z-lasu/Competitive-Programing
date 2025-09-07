// O(q*log(q)^2)
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
 
constexpr int maxi=3e16;

int q;
int zapytanie;
int x, y;
int a, b;

inline int sufit(int n, int d)
{
    int odp=n/d;
    if(n%d>0) odp++;
    return odp;
}

constexpr int M=(1<<14);
int tree[2*M];
void set_tree(int poz, int val)
{
    poz=poz+M-1;
    if(tree[poz]>=val) return;
    tree[poz]=val;
    poz/=2;
    while(poz)
    {
        tree[poz]=max(tree[2*poz], tree[2*poz+1]);//possible opt
        poz/=2;
    }
}
int get_max(int a, int b, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return 0;
    if(a<=l && r<=b)
        return tree[v];
    int mid=(l+r)/2;
    return max(get_max(a,b, 2*v, l,mid), get_max(a,b, 2*v+1, mid+1,r));
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>q;
    while(q--)
    {
        cin>>zapytanie;
        if(zapytanie==1)
        {
            cin>>x>>y;
            int X = x*x + (int)2*x*y;
            int Y = y;//*y;
            set_tree(Y, X);
        }
        else
        {
            cin>>a>>b;
            int A = a*a;
            int B = b*b + (int)2*a*b;

            int l=0, r=maxi;
            while(l<r)
            {
                int mid=(l+r+1)/2;
                int min_Y=ceil(sqrt(sufit(mid, B)));
                if(min_Y > M || A*get_max(min_Y,M) < mid)
                    r=mid-1;
                else
                    l=mid;
            }
            cout<<l<<'\n';
        }
    }
    return 0;
}