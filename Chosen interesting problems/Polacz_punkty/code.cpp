#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define int long long
#define v vector<vector<int>>

constexpr int mod=1e9;

int n;

v multiply_matrix(v &x1, v &x2)
{
    v solv; solv.resize(4);
    solv[0].resize(4);
    solv[1].resize(4);
    solv[2].resize(4);
    solv[3].resize(4);


    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            for(int z=0;z<4;z++)
                solv[i][j] = (solv[i][j] + x1[i][z]*x2[z][j])%mod;
    return solv;
}

v pot(v x, int p)
{
    v solv={
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1}};
    while(p)
    {
        if(p%2)
            solv = multiply_matrix(solv, x);
        x = multiply_matrix(x,x);
        p/=2;
    }
    return solv;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    v start={
    {1,0,0,2},
    {1,0,0,2},
    {1,0,0,2},
    {1,0,0,2}};

    v move={
    {2,1,2,2},
    {0,0,2,0},
    {2,1,2,2},
    {1,0,0,0}};

    move = pot(move, n-2);
    start = multiply_matrix(start, move);

    cout<<(start[0][0] + 2*start[0][1] + start[0][2])%mod;
    return 0;
}