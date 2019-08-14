#include<bits/stdc++.h>

using namespace std;

#define ms(x,v) memset(x,(v), sizeof(x))
#define msn(x,v,n) memset(x,(v),sizeof(x[0]) * n)
/**
 * KM algorithm template
 */

#define MAXN 300+3
#define INF 0x3f3f3f3f

int n; //number of points 
bool S[MAXN]; // auxlary variable, current matched set on left
bool T[MAXN]; // auxlary variable, current matched set on right
int w[MAXN][MAXN]; // weight matrix, if i cannot conect to j,than w[i][j] = -inf
int slack[MAXN]; // auxlary variable, current slack variable
int mat[MAXN]; // point that right points matched
int lx[MAXN],ry[MAXN]; // value of left points x and value of right points y

/*
 * match function, from left to right
 */
bool match(int u){
    S[u] = true;
    for(int v = 0 ; v <n ; ++ v){
        if(T[v])continue;// v has been matched

        auto dis = lx[u] + ry[v] - w[u][v];
        if(dis==0){// ok, match it
            T[v] = true;
            if(mat[v] == -1 || match(mat[v])){// find a augumentation path
                mat[v] = u;
                return true;
            }
        }else slack[v] = min(slack[v],dis);// slack
    }
    return false;
}

int KM(){
    /*
    * init
    */
    ms(ry,0);
    ms(mat,-1);
    for(int v =0 ; v <n ; ++v)
        lx[v] = *max_element(w[v],w[v]+n);// not check
    
    for(int v =0 ; v < n ; ++ v){
        msn(slack,INF,n);
        
        while (true)
        {
            msn(S,0,n);
            msn(T,0,n);
            if(match(v))break;
            else{// update
                int d = INF;
                for(int i=0 ; i<n ; ++i)
                    if(!T[i]){// not in matched set
                        d = min(d,slack[i]);
                    }
                for(int i=0 ; i<n ; ++i)
                {
                    if(S[i])lx[i] -= d;
                    if(T[i])ry[i] += d;
                }
            }
        }
        
    }

    int ans =0;
    for(int v =0; v < n ; ++v)
        if(mat[v] !=-1){
            ans += w[mat[v]][v];
        }else return -1;
    return ans;
}

int noT;
int si[MAXN],ei[MAXN],li[MAXN];

int main(int argc, char const *argv[])
{   
    ios :: sync_with_stdio(0);
    cin.tie(0);
    std::cout.precision(8);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
    // another test for kick start 2019-B-B https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050eda/00000000001198c3, only test set1
    // cin >> noT;
    
    // for(int t_case =1 ; t_case <= noT; ++ t_case){
    //     cin >> n;
    //     for(int i=0 ; i<n; ++i)
    //         cin >> si[i] >> ei[i] >> li[i];
    //     for(int i=0; i< n ; ++i){
    //         w[i][0] = ei[i];
    //         auto loss = li[i]*si[i];
    //         for(int j=1 ; j<n ; ++j)
    //             w[i][j] = max(0,w[i][j-1]- loss);
    //     }

    //     cout << "Case #"<<t_case<<": " <<KM() << "\n";

    // }

    /*
     * test for hduoj 2255 http://acm.hdu.edu.cn/showproblem.php?pid=2255
     */
    while (cin >> n)
    {
        for(int i=0 ; i< n ; ++i)
            for(int j=0 ; j<n ; ++j)
                cin >> w[i][j];
        cout << KM() << "\n";
    }
    
    return 0;
}
