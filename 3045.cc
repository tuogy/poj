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

const int mxn = 50000;
int N, w[mxn], s[mxn];
ii b[mxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d%d", w + i, s + i);
    for (int i = 0; i < N; i++) b[i].first = w[i] + s[i], b[i].second = i;
    sort(b, b + N);
    int risk = INT_MIN;
    for (int i = 0, top = 0; i < N; i++) {
        risk = max(risk, top - s[b[i].second]);
        top += w[b[i].second];
    }
    printf("%d\n", risk);

    return 0;
}