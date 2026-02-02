//Solution when ai <= x
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
// #define ll long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=2e5+7;
constexpr int mod=998244353;

int Z;
int n,x;
int a[maxn];

struct node
{
    int val;
    int nxt[2];
    node()
    {
        val=0;
        nxt[0]=-1;
        nxt[1]=-1;
    }
};
vector<node> trie;
int wys;
void add(int war, int i, int v=0)
{
    if(trie[v].nxt[(war>>i) & 1]==-1)
    {
        trie.pb(node());
        trie[v].nxt[(war>>i) & 1] = sz(trie)-1;
        // cout<<v<<" -> "<<sz(trie)-1<<" bit: "<<((war>>i) & 1)<<endl;
    }
    if(i-1>=0)
        add(war, i-1, trie[v].nxt[(war>>i) & 1]);
    else
        trie[trie[v].nxt[(war>>i) & 1]].val++;
    
    trie[v].val=0;
    if(trie[v].nxt[0]!=-1)
        trie[v].val+=trie[trie[v].nxt[0]].val;
    if(trie[v].nxt[1]!=-1)
        trie[v].val+=trie[trie[v].nxt[1]].val;
}
int solv;
void get_solv(int war, int i, int v1=0, int v2=0)
{
    if(v1==-1 || v2==-1) return;

    int bit_war = (war>>i) & 1;
    int bit_x = (x>>i) & 1;

    if(bit_x==0 && bit_war==1)
    {
        if(trie[v2].nxt[0]!=-1)
        {
            solv += (trie[trie[v2].nxt[0]].val);
            solv %= mod;
        }
    }
    if(bit_x==0 && bit_war==0)
    {
        if(trie[v2].nxt[1]!=-1)
        {
            solv += (trie[trie[v2].nxt[1]].val);
            solv %= mod;
        }
    }
    v1=trie[v1].nxt[bit_war];
    if(trie[v2].nxt[bit_war^bit_x]==-1) return;
    v2=trie[v2].nxt[bit_war^bit_x];
    if(i>0)
        get_solv(war, i-1, v1, v2);
    else
    {
        solv += trie[v2].val;
        solv %= mod;
        return;
    }
}

int SOLV(int war, int i)
{
    solv = 0;
    get_solv(war, i);
    return solv;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>Z;
    while(Z--)
    {
        cin>>n>>x;
        trie.clear();
        trie.pb(node());
        wys = 0;
        while((1LL<<wys)<=x)
            wys++;
        // cout<<"WYS: "<<wys<<"\n";
        for(int i=1;i<=n;++i)
        {
            cin>>a[i];
            // if(a[i]>x)
            //     return 13;
        }

        int odp = 0;
        for(int i=1;i<=n;++i)
        {
            add(a[i], wys);
            odp += SOLV(a[i], wys);
            odp %= mod;
        }
        odp += n;
        odp %= mod;
        cout<<odp<<"\n";
    }
}