#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
// #define ll long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=5e5+7;
constexpr int inf=1e9+7;

int n;
int a[maxn];
int solv[maxn];

constexpr int M=1<<19;
int tree[2*M];

int find_first_less(int L, int target, int v=1, int l=1, int r=M)
{
    if(r < L || tree[v] >= target) return -1;
    if(l == r) return l;
    
    int mid = (l + r) / 2;
    int left = find_first_less(L, target, 2*v, l, mid);
    if(left != -1) 
        return left;
    else
        return find_first_less(L, target, 2*v+1, mid+1, r);
}

int find_last_less(int R, int target, int v=1, int l=1, int r=M)
{
    if(l > R || tree[v] >= target) return -1;
    if(l == r) return l;

    int mid = (l + r) / 2;
    int right = find_last_less(R, target, 2*v+1, mid+1, r);
    if(right != -1) 
        return right;
    else
        return find_last_less(R, target, 2*v, l, mid);
}

int get_r(int poz)
{
    int target = a[poz];
    int first_bad = find_first_less(poz, target);
    if(first_bad == -1 || first_bad > n) return n;
    return first_bad - 1;
}

int get_l(int poz)
{
    int target = a[poz];
    int last_bad = find_last_less(poz, target);
    if(last_bad == -1) return 1;
    return last_bad + 1;
}


int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for(int i=1;i<2*M;i++)
        tree[i]=inf;
    
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        tree[M+i-1]=a[i];
    }

    for(int i=M-1;i>=1;i--)
        tree[i]=min(tree[2*i], tree[2*i+1]);

    vector<pi> vec;
    for(int i=1;i<=n;i++)
    {
        int l = get_l(i), r = get_r(i);
        vec.pb({r-l+1, a[i]});
    }
    sort(vec.begin(), vec.end());
    int odp = 0;
    for(int i=n;i>=1;i--)
    {
        while(!vec.empty() && vec.back().f>=i)
        {
            odp = max(odp, vec.back().s);
            vec.pop_back();
        }
        solv[i] = odp;
    }
    for(int i=1;i<=n;i++)
        cout<<solv[i]<<" ";
    return 0;
}