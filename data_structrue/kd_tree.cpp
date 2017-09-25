
int _idx;//比较维度
struct KDNode{
    const static int max_dims = 5;
    int featrue[max_dims];
    int size;//子树节点个数
    int region[max_dims][2];//每个维度最大值最小值
    int dim;
    bool operator < (const KDNode& o)const{
        return featrue[_idx]<o.featrue[_idx];
    }
};
struct KDTree{
    int dims;
    KDNode Node[maxn];
    KDNode data[maxn<<2];
    bool flag[maxn<<2];
    priority_queue<pair<int,KDNode> > Q;//查询结果队列
    void build(int l,int r,int o,int dep,bool clc_region = false){
        //最后一个参数表明是否记录区域大小
        if(l>r)return;
        _idx = dep % dims;
        int lc = o<<1,rc = o<<1|1;
        flag[o] = true;
        flag[lc]=flag[rc] = 0;
        int mid = (l+r) >> 1;
        nth_element(Node+l,Node+mid,Node+r+1);
        data[o] = Node[mid];data[o].dim = _idx;
        // std::cout <<"node "<< o << '\n';
        // std::cout << _idx << '\n';
        // for(int i=0 ; i<dims ; ++i)std::cout << data[o].featrue[i] << ' ';std::cout  << '\n';
        data[o].size = r-l+1;
        if(clc_region){
            for(int i=0 ; i<dims ; ++i){
                _idx = i;
                data[o].region[i][0] = min_element(Node+l,Node+r+1)->featrue[i];
                data[o].region[i][1] = max_element(Node+l,Node+r+1)->featrue[i];
            }
            _idx = dep%dims;
        }
        build(l,mid-1,lc,dep+1,clc_region);
        build(mid+1,r,rc,dep+1,clc_region);
    }

    void k_close(const KDNode& p,int k,int o){
        if(!flag[o])return;
        int dim = data[o].dim;
        int lc = o<<1;int rc = o<<1|1;
        if(p.featrue[dim] >data[o].featrue[dim])swap(lc,rc);
        if(flag[lc])k_close(p,k,lc);
        pair<int,KDNode> cur(0,data[o]);
        for(int i=0 ; i<dims ; ++i)cur.fi+=SQ(p.featrue[i]-data[o].featrue[i]);
        bool fg = false;//右子树遍历标志
        if(Q.size() < k){
            Q.push(cur);fg =1;
        }else{
            if(cur.fi < Q.top().fi){
                Q.pop();Q.push(cur);
            }
            fg = SQ(p.featrue[dim]-data[o].featrue[dim]) < Q.top().fi;
        }
        if(flag[rc] && fg)k_close(p,k,rc);
    }
    int  check(int region[][2],int o){
        //1表示相交
        //－１表示全属于
        //0表示不相交
        if(!flag[o])return 0;
        bool fg = true;
        for(int i=0 ; i<dims ; ++i){
            if(data[o].region[i][0] < region[i][0] || data[o].region[i][1] > region[i][1]){
                fg = false;break;
            }
        }
        int d = data[o].dim;
        return fg?-1 : data[o].region[d][1] > region[d][0] || data[o].region[d][0]<region[d][1];
    }
    int find_size(int region[][2],int o){
        //查找范围内的点数
        //默认建树时有ｒｅｇｉｏｎ记录
        if(!flag[o])return 0;
        int ret =0;
        bool fg =1 ;//当前点是否在范围内
        for(int i=0 ; i<dims ; ++i)
            if(data[o].featrue[i]<region[i][0]||data[o].featrue[i]>region[i][1]){
                fg = 0;break;
            }
        ret += fg;
        int lc = o<<1,rc = o<<1|1;
        int lstate = check(region,lc),rstate = check(region,rc);
        if(lstate ==-1)ret += data[lc].size;
        else if(lstate == 1)ret += find_size(region,lc);
        if(rstate ==-1)ret += data[rc].size;
        else if(rstate == 1)ret += find_size(region,rc);
        return ret;
    }
};
