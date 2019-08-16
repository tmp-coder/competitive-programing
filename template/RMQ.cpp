struct RMQ{
    int minA[10][MAXN],maxA[10][MAXN];
    void init(const int * a,int n){
        for(int i=0 ; i<n ; ++i){
            minA[0][i] = maxA[0][i] = a[i];
        }
        for(int j=1 ; (1<<j)<=n ; ++j)
            for(int i=0 ; i+(1<<(j-1)) <n ; ++i){
                minA[j][i] = min(minA[j-1][i],minA[j-1][i+(1<<(j-1))]);
                maxA[j][i] = max(maxA[j-1][i],maxA[j-1][i+(1<<(j-1))]);
            }
    }

    pair<int,int> query_min_max(int l,int r){
        if(l>r)return PII(0,0);
        int k=0;
        while((1<<(k+1)) <= r-l+1) ++k;
        return make_pair(min(minA[k][l],minA[k][r-(1<<k)+1]),max(maxA[k][l],maxA[k][r-(1<<k)+1]));
    }

};
