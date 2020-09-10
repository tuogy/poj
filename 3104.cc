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

int n, k, a[100000];

bool feasible(int x) {
    int c = 0;
    for (int i = 0; i < n && c <= x; i++) {
        if (a[i] > x) c += (a[i] - x - 1) / (k - 1) + 1;
    }
    return c <= x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    scanf("%d", &k);


    int l = 0, r = 1e9 + 1;
    if (k == 1) l = r = *max_element(a, a + n);
    while (l < r - 1) {
        int c = l + (r - l) / 2;
        if (feasible(c)) r = c;
        else l = c;
    }
    printf("%d\n", r);

    return 0;
}