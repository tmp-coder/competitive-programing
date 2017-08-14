#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define PI acos(-1)
#define fi first
#define se second
#define INF 0x3f3f3f3f
#define INF64 0x3f3f3f3f3f3f3f3f
#define random(a,b) ((a)+rand()%((b)-(a)+1))
#define ms(x,v) memset((x),(v),sizeof(x))
#define scint(x) scanf("%d",&x );
#define scf(x) scanf("%lf",&x );
#define eps 1e-10
#define dcmp(x) (fabs(x) < eps? 0:((x) <0?-1:1))
#define torad(x) (PI*x/180)
#define lc o<<1
#define rc o<<1|1
using namespace std;
#define dcmp(x) (fabs(x) < eps? 0:((x) <0?-1:1))
struct Point{
    double x,y;
    Point( double _x=0,double _y=0):x(_x),y(_y){}
};
typedef Point Vector;

Vector operator + (Vector A,Vector  B){return Vector(A.x+B.x,A.y+B.y);}
Vector operator - (Vector A,Vector B){return Vector(A.x-B.x,A.y-B.y);}
Vector operator * (Vector A,double a){return Vector(a*A.x,a*A.y);}
Vector operator / (Vector A,double p){return A*(1/p);}
bool operator < (const Point  A,const Point  B){return mp(A.x,A.y) < mp(B.x,B.y);}
bool operator == (const Point A,const Point  B){return !dcmp(A.x-B.x) && !dcmp(A.y-B.y);}
double Dot(Vector A, Vector B){return A.x*B.x+A.y*B.y;}
double Length(Vector & A){return sqrt(Dot(A,A));}
double Angle(Vector &A,Vector & B){return acos(Dot(A,B)/Length(A)/Length(B));}
Vector Rotate(const Vector &A,double rad){return Vector(A.x*cos(rad)-sin(rad)*A.y,A.x*sin(rad)+A.y*cos(rad));}
Vector Normal(Vector A){//A 的单位法向量
    double L = Length(A);
    return Vector(-A.y/L,A.x/L);
}
double Cross(Vector A,Vector B){return A.x*B.y-A.y*B.x;}
double Area2(Point A,Point B,Point C){return Cross(B-A,C-A);}

Point GetLineIntersection(Point &P,Vector & v, Point & Q,Vector w){
    //计算交点,当v,w平行时无效
    Point u = P-Q;
    double t = Cross(v,u) / Cross(v,w);
    return Q+w*t;
}
double Dis2Line(Point &P,Point & A,Point & B){
    //点p到Ａ,B的距离
    Vector u1 = P-A;
    Vector u2 = B-A;
    return abs(Cross(u1,u2)/Length(u2));
}
Point GetLineProjection(Point &P,Point &A,Point & B){
    //the projection Point Q of P to Line A,B;
    Vector v = B-A;
    return A+ v*(Dot(v,P-A)/Dot(v,v));
}
bool SegInsertion(Point &A1,Point &A2,Point &B1,Point &B2){
    double c1 = Cross(A2-A1,B1-A1),c2 = Cross(A2-A1,B2-A1);
    double c3 = Cross(B2-B1,A1-B1),c4 = Cross(B2-B1,A2-B1);
    return dcmp(c1)*dcmp(c2) <0 && dcmp(c3)*dcmp(c4) <0;
}
bool onSegment(Point & P,Point &A,Point &B){
    return dcmp(Cross(A-P,B-P))==0 && dcmp(Dot(A-P,B-P)) <0;
}

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

//test
const int maxn = 2500+10;
Point p[maxn];
Point ch[maxn];

int main(int argc, char const *argv[]) {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);

    int T;
    cin>>T;
    while (T--) {
        int n;
        int cnt =0;
        cin>>n;
        double area = 0;
        for(int i=0 ; i<n ; ++i){
            double x,y,w,h,j;
            cin>>x>>y>>w>>h>>j;
            Point o(x,y);
            double rad = -torad(j);
            // std::cout << rad << '\n';
            // std::cout << "rad" << '\n';
            // std::cout << j << '\n';
            p[cnt++] = o+Rotate(Vector(-w/2,-h/2),rad);
            p[cnt++] = o+Rotate(Vector(-w/2,h/2),rad);
            p[cnt++] = o + Rotate(Vector(w/2,-h/2),rad);
            p[cnt++] = o + Rotate(Vector(w/2,h/2),rad);
            area+= w*h;
        }
        // std::cout << area << '\n';
        int m = ConvexHull(p,cnt , ch);
        double ans = area / polygonArea(ch,m);

        printf("%.1lf %%\n", ans*100);
    }
    return 0;
}
