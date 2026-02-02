#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=1e5+7;
constexpr int maxq=2e5+7;
constexpr int inf=1e9+7;

int n,q;
int a[maxn];
int l,r,m,k;

int get_kratka()
{
    int poz = l+k+m-2;
    if(poz>r) return inf;
    return a[poz];
}

struct Node
{
    vector<int>A;
    vector<int>B;

    int l = inf;
    int r = -inf;
    int mid;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(vector<int>x={})
    {
        A = {0};
        A.insert(A.end(), x.begin(), x.end());
        B.resize(sz(A)); B[0] = 0;

        for(int i=1;i<sz(A);++i)
        {
            l = min(l, A[i]);
            r = max(r, A[i]);
        }
        mid = (l+r)/2;
        if(l==r) return;

        int went_left = 0;
        vector<int>L,R;
        for(int i=1;i<sz(A);++i)
        {
            if(A[i]<=mid)
            {
                went_left++;
                L.pb(A[i]);
            }
            else
                R.pb(A[i]);
            B[i] = went_left;
        }

        if(!L.empty()) left = new Node(L);
        if(!R.empty()) right = new Node(R);
    }
    int get_k_th_smallest(int L, int R, int K)
    {
        if(L>R || K>R-L+1) return inf;
        if(l==r) return l;
        int went_left = B[R]-B[L-1];
        if(went_left>=K)
        {
            int new_L = B[L-1]+1;
            int new_R = B[R];
            return left->get_k_th_smallest(new_L, new_R, K);
        }
        else
        {
            int new_L = L-B[L-1];
            int new_R = R-B[R];
            return right->get_k_th_smallest(new_L, new_R, K-went_left);
        }
    }
};

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>q;
    vector<int> input;
    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        input.pb(a[i]);
    }
    
    Node* root = new Node(input);

    for(int iter=1;iter<=q;++iter)
    {
        cin>>l>>r>>m>>k;
        int solv = get_kratka();
        r=min(r,l+k+m-3);
        solv = min(solv, root->get_k_th_smallest(l, r, k));
        cout<<solv<<"\n";
    }
    return 0;
}