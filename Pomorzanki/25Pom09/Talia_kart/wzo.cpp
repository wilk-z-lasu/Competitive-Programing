#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define ld long double

#define pi pair<int,int>
#define f first
#define s second
#define pb push_back
#define sz(A) (int)A.size()

constexpr int inf = 1e9+7;
constexpr int maxn = 17;

int n;
char C[maxn];
int R[maxn];
int B[maxn];
vector<int>vec;
int solv = inf;

int f(vector<int> &x)
{
    int hR=0;
    int hB=0;
    int costR=0, costB=0;
    for(auto &i: x)
    {
        costR += max((int)0, R[i] - hR);
        costB += max((int)0, B[i] - hB);
        if(C[i]=='R')
            ++hR;
        else
            ++hB;
    }
    return n+max(costR, costB);
}

void Solve()
{
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> distribN(0, n-2);
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    std::shuffle(vec.begin(), vec.end(), g);
    ld T = 1000000000000000000;
    while(T>= (ld)0.00000000001)
    {
        // cout<<std::setprecision(6) << T << endl;
        int S = f(vec);
        solv = min(solv, S);
        int change = distribN(g);
        swap(vec[change], vec[change+1]);
        int S_prim = f(vec);

        if(S_prim >= S)
        {
            ld r = dis(g);
            ld num = std::exp(-(ld)abs(S-S_prim)/T);
            if(num < r)
                swap(vec[change], vec[change+1]);
        }
        T *= (ld)0.999;
    }
}
int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    // auto start = std::chrono::high_resolution_clock::now();

    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>C[i]>>R[i]>>B[i];

    if(n==1)
    {
        cout<<max(R[1], B[1])+1;
        return 0;
    }
    
    for(int i=1;i<=n;++i)   
        vec.pb(i);
    
    for(int IT=1; IT<=10; ++IT)
        Solve();

    cout<<solv;

    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> diff = end - start;
    // std::cout << " Seconds : " << diff.count() << " s\n";
    return 0;
}