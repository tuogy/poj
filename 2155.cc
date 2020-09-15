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

const int mxn = 1000;
bool bit[mxn + 1][mxn + 1];

void add(int x, int y) {
    for (int xx = x; xx; xx -= xx & -xx) {
        for (int yy = y; yy; yy -= yy & -yy) {
            bit[xx][yy] ^= 1;
        }
    }
}

bool query(int x, int y, int N) {
    bool tot = 0;
    for (int xx = x; xx <= N; xx += xx & -xx) {
        for (int yy = y; yy <= N; yy += yy & -yy) {
            tot ^= bit[xx][yy];
        }
    }
    return tot;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int X, N, T, x1, y1, x2, y2, x, y; 
    char op;
    scanf("%d", &X);
    for (int ks = 0; ks < X; ++ks) {
        scanf("%d%d", &N, &T);
        for (int i = 0; i <= N; i++) memset(bit[i], 0, (N + 1) * sizeof(bool));
        for (int i = 0; i < T; i++) {
            scanf(" %c", &op);
            if (op == 'C') {
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                add(x2, y2);
                add(x2, y1 - 1);
                add(x1 - 1, y2);
                add(x1 - 1, y1 - 1);
            }
            else {
                scanf("%d%d", &x, &y);
                int tot = query(x, y, N);
                printf("%d\n", tot);
            }
        }
        printf("\n");
    }

    return 0;
}