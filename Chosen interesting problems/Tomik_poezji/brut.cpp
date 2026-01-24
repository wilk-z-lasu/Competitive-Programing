#include <bits/stdc++.h>
using namespace std;

#define int long long

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int maxn=500007;
constexpr int inf=1e9+7;

int N,S;
int tab[maxn];
vector<int>vec;
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>N>>S;
    for(int i=1;i<=N;++i)
    {
        cin>>tab[i];
        tab[i]++;
    }

    for(int i=1;i<=N;++i)
        vec.pb(i);
    
    int odp=inf;
    vector<int> solv;
    do 
    {
        int akt=0;
        int tmp_odp=0;
        for(auto &u: vec)
        {
            if(akt==S-1)
            {
                akt=0;
                tmp_odp++;
            }
            akt+=tab[u];
            akt%=S;
        }

        if(tmp_odp<odp)
        {
            odp = tmp_odp;
            solv = vec;
        }
    } while(next_permutation(vec.begin(),vec.end()));
    cout<<odp<<'\n';
    // for(auto &u: solv)
    //     cout<<u<<' ';
    return 0;
}