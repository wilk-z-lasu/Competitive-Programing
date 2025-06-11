#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second

int n;
stack<int>S;
stack<int>S2;

int wys[100007];
bool visited[50007];

vector<int>odp;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin>>n;
    for(int i=0;i<2*n;++i)
        cin>>wys[i];

    for(int i=2*n-1;i>=0;--i)
        S.push(wys[i]);

    while(!S.empty())
    {
        int x=S.top();
        S.pop();
        if(!visited[x])
        {
            visited[x]=true;
            S2.push(x);
        }
        else
        {
            int j=S2.size();
            int y=S2.top();
            S2.pop();
            visited[y]=false;
            if(x!=y)
            {
                odp.push_back(j);
                S.push(y);
                S.push(x);
            }
        }
    }

    cout<<odp.size()<<"\n";
    for(int i=0;i<odp.size();++i) 
        cout<<odp[i]<<"\n";
    
    return 0;
}