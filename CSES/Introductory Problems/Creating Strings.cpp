#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

#define pb push_back
#define sz(A) (int)A.size()

string w;
map<string,bool>have;

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>w;
	sort(w.begin(), w.end());
	do
		have[w]=1;
	while(next_permutation(w.begin(), w.end()));

	cout<<have.size()<<'\n';
	for(auto &[u, xd]: have)
		cout<<u<<'\n';
}