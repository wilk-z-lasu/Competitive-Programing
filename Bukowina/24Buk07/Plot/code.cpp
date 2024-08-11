#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

#pragma GCC optimize("Ofast,unroll-loops")
#define int long long

constexpr int maxn=100000+1;
constexpr int inf=1e9+1;
constexpr int maxm=5e4+1;

int n,m,k;
int a;
int c[maxn];
vector<int>pracownicy[maxn];

int dp[2][maxm];
vector<int>przedzialy;

vector<int>do_wyzerowania[2];

int solv[maxn];

bitset<maxn>help;

void fastscan(int &number) 
{ 
    //variable to indicate sign of input number 
    bool negative = false; 
    register int c; 
  
    number = 0; 
  
    // extract current character from buffer 
    c = getchar(); 
    
    // Keep on extracting characters if they are integers 
    // i.e ASCII Value lies from '0'(48) to '9' (57) 
    for (; (c>47 && c<58); c=getchar()) 
        number = number *10 + c - 48; 
} 

int32_t main()
{
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);

    // cin>>n>>m>>k;
    fastscan(n);
    fastscan(m);
    fastscan(k);


    bool all_clors_same=1;
    int git_worker=0;
    for(int i=1;i<=n;++i)
    {
        // cin>>c[i]
        fastscan(c[i]);
        if(i>=2 && c[i]!=c[i-1])
            all_clors_same=0;
        // c[i]++;
    }


    for(int j=1;j<=m;++j)
    {
        // cin>>k;
        fastscan(k);
        while(k--)
        {
            // cin>>a;
            fastscan(a);
            if(a==c[1])
                git_worker++;
            // a++;
            pracownicy[a].push_back(j);
        }
    }

    if(all_clors_same && git_worker==m)
    {
        if(n%m==0)
            cout<<n/m;
        else
            cout<<(n/m)+1;
        return 0;
    }

    for(int i=n;i>=1;--i)
    {
        for(int &u: pracownicy[c[i]])
        {
            dp[i%2][u]=dp[(i+1)&1][u%m + 1]+1;
            do_wyzerowania[i&1].emplace_back(u);
            if(dp[i&1][u]>=m)
                // if(przedzialy.empty() || przedzialy.back() != i+m-1)
                    help[i+m-1]=1;
                    // przedzialy.emplace_back(i+m-1);
        }
        for(int &u: do_wyzerowania[(i-1)&1])
            dp[(i+1)&1][u]=0;
        do_wyzerowania[(i+1)&1].clear();
    }

    for(int i=maxn-1;i>=1;--i)
        if(help[i])
            przedzialy.emplace_back(i);

    if(przedzialy.empty() || przedzialy.front()!=n || przedzialy.back()!=m)
    {
        cout<<-1;
        return 0;
    }
    int akt=n-m;
    if(akt==0)
    {
        cout<<1;
        return 0;
    }
    int solv=1;

    int s_przedzialy=przedzialy.size();
    for(int i=0;i<s_przedzialy-1;++i)
    {
        if((i+1)<s_przedzialy && przedzialy[i+1]>=akt)
        {
            if((i+2)<s_przedzialy && przedzialy[i+2]>=akt)
                continue;
            else
            {
                ++solv;
                akt=przedzialy[i+1]-m;
            }
        }
        else
        {
            cout<<-1;
            return 0;
        }
    }
    cout<<solv;
    return 0;
}