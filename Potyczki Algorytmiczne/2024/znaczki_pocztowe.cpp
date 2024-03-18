#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

int n;
int x;

unordered_map<int,int>input;
unordered_map<int,int>grup;

int solv;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>x;
        ++input[x];
    }
    for(auto &u: input)
        ++grup[u.s];

    for(int k=1;k<=n;++k)
    {
        solv=0;
        for(auto &u: grup)
            solv+=(u.f-u.f%k)*u.s;
        cout<<solv<<' ';
    }
    return 0;
}