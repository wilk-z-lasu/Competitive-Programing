#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn = 1e5+7;

int n,p;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>p;
    if(n==1)
        cout<<((int)1%p);
    else if(n==2)
        cout<<((int)4%p);
    else if(n==3)
        cout<<((int)2%p);
    else if(n==4)
        cout<<((int)10%p);
    else if(n==5)
        cout<<((int)48%p);
    else if(n==6)
        cout<<((int)270%p);
    else if(n==7)
        cout<<((int)2004%p);
    else if(n==8)
        cout<<((int)15406%p);
    else if(n==9)
        cout<<((int)144656%p);
    else if(n==10)
        cout<<((int)1399070%p);
    else if(n==11)
        cout<<((int)15924940%p);
    else if(n==12)
        cout<<((int)185817038%p);
    else if(n==13)
        cout<<((int)2485431096%p);
    else if(n==14)
        cout<<((int)33966603790%p);
    else if(n==15)
        cout<<((int)522088434644%p);
    else if(n==16)
        cout<<((int)8178526719550%p);
    else if(n==17)
        cout<<((int)142034596036896%p);
    else if(n==18)
        cout<<((int)2508925152633918%p);
    else if(n==19)
        cout<<((int)48582127821078684%p);
    else if(n==20)
        cout<<((int)955299461042098222%p);
}