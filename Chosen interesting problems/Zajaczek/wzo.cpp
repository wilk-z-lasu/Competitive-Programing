#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

struct num{
    // const int base = 10;
    vector<int> x;
    num() {
        x.push_back(0);
    }
    bool operator==(const num &b) const {
        if(x.size() != b.x.size()) return 0;
        for(int i=0; i<(int)x.size(); i++) {
            if(x[i] != b.x[i]) return 0;
        }
        return 1;
    }
    void print() {
        for(auto i : x) cout<<i;
        cout<<"\n";
    }
    void get(){
        string s; cin>>s;
        x.clear();
        for(auto i : s) x.push_back(i-'0');
        if(x.size() == 0) x.push_back(0);
    }
    bool is_zero() {
        return (x.size() == 1 && x[0] == 0);
    }
    bool is_one() {
        return (x.size() == 1 && x[0] == 1);
    }
    bool is_even() {
        return (x.back() % 2 == 0);
    }
    bool is_odd() {
        return !is_even();
    }
    void remove_leading_zeros() {
        reverse(x.begin(), x.end());
        while(x.size() > 1 && x.back() == 0) x.pop_back();
        reverse(x.begin(), x.end());
    }
    void divide_by_2() { //floor of x/2
        int carry = 0;
        for(int i=0; i<(int)x.size(); i++) {
            int curr = carry * 10 + x[i];
            x[i] = curr / 2;
            carry = curr % 2;
        }
        remove_leading_zeros();
    }
    void multiply_by_2() {
        int carry = 0;
        for(int i=(int)x.size()-1; i>=0; i--) {
            int curr = x[i] * 2 + carry;
            x[i] = curr % 10;
            carry = curr / 10;
        }
        reverse(x.begin(), x.end());
        if(carry) x.push_back(carry);
        reverse(x.begin(), x.end());
    }
    num operator+(const num &b) const {
        num res;
        res.x.clear();
        int carry = 0;
        int n1 = (int)x.size(), n2 = (int)b.x.size();
        for(int i=0; i<max(n1, n2) || carry; i++) {
            int curr = carry;
            if(i < n1) curr += x[n1 - 1 - i];
            if(i < n2) curr += b.x[n2 - 1 - i];
            res.x.push_back(curr % 10);
            carry = curr / 10;
        }
        reverse(res.x.begin(), res.x.end());
        return res;
    }
    bool is_power_of_2() {
        num original = *this;
        while(!is_zero() && is_even()) {
            divide_by_2();
        }
        bool result = is_one();
        *this = original;
        return result;
    }
};

num n;
int LOG = 0;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    n.get();

    num akt = n;
    while(!akt.is_zero())
    {
        akt.divide_by_2();
        LOG++;
    }

    if(n.is_odd()) cout<<2*LOG + 1;
    else if(n.is_power_of_2()) cout<<2*LOG + 1;
    else cout<<2*LOG + 3;
    return 0;
}