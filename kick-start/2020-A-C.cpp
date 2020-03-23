#include<bits/stdc++.h>

using namespace std;


bool ok(int x,int k,const vector<int> & time){
    int cnt = 0;
    for(int i=1 ; i<time.size() ; ++i){
        
        cnt += (time[i] - time[i-1] - 1) / x;
        if(cnt > k)
            return false;
    }
    return cnt <=k;
}
void solve(){
    int N, K;
    cin >> N >> K;
    vector<int> a(N,0);
    for(int i=0; i<N ; ++i)
        cin >> a[i];
    int left = 1;
    int right = a.back() - a[0];
    while(left <=right){
        int mid = (left + right) >> 1;

        if(ok(mid,K, a))right = mid -1;
        else left = mid +1;
    }
    cout << right + 1 << "\n";
}

int main(){
    int T;
    cin >> T;

    for(int t =1 ; t <= T ; ++ t){
        cout << "Case #"<<t<<": ";

        solve();
    }
    return 0;
}
