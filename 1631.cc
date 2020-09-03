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

int p[40000];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T; cin >> T;
    for (int ks = 0; ks < T; ks++) {
        int P, x; cin >> P;
        for (int i = 0; i < P; i++) {
            cin >> x; p[i] = x - 1;
        }
        map<int, int> mp;
        map<int, int>::iterator it, del;
        mp[P] = 0;
        for (int i = P - 1; i >= 0; i--) {
            int v = mp.lower_bound(p[i] + 1)->second;
            it = mp.lower_bound(p[i]);
            if (it != mp.end() && it->second >= v + 1) continue;
            else {
                if (it != mp.begin()) {
                    --it;
                    while (true) {
                        if (it->second <= v + 1) {
                            if (it != mp.begin()) {
                                del = it; --it; mp.erase(del);
                            }
                            else {
                                mp.erase(it); break;
                            }
                        }
                        else break;
                    }
                }
                mp[p[i]] = v + 1;
            }
        }
        cout << mp.begin()->second << endl;

    }

    return 0;
}