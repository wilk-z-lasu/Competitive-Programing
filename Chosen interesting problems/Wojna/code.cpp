#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=100000+7;

int n;
int a;

deque<int>p1;
deque<int>p2;

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a; p1.push_back(a);
    }
    for(int i=1;i<=n;i++){
        cin>>a; p2.push_back(a);
    }
    
    while(p1.size()>=2)
    {
        int bounces=ceil(log2(p1.size()));
        int e1=p1.front();
        p1.pop_front();
        int e2=p1.front();
        p1.pop_front();

        int r1=p2.front();
        p2.pop_front();
        int r2=p2.front();
        p2.pop_front();
        if(bounces%2==0)
        {
            p2.push_back(max(e1,e2));
            p1.push_back(max(r1,r2));
            // cout<<e1<<" "<<e2<<endl;
        }
        else if(bounces%2==1)
        {
            p2.push_back(min(e1,e2));
            p1.push_back(min(r1,r2));
            // cout<<e1<<" "<<e2<<endl;
        }
    }
    cout<<p1.front()-p2.front();
    
	return 0;
}