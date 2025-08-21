#include <bits/stdc++.h>
using namespace std;
#define int long long

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

constexpr int maxn = 2e5+7;

int n;
int X[maxn];
int H[maxn];
int N1, H1;
int N2, H2;

int sufit(int a, int b)
{
    int odp = a/b;
    if(a%b != 0) ++odp;
    return odp;
}

int go(int s, int maxi=0, int o1=N1, int o2=N2)
{
    for(int i=s;i<=n-1;++i)
    {
        maxi = max(maxi, X[i] + H[i]);
        // cout<<i<<": "<<maxi<<" o1 = "<<o1<<" o2 = "<<o2<<endl;
        if(maxi >= X[i+1]) continue;//if I can instantly pass to i+1
        if((__int128)maxi + (__int128)o1*H1 + (__int128)o2*H2 < (__int128)X[i+1]) return i-s+1 + N1 + N2;//if I won't be able to pass to i+1

        int next = X[i+1] - maxi;

        int could1 = min(o1, next/H1);
        o1 -= could1;
        next -= could1*H1;
        maxi += could1*H1;
        if(maxi >= X[i+1]) continue;//I can pass to i+1 without using o2        

        int could2 = min(o2, sufit(next, H2));
        if(next <= could2*H2)
        {
            maxi += could2*H2;
            o2 -= could2;
        }
        else
        {
            maxi += H1;
            --o1;
        }
    }
    return n-s+1 + N1 + N2;
}
void rev()
{
    int maxi = X[n];
    for(int i=1;i<=n;++i)
        X[i] = maxi-X[i];
    reverse(&X[1], &X[n+1]);
    reverse(&H[1], &H[n+1]);
}
int solv = 0;

int32_t main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>X[i]>>H[i];
    
    cin>>N1>>H1;
    cin>>N2>>H2;

    if(H1 < H2) //H1 >= H2 => it is better to use H1
    {
        swap(N1, N2);
        swap(H1, H2);
    }

    // for(int i=1;i<=n;++i)
    //     cout<<X[i]<<' ';
    //     cout<<endl;
    // for(int i=1;i<=n;++i)
    //     cout<<H[i]<<' ';
    //     cout<<endl;
    // for(int i=1;i<=n;++i)
    //     cout<<i<<": "<<go(i)<<endl;

    for(int i=1;i<=n;++i)
        solv = max(solv, go(i));
    rev();
    for(int i=1;i<=n;++i)
        solv = max(solv, go(i));
    cout<<solv;
    return 0;
}