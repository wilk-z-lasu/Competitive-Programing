#include <bits/stdc++.h>
using namespace std;
#define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)(A.size())

constexpr int maxa=5e5+7;

int n;
int a,b;

constexpr int M=(1<<19);
int tree[2*M];
void set_tree(int poz, int val)
{
    poz=M+poz;
    tree[poz]=__gcd(tree[poz],val);
}
int get_tree(int a, int b)//SPEED UP
{
    a+=M-1;
    b+=M+1;
    int odp = 0;
    while((a>>1) != (b>>1))
    {
        if(a%2==0)
            odp = __gcd(odp, tree[a+1]);
        if(b%2==1)
            odp = __gcd(odp, tree[b-1]);
        a>>=1; 
        b>>=1;
    }
    return odp;
}
// int get_tree(int a, int b, int v=1, int l=0, int r=M-1)
// {
//     if(r<a || b<l) return 0;
//     if(a<=l && r<=b) return tree[v];
//     int mid=(l+r)/2;
//     return __gcd(get_tree(a,b,2*v, l,mid), get_tree(a,b,2*v+1, mid+1,r));
// }

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    int solv=0;
    for(int i=1;i<=n;++i)
    {
        cin>>a>>b;
        set_tree(a,b);
        solv=__gcd(solv, b);
    }
    for(int i=M-1;i>=1;--i)
        tree[i] = __gcd(tree[2*i], tree[2*i+1]);
    for(int g=2;g<maxa;++g)
    {
        int possible=g;
        int l=1, r=g-1; 
        while(r<=maxa)
        {
            possible = __gcd(possible, get_tree(l,r));
            l += g;
            r += g;
        }
        possible = __gcd(possible, get_tree(l,maxa));

        solv=max(solv, possible);
    }
    cout<<solv;
    return 0;
}