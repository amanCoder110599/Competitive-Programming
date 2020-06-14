struct SegTree {
    vector<int> tree, lazy;
    SegTree(int n): tree(n * 4, MAXN), lazy(n * 4, -1) {

    }
    void merge(int node) {
        tree[node] = min(tree[node << 1], tree[node << 1 | 1]);
    }
    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
    int query(int node, int tl, int tr, int l, int r) {
        if (r < tl || tr < l)
            return MAXN;
        if (tl >= l && tr <= r)
            return tree[node];
        if(lazy[node] != -1)
            push(node);
        int mid = tl + tr >> 1, left = node * 2, right = left + 1;
        return min(query(left, tl, mid, l, r), query(right, mid + 1, tr, l, r));
    }
    int find_it(int l, int r, int X){
        return find_it(1, 0, n - 1, l, r, X);
    }
    int find_it(int node, int tl, int tr, int l, int r, int X){
        if (r < tl || tr < l)
            return 0;
        if (tl >= l && tr <= r) {
            if(tree[node] > X)
                return tr;
            if(tl == tr)
                return 0;
            if(lazy[node] != -1)
                push(node);
            int mx = 0;
            int mid = tl + tr >> 1, left = node * 2, right = left + 1;
            if(tree[left] < X)
                mx = max(mx, find_it(left, tl, mid, l, r, X));
            else if(tree[right] < X)
                mx = max(mx, max(mid, find_it(right, mid + 1, tr, l, r, X)));
            return mx;
        }
        if(lazy[node] != -1)
            push(node);
        int mid = tl + tr >> 1, left = node * 2, right = left + 1;
        return max(find_it(left, tl, mid, l, r, X), find_it(right, mid + 1, tr, l, r, X));
    }
    void update(int i, int j, int val) {
        rangeupdate(1, 0, n - 1, i, j, val);
    }
    void rangeupdate(int node, int tl, int tr, int l, int r, int val) {
        if (r < tl || tr < l) {
            return;
        }
        if (tl >= l && tr <= r) {
            tree[node] = val;
            lazy[node] = val;
        } else {
            int mid = tl + tr >> 1, left = node * 2, right = left + 1;
            if (lazy[node] != -1)
                push(node);
            rangeupdate(left, tl, mid, l, r, val);
            rangeupdate(right, mid + 1, tr, l, r, val);
            merge(node);
        }
    }
    void push(int node) {
        lazy[node * 2] = lazy[node];
        lazy[node * 2 + 1] = lazy[node];
        tree[node * 2] = lazy[node];
        tree[node * 2 + 1] = lazy[node];
        lazy[node] = -1;
    }
};
