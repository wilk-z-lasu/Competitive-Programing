#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back

int n;
int a;
vector<pi> vec;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=0;i<n;++i)
    {
        cin>>a;
        vec.pb({a, i});
    }
    sort(vec.begin(), vec.end());
    int akt = 0;
    while(n--)
    {
        cout<<vec[akt].f<<' ';
        akt = abs(vec[akt].s);
    }
    return 0;
}