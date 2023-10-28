class Segment_tree {
            long INF = (long) 1e14;
            long[] sum;
            long[] lazy;
            int n;

            Segment_tree(int x) {
                n = x;
                sum = new long[4 * n];
                lazy = new long[4 * n];
                Arrays.fill(sum, 0);
                Arrays.fill(lazy, 0);
            }

            long query(int l, int r) {
                return query(1, 0, n - 1, l, r);
            }

            long query(int node, int start, int end, int l, int r) {
                if(start > end || start > r || end < l) {
                    return 0;         // Out of range
                }
                if(lazy[node] != 0) {
                    // This node needs to be updated
                    sum[node] += (end - start + 1) * lazy[node];            // Update it
                    if(start != end) {
                        lazy[node*2] += lazy[node];         // Mark child as lazy
                        lazy[node*2+1] += lazy[node];    // Mark child as lazy
                    }
                    lazy[node] = 0;                 // Reset it
                }
                if(start >= l && end <= r) {           // Current segment is totally within range [l, r]
                    return sum[node];
                }
                int mid = (start + end) / 2;
                long p1 = query(node*2, start, mid, l, r);         // Query left child
                long p2 = query(node*2 + 1, mid + 1, end, l, r); // Query right child
                return (p1 + p2);
            }

            void rangeupdate(int i, int j, int val) {
                if (i > j) {
                    return;
                }
                rangeupdate(1, 0, n - 1, i, j, val);
            }

            void rangeupdate(int node, int start, int end, int l, int r, int val) {
                if(lazy[node] != 0) {
                    // This node needs to be updated
                    sum[node] += (end - start + 1) * lazy[node];    // Update it
                    if(start != end) {
                        lazy[node*2] += lazy[node];                  // Mark child as lazy
                        lazy[node*2+1] += lazy[node];                // Mark child as lazy
                    }
                    lazy[node] = 0;                                  // Reset it
                }
                if(start > end || start > r || end < l) {       // Current segment is not within range [l, r]
                    return;
                }
                if(start >= l && end <= r) {
                    // Segment is fully within range
                    sum[node] += (end - start + 1) * (long)val;
                    if(start != end) {
                        // Not leaf node
                        lazy[node*2] += val;
                        lazy[node*2+1] += val;
                    }
                    return;
                }
                int mid = (start + end) / 2;
                rangeupdate(node*2, start, mid, l, r, val);        // Updating left child
                rangeupdate(node*2 + 1, mid + 1, end, l, r, val);   // Updating right child
                sum[node] = sum[node*2] + sum[node*2+1];        // Updating root with max value
            }

        }
