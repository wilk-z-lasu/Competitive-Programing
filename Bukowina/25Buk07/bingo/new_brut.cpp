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

constexpr int maxn = 1e5+7;

int n,p;

bool tab[10][10];

bool possible()
{
    bool pos=0;
    for(int i=0;i<n;++i)
    {
        pos=1;
        for(int j=0;j<n;++j)
        {
            if(tab[i][j]==0)
            {
                pos=0;
                break;
            }
        }
        if(pos)
            return 1;
    }
    for(int i=0;i<n;++i)
    {
        pos=1;
        for(int j=0;j<n;++j)
        {
            if(tab[j][i]==0)
            {
                pos=0;
                break;
            }
        }
        if(pos)
            return 1;
    }
    pos=1;
    for(int i=0;i<n;++i)
    {
        if(tab[i][i]==0)
        {
            pos=0;
            break;
        }
    }
    if(pos)
        return 1;
    pos=1;
    for(int i=0;i<n;++i)
    {
        if(tab[n-1-i][i]==0)
        {
            pos=0;
            break;
        }
    }
    if(pos)
        return 1;
    return 0;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    pi solv = {0,0};
    for(int mask = 0; mask<(1<<(n*n)); ++mask)
    {
        int m = mask;
        for(int i=0;i<n*n;++i)
        {
            tab[i/n][i%n] = m%2;
            m/=2;
        }
        int pelne = 0;
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                if(tab[i][j]==1)
                    ++pelne;
        
        if(!possible())
        {
            bool add=1;
            for(int i=0;i<n;++i)
            {
                for(int j=0;j<n;++j)
                {
                    if(tab[i][j]==0)
                    {
                        tab[i][j]=1;
                        if(!possible())
                            add=0;
                        tab[i][j]=0;
                    }
                    if(add==0) break;
                }
                if(add==0) break;
            }
            if(add)
            {
                if(pelne==solv.f)
                    solv.s++;
                else if(pelne > solv.f)
                    solv = {pelne, 1};
            }
        }
    }
    cout<<solv.s;
}