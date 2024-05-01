#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=500+7;
constexpr int inf=1e9+7;

int n;
int xw,yw;

struct p
{
    int x,y;
}P[maxn];

inline int len(int i, int j)
{
    return abs(P[i].x-P[j].x)+abs(P[i].y-P[j].y);
}

vector<pair<int,int>>vec; 
pair<int,int> sufix[maxn];

int mini=inf;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>xw>>yw;
        P[i]={xw,yw};
    }

    if(n==2)
    {
        cout<<len(1,2);
        return 0;
    }

    for(int i=1;i<=n;++i)//1 stacja
    {
        for(int j=i+1;j<=n;++j)//2 stacja
        {
            int maxi=inf;
            int odl=len(i,j);

            vec.clear();
            for(int z=1;z<=n;++z)
            {
                if(z==i || z==j) continue;
                vec.push_back({len(i,z),len(j,z)});
            }
            sort(vec.begin(),vec.end());

            sufix[vec.size()]={0,0};
            for(int z=vec.size()-1;z>=0;--z)
            {
                sufix[z]=sufix[z+1];
                if(vec[z].s>=sufix[z].f)
                {
                    sufix[z].s=sufix[z].f;
                    sufix[z].f=vec[z].s;
                }
                else if(vec[z].s>=sufix[z].s)
                    sufix[z].s=vec[z].s;
            }

            for(int z=0;z<vec.size()-1;++z)
            {
                if(z>=1)
                    maxi=min(maxi,max({vec[z].f+sufix[z+1].f+odl, sufix[z+1].f+sufix[z+1].s, vec[z].f+vec[z-1].f}));
                else
                    maxi=min(maxi,max({vec[z].f+sufix[z+1].f+odl, sufix[z+1].f+sufix[z+1].s}));
            }

            mini=min(mini,maxi);
        }
    }

    cout<<mini;

    return 0;
}