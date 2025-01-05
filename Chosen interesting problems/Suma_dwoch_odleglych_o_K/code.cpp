#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,k;
    cin>>n>>k;

    int vec[n];
    for(int i=0;i<n;i++)
        cin>>vec[i];

    int pre[n];
    pre[0]=vec[0];
    for(int i=1;i<n;i++)
        pre[i]=max(pre[i-1],vec[i]);

    int su[n];
    su[n-1]=vec[n-1];
    for(int i=n-2;i>=0;i--)
        su[i]=max(vec[i],su[i+1]);

    int maxi=0;
    for(int i=0;i<n-k;i++)
        maxi=max(maxi,pre[i]+su[i+k]);
    cout<<maxi;
    return 0;
}