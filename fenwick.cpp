struct Fenwick {
    int n;
    vector<long long> t;
    Fenwick(int n_): n(n_), t(n_ + 1) {}
    long long query(int i) {
        long long v = 0;
        for (; i > 0; i -= (i & -i)) v += t[i];
        return v;
    }
    long long query(int i, int j) {
        return query(j) - query(i - 1);
    }
    void update(int i, long long v) {
        for (; i <= n; i += (i & -i)) t[i] += v;
    }
};
