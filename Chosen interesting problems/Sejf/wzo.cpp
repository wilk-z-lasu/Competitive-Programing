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

constexpr int maxk = 250007;
int n,k;
int tab[maxk];
int S;
vector<int> vec;
vector<int> Divisors(int x)
{
    vector<int> odp;
    for(int i=1;i*i<=x;++i)
    {
        if(x%i==0)
        {
            odp.pb(i);
            if(i!=x/i)
                odp.pb(x/i);
        }
    }
    return odp;
}

void some_weird_cases()
{
    for(int i=1;i<=k-1;++i)
        if(tab[i]==0)
        {
            cout<<0;
            exit(0);
        }
    if(S==0)
        S=n;
    if(k==1)
    {
        cout<<n;
        exit(0);
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>k;
    for(int i=1;i<=k-1;++i)
        cin>>tab[i];
    cin>>S;
    some_weird_cases();
    
    vector<int>d1 = Divisors(S);
    vector<int>d2 = Divisors(n);
    sort(d1.begin(), d1.end());
    sort(d2.begin(), d2.end());

    while(!d1.empty() && !d2.empty())
    {
        if(d1.back()>d2.back())
            d1.pop_back();
        else if(d2.back()>d1.back())
            d2.pop_back();
        else if(d1.back()==d2.back())
        {
            vec.pb(d1.back());
            d1.pop_back();
            d2.pop_back();
        }
    }
    reverse(vec.begin(), vec.end());
    sort(&tab[1], &tab[k], greater<int>());
    for(int i: vec)
    {
        bool ok=true;
        for(int j=1;j<=k-1;++j)
            if(tab[j]%i==0)
            {
                ok=false;
                break;
            }
        if(ok)
        {
            cout<<(n/i);
            return 0;
        }
    }
    return 0;
}