#include<bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f
#define INF64 0x3f3f3f3f3f3f3f3f
#define ms(x,v) memset(x,(v),sizeof(x))

typedef long long LL;
typedef pair<int,int> PII;
typedef tuple<int,int,int> TIII;
typedef pair<PII,int> PIII;
const int MAXN = 1e6+10;

int n, q;
vector<PII> book;

bool ok(int k){
    if(k==0)return true;
    vector<int> bg(q,0);

    for(int i=0 ; i< q ; ++i){
        int sweep_to = max(book[i].first,bg[i]),ed = book[i].second;
        int next_start = ed;
        int cnt =0;

        for(int j=i+1 ; j < q ; ++j){
            int l = book[j].first,r = book[j].second;
            if(l >ed)break;
            if(r <= ed){// must before the ith booking
                if(l >sweep_to)cnt += l - sweep_to;
                sweep_to = max(sweep_to,r);
                if(cnt >=k){// just ok
                    next_start = l - (cnt -k);
                    break;
                }
            }
        }
        assert(sweep_to <= ed);
        if(cnt <k){
            cnt += ed - sweep_to;
            if(cnt <k)return false;
            next_start = ed - (cnt - k);
        }

        // update left start point

        for(int j = i+1; j<q ; ++j){
            int l = book[j].first,r = book[j].second;
            if(l>=next_start)break;// can book before ith booking
            if(book[j].second > ed){// those booking must after ith booking 
                bg[j] = max(bg[j],ed);
            }
        }
    }
    return true;
}


int solve(){
    sort(book.begin(), book.end());
    int lo =0,hi = n;
    while(lo <= hi){
        int mid = (hi + lo) >> 1;
        if(ok(mid))lo = mid +1;
        else hi = mid -1;
    }
    assert(lo-1>=0);
    return lo -1;
}

int main(){

    ios :: sync_with_stdio(0);
    cin.tie(0);
    std::cout.precision(8);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
   
    int T;
    cin >> T;
    // cout << "T = " << T << "\n";
    for(int t =1 ; t <= T; ++t){

        cin >> n >> q;
        book.resize(q);
        for(int i=0 ; i<q ; ++i)
        {
            int l,r;
            cin >> l >> r;
            book[i] = {--l,r};
        }

        auto ans = solve();
        std::cout << "Case #"<<t<<": "<<ans<<"\n";
    }
    return 0;
}
