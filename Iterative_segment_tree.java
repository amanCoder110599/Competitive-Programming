class SegtreeMX {
            int[] segtree;
            int n;
            SegtreeMX(int n) {
                this.n = n;
                segtree = new int[2 * n];
            }

            int merge(int x, int y) {
                return Math.max(x, y);
            }

            void update(int ind, int val) {
                ind += n;
                segtree[ind] = val;
                for (; ind > 1; ind >>= 1)
                    segtree[ind >> 1] = merge(segtree[ind], segtree[ind ^ 1]);
            }

            int query(int l, int r) {
                int res = 0;
                for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
                    if ((l & 1) == 1)
                        res = merge(res, segtree[l++]);
                    if ((r & 1) == 1)
                        res = merge(res, segtree[--r]);
                }
                return res;
            }
        }
