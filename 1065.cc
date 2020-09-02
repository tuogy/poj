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

ii stick[5000];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T, n;
    cin >> T;
    for (int ks = 0; ks < T; ks++) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> stick[i].first >> stick[i].second;
        sort(stick, stick + n);

        multiset<int> s; int ret = 0;
        multiset<int>::iterator it;
        for (int i = 0; i < n; i++) {
            it = upper_bound(s.begin(), s.end(), stick[i].second);
            if (it == s.begin()) ret++;
            else s.erase(--it);
            s.insert(stick[i].second);
        }

        cout << ret << endl;

    }

    return 0;
}