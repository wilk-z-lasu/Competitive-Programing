#include <iostream>
#include <algorithm>
using namespace std;


constexpr int maxn = 1e6+7;

int n;
char x;
char last='#';
int tmp_solv;
int solv=0;

int32_t main() 
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	while(cin>>x)
	{
		if(x==last)
			tmp_solv++;
		else
		{
			tmp_solv=1;
			last = x;
		}
		solv = max(solv, tmp_solv);
	}
	cout<<solv;
	return 0;
}