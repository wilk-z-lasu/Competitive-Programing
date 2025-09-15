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

constexpr int maxn = 5e5+7;
constexpr int inf = 1e18;

int n;
int x[maxn], y[maxn], z[maxn];

int o[9][2];
int akt[9];
//[1] = +x+y+z
//[2] = +x+y-z
//[3] = +x-y+z
//[4] = +x-y-z
//[5] = -x+y+z
//[6] = -x+y-z
//[7] = -x-y+z
//[8] = -x-y-z

int solv[maxn];
void prepare()
{
    for(int i=1;i<=8;++i)
        o[i][0] = inf, o[i][1] = -inf;
}
void get_inpt()
{
    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>x[i]>>y[i]>>z[i];
}
void reverse_data()
{
    reverse(x+1, x+n+1);
    reverse(y+1, y+n+1);
    reverse(z+1, z+n+1);
}

void calculeate(bool opt)
{
    prepare();
    for(int i=1;i<=n;++i)
    {
        akt[1] = x[i]+y[i]+z[i];
        akt[2] = x[i]+y[i]-z[i];
        akt[3] = x[i]-y[i]+z[i];
        akt[4] = x[i]-y[i]-z[i];
        akt[5] = -x[i]+y[i]+z[i];
        akt[6] = -x[i]+y[i]-z[i];
        akt[7] = -x[i]-y[i]+z[i];
        akt[8] = -x[i]-y[i]-z[i];

        if(opt && i>=2)
            for(int k=1;k<=8;++k)
                solv[n-i+1] = max(solv[n-i+1], max(o[k][1] - akt[k], akt[k] - o[k][0]));
        else if(i>=2)
            for(int k=1;k<=8;++k)
                solv[i] = max(solv[i], max(o[k][1] - akt[k], akt[k] - o[k][0]));
            
        for(int k=1;k<=8;++k)
            o[k][0] = min(o[k][0], akt[k]), o[k][1] = max(o[k][1], akt[k]);
    }
}
void print()
{
    for(int i=1;i<=n;++i)
        cout<<solv[i]<<"\n";
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    get_inpt();
    calculeate(false);
    reverse_data();
    calculeate(true);
    print();
    return 0;
}