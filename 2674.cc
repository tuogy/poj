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

const int mxn = 32000;
char dir[mxn], names[mxn][251];
int n;
float L, V, pos[mxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (scanf("%d", &n), n) {
        scanf("%f %f", &L, &V);
        for (int i = 0; i < n; i++) {
            scanf(" %c%f %s", dir + i, pos + i, names[i]);
        }
        char d = ' ';
        float longest = 0., t;
        int tot_n = 0;
        for (int i = 0; i < n; i++) {
            t = (dir[i] == 'p' || dir[i] == 'P') ? (L - pos[i]) / V : (tot_n++, pos[i] / V);
            if (t > longest) longest = t, d = dir[i]; 
        }
        if (d == 'n' || d == 'N') tot_n--;
        printf("%13.2f %s\n", int(longest * 100) / 100., names[tot_n]); 
    }

    return 0;
}