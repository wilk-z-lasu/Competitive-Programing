#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O1,O2,O3,Ofast,unroll-loops")
constexpr int maxn=1e6+7;
int n;
int S,B,C;
char a[maxn];

inline void clear()
{
    S=B=C=0;
}
inline void add(int x)
{
    if(a[x]=='S')
        S++;
    else if(a[x]=='B')
        B++;
    else
        C++;
}
inline bool same()//S B C
{
    return ((S==B && S!=0) || (S==C && S!=0) || (B==C && B!=0));
}

int solv;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>a[i];

    for(int i=1;i<=3;++i)
    {
        clear();
        for(int j=i;j<=n;++j)
        {
            add(j);
            if(!same())
                solv=max(solv,j-i+1);
        }
    }

    for(int i=n;i>=n-2;--i)
    {
        clear();
        for(int j=i;j>=1;--j)
        {
            add(j);
            if(!same())
                solv=max(solv,i-j+1);
        }
    }
    cout<<solv;
    return 0;
}