#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long //usually needed because you multiply two coordinates which are usually <=1e9

constexpr int maxn=2e5+7;//maximum number of points

int n;

struct point
{
    int x,y;
} tab[maxn];

bool cmp(point& p1, point& p2)
{
    if(p1.y == p2.y)
        return p1.x < p2.x;
    else
        return p1.y < p2.y;
}

bool cmp2(point& p1, point& p2)
{
    if((p1.x-tab[1].x) * (p2.y-tab[1].y) == (p2.x-tab[1].x) * (p1.y-tab[1].y))
        return (p1.x-tab[1].x)*(p1.x-tab[1].x) + (p1.y-tab[1].y)*(p1.y-tab[1].y) < (p2.x-tab[1].x)*(p2.x-tab[1].x) + (p2.y-tab[1].y)*(p2.y-tab[1].y);
    else
        return (p1.x-tab[1].x) * (p2.y-tab[1].y) < (p2.x-tab[1].x) * (p1.y-tab[1].y);
}

int orientation(point& p1, point& p2, point& p3)
{
    int val = (p3.x - p2.x) * (p2.y - p1.y) - (p2.x - p1.x) * (p3.y - p2.y);
    if(val == 0) return 0;//collinear
    if(val < 0 ) return 1;//counterclockwise
    if(val > 0) return -1;//clockwise
}

vector<point>ans;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>tab[i].x>>tab[i].y;

    sort(tab+1, tab+n+1, cmp);

    sort(tab+2, tab+n+1, cmp2);

    int poz = n;
    while (poz >= 2 && orientation(tab[1], tab[poz], tab[n]) == 0) poz--;
    reverse(tab+poz+1, tab+n+1);

    // cout<<"soreted points:\n";
    // for(int i=1;i<=n;i++)
    //     cout<<tab[i].x<<" "<<tab[i].y<<endl;
    
    for(int i=1;i<=n;i++)
    {
        while(ans.size() >= 2 && orientation(ans[ans.size()-2], ans.back(), tab[i]) == 1)
            ans.pop_back();
        ans.push_back(tab[i]);
    }

    cout<<ans.size()<<'\n';
    for(auto &u: ans)
        cout<<u.x<<' '<<u.y<<'\n';
    return 0;
}