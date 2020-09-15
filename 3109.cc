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

const int mxn = 100000;
ii v[mxn];
int n, x[mxn], y[mxn], miny[mxn], maxy[mxn], minx[mxn], maxx[mxn];
int bit[mxn + 1];

void add(int* bit, int val, int yy, int ny) {
    for (yy++; yy <= ny; yy += yy & -yy) bit[yy] += val;
}

int prefix(int* bit, int yy) {
    int tot = 0;
    for (yy++; yy; yy -= yy & -yy) tot += bit[yy];
    return tot;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d%d", &v[i].first, &v[i].second);

    for (int i = 0; i < n; i++) {
        x[i] = v[i].first, y[i] = v[i].second;
    }
    sort(x, x + n);
    sort(y, y + n);
    int nx = unique(x, x + n) - x;
    int ny = unique(y, y + n) - y;
    memset(miny, 0x3f, nx * sizeof(int));
    memset(maxy, 0xc0, nx * sizeof(int));
    memset(minx, 0x3f, ny * sizeof(int));
    memset(maxx, 0xc0, ny * sizeof(int));
    memset(bit, 0, (ny + 1) * sizeof(int));
    vector<vector<int> > y_left(nx), y_right(nx);
    for (int i = 0; i < n; i++) {
        int xx = lower_bound(x, x + nx, v[i].first) - x;
        int yy = lower_bound(y, y + ny, v[i].second) - y;
        miny[xx] = min(miny[xx], yy);
        maxy[xx] = max(maxy[xx], yy);
        minx[yy] = min(minx[yy], xx);
        maxx[yy] = max(maxx[yy], xx);
        v[i].first = xx, v[i].second = yy;
    }
    for (int yy = 0; yy < ny; yy++) {
        y_left[minx[yy]].push_back(yy);
        y_right[maxx[yy]].push_back(yy);
    }
    ll tot = 0;
    for (int xx = 0; xx < nx; xx++) {
        for (int i = 0; i < y_left[xx].size(); i++) add(bit, 1, y_left[xx][i], ny);
        tot += prefix(bit, maxy[xx]) - prefix(bit, miny[xx] - 1);
        for (int i = 0; i < y_right[xx].size(); i++) add(bit, -1, y_right[xx][i], ny);
    }
    printf("%lld\n", tot);

    return 0;
}