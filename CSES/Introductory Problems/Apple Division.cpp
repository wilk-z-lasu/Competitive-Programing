#include <iostream>
using namespace std;

#define int long long

int n;
int p[21];

int solv=0;
int All=0;
int tmp;
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n;
	for(int i=0;i<n;++i)
		cin>>p[i];

	for(int i=0;i<n;++i)
		All+=p[i];

	solv = All;//mask=0
	for(int mask=1;mask<(1<<(n-1));++mask)
	{
		tmp=0;
		for(int i=0;i<n;++i)
			if((mask>>i) & 1)
				tmp+=p[i];
		solv = min(solv, abs(tmp-(All-tmp)));
	}
	cout<<solv;
	return 0;
}