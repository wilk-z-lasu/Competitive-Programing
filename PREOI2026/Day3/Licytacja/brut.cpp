#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
// #define ll long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=507;
constexpr int mod=1e9+7;

int n,a,b;

struct Node {
    int sum = 0;
    Node *left = nullptr;
    Node *right = nullptr;
};

struct DynamicTree {
    Node* root = nullptr;
    const int MAX = 1e9;
    
    void add_tree(int pos, int val) {
        add_tree(root, 0, MAX, pos, val);
    }
    
    void add_tree(Node*& node, int l, int r, int pos, int val) {
        if(!node) node = new Node();
        node->sum += val;
        if(l == r) return;
        int mid = l + (r - l) / 2;
        if(pos <= mid) add_tree(node->left, l, mid, pos, val);
        else add_tree(node->right, mid + 1, r, pos, val);
    }
    
    int get_sum(int l, int r) {
        return get_sum(root, 0, MAX, l, r);
    }
    
    int get_sum(Node* node, int l, int r, int ql, int qr) {
        if(!node || r < ql || l > qr) return 0;
        if(ql <= l && r <= qr) return node->sum;
        int mid = l + (r - l) / 2;
        return get_sum(node->left, l, mid, ql, qr) + 
               get_sum(node->right, mid + 1, r, ql, qr);
    }
} tree;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>a>>b;
        for(int j=b;j>=a;--j)
        {
            int sum=tree.get_sum(1, j-1) + 1;
            tree.add_tree(j, sum);
        }
        
    }
    cout<<tree.get_sum(1, 1e9);
    return 0;
}