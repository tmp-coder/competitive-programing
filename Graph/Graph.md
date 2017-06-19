总结一下图论算法的模板
#图的储存
临接表，用这种方法比"链式前向星"，好，主要是写起来简单，而且在空间上的效率是一样的 $O(|V|+|E|)$
```c++
int ne,nv;
struct Edge{
  int from,to,weight;
  Edge(int u,int v,int w):from(u),to(v),weight(w){};
};
std::vector<Edge> E;
std::vector<int> G[MAX_V];
void add_edge(int u,int v,int w){
  E.push_back(Edge(u,v,w));
  G[u].push_back(E.size()-1);
}
```
#最短路

##dijkstra
在没有负边的时候使用，$O(|E|lg|V|)$
```c++
void dijkstra(int s){
  priority_queue<PII,std::vector<PII> ,greater<PII> > pq;
  memset(dist,INF,sizeof(dist));
  pq.push(PII(0,s));
  dist[s] = 0;
  while (!pq.empty()) {
    PII p = pq.top();pq.pop();
    int d = p.fi,u = p.se;
    if(dist[u]<d)continue;
    for(int i=0 ; i<G[u].size() ; ++i)
    {
      int e = G[u][i];
      int v = E[e].to;
      if(dist[v]>dist[u]+E[e].weight){
        dist[v] = dist[u]+E[e].weight;
        pq.push(PII(dist[v],v));
      }
    }
  }
}

```
##Bellman_Ford
实现简单，复杂度 $O(|V|*|E|)$
```c++
bool Bellman_Ford(s)
{
  memset(d,INF,sizeof(INF));
  for(int i=0 ; i<nv ; ++i){
    for(int j=0 ; j<E.size() ; ++j)
    d[E[i].to] = min(d[E[i].to],d[E[i].from]+E[i].weight);
  }
  //负环判定
  for(int i=0 ; i<E.size() ; ++i){
    if(d[E[i].to]<d[E[i].from]+E[i].weight)return false;
  }
  return true;
}
```
##spfa
```c++
bool spfa(int s){
  memset(d,INF,sizeof(d));
  memset(inq,false,sizeof(inq));
  memset(cnt,0,sizeof(cnt));
  queue<int> Q;
  Q.push(s);
  d[s] = 0;
  inq[s] = true;
  while(!Q.empty())
  {
    int u = Q.front();
    inq[u] = false;
    for(int i=0 ; i<G[u].size() ; ++i){
      Edge &e = E[G[u][i]];
      if(d[e.to]>d[e.from]+e.weight){
        d[e.to] = d[e.from]+e.weight;
        if(!inq[e.to]){
          Q.push(e.to);inq[e.to] = true;
          if(++cnt[e.to]>n)return false;
        }
      }
    }
  }
  return true;
}
```
#次短路

##dijkstra
仿照求最短路，我们记录一下他的次短路，再做相应的更新，（允许重复走，所以肯定有次短路）
```c++
void dijkstra2(int s){
  memset(dist,INF,sizeof(dist));
  memset(dist2,INF,sizeof(dist2));
  priority_queue<PII,std::vector<PII> ,greater<PII> > pq;
  pq.push(PII(0,s));
  dist[s] = 0;
  while (!pq.empty()) {
    int d = pq.top().fi; int u = pq.top().se;
    pq.pop();
    if(dist2[u]<d)continue;
    for(int i=0 ; i<G[u].size() ; ++i){
      int e = G[u][i];
      int v = E[e].to;
      int tmp = d+E[e].weight;
      if(dist[v]>tmp){
        swap(dist[v],tmp);//可能d成为次短路
        pq.push(PII(dist[v],E[e].to));
      }
      if(dist2[v]>tmp && tmp>dist[v])
      {
        dist2[v] = tmp;
        pq.push(PII(tmp,E[e].to));
      }
    }
  }
}
```
#最小生成树
```c++
int kruskal(){
    sort(E.begin(),E.end());
    int res = 0;
    for(int i=0 ; i<E.size() ; ++i){
      int u = E[i].from,v = E[i].to;
      if(find(u)!=find(v)){
        UNION(u,v);
        res+=E[i].weight;
      }
    }
    return res;
}

```
#所有节点对的最短路
```
void floyd(){
  for(int k=1 ; k<=nv ; ++k)
    for(int i =1 ; i<=nv ; ++i)
      for(int j=1 ; j<=nv ; ++j){
        d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
      }
}
```
##传递闭包
上面的算法稍微修改以下就可以求传递传递闭包了。
```c++
void floyd(){
  for(int k=1 ; k<=nv ; ++k)
    for(int i =1 ; i<=nv ; ++i)
      for(int j=1 ; j<=nv ; ++j){
        d[i][j] |=d[i][k]&d[k][j];
      }
}
```
# 若干和dfs相关的算法

##　二分图判定
```c++
std::vector<int> G[maxn];//G[u][i]表示第ｉ个邻居

int color[maxn];//0:未着色,1:黑色,2:白色.
//同找奇环
bool bipartite(int u){
    //仿照dfs
    for(auto v: G[u]){
        if(color[v]==color[u])return false;
        if(!color[v]){
            color[v] = 3-color[u]//对立颜色
            if(!bipartite(v))return false;
        }
    }
    return true;
}
```

## 割点和桥
```c++
//判断重边可以开个map来判断.然后置为-1
int dfs_clock = 0;//时间戳
int pre[maxn];//顶点的访问顺序
int low[maxn];//子树的最低访问时间
int cut[maxn];//割点后能增加的联通分量数
void init(){
    memset(pre,0,sizeof(pre));
    memset(cut,0,sizeof(cut));
    dfs_clock = 0;
}
//只能跑一个连通分量中的割点
void dfs(int u,int fa){
    low[u] = pre[u] = ++dfs_clock;
    int cl = 0;//孩子数目
    for(int i=0 ; i<G[u].size() ; ++i){
        Edge & e = E[G[u][i]];
        int v = e.to;
        if(!pre[v]){
            cl++;
            dfs(v,u);
            low[u]= min(low[u],low[v]);
            //判断割点
            if(low[v] >= pre[u])cut[u]++;//增加(u,v)的联通集
            //判断割边
            if(low[v] > pre[u] && e.qiao !=-1)e.qiao = 1;
        }else if(pre[v] < pre[u] && v != fa){
            low[u] = min(low[u],pre[v]);
        }
    }
    if(fa == -1 && cl == 1)cut[u] = 0;//根节点
}
```
## 双连通分量bcc
```c++
std::vector<int> G[maxn];
int dfs_clock = 0;//时间戳
int pre[maxn];//顶点的访问顺序
int low[maxn];//子树的最低访问时间
int cut[maxn];//割点后能增加的联通分量数
int bcc_cnt;
std::vector<int> bcc[maxn];//双连通分量点集
int bcc_no[maxn];//每个点的临时编号

stack<Pair> S;

void init(){
    memset(pre,0,sizeof(pre));
    memset(cut,0,sizeof(cut));
    dfs_clock = 0;
    bcc_cnt = 0;
    memset(bcc_no,0,sizeof(bcc_no));
}
//求双连通分量
void dfs(int u,int fa){
    low[u] = pre[u] = ++dfs_clock;
    int cl =0;
    for(auto v : G[u]){
        Pair e = mp(u,v);
        if(!pre[v]){
            ++cl;
            S.push(e);
            dfs(v,u);
            low[u] = min(low[u],low[v]);
            if(low[v]>=pre[u]){
                cut[u]++;//割点
                ++bcc_cnt;bcc[bcc_cnt].clear();
                while (true) {
                    Pair x = S.top();S.pop();
                    if(bcc_no[x.fi] != bcc_cnt){bcc[bcc_cnt].pb(x.fi);bcc_no[x.fi] = bcc_cnt;}
                    if(bcc_no[x.se]!= bcc_cnt){bcc[bcc_cnt].pb(x.se);bcc_no[x.se] = bcc_cnt;}
                    if(x == e)break;
                }
            }
        }else if(pre[v]<pre[u] && v!=fa){
            S.push(e);
            low[u] = min(low[u],pre[v]);
        }
    }
    if(fa<0 && cl==1)cut[u] = 0;//根节点
}

void get_bcc(int n){
    for(int i=0 ; i<n ; ++i){
        if(!pre[i])dfs(i,-1);
    }
}
```
# 强联通分量分解
```c++



std::vector<int> G[MAX_V];
std::vector<int> rG[MAX_V];
bool vis[MAX_V];
int scc[MAX_V];
std::vector<int> vs;//访问结束时间栈
void add_edge(int u,int v){
  G[u].push_back(v);
  G[v].push_back(u);
}
void dfs(int u) {
  vis[u] = true;
  for(int i=0 ; i<G[u].size() ;++i)
    if(!vis[G[u][i]])dfs(G[u][i]);
  vs.push_back(u);
}

void rdfs(int u,int scc_cnt) {
  vis[u] = true;
  scc[u] = scc_cnt;
  for(int i=0 ; i<rG[u].size() ; ++i)
    if(!vis[rG[u][i]])rdfs(rG[u][i]);
}

int Kosaraju(int nv){
  int scc_cnt = 0;
  memset(vis,false,sizeof(vis));
  vs.clear();
  for(int i=0 ; i<v ; ++i)
    if(!vis[i])dfs(i);
  memset(vis,false,sizeof(vis));
  for(int i= vs.size()-1 ; i>=0 ; --i)
    if(!vis[vs[i]])rdfs(vs[i],++scc_cnt);
  return scc_cnt;
}

```
# 网络流
##Dinic
```c++

struct Edge{
  int from,to,cap;
  Edge(int u,int v,int c = 0):from(u),to(v),cap(c){};
};

//残量网络
void add_edge(int u,int v,int cap){
  E.push_back(Egde(u,v,cap));G[u].push_back(E.size()-1);
  E.push_back(Edge(v,u,0));  G[v].push_back(E.size()-1);
}

struct Dinic{
  std::vector<Edge> E;
  std::vector<int> G[MAX_V];
  int level[MAX_V],cur[MAX_V];//分层，当前弧；
  void bfs(int s){
    memset(level,-1,sizeof(level));
    queue<int> Q;Q.push(s);
    level[s] = 0;
    while (!Q.empty()) {
      int u = Q.front();Q.pop();
      for(int i=0 ; i<G[u].size() ; ++i){
        Edge & e = E[G[u][i]];
        if(e.cap>0 && level[e.to]<0){
          level[e.to] = level[u]+1;
          Q.push(e.to);
        }
      }
    }
  }

  int dfs(int v,int t,int f){
    if(v==t || f == 0)return f;
    for(int& i = cur[v] ; i<G[v].size() ; ++i){
      Edge & e = E[G[v][i]];Edge & rev = E[G[v][i]^1];
      if(e.cap>0 && level[v]<level[e.to]){
        int a = dfs(e.to,t,min(f,e.cap));
        if(a>0){
          e.cap-=a;
          rev.cap+=a;
          return a;
        }
      }
    }
    return 0;
  }

  int max_flow(int s,int t){
    int flow = 0;
    for(;;){
      bfs(s);
      if(level[t]<0)break;
      memset(cur,0,sizeof(cur));
      int f;
      while ((f = dfs(s,t,INF))>0) {
        flow+=f;
      }
    }
    return flow;
  }
}

```
对于上面的建边的方式,e的反向边就是e^1,这个可以自行枚举证明.

##最大流最小切割定理
以下三个条件等价:
1. $f$ 是 $G$ 的最大流.
2. 残存网络中没有增广路
3. $|f| = c(S,T)$ 其中(S,T)是最小切割

###切割

$G$的某个切割 $\{S,T\}$ 是指，将图分为两个不相交的集合，$\{S,T\}$ 的容量为，从 ${S}$ d到 $T$ 的最大容量，即割边的最大容量

#二分图匹配
二分图的一个匹配是指二分图中的一些没有公共顶点的边集，匹配数就是边集的数目，最大匹配是指，使得这样的边集的数目最大.

##算法
当作网络流来处理，将$U 与 V$ 的边改成从 $U 流入 V$ 的一条边，其容量为一.对于这个多元多汇问题，我们只需要连一个超级节点 $S$ 到每一个源点，容量为1，再从每一个汇点连到一个超级汇点 容量也为一，这样这个图的最大流就是最大匹配数.

不过由于是二分图我们可不必真的这样实现

**Code**
```c++
int V;
std::vector<int> G[MAX_V];
bool used[MAX_V];
int match[MAX_V];

bool dfs(int u){
  used[u] = true;
  for(int i=0 ; i<G[u].size() ; ++i){
    int v = G[u][i];int w = match[v];
    if(w<0 || !used[w] && dfs(w)){
      match[u] = v;match[v] = u;
      return true;
    }
  }
  return false;
}

int bipartite_match(){
  int res = 0;
  memset(match,-1,sizeof(match));
  for(int i = 1 ; i<=V ; ++i){
    if(match[i]<0){
      memset(used,false,sizeof(used));
      if(dfs(i))res++;
    }
  }
  return res;
}

void add_edge(int u,int v){
  G[u].push_back(v);
  G[v].push_back(u);
}
```

#最小费用流
在概念上最小费用流只是在最大流的边上在附加一个费用，即求出从源点到汇点的给定流量的最小费用.

##算法
先从源点找一条到汇点的最短路，然后沿着最短路增广.建图的时候将反向边的费用设为-cost.(退流退费用)

**Code**

```c++
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
      if(dist[t]==INF)return break;//不能增广
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

```
