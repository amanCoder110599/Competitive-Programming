int nxt[MAXN * 22][2];
int cnt[MAXN * 44];
struct Trie{
    int ptr;
    Trie(int n){
        ptr = 0;
        int i = 0;
        for(i = 0; i < n * 22; i++){
            for(int j = 0; j < 2; j++)
                nxt[i][j] = -1;
        }
    }
    void insert(int num){
        int root = 0;
        for(int i = 19; i >= 0; i--){
            if(num & (1 << i)){
                if(nxt[root][1] == -1){
                    ptr++;
                    nxt[root][1] = ptr;
                    cnt[ptr]++;
                    root = ptr;
                }
                else{
                    cnt[nxt[root][1]]++;
                    root = nxt[root][1];
                }
            }
            else{
                if(nxt[root][0] == -1){
                    ptr++;
                    nxt[root][0] = ptr;
                    cnt[ptr]++;
                    root = ptr;
                }
                else{
                    cnt[nxt[root][0]]++;
                    root = nxt[root][0];
                }
            }
        }
    }
    void erase(int num){
        int root = 0;
        for(int i = 19; i >= 0; i--){
            if(num & (1 << i)){
                cnt[nxt[root][1]]--;
                root = nxt[root][1];
            }
            else{
                cnt[nxt[root][0]]--;
                root = nxt[root][0];
            }
        }
    }
    int max_num(){
        int num = 0;
        int root = 0;
        for(int i = 19; i >= 0; i--){
            if(cnt[nxt[root][1]] > 0){
                num |= (1 << i);
                root = nxt[root][1];
            }
            else
                root = nxt[root][0];
        }
        return num;
    }
    int query(int num){
        int to = 0;
        int root = 0;
        for(int i = 19; i >= 0; i--){
            if(num & (1 << i)){
                if(cnt[nxt[root][0]] > 0){
                    root = nxt[root][0];
                    to |= 1 << i;
                }
                else{
                    root = nxt[root][1];
                }
            }
            else{
                if(cnt[nxt[root][1]] > 0){
                    root = nxt[root][1];
                    to |= 1 << i;
                }
                else{
                    root = nxt[root][0];
                }
            }
        }
        return to;
    }
};