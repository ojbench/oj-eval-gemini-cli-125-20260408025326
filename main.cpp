#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX_BUF = 1 << 20;
char buf[MAX_BUF], *p1 = buf, *p2 = buf;

inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

inline int read() {
    int x = 0, f = 1;
    char ch = gc();
    while (ch < '0' || ch > '9') {
        if (ch == EOF) return -1;
        if (ch == '-') f = -1;
        ch = gc();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = gc();
    }
    return x * f;
}

const int MAXN = 2000005;
int I[MAXN], J[MAXN], E[MAXN];
int vals[MAXN * 2];
int parent_arr[MAXN * 2];

int find_set(int i) {
    int root = i;
    while (root != parent_arr[root]) {
        root = parent_arr[root];
    }
    int curr = i;
    while (curr != root) {
        int nxt = parent_arr[curr];
        parent_arr[curr] = root;
        curr = nxt;
    }
    return root;
}

void solve() {
    int t = read();
    if (t == -1) return;
    while (t--) {
        int n = read();
        int num_vals = 0;
        for (int k = 0; k < n; ++k) {
            I[k] = read();
            J[k] = read();
            E[k] = read();
            vals[num_vals++] = I[k];
            vals[num_vals++] = J[k];
        }
        sort(vals, vals + num_vals);
        num_vals = unique(vals, vals + num_vals) - vals;
        
        for (int k = 0; k < num_vals; ++k) {
            parent_arr[k] = k;
        }
        
        for (int k = 0; k < n; ++k) {
            if (E[k] == 1) {
                int u = lower_bound(vals, vals + num_vals, I[k]) - vals;
                int v = lower_bound(vals, vals + num_vals, J[k]) - vals;
                int root_u = find_set(u);
                int root_v = find_set(v);
                if (root_u != root_v) {
                    parent_arr[root_u] = root_v;
                }
            }
        }
        
        bool possible = true;
        for (int k = 0; k < n; ++k) {
            if (E[k] == 0) {
                int u = lower_bound(vals, vals + num_vals, I[k]) - vals;
                int v = lower_bound(vals, vals + num_vals, J[k]) - vals;
                if (find_set(u) == find_set(v)) {
                    possible = false;
                    break;
                }
            }
        }
        
        if (possible) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
}

int main() {
    solve();
    return 0;
}
