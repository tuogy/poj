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

typedef pair<int, int> ii;
typedef long long ll;
const int INT_INF = 0x3f3f3f3f;
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};

int mem[1000005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N, T, s, e;
    cin >> N >> T;
    map<int, int> m;
    memset(mem, 0, (T + 1) * sizeof(int));
    for (int i = 0; i < N; i++) {
        cin >> s >> e;
        mem[s] = max(mem[s], e);
    }
    int ret = 0, cur = 0, next = 0;
    for (int i = 1; i <= T; i++) {
        if (i <= cur) next = max(next, mem[i]);
        else if (i <= next || mem[i] > 0) {
            ret++, next = max(next, mem[i]), cur = next;
        }
        else {
            cout << -1 << endl; return 0;
        }
    }
    cout << ret << endl;


    return 0;
}