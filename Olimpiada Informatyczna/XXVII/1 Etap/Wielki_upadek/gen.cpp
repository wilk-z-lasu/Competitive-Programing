#include <bits/stdc++.h>
using namespace std;

int N1;
int H1;
int N2;
int H2;
int MIN_N = 2, MAX_N = 20;
int MIN_X = 1, MAX_X = 1000;
int MIN_H = 1, MAX_H = 999;
int MIN_PARAM = 1, MAX_PARAM = 4;

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_param(MIN_PARAM, MAX_PARAM);

    N1 = dist_param(gen);
    H1 = dist_param(gen);
    N2 = dist_param(gen);
    H2 = H1*dist_param(gen);
    MIN_H = H2+1;
    
    std::uniform_int_distribution<> dist_n(MIN_N, MAX_N);
    std::uniform_int_distribution<> dist_x(MIN_X, MAX_X);
    std::uniform_int_distribution<> dist_h(MIN_H, MAX_H);
    int n = dist_n(gen);
    cout << n << "\n";
    vector<int> X(n), H(n);
    X[0] = dist_x(gen);
    H[0] = dist_h(gen);
    for (int i = 1; i < n; ++i) {
        // Ensure X is strictly increasing
        X[i] = X[i-1] + dist_x(gen);
        H[i] = dist_h(gen);
    }
    for (int i = 0; i < n; ++i)
        cout << X[i] << " " << H[i] << "\n";
    cout << N1 << " " << H1 << " " << N2 << " " << H2;
    return 0;
}