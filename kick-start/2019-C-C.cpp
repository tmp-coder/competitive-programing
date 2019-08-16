#include<bits/stdc++.h>

using namespace std;

#define ms(x,v) memset(x,(v), sizeof(x))
#define msn(x,v,n) memset(x,(v),sizeof(x[0]) * n)
#define INF 0x3f3f3f3f

typedef long long LL;
typedef pair<int,int> PII;

const int MAXN = 1000 + 3;

// discretize a vector
// 
// example:
// 1,10,3,5 -> 0,3,1,2
// NOTE: re-write parameter, not functional
// return : number of non-duplicated elements
int discretization(vector<int> & raw){
  
    // discretization
    vector<int> id = raw;
    sort(id.begin(),id.end());
    auto it_end = unique(id.begin() , id.end());
    for(int i=0 ; i<raw.size() ; ++i)
        raw[i] = lower_bound(id.begin(),it_end,raw[i]) - id.begin();
    
    return it_end - id.begin();
}


int n,K;
int main(int argc, char const *argv[])
{   
    ios :: sync_with_stdio(0);
    cin.tie(0);
    std::cout.precision(8);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
    int T;
    cin >> T;

    for(int t =1;  t <= T ; ++t)
    {   
        cin >> n >> K;
        
        vector<int> pos(n),comp(n);
        for(int i=0 ; i<n ; ++i)
            cin >> pos[i];
        for(int i=0 ; i<n ; ++i)
            cin >> comp[i];

        const int sz = discretization(comp);

        vector<vector<int> > groups(sz);
        for(int i=0 ; i<n ; ++i)
            groups[comp[i]].push_back(pos[i]);
        
        for(int i=0 ; i< sz ; ++i){
            sort(groups[i].begin(),groups[i].end());
        }

        vector<vector<int> > ldp(sz+1,vector<int>(K+1,INF)),rdp(sz+1,vector<int>(K+1,INF));

        ldp[0][0] = 0;
        for(int i=0 ; i< sz ; ++i){
            ldp[i+1] = ldp[i];
            for(int j=1 ; j<=groups[i].size() ; ++j)
                for(int k=j ; k <= K ; ++k)
                    ldp[i+1][k] = min(ldp[i+1][k],ldp[i][k-j] + groups[i][j-1]*2);
        }

        rdp[sz][0] =0;
        for(int i = sz -1 ; i>=0 ; --i){
            rdp[i] = rdp[i+1];
            for(int j=1 ; j<=groups[i].size() ; ++j)
                for(int k =j ; k<=K ; ++k)
                    rdp[i][k] = min(rdp[i][k],rdp[i+1][k-j] + groups[i][j-1]*2);
        }

        int ans = INF;
        for(int i=0; i<sz ; ++i)
            for(int j=1 ; j<=groups[i].size() && j<=K ; ++j)
                for(int k=0; k<=K-j ;++k){
                    int cur_ans = groups[i][j-1] + ldp[i][k]  + rdp[i+1][K-j-k];
                    ans = min(ans,cur_ans);
                }
        cout << "Case #"<<t << ": " << ans << "\n";
    }

    return 0;
}
