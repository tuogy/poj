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
FILE *__fp = fopen("__sample.in", "r");
#define scanf(...) fscanf(__fp, __VA_ARGS__)
#define cin fin
std::ifstream cin("__sample.in");
#endif

using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
const int INT_INF = 0x3f3f3f3f, INT_NINF = 0xc0c0c0c0;
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};

const int mxn = 1e6 + 5;
bool ishp[mxn], issemip[mxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(ishp, 0xff, sizeof(ishp));
    memset(issemip, 0, sizeof(issemip));
    for (int p = 5; p * p < mxn; p += 4) {
        if (!ishp[p]) continue;
        for (int q = p * p; q < mxn; q += (p << 2)) ishp[q] = false;
    }
    vector<int> hprimes;
    for (int p = 5; p < mxn; p += 4) {
        if (ishp[p]) hprimes.push_back(p);
    }

    for (int i = 0; hprimes[i] * hprimes[i] < mxn; i++) {
        int p = hprimes[i];
        for (int j = i; p * hprimes[j] < mxn; j++) {
            issemip[p * hprimes[j]] = true;
        }
    }   
    vector<int> hsemiprimes;
    for (int p = 1; p < mxn; p += 4) {
        if (issemip[p]) hsemiprimes.push_back(p);
    }

    int x;
    while (cin >> x) {
        if (x == 0) break;
        cout << x << " " << upper_bound(hsemiprimes.begin(), hsemiprimes.end(), x) - hsemiprimes.begin() << endl;
    }

    return 0;
}