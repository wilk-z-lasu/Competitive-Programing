#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

int n;

map<pi,int> wys;
int get(int a, int b) {
    if(a<1 || a>n) return 0;
    if(b<1 || b>n) return 0;
    if(wys.find({a,b}) == wys.end())
    {
        cout<<"? "<<a<<' '<<b<<'\n';
        std::cout.flush();
        int odp;
        cin>>odp;
        wys[{a,b}] = odp;
    }
    return wys[{a,b}];
}
void odpowiedz(int w) {
    cout<<"! "<<w<<'\n';
    std::cout.flush();
    exit(0);
}

void solv(int l, int r, int u, int d, int x_last=0, int y_last=0, bool orient=0)
{
    if (l == r && u == d) odpowiedz(get(l, u));
    if(orient == 0)
    {
        int y = (u+d)/2;
        pair<int, pi>maxi = {0,{0,0}};
        for(int x=l;x<=r;++x)
            maxi = max(maxi, {get(x,y),{x,y}});

        if(maxi.f < get(x_last, y_last))
        {
            if(y_last > y)
            {
                solv(l,r,u,y,x_last,y_last, !orient);
                return;
            }
            if(y_last < y)
            {
                solv(l,r,y+1,d,x_last,y_last, !orient);
                return;
            }
        }
        int up = get(maxi.s.f, maxi.s.s+1);
        int down = get(maxi.s.f, maxi.s.s-1);

        if(maxi.f > up && maxi.f > down)
            odpowiedz(maxi.f);//get(maxi.s.f, maxi.s.s)
        if(up > down)
        {
            solv(l,r,u,y,maxi.s.f,maxi.s.s, !orient);
            return;
        }
        else
        {
            solv(l,r,y+1,d,maxi.s.f,maxi.s.s, !orient);
            return;
        }
    }
    else
    {
        int x = (l+r)/2;
        pair<int, pi>maxi = {0,{0,0}};

        for(int y=d;y<=u;++y)
            maxi = max(maxi, {get(x,y),{x,y}});

        if(maxi.f < get(x_last, y_last))
        {
            if(x_last > x)
            {
                solv(x+1, r, u, d ,x_last,y_last, !orient);
                return;
            }
            if(x_last < x)
            {
                solv(l, x, u, d ,x_last,y_last, !orient);
                return;
            }
        }


        int left = get(maxi.s.f-1, maxi.s.s);
        int right = get(maxi.s.f+1, maxi.s.s);

        if(maxi.f > left && maxi.f > right)
            odpowiedz(maxi.f);//get(maxi.s.f, maxi.s.s)
        if(left > right)
        {
            solv(l,maxi.s.f,u,d,maxi.s.f,maxi.s.s, !orient);
            return;
        }
        else
        {
            solv(maxi.s.f+1,r,u,d,maxi.s.f,maxi.s.s, !orient);
            return;
        }
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    if(n==1)
        odpowiedz(get(1,1));
    else
        solv(1,n,n,1);
    return 0;
}
