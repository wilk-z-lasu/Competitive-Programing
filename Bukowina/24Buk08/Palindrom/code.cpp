#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=2e5+7;
constexpr int inf=1e9+7;

string s;
int n;
deque<int>literki[30];
int solv;

constexpr int M=(1<<18);
int tree[2*M];
void add_tree(int a, int b, int val, int v=1, int l=1, int r=M)
{
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
}

int get_tree(int poz)
{
    poz=poz+M-1;
    int odp=0;
    while(poz)
    {
        odp+=tree[poz];
        poz/=2;
    }
    return odp;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>s;
    s='#'+s;
    n=s.size()-1;

    for(int i=1;i<s.size();i++)
        literki[s[i]-'a'].push_front(i);

    for(int i=1;i<s.size();i++)
        add_tree(i,i,i);

    for(int i=1;i<=n/2;i++)
    {
        pair<int, int>kan={inf,0};
        for(int z=0;z<30;z++)
            if(literki[z].size()>=2)
                kan=min(kan,{abs(i-get_tree(literki[z].back())) + abs(n-i+1-get_tree(literki[z].front())), z});

        // cout<<kan.f<<endl;
        if(kan.f == inf)
        {
            cout<<"NIE";
            return 0;
        }
        
        solv+=kan.f;
        add_tree(1, literki[kan.s].back(), 1);
        add_tree(literki[kan.s].front(), n, -1);
        literki[kan.s].pop_front();
        literki[kan.s].pop_back();
    }
    cout<<solv;
    return 0;
}