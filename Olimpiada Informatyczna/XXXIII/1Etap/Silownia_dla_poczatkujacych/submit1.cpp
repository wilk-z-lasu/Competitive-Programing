#include <bits/stdc++.h>
using namespace std;

int n;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    // 1 2 4 5 7 10 13 <- got these by running knapsack problem on my machine
    if(n==1 || n==2 || n==4 || n==5 || n==7 || n==10 || n==13)
        cout<<"NIE";
    else
        cout<<"TAK";
    return 0;
}