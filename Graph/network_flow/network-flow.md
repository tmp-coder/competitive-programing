简要总结以下网络流的学习.

**参考资料**

* 《挑战程序设计竞赛》

* 《算法竞赛入门经典》-刘汝佳

* 《算法导论》

#最大流
**符号说明**

* $f(u,v)\ u,流向\ v$的流量
* $c(u,v)\ u,\ v$ 的容量
* $s,t$ 源点和汇点
##流网络
一个流网络总是满住以下限制条件的
****
**流量限制：** 对于任意的节点 $u,v$ 满足 $0 \le f(u,v) \le c(u,v)$

**流量守恒：** 任意顶点 $u\in V-\{s,t\}$  满足 流入总流量等于流出总流量

在最大流问题中我们要找到从源点到汇点的最大流量

##反向边
反向边可以这样理解，从 $a$到 $b$,发送 $10$ 箱货物，从 $b$ 到$a$ 发送 $5$ 箱货物，就等价于$a$ 向$b$ 发送了 5 箱货物.

##残留网络(residual network)
从直观上看，给定流网络$G$ ,与流量 $f$,残存网络 $G_f$ 表示那些每条边还能调整的容量，例如，在下图中

$v_3$到 $v_2$的流量为 $4$容量为 $9$ 在残存网络中，$v_3$ 到 $v_2$ 的最大改进量为 5,即最多还能流 $5$ 过去，而因为 $v_3$ 流了 $4$ 到 $v_2$ 所以 $v_2$ 流入 $v_3$ 的最多为 $4$,(把4流量退回去),形式化定义

>$$ c_f(u,v)=\left\{
\begin{aligned}
c(u,v) - f(u,v)  &\  若(u,v)\in E\\
f(u,v) &\ 若 (v,u)\in E(反向边)\\
0 & \ 其他
\end{aligned}
\right.
$

$c_f(u,v) = 0$的边不再算入，残存网络中.
##Ford-Fulkerson方法
这是一类算法，而不是一个算法。简单的说就是
1. 初始化flow = 0；
2. $while$ 存在一条增广路 $p$ (从汇点到源点的道路)在残留网络中
3. 沿着增广路增广.

用朴素的深搜找增广路的方法的复杂度是$O(F*V*E)$,我们可以做一些优化，先用广搜找出最短路，然后每次沿着最短路增广.这就是 *Dinic* 算法,

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

##负圈
$f$ 是最小费用流 $\iff$ 残留网络中没有负圈.

如果有负圈，很显然，沿着负圈走费用会更少，而且沿着圈走是永远满足条件的
