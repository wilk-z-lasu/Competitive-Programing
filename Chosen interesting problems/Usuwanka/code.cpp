#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=1e6+7;

int n,k;
char x;

bool tab[maxn];

vector<vector<int>>vec;
vector<pair<int,int>>s;

int f()
{
    int solv = s.back().f;
    if(!s.empty() && (int)s.size()-(k+2)>=0)
        solv -= s[(int)s.size()-(k+2)].f;
    return solv;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        if(x=='c')
            tab[i]=1;
    }

    for(int i=1;i<=n;i++)
    {
        int top = 0;
        if(!s.empty())
            top = s.back().f;

        if(tab[i])
            s.push_back({top+maxn, i});
        else
            s.push_back({top+1, i});

        while(s.size()>=k+1 && f()==maxn+k)
        {
            vec.push_back({});
            int ile=k+1;
            while(ile--)
            {
                vec.back().push_back(s.back().s);
                s.pop_back();
            }
        }
    }

    reverse(vec.begin(), vec.end());
    int solv=0;
    for(auto &v: vec)
    {
        sort(v.begin(), v.end());
        for(auto &u: v)
            cout<<u<<' ';
        cout<<'\n';
    }
    return 0;
}
//veni vini vici