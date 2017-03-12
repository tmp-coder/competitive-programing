#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#include <set>
#define fi first
#define se second

using namespace std;

typedef long long LL;
typedef pair<int,int> Pair;

const int maxn = 50;
const int MAX_V = 2500;

struct Edge{
  int from,to,cap,cost;
  Edge(int f,int t,int c,int co):from(f),to(t),cap(c),cost(co){}
};
std::vector<Edge> E;
std::vector<int> G[MAX_V];
void add_edge(int u,int v,int cap,int cost){
  E.push_back(Edge(u,v,cap,cost));G[u].push_back(E.size()-1);
  E.push_back(Edge(v,u,0,-cost)) ;G[v].push_back(E.size()-1);
}
struct MCMF{
  int V;
  int dist[MAX_V];
  int pre_E[MAX_V];//最短路径弧
  bool inq[MAX_V];//spfa判断
  //未判断负圈
  void spfa(int s){
    memset(dist,INF,sizeof(dist));
    memset(inq,false,sizeof(inq));
    queue<int> Q;
    Q.push(s);
    dist[s] = 0;
    inq[s] = true;
    pre_E[s] = -1;
    while(!Q.empty())
    {
      int u = Q.front();Q.pop();
      inq[u] = false;
      for(int i=0 ; i<G[u].size() ; ++i){
        Edge &e = E[G[u][i]];
        if(e.cap>0&&dist[e.to]>dist[u]+e.cost){
          dist[e.to] = dist[u]+e.cost;
          pre_E[e.to] = G[u][i];
          if(!inq[e.to]){Q.push(e.to);inq[e.to] = true;}
        }
      }
    }
  }

  int min_cost_flow(int s,int t,int f){
    int res = 0;
    while (f>0) {
      spfa(s);
      if(dist[t]==INF) break;//不能增广
      //沿着最短路增广
      int d = f;
      for(int i = pre_E[t] ; i!=-1 ;i = pre_E[E[i].from])d = min(d,E[i].cap);
      f-=d;
      res+=d*dist[t];
      for(int i = pre_E[t] ; i!=-1 ;i = pre_E[E[i].from]){
        E[i].cap-=d;
        E[i^1].cap+=d;
      }
    }
    return res;
  }
};

MCMF mcf;

int a[maxn][maxn];
int main(int argc, char const *argv[]) {
  int N,M;
  while (scanf("%d%d",&N,&K )!=EOF) {
    for(int i=0 ; i<N ; ++i)
      for(int j=0 ; j<M ; ++j)
        scanf("%d",&a[i][j] );
    int ans  = a[0][0]+a[N-1][M-1];
    int s = N*M,t = s+1;
    E.clear();
    for(int i=0 ; i<= t  ; ++i)G[i].clear();
    for(int i=0 ; i<N ; ++i){
      for(int j = 0 ; j<M ; ++j){
        int u = i*M+j,v1 = u+1,v2 = (i+1)*N+j;
        if(j!=M-1){
          add_edge(u,v1,1,-a[i][j+1]);
          add_edge(u,v1,INF,0);
        }
        if(i!=N-1){
          add_edge(u,v2,1,-a[i+1][j]);
          add_edge(u,v2,INF,0);
        }
      }
    }
    add_edge(N*M-1,t,K,0);
    add_edge(s,0,K,0);
    ans+=(-mcf.min_cost_flow(s,t,K));
    std::cout << ans << '\n';
  }


  return 0;
}
