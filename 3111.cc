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
int n, k, v[mxn], w[mxn];
double d[mxn];
pair<double, int> dd[mxn];

bool feasible(double x) {
    for (int i = 0; i < n; i++) d[i] = v[i] - x * w[i];
    int kk = k - 1, l = 0, r = n - 1;
    while (l < r) {
        int c = l + rand() % (r - l + 1);
        swap(d[c], d[r]);
        double pivot = d[r];
        int i = l, j = l, p = r;
        while (j < p) {
            if (d[j] < pivot) swap(d[j], d[--p]);
            else if (d[j] > pivot) swap(d[i++], d[j++]);
            else j++;
        }
        swap(d[j], d[r]);
        if (l + kk < i) r = i - 1;
        else if (l + kk < j) break;
        else kk -= j - l, l = j;
    }
    double tot = 0;
    for (int i = 0; i < k; ++i) tot += d[i];
    return tot >= 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) scanf("%d%d", v + i, w + i);
    double l = 0., r = 1e7 + 1;
    for (int i = 0; i < 50; i++) {
        double c = (l + r) / 2;
        if (feasible(c)) l = c;
        else r = c;
    }
    for (int i = 0; i < n; i++) dd[i].first = v[i] - l * w[i], dd[i].second = i;
    
    int kk = k - 1, ll = 0, rr = n - 1;
    while (ll < rr) {
        int c = ll + rand() % (rr - ll + 1);
        swap(dd[c], dd[rr]);
        double pivot = dd[rr].first;
        int i = ll, j = ll, p = rr;
        while (j < p) {
            if (dd[j].first < pivot) swap(dd[j], dd[--p]);
            else if (dd[j].first > pivot) swap(dd[i++], dd[j++]);
            else j++;
        }
        swap(dd[j], dd[rr]);
        if (ll + kk < i) rr = i - 1;
        else if (ll + kk < j) break;
        else kk -= j - ll, ll = j;
    }

    for (int i = 0; i < k; ++i) {
        if (i < n - 1) printf(" ");
        printf("%d", dd[i].second + 1);
    }
    printf("\n");


    return 0;
}