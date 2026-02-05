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

int n,m;
int A[maxn],B[maxn];

vector<int>poz[3];

void wypisz(int *S)
{
    for(int i=1;i<=n;++i)
    {
        cout<<S[i]<<" ";
    }
    cout<<endl;
}

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
    if(a>b) return;
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
    for(int i=1;i<=n;++i)
    {
        char c; cin>>c;
        if(c=='A')
            A[i] = i%3;
        if(c=='G')
            A[i] = (i+1)%3;
        if(c=='S')
            A[i] = (i+2)%3;
    }
    for(int i=1;i<=n;++i)
    {
        char c; cin>>c;
        if(c=='A')
            B[i] = i%3;
        if(c=='G')
            B[i] = (i+1)%3;
        if(c=='S')
            B[i] = (i+2)%3;
    }
    
    for(int i=1;i<=n;++i)
    {
        int id=A[i];
        poz[id].pb(i);
    }

    int solv = 0;
    for(int i=n;i>=1;--i)
    {
        int id = B[i];
        int find=i;
        while(find>0 && A[find]!=id)
            find--;
        if(find==0)
        {
            cout<<"Nie";
            return 0;
        }
        for(int j=find;j+1<=i;++j)
        {
            ++solv;
            swap(A[j],A[j+1]);
        }
    }
    cout<<"Tak\n";
    cout<<solv;
    return 0;
}