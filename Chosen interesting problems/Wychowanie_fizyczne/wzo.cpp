#include<bits/stdc++.h>
using namespace std;
#define int long long

constexpr int maxn = 2000007;

int N, P, K;
int A[maxn];

int B[maxn];//Bigger the A[P]
int BE[maxn];//Bigger-Equal the A[P]
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

    cin >> N >> P >> K;
    
    for(int i = 1; i <= N; ++i)
        cin>>A[i];

    for(int i = 1; i <= N; ++i)
    {
        B[i] = B[i-1];
        BE[i] = BE[i-1];

        if(A[i]>A[P]) B[i]++;
        if(A[i]>=A[P]) BE[i]++;
    }

    int odp = N - (BE[N] - BE[P]) - B[P-1];
    for(int i = P+1; i <= N; ++i)
    {
        // if(A[i] >= A[P]) continue;
        int poz = i - B[P] - (BE[i-1]-BE[P]) - 1;
        int round = (BE[i-1] - BE[P]) + B[P-1];
        if(round + K >= N-1)
            odp = min(odp, poz);
    }
    cout<<odp;
    return 0;
}