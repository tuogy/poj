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

const int mxn = 15, mxl = 101;
const ll mod = 1000000007LL * 1000000007LL;
string str[mxn];
int strl[mxn], arrpfx[mxn][mxl], lcsp[mxn][mxn], dp[1 << mxn][mxn], dp_opt[1 << mxn][mxn];
ll hashsuffix[mxn][mxl], hashprefix[mxn][mxl], c2ll[26], mul[mxl];
bool issubstr[mxn];

void kmp_prefix(int i) {
    string& s = str[i];
    int n = strl[i], *q = arrpfx[i];
    q[0] = -1;
    for (int i = 1, j = -1; i < n; i++) {
        while (j > -1 && s[j + 1] != s[i]) j = q[j];
        if (s[j + 1] == s[i]) j++;
        q[i] = j;
    }
}

bool match(int is, int ip) {
    string &s = str[is], &p = str[ip];
    int ns = strl[is], np = strl[ip], *q = arrpfx[ip];
    for (int i = 0, j = -1; i < ns; i++) {
        while (j > -1 && p[j + 1] != s[i]) j = q[j];
        if (p[j + 1] == s[i]) j++;
        if (j == np - 1) return true;
    }
    return false;
}

bool verify(int isuff, int ipref, int l) {
    string &s = str[isuff], &p = str[ipref];
    int ls = strl[isuff];
    for (int i = 0; i < l; i++) {
        if (p[i] != s[ls - l + i]) return false;
    }
    return true;
}

bool lt_lexi(int s, int i_cur, int i_prev, int j_cur, int j_prev) {
    int s_cur = s, s_prev = s;
    while (j_cur >= 0) {
        if (str[j_cur][i_cur] < str[j_prev][i_prev]) return true;
        else if (str[j_cur][i_cur] > str[j_prev][i_prev]) return false;
        else i_cur++, i_prev++;
        if (i_cur == strl[j_cur]) {
            int j_cur_next = dp_opt[s_cur][j_cur];
            s_cur ^= 1 << j_cur;
            if (s_cur)
                i_cur = lcsp[j_cur][j_cur_next];
            j_cur = j_cur_next;
        }
        if (i_prev == strl[j_prev]) {
            int j_prev_next = dp_opt[s_prev][j_prev];
            s_prev ^= 1 << j_prev;
            if (s_prev)
                i_prev = lcsp[j_prev][j_prev_next];
            j_prev = j_prev_next;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    mul[0] = 1;
    for (int i = 1; i < mxl; i++) mul[i] = (mul[i - 1] << 2) % mod;
    int T, n; cin >> T;
    for (int ks = 1; ks <= T; ks++) {
        memset(issubstr, false, sizeof(issubstr));
        memset(lcsp, 0, sizeof(lcsp));
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> str[i];
            strl[i] = str[i].size();
            kmp_prefix(i);
        }
        for (int ip = 0; ip < n; ip++) {
            for (int is = 0; is < n; is++) {
                if (ip == is || strl[ip] > strl[is] || (strl[ip] == strl[is] && ip < is)) continue;
                if (match(is, ip)) {
                    issubstr[ip] = true; break;
                }
            }
        }
        c2ll['A' - 'A'] = 0, c2ll['C' - 'A'] = 1, c2ll['G' - 'A'] = 2, c2ll['T' - 'A'] = 3;
        for (int i = 0; i < n; i++) {
            if (issubstr[i]) continue;
            int l = strl[i];
            string& s = str[i];
            ll h = 0;
            for (int j = 0; j < l; j++) {
                h = (h << 2 | c2ll[s[j] - 'A']) % mod;
                hashprefix[i][j + 1] = h; 
            }
            h = 0;
            for (int j = 0; j < l; j++) {
                h = (h + c2ll[s[l - j - 1] - 'A'] * mul[j]) % mod;
                hashsuffix[i][j + 1] = h;
            }
        }
        for (int i = 0; i < n; i++) {
            if (issubstr[i]) continue;
            for (int j = 0; j < n; j++) {
                if (i == j || issubstr[j]) continue;
                int lmax = min(strl[i], strl[j]);
                for (int l = lmax; l; l--) {
                    if (hashsuffix[i][l] == hashprefix[j][l] && verify(i, j, l)) {
                        lcsp[i][j] = l; break;
                    }
                }
            }
        }
        int substrmask = 0;
        for (int i = 0; i < n; i++) {
            if (issubstr[i]) substrmask |= 1 << i;
        }
        for (int s = 1; s < 1 << n; s++) {
            if (s & substrmask) continue;
            for (int i = 0; i < n; i++) {
                if (s >> i & 1) {
                    int ss = s ^ 1 << i, best = INT_MAX, best_opt = -1;
                    if (ss == 0) best = 0;
                    else {
                        for (int j = 0; j < n; j++) {
                            if (ss >> j & 1) {
                                int cur = dp[ss][j] - lcsp[i][j];
                                if (cur < best || (cur == best && lt_lexi(ss, lcsp[i][j], lcsp[i][best_opt], j, best_opt))) 
                                    best = cur, best_opt = j;
                            }
                        }
                    }
                    dp[s][i] = strl[i] + best;
                    dp_opt[s][i] = best_opt;
                }
            }
        }
        int allstr = ((1 << n) - 1) ^ substrmask, best = INT_INF, bestj = -1;
        for (int j = 0; j < n; j++) {
            if (issubstr[j]) continue;
            if (dp[allstr][j] < best || (dp[allstr][j] == best && lt_lexi(allstr, 0, 0, j, bestj))) 
                best = dp[allstr][j], bestj = j;
        }
        cout << "Scenario #" << ks << ":" << endl;
        for (int i = 0, j = bestj, s = allstr; j >= 0;) {
            cout << str[j][i++];
            if (i == strl[j]) {
                int j_next = dp_opt[s][j];
                i = lcsp[j][j_next];
                s ^= 1 << j;
                j = j_next;
            }
        }
        cout << endl << endl;
    }

    return 0;
}
