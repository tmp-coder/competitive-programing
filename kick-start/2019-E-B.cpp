#include<bits/stdc++.h>

using namespace std;

#define ms(x,v) memset(x,(v), sizeof(x))
#define msn(x,v,n) memset(x,(v),sizeof(x[0]) * n)
#define INF 0x3f3f3f3f
#define random(a,b) (rand() % ((b) -(a)) +(a))

typedef long long LL;
typedef pair<int,int> PII;

const double EPS = 2e-8;


bool cmp(const PII & a,const PII & b){
    //a.first /a.second > b.first /b.second
    return a.first * b.second > a.second * b.first;
}

bool check(double c,double e,double a,double b){
    if(c + EPS <a  || e +EPS < b )return false;
    double f = a /(c+EPS);
    if(c < EPS) return e+EPS >=b;
    return (1 - f) * e +EPS>=b ;
}

struct Query{
    int a,b;
    int id;
    bool ans;
};

void solve(){

    int D,S;
    cin >> D >> S;
    vector<PII> dd(S);
    for(int i=0 ; i<S ; ++i)cin >> dd[i].first >> dd[i].second;

    sort(dd.begin(), dd.end(), cmp);

    vector<int> sumC(S+1,0),sumE(S+1,0);

    for(int i=1; i<=S;  ++i)
        sumC[i] = sumC[i-1] + dd[i-1].first;
    for(int i=S-1 ; i >=0 ; --i)
        sumE[i] = sumE[i+1] + dd[i].second;
    vector<Query> qq(D);
    for(int i=0 ; i< D ; ++i)cin >> qq[i].a >> qq[i].b, qq[i].id = i;
    
    sort(qq.begin(),qq.end(),[](const Query& x,const Query &y)->bool{return x.a < y.a;});
    
    int pointer = 0;
    for(int i=0 ; i< S && pointer<D ; pointer++){
        auto & cur = qq[pointer];
        while (i<S-1 && sumC[i+1] < cur.a)
            ++i;
        if(sumC[i+1]>=cur.a && sumE[i+1]>=cur.b){
            cur.ans = true;
        }else{
            cur.ans = check(dd[i].first,dd[i].second,cur.a - sumC[i],cur.b - sumE[i+1]);
        }
    }
    sort(qq.begin(),qq.end(),[](const Query&x,const Query&y)->bool{return x.id < y.id;});

    cout << " ";
    for(const auto & e : qq)
        cout <<  (e.ans?'Y':'N');
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
