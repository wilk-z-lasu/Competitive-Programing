#include <bits/stdc++.h>
using namespace std;
#define int long long

int a, b;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>a>>b;
    int n = b-a+1;

    int p1 = n/2 + n%2;
    int p2 = n/2;

    cout<<(int)2*(p1/2 + p2/2);
    return 0;
}