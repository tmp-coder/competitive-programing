#include<bits/stdc++.h>

using namespace std;

#define ms(x,v) memset(x,(v), sizeof(x))
#define msn(x,v,n) memset(x,(v),sizeof(x[0]) * n)
#define INF 0x3f3f3f3f

typedef long long LL;
typedef pair<int,int> PII;

const int MAXN = 100000 + 3;
int n,r,c;
int sr,sc;
map<pair<int,int>,map<char,PII> > cell;
set<PII> mat;
PII next_cell(int x,int y,char dir){
    switch (dir)
    {
    case 'E':
        return make_pair(x,y+1);
    
    case 'W':
        return make_pair(x,y-1);
    case 'N':
        return make_pair(x-1,y);
    case 'S':
        return make_pair(x+1,y);
    }
}

pair<int,int > solve(int x,int y,char dir){
    auto cur_pos=  make_pair(x,y);
    PII ret;
    if(cell.count(cur_pos) && cell[cur_pos].count(dir))
    {   
        PII raw = cell[cur_pos][dir];
        ret = solve(raw.first,raw.second,dir);
        cell[cur_pos][dir] = ret;
        return ret;
    }
    if(!cell.count(cur_pos)){// bulid a empty map
        map<char,PII> tmp;
        cell[cur_pos] = tmp;
    }
    auto next_pos  = next_cell(x,y,dir);
    if(!mat.count(next_pos)){
        mat.insert(next_pos);
        cell[cur_pos][dir] = next_pos;
        return next_pos;
    }else{
        cell[cur_pos][dir] = solve(next_pos.first,next_pos.second,dir);
        return cell[cur_pos][dir];
    }
}

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
        cin >>n >>r >> c >> sr >> sc;
        string s;
        cin >> s;
        mat.clear();
        mat.insert(make_pair(sr,sc));
        cell.clear();
        
        auto cur = make_pair(sr,sc);
        for(auto e : s){
            cur = solve(cur.first,cur.second,e);
        }
        cout << "Case #"<<t << ": " << cur.first << " " << cur.second << "\n";
    }

    return 0;
}
