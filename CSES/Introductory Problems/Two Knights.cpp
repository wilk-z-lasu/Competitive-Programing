#include <iostream>
using namespace std;

#define int long long

int n;

int32_t main() 
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;++i)
	{
		// int odp = (i*i)*(i*i-1)/2;
		// int second_row = 8*i;//2nd row above
		// int first_row = (16*i - 16);//1st row about
		// cout<<odp - ((8*i*i)-first_row-second_row)/2<<endl;

		cout<< (i*i*i*i - 9*i*i + 24*i - 16)/2<<endl;
	}
	return 0;
}