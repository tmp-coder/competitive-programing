#强联通分量分解总结
一个有向图的强联通分量的定义如下:

>若对于子图中的任意两个节点$u,v$总存在 $u$ 到 $v$ 的路径则这个子图称作这个图G的一个强联通分量

对于图的强联通分量分解，《算法导论》中介绍了Kosaraju Algorithm.

这个算法思想很简单:
1. dfs遍历有向图. 计算节点访问结束的时间.
2. 计算 $G^T$ 即边反向后的图.
3. 按照结束时间递减的顺序，dfs $G^T$

下面我们简单证明一下这个结论(不是很严谨，详细证明参见《算法导论》)

**引理 1**
>对于有向图中的两个强联通分量 $c1,c2$ 如果说有一条边 $(u,v)\in E，u\in c1,v\in c2$，则必定没有一条从 $c2到c1$ 的边.

这个结论是很显然的如果有一条边从 $u \leadsto v$显然 $c1$中的所有节点都可以到达 $c2$，如果又有另外一条边从 $c2$到达 $c1$ 那不是$c1,c2$ 中的所有节点都可以互相到达类吗.

**定理1**

>对于又向图中的两个强联通分量 $c1,c2$ 如果说有一条从 $c1$ 到 $c2$ 的边，则在第一次dfs中，$c1$ 的结束时间肯定比$c2$大,即 $f(c1)>f(c2)$

$$
f(c) = min(f(v))_{v\in c}
$$


分两种情况考虑，
1. $start(c1)>start(c2)$  分量$c1$的开始时间比$c2$晚的情况，由于$c2$没有到达$c1$的边，所以在$c2$中dfs的时候一定不能搜索到$c1$ 中的点，所以 $c2$会先结束.
2. $start(c1)<start(c2)$  分量$c1$的开始时间先于$c2$的情况，由于$c1$中一定有一条边 $(u,v)\in E,u\in c1,v\in c2$ 即$u$是$c2$的祖先,由深度优先的性质，祖先节点总是晚与子孙节点的结束时间，因此，$f(c1)>f(c2)$

由前面两个定理我们可以"感觉" 的到，当反过来遍历的时候由于从结束时间最大节点开始，由于边都已反向所以必然不会有边指出去，所以dfs,搜索到的节点一定是一个强联通分量.这样我们就可以由归纳法来证明这个算法的正确性.这里不做证明.

 下面给出这个算法的c++代码
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
