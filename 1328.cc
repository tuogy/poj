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

#ifdef __APPLE__
#define cin fin
std::ifstream cin("__sample.in");
#endif

using namespace std;


typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int INT_INF = 0x3f3f3f3f;
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};

bool compare(const pii& a, const pii& b) {
    return a.first + sqrt(a.second) < b.first + sqrt(b.second);
}

void solve(int n, int d) {
    vector<pii> v;
    int x, y;
    bool valid = true;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        if (y > d) {
            valid = false;
        }
        else {
            v.push_back(make_pair(x, d * d - y * y));
        }
    }
    if (!valid) {
        cout << -1 << endl; return;
    }
    sort(v.begin(), v.end(), compare);
    double cur = -1e20;
    const double eps = 1e-8;
    int ret = 0;
    for (int i = 0; i < v.size(); i++) {
        pii p = v[i];
        if (p.first - sqrt(p.second) > cur + eps) {
            ret++, cur = p.first + sqrt(p.second);
        }
    }
    cout << ret << endl;
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, d;
    int ks = 1;
    while (cin >> n >> d) {
        if (n == 0 && d == 0) break;
        cout << "Case " << ks << ": ";
        solve(n, d);
        ks++;
    }

    return 0;
}