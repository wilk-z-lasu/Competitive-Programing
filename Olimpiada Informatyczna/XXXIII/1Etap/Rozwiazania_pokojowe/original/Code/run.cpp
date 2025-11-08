#include <bits/stdc++.h>
using namespace std;

#include "Solver.h"

int n,x;
vector<int> vec;
int main() {
    CSolver solver;

    cin>>n;
    for(int i=1;i<=n*n;++i)
    {
        cin>>x;
        vec.push_back(x);
    }

    int result = solver.Solve(n, vec);
    cout<<result<<endl;
    return 0;
}
