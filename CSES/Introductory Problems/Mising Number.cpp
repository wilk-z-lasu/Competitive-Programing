#include <iostream>
using namespace std;


constexpr int maxn = 2e5+7;

int n;
int x;
bool tab[maxn];
int32_t main() 
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;++i)
		tab[i]=0;
	for(int i=1;i<=n-1;++i)
	{
		cin>>x;
		tab[x]=1;
	}
	for(int i=1;i<=n;++i)
		if(!tab[i])
			cout<<i;
	return 0;
}