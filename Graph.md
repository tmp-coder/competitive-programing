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
```

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
