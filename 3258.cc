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

int L, N, M, rocks[50000];

bool feasible(int x) {
    int c = 0, prev = 0;
    for (int i = 0; i < N && c <= M; i++) {
        if (rocks[i] >= prev + x) prev = rocks[i];
        else c++;
    }
    return c <= M && prev + x <= L;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> L >> N >> M;
    for (int i = 0; i < N; i++) cin >> rocks[i];
    sort(rocks, rocks + N);

    int l = 0, r = L + 1;
    while (l < r - 1) {
        int c = l + (r - l) / 2;
        if (feasible(c)) l = c;
        else r = c;
    }
    cout << l << endl;

    return 0;
}