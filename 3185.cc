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

const int mxn = 20;
int init[mxn], cur[mxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for (int i = 0; i < mxn; i++) cin >> init[i];
    memcpy(cur, init, sizeof(cur));
    int f0 = 1, nf0 = 0;
    for (int i = 1; i < mxn - 1; i++) {
        if (cur[i - 1]) {
            for (int k = -1; k <= 1; k++) cur[i + k] ^= 1;
            nf0++;
        }
    }
    if (cur[mxn - 2] ^ cur[mxn - 1]) nf0 = INT_MAX;
    else nf0 += cur[mxn - 1];

    memcpy(cur, init, sizeof(cur));
    cur[0] ^= 1, cur[1] ^= 1;
    for (int i = 1; i < mxn - 1; i++) {
        if (cur[i - 1]) {
            for (int k = -1; k <= 1; k++) cur[i + k] ^= 1;
            f0++;
        }
    }
    if (cur[mxn - 2] ^ cur[mxn - 1]) f0 = INT_MAX;
    else f0 += cur[mxn - 1];
    printf("%d\n", min(f0, nf0));
    

    return 0;
}