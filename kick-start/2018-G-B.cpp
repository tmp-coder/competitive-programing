#include<bits/stdc++.h>
#define ms(x,v) memset((x),v,sizeof(x))
#define INF 0x3f3f3f3f
using namespace std;
 
const int MAXN = 100+10;
typedef long long LL;

bool ok(LL x,int k,const vector<int>&L,const vector<int>&R,const vector<LL>&preL,const vector<LL>& preR){
    // cout << "\nok " << x << " " << k << "\n";
    auto iR = lower_bound(R.begin(),R.end(),x,greater_equal<int>()) - R.begin();
    auto iL = lower_bound(L.begin(),L.end(),x,greater_equal<int>()) - L.begin();
    // cout << iR << " " << iL << "\n";
    LL rank = preR[iR] - iR *x+iR;
    rank -= preL[iL] - iL * x;
    // cout << x << "rank " <<rank << "\n";
    return rank <k;
}


LL solve(vector<int >& L,vector<int>& R,const vector<int>&Q){
    LL ret =0;
    vector<LL> preSumR(L.size()+1),preSumL(L.size()+1);
    sort(L.begin(),L.end(),[](int a,int b){return a>b;});
    sort(R.begin(),R.end(),[](int a,int b){return a > b;});
    for(int i=0 ;i<L.size() ; ++i)
    {
        preSumL[i+1] = preSumL[i]+L[i];
        preSumR[i+1] = preSumR[i] + R[i];
    }

    for(int i=0 ; i<Q.size();  ++i){
        auto q = Q[i];
        int l =0,r = R[0]+1;
        while (l <r)
        {
            int mid = (l +r) >> 1;
            if(ok(mid,q,L,R,preSumL,preSumR)) r = mid -1;
            else l = mid;
            if(l + 1 >=r){
                if(!ok(r,q,L,R,preSumL,preSumR))l = r;
                break;
            }
        }
        LL ans = l;
        if(ans <0 || ans > R[0])ans =0;
        ret  += ans * (i+1);
    }
    return ret;
}


void solve(){
    int N,Q;
    cin >> N >> Q;

    LL x1,x2,a1,b1,c1,m1,y1,y2,a2,b2,c2,m2,z1,z2,a3,b3,c3,m3;
    cin >> x1 >> x2 >> a1 >> b1 >> c1 >> m1;
    cin >> y1 >> y2 >> a2 >> b2 >> c2 >> m2;
    cin >> z1 >> z2 >> a3 >> b3 >> c3 >> m3;
    vector<int> L(N),R(N),K(Q);
    L[0] = min(x1,y1) + 1,L[1] = min(x2,y2) + 1,K[0] = z1 + 1;
    R[0] = max(x1,y1) + 1,R[1] = max(x2,y2) + 1,K[1] = z2 + 1;
    for(int i=2 ; i<N ; ++i){

        LL x3 = (a1 *  x2 +b1*x1 + c1) % m1;
        LL y3 = (a2 * y2 + b2 * y1 + c2) % m2;
        x1 = x2,x2 = x3;
        y1 = y2, y2 = y3;
        if(x3 > y3)swap(x3,y3);
        L[i] = x3 + 1;
        R[i] = y3 + 1;
    }
    for(int i=2 ; i< Q;  ++i){
        
        LL z3 = (a3 * z2 + b3 * z1 + c3) % m3;
        K[i] = z3 +1;
        z1 = z2,z2 = z3;
    }
    cout << solve(L,R,K) << "\n";
}




int main(){
    ios :: sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0);
    std::cout.precision(10);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
 
    int T;
    cin >> T;
    for(int tt =1 ; tt <=T ; ++tt)
    {
        cout << "Case #" << tt << ": ";
        solve();
    }
    
 
    return 0;
}
