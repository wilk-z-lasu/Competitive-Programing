#include <bits/stdc++.h>
using namespace std;
#define int long long

constexpr int maxn=5e5+7;
constexpr int inf=1e9+7;

int n;

struct rectangle
{
    int x,y,x2,y2;
}zero, p[maxn], sum_pref[maxn], sum_suf[maxn];

rectangle merge(struct rectangle p1, struct rectangle p2) 
{
    rectangle intersection;
    if (p1.x > p2.x)
        intersection.x = p1.x;
    else
        intersection.x = p2.x;

    if (p1.y > p2.y)
        intersection.y = p1.y;
    else
        intersection.y = p2.y;

    if (p1.x2 < p2.x2)
        intersection.x2 = p1.x2;
    else
        intersection.x2 = p2.x2;

    if (p1.y2 < p2.y2)
        intersection.y2 = p1.y2;
    else
        intersection.y2 = p2.y2;

    if (intersection.x > intersection.x2 || intersection.y > intersection.y2)
        intersection.x = intersection.x2 = intersection.y = intersection.y2 = 0;

    return intersection;
}

int get_area(rectangle p1)
{
    return (p1.x2-p1.x)*(p1.y2-p1.y);
}

int solv;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    zero={0,0,0,0};
 
    cin>>n;

    for(int i=1;i<=n;i++)
        cin>>p[i].x>>p[i].y>>p[i].x2>>p[i].y2;

    sum_pref[0]={0,0,inf,inf};
    for(int i=1;i<=n;i++)
        sum_pref[i]=merge(sum_pref[i-1],p[i]);

    sum_suf[n+1]={0,0,inf,inf};
    for(int i=n;i>=1;i--)
        sum_suf[i]=merge(sum_suf[i+1],p[i]);

    for(int i=1;i<=n;i++)
        solv+=get_area(merge(sum_pref[i-1],sum_suf[i+1]))-get_area(merge(merge(sum_pref[i-1],sum_suf[i+1]),sum_pref[n]));
    solv+=get_area(sum_pref[n]);
    cout<<solv;

    return 0;
}