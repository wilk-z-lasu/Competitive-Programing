#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=1e6+7;

int B,q;
int k;

int a[maxn];
int del;

vector<int> pref;
vector<int> odp;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>B>>q;
    for(int i=0;i<=B-1;i++)
    {
        cin>>a[i];
        del=(del+(a[i]*i)%(B-1))%(B-1);
    }
    if(del!=0)
        a[del]--;

    for(int i=0;i<=B-1;i++)
        if(a[i])
        {
            if(pref.empty())
            {
                pref.push_back(a[i]);
                odp.push_back(i);
            }
            else
            {
                pref.push_back(a[i]+pref[pref.size()-1]);
                odp.push_back(i);
            }
        }

    while(q--)
    {
        cin>>k;
        auto it=upper_bound(pref.begin(), pref.end(), k);
        if(it==pref.end())
            cout<<"-1\n";
        else
            cout<<odp[it-pref.begin()]<<"\n";
    }
    return 0;
}