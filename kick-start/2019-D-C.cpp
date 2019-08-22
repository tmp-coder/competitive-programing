#include<bits/stdc++.h>

using namespace std;

#define ms(x,v) memset(x,(v), sizeof(x))
#define msn(x,v,n) memset(x,(v),sizeof(x[0]) * n)
#define INF 0x3f3f3f3f

typedef long long LL;

typedef LL set_type;

typedef pair<LL,LL> PII;

const int MAXN = 2e5 +10;



void mutiset_delete_one(multiset<set_type>& se,const set_type val){
    se.erase(se.find(val));
}

void delete_from(const set_type val,multiset<set_type>& dele,multiset<set_type>& inse,LL & update_val,int multiplier){
    inse.insert(val);
    mutiset_delete_one(dele,val);
    update_val += val * multiplier;
}
void solve(){

    int N,K;
    cin >> K >> N;
    vector<PII> X(N);
    for(int i=0 ; i<N ; ++i)cin >> X[i].first;
    for(int i=0 ; i<N ; ++i)cin >> X[i].second;
    sort(X.begin(),X.end());

    multiset<set_type> lower,upper,lower_left,upper_left;
    lower_left.insert(INT32_MAX);
    upper_left.insert(INT32_MAX);
    LL usum = 0,lsum=0;
    for(int i=1;  i< X.size() ; ++i)upper.insert(X[i].first + X[i].second);
    int number = 0;
    auto rit = upper.begin();
    for( ; number < K ; ++number,++rit){
        usum += *rit;
    }
    upper_left.insert(rit,upper.end());
    upper.erase(rit,upper.end());
    LL ans = usum + X[0].second - K * X[0].first;

    for(int i = 1 ; i<N ; ++i){
        set_type center = X[i].first;
        set_type left =  - X[i-1].first + X[i-1].second;
        set_type right = X[i].first + X[i].second;
        // insert to left
        if(*(lower_left.begin()) <=left){
            lower_left.insert(left);
        }else
        {
            lsum += left;
            lower.insert(left);
            delete_from(*(--lower.end()),lower,lower_left,lsum,-1);
        }
        if(*upper_left.begin() > right){ // delete from upper
            mutiset_delete_one(upper,right);
            usum -= right;
            if(upper_left.size() > 1)
                delete_from(*upper_left.begin(),upper_left,upper,usum,1);
            else delete_from(*lower_left.begin(),lower_left,lower,lsum,1);
        }else
        {
            upper_left.erase(upper_left.find(right));//delete only one
        }
        

        bool balance = N==K+1;
        while (!balance)
        {
            LL lower_th = *lower_left.begin();
            LL upper_th = * upper_left.begin();
            
            if(lower_left.size() > 1 && lower_th  < upper_th - 2 *center && upper.size() >0){
                auto end_it = --upper.end();
                auto end_val = * end_it;
                if(lower_th  < end_val - 2 *center){
                    delete_from(end_val,upper,upper_left,usum,-1);
                    delete_from(lower_th,lower_left,lower,lsum,1);
                }else balance = true;
            }else if(lower.size() >0 && upper_left.size() >1){
                auto end_it = -- lower.end();
                auto end_val = * end_it;
                if(upper_th  < end_val + 2 *center){
                    delete_from(end_val,lower,lower_left,lsum,-1);
                    delete_from(upper_th,upper_left,upper,usum,1);
                }else balance = true;
            }else balance = true;
        }

        LL cur_ans = lsum + lower.size() * center + usum - upper.size() * center + X[i].second;
        if(ans > cur_ans)ans = cur_ans;
    }
    assert(ans >0);
    cout <<" "<< ans;
}

int main(int argc, char const *argv[])
{   
    
    ios :: sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0);
    std::cout.precision(8);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
    int T;
    cin >> T;
    
    for(int kase =1;  kase <= T ; ++kase)
    {   
        cout << "Case #"<<kase << ":";

        solve();
        cout << '\n';
    }
    return 0;
}
