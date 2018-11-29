#include<bits/stdc++.h>

using namespace std;

#define ms(x,v) memset((x),v,sizeof(x))
#define INF 0x3f3f3f3f

const int MAXN = 55;


int a[MAXN];
int n,k;
bool ok(int x){
    int kk =1;
    int s =0;
    for(int i=1;  i<=n ; ++i){
        if(s + a[i] > x){
            kk++;
            s = a[i];
        }else s+=a[i];
    }
    return kk <=k;
}

int main(int argc, const char * argv[]) {

    int T;
    ios :: sync_with_stdio(0);
    cin.tie(0);


    cin >> T;
    while(T--){
        cin >> k >> n;
        if(k >n)k = n;
        for(int i=1 ; i <=n ; ++i)cin >>a[i];
        int low = 0;
        for(int i=1 ; i<=n ; ++i)if(low <a[i])low = a[i];

        int l = low;
        int r = 500 * n;
        while(l <=r){
            int mid = (l + r) >> 1;
            if(ok(mid))r = mid -1;
            else l = mid +1;
        }
        cout << r +1 << "\n";
    }    
    
    return 0;
}