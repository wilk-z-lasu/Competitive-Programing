//code gets 9
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

#pragma GCC optimize("O3","unroll-loops")

constexpr int maxn=200000+7;
int n,x;
int tab[maxn];

constexpr int M=(1<<19);

int before[2*M];
int after[2*M];

inline void update(int poz, int val, int *tree)
{
    poz = poz+M;
    while(tree[poz] < val)
    {
        tree[poz] = val;
        poz/=2;
    }
}
inline int get_max(int a, int b, int *tree, int v=1, int l=0, int r=M-1)
{
    if(r<a || b<l) 
        return 0;
    else if(a<=l && r<=b)
        return tree[v];
    int mid=(l+r)/2;
    return max(get_max(a,b,tree, 2*v, l,mid), get_max(a,b,tree, 2*v+1, mid+1,r));
}

vector<int>skal_vec;
unordered_map<int,int>skal;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>x;
    for(int i=1;i<=n;++i)
    {
        cin>>tab[i];
        skal_vec.push_back(tab[i]);
        skal_vec.push_back(tab[i]+x);
    }

    sort(skal_vec.begin(), skal_vec.end(), greater<int>());

    int it=0;
    while(!skal_vec.empty())
    {
        int v=skal_vec.back();
        skal[v] = ++it;
        while(!skal_vec.empty() && skal_vec.back() == v)
            skal_vec.pop_back();
    }
    for(int i=1;i<=n;++i)
    {
        int s=skal[tab[i]];
        int new_before=get_max(0, s-1, before)+1;
        int new_after=get_max(0, s-1, after)+1;

        int action=get_max(0, skal[tab[i]+x]-1, before)+1;

        // cout<<i<<": "<<new_before<<" "<<new_after<<" "<<action<<endl;
        update(s, new_before, before);
        update(s, max(new_after,action), after);
    }
    cout<<after[1];
    return 0;
}