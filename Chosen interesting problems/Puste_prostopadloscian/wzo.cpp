#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int inf = 1e6;
constexpr int M=(1<<20);

int n;
int X,Y,Z;
vector<pair<int,pi>> vec;

int solv_num=0;
int solv[3];

vector<int> allX;
int minY[inf+2];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>X>>Y>>Z;
        vec.pb({Z,{X,Y}});
        allX.pb(X);
    }
    allX.pb(inf);
    sort(allX.begin(), allX.end());
    allX.erase(unique(allX.begin(), allX.end()), allX.end());
    if(n==0)
    {
        cout<<inf<<" "<<inf<<" "<<inf<<"\n";
        return 0;
    }
    if(n==1)
    {
        int maxi = max({vec[0].f, vec[0].s.f, vec[0].s.s});
        if(vec[0].s.f==maxi)
            cout<<vec[0].s.f<<" "<<inf<<" "<<inf<<"\n";
        else if(vec[0].s.s==maxi)
            cout<<inf<<" "<<vec[0].s.s<<" "<<inf<<"\n";
        else
            cout<<inf<<" "<<inf<<" "<<vec[0].f<<"\n";
        return 0;
    }
    sort(vec.begin(), vec.end());
    for(auto &u: allX)
        minY[u] = inf;
    for(int i=0;i<sz(vec);++i)
    {
        Z = vec[i].f;
        int start_i = i;
        while(i+1<sz(vec) && vec[i+1].f==Z) 
            ++i;
        
        int max_y=inf;
        for(auto &x: allX)
        {
            if(x*max_y*Z > solv_num)
            {
                solv_num = x*max_y*Z;
                solv[0] = x;
                solv[1] = max_y;
                solv[2] = Z;
            }
            max_y = min(max_y, minY[x]);
        }
        
        for(int j=start_i; j<=i; ++j)
            minY[vec[j].s.f] = min(minY[vec[j].s.f], vec[j].s.s);
    }
    cout<<solv[0]<<" "<<solv[1]<<" "<<solv[2]<<"\n";
    return 0;
}