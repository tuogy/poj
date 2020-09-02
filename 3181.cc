#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <climits>
#include <bitset>
#include <functional>

#ifdef __APPLE__
#define cin fin
std::ifstream cin("__sample.in");
#endif

using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
const int INT_INF = 0x3f3f3f3f;
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};
const int base = 10;
class BigInt {
public:
    vector<int> dts;
    BigInt(int n = 0) {
        dts.push_back(n);
    }
    void operator+=(const BigInt& val) {
        int sz_left = dts.size(), sz_right = val.dts.size();
        int sz = max(sz_left, sz_right);
        int carry = 0;
        for (int i = 0; i < sz; i++) {
            int left = i < sz_left ? dts[i] : 0;
            int right = i < sz_right ? val.dts[i] : 0;
            if (i >= sz_right && carry == 0) return;
            int s = left + right + carry;
            carry = s / base;
            if (i < sz_left) dts[i] = s % base;
            else dts.push_back(s % base);
        }
        if (carry) dts.push_back(carry);
    }

    void print() {
        for (int i = dts.size() - 1; i >= 0; i--) cout << dts[i];
    }
};

BigInt dp[1001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K; cin >> N >> K;

    dp[0] = 1;
    for (int k = 1; k <= K; k++) {
        for (int n = k; n <= N; n++) {
            dp[n] += dp[n - k];
        }
    }
    dp[N].print();

    return 0;
}