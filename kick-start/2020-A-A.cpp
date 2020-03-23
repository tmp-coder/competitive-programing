#include<bits/stdc++.h>

using namespace std;



void solve(){
    int N,B;
    cin >> N >> B;
    vector<int> house(N,0);
    for(int i=0 ; i < N ; ++i)
        cin >> house[i];
    sort(house.begin(), house.end());
    int ans =0;
    for (int i=0 ; i< N ; ++i)
    {
        if(B < house[i])
            break;
        ans ++;
        B -= house[i];
    }
    cout << ans << "\n";
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
