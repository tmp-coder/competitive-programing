//凸多边形面积凸包，及点在多边形内部的判断
//多边形

double polygonArea(Point *p,int n){
    double area =0;
    for(int i=1 ; i<n-1 ; ++i)
        area += Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}
//点在多边型内的判定
int isPointInPolygon(Point P,Point* poly,int n){
    int wn =0;
    for(int i=0 ; i<n ; ++i){
        if(onSegment(P,poly[i],poly[(i+1)%n]))return -1;//在直线上
        int k = dcmp(Cross(poly[(i+1)%n]-poly[i],P - poly[i]));
        int d1 = dcmp(poly[i].y - P.y);
        int d2 = dcmp(poly[(i+1)%n].y - P.y);
        if(k>0 && d1 <= 0 && d2>0)wn++;//逆时针穿过
        else if(k<0 && d2<=0 && d1 >0)wn--;
    }
    return wn !=0;
}

int ConvexHull(Point * p,int n,Point* ch){
    sort(p,p+n);
    int m=0;
    for(int i=0 ; i<n ; ++i){
        while (m>1 && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0)m--;//下凸包
        ch[m++] = p[i];
    }
    int k =m;
    for(int i=n-2 ; i>=0 ; --i){
        while (m >k && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2]) <=0)m--;
        ch[m++] = p[i];
    }
    if(n>1)m--;//第一个点
    return m;
}
