#include <iostream>
#include <string>
#include <queue>
using namespace std;

#define sz(A) (int)A.size()

string w;
int cnt[30];
deque<char>odp;
int32_t main() 
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>w;

	for(char &u: w)
		cnt[u-'A']++;

	for(int i=0;i<30;++i)
		if(cnt[i]%2==1)
		{
			odp.push_back('A'+i);
			cnt[i]--;
		}
	if(sz(odp)>1)
	{
		cout<<"NO SOLUTION";
		return 0;
	}

	for(int i=0;i<30;++i)
	{
		for(int j=1;j<=cnt[i];j+=2)
		{
			odp.push_back('A'+i);
			odp.push_front('A'+i);
		}
	}

	for(char &u: odp)
		cout<<u;
	return 0;
}