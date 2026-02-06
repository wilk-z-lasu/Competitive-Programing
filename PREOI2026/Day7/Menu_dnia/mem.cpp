#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=3e6+7;

int odp[maxn];//odp[A] = max solution ending with A
pair<pi,pi> maxi = {{0,0},{0,0}};//.f.f = first maximum ending A .f.s=odp[A] .s.f = second maximum ending A .s.s=odp[A]

int n,m;
int A,W;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    cin>>m;
    for(int i=1;i<=n;++i)
    {
        cin>>A>>W;
        if(A == maxi.f.f)
        {
            odp[A] = max(odp[A], odp[maxi.s.f] + W);
        }
        else
        {
            odp[A] = max(odp[A], odp[maxi.f.f] + W);
            if(odp[A] >= odp[maxi.f.f])
            {
                maxi.s = maxi.f;
                maxi.f = {A, odp[A]};
            }
            else if(odp[A] > odp[maxi.s.f])
                maxi.s = {A, odp[A]};
        }
    }
    cout<<odp[maxi.f.f]<<"\n";
    return 0;
}