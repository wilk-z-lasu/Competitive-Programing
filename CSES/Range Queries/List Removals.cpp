#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long
 
constexpr int maxn=2e5+7;
constexpr int inf=1e9+7;
 
int n;
int x[maxn];
int p;
 
constexpr int M=(1<<18);
int tree[2*M];
 
void update_tree(int poz, int val)
{
    poz=poz+M-1;
    while(poz)
    {
        tree[poz]+=val;
        poz/=2;
    }
}
 
int find_node(int k, int v=1)//finds k'th node
{ 
    if(M<=v && v<=2*M-1)
        return v-M+1;

    int l=tree[2*v];
    
    if(k<=l)
        return find_node(k, 2*v);
    else
        return find_node(k-l, 2*v+1);
}
 
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>x[i];
 
    for(int i=1;i<=n;i++)
        update_tree(i,1);
 
    while(n--)
    {
        cin>>p;
        int node=find_node(p);
        update_tree(node,-1);
        cout<<x[node]<<' ';
    }
    return 0;
}