# 计数

[BEST定理](http://blog.csdn.net/popoqqq/article/details/77017325)
和这里不加证明的给出BEST定理，有向图$G,d_i = d_i^-=d_i^+$的欧拉回路数目为
$$
T_v*\prod_{i\in V(G)}(d_i-1)!
$$
i其中$T_v$ 为任意顶点$v$ 的　in_tree 或者　out_tree 数目

**注意：**
d定理中的欧拉回路和这个题里的不一样，定理中由于欧拉回路有环结构，与第一条边选取无关，而这个问题是算作不同的.


# mobius

# 基本公式定理

$$
\begin{aligned}
n &= \sum_{d\mid n}\phi(d)\\
\phi(n)&=\sum_{d\mid n}\mu(d)\frac nd
\end{aligned}
$$

# 分块求和

如果说计算式中出现了 $\sum_if(i)*g(\lfloor(n/i)\rfloor)$,则由于 $\lfloor\frac{n}{i}\rfloor$的取值只有 $O(\sqrt n)$ 种显然我们可以运用分段求和(可以打印出这样的值来看一下)记录$f$的前缀和，然后g就进行分段求和.
```c++
ll F(int n, int m, int d) {
    if (n > m) swap(n, m);
    ll ans = 0;
    n /= d, m /= d;
    for (int i = 1, last = 1; i <= n; i = last + 1) {
        last = min(n / (n / i), m / (m / i));
        ans += (ll)(sum[last] - sum[i - 1]) * (n / i) * (m / i);
    }
    return ans;
}
```

# 线性筛法笔记整理

线性筛法处理积性函数
```
void monius(){
    cnt =0;
    mu[1] = 1;
    memset(prime,0,sizeof(prime));
    for(int i = 2 ; i<maxn ; ++i){
        if(!prime[i]){
            prime[cnt++] = i;
            mu[i] =-1;
        }
        for(int j=0 ; j<cnt && i*prime[j]<maxn ; ++j){
            prime[i*prime[j]] = 1;
            if(i%prime[j])mu[prime[j]*i] = -mu[i];
            else {
                mu[i*prime[j]] = 0;
                break;
            }
        }
    }
    sum_mu[0] = 0;
    for(int i=1 ; i<maxn ; ++i)
        sum_mu[i] = sum_mu[i-1]+mu[i];
}
```

```c++
void phi_table(){
    cnt =0;
    phi[1] = 0;
    memset(prime,0,sizeof(prime));
    for(int i = 2 ; i<maxn ; ++i){
        if(!prime[i]){
            prime[cnt++] = i;
            phi[i] =i-1;
        }
        for(int j=0 ; j<cnt && i*prime[j]<maxn ; ++j){
            prime[i*prime[j]] = 1;
            if(i%prime[j])phi[prime[j]*i] = phi[i]*(prime[j]-1);
            else {
                phi[i*prime[j]]= phi[i]*prime[j];
                break;
            }
        }
    }
}
```
参考文献:

[贾智鹏 线性筛](https://wenku.baidu.com/view/2d706761aa00b52acec7ca63.html?re=view)

# 数论


# 公约数
## gcd

```c++
LL gcd(LL a,LL b)
{
    return b==0? a:gcd(b,a%b);
}
```
## ex_gcd

```c++
//返回值为最大公约数
LL ex_gcd(LL a,LL b,LL &x,LL &y)
{
    LL d = a;
    if(!b){x = 1,y = 0;}
    else{
      d = ex_gcd(b,a%b,y,x);
      y-=a/b*x;
    }
    return d;
}
```
# 素数

## 素因子分解
$朴素算法O(\sqrt n)$

```c++
void prime_factor(int n,map<int,int> &pf)//
{
    for(int i =2 ; i*i<=n ; ++i)//n为素数时!
    {
        while(n%i==0)
        {
            ++pf[i];
            n/=i;
        }
    }
    if(n!=1)pf[n] = 1;
}
```
## Eratosthenes筛法

```c++
void Eratosthenes(int n)
{
    memset(is_prime,true,sizeof(is_prime));

    for(int i = 2 ; i*i<=n; ++i)
        if(is_prime[i])
        for(int j=i*i ; j<=n ; j+=i)is_prime[j] = false;
}
```
## 区间筛法

```c++
void segment_sieve(LL a,LL b)//[a,b]
{
    memset(is_prime_ab,true,sizeof(is_prime_ab[0])*(b-a+1));
    memset(is_prime_sqrtb,true,sizeof(is_prime_sqrtb[0])*(sqrt(b)+2));
    for(LL i = 2 ; i*i<=b ; ++i)
    if(is_prime_sqrtb[i]){
        for( LL j = i*i ; j*j<=b ; j+=i)is_prime_sqrtb[j] = false;
        for(LL j = max(i*i,(a-1)/i+1)*i ; j<=b ; j+=i)is_prime_ab[j-a] = false;
    }
}
```
#大素数分解与大素数测试

##miller_rabin

已知最快的素数分解算法.$O(lgV)$

```c++
bool witness(LL a,LL n,LL u,LL t){
	LL x0 = power_mod(a,u,n),x1;
	for(int i=1 ;i<=t ; ++i){
		x1 = mulmod(x0,x0,n);
		if(x1==1 && x0!=1 && x0!=n-1)
			return false;
		x0 = x1;
	}
	if(x1 !=1)return false;
	return true;
}

bool miller_rabin(LL n, int times = 20){
	if(n<2)return false;
	if(n==2)return true;
	if(!(n&1))return false;
	LL u = n-1,t =0;
	while (u%2==0) {
		t++;u>>=1;
	}
	while (times--) {
		LL a = random(1,n-1);
		//if(a == 0)std::cout << a << " "<<n<< " "<<u<<" " << t<<'\n';
		if(!witness(a,n,u,t))return false;
	}
	return true;
}
```

##pollard_rho
分解一个合数$V$的运行时间$O(V^{1/4 })$
```c++
/*
*pollard_rho分解n,
*c : 随机迭代器，每次运行设置为随机种子往往更快.
*/
LL pollard_rho(LL n,LL c = 1){
	LL x  = random(1,n);
	LL i =1,k =2,y = x;
	while (1) {
		i++;
		x = (mulmod(x,x,n)+c)%n;
		LL d = gcd(y-x>=0?y-x:x-y,n);
		if(d!=1 && d!=n)return d;//非平凡因子.
		if(y==x)return n;//重复.
		if(i==k){ y = x ; k<<=1;}//将x_1,2,4,8,16,..赋值为y.
	}
}
```
* 找出因子分解
$O(V^{1/4}lgV)$


```c++
void find_factor(LL n,std::map<LL, int>  & m){
	if(n<=1)return ;
	if(miller_rabin(n)){
		++m[n];
		return ;
	}
	LL p = n;

	while (p==n)p = pollard_rho(p,random(1,n));
	find_factor(p,m);
	find_factor(n/p,m);
}
```

#euler phi函数
$\phi(n) = n\prod_{i = 1}^{k}(1-\frac{1}{p_i})$
证明详见《初等数论及其应用》

```c++
int  euler_phi(int  n)
{
    int  ans = n;
    for(int i=2 ; i*i<=n ; ++i)
        if(ans%i ==0)
        {
            ans = ans/i*(i-1);
            while(n%i==0)n/=i;
        }
        if(n>1)ans = ans/n*(n-1);
    return ans;
}
```
phi_table,类似于线性筛的做法

```c++
void phi_table(int n)
{
    memset(phi,0,sizeof(phi[0])*(n+5));
    phi[1] = 1;
    for(int i = 2 ; i<=n ; ++i)
    {
        if(!phi[i])//素数标记
        {
            for(int j = i ; j<=n ; j+=i)
            {
                if(!phi[j])phi[j] = j;
                phi[j] = phi[j]/i*(i-1);
            }
        }
    }
}
```

# 模运算
## power_mod

```c++
LL power_mod(LL x,LL n,LL mod)
{
    LL res = 1;
    while(n)
    {
        if(n&1)res = (res*x)%mod;
        x = (x*x)%mod;
        n>>=1;
    }
    return res;
}

```
## 大数乘法取模

```c++
LL mulmod(LL a,LL b,LL mod){
	LL res =0,y = a%mod;
	while (b) {
		if(b&1)res = (res+y)%mod;
		b>>=1;
		y = (y<<1)%mod;
	}
	return res;
}
```


##大整数取模

```c++
LL big_mod(string val,LL mod)
{
    LL res = 0;
    for(int i=0 ; i<val.length() ; ++i)
    {
        res = ((res)*10+val[i]-'0')%mod;
    }
    return res;
}
```
## 模方程
```c++
LL MLE(LL a,LL b,LL n){
    LL d,x,y;
    d = ex_gcd(a,n,x,y);
    if(b%d !=0){
        return -1;
    }else{
        LL x0 = x*b/d%n+n;
        return x0%(n/d);//模（n/d)
    }
}
```
## 乘法逆元
a在模n意义下的逆
```c++
LL inv(LL a,LL n){
    LL x,y;
    LL d = ex_gcd(a,n,x,y);
    return d==1? (x+n)%n:-1;//非负性保证.
}
```
## 中国剩余定理
```c++
//x % m[i] = a[i]
LL china(int n,int *a,int *m){
    LL M = 1,x = 0,y,z;
    for(int i=0 ; i<n ; ++i)M*=m[i];
    for(int i=0 ; i<n ; ++i){
        LL M_i = M/m[i];
        ex_gcd(M_i,m[i],y,z);//M_i*y = 1(mod m[i])
        x = (x+M_i*a[i]*y)%M;
    }
    return (x+M)%M;
}
```

## 朴素模方程($m_i不两两互素的时候$)

```c++
LL MLE(int *r,int *mod,int n){
	LL lm = 0, lb = 1;
	for (int i = 0; i < n; i++)
	{
		LL k1,k2;
		LL d= exgcd(lb, mod[i],k1,k2);	// x=c1(mod r1)
		if ((lm - r[i]) % d) { return -1; }	// 联立x=r2(mod m2)，(r1-r2)=0(mod gcd)才有解
		lb = lb / d * mod[i];							// lcm
		LL z = k2 * ((lm - r[i]) / d);						// 求出k2
		lm = z * mod[i] + r[i];											// 得到方程组的一个最小解
		lm = ((lm % lb) + lb) % lb;										// 保证最小解大于0
	}
	return lm;
}

```
# 莫比乌斯反演
线性筛法$O(n)$
```c++
int prime[maxn],cnt;
int mu[maxn];

void init_mobius(){
    memset(prime,0,sizeof(prime));
    mu[1] =1;
    cnt =0;
    for(int i=2 ;i<maxn ; ++i){
        if(!prime[i]){
            prime[cnt++] = i;
            mu[i] = -1;
        }
        for(int j=0 ; j<cnt && i*prime[j]<maxn ; ++j){
            prime[i*prime[j]] = 1;
            if(i%prime[j])mu[i*prime[j]] = -mu[i];
            else {
                mu[i*prime[j]] = 0;
                break;
            }
        }
    }
}
```

＃　离散对数

# 原根与阶

## 阶定义
设 $(a,m)=1$, 满足 $a^x \equiv 1(mod\ m)$ 的最小的 $x$，称为a对m的阶，记为
$ord_{m}(a)$
当 $ord_{m}(a)=\phi(m)$ 时称为a为m的原根.

## 简单性质

1. $a^x\equiv 1\Leftrightarrow ord_m(a) \mid x$
2. $ord_m(a) \mid \phi(m)$
3. $a^0,a^1,\dots ,a^{ord_m(a)-1}$ 构成摸m的既约剩余系.
4. $a^x\equiv a^y(mod\ m)\Leftrightarrow x\equiv y(mod \ ord_m(a))$
5. $ord_m(a^d) = \frac{ord_m(a)}{(ord_m(a),d)}$(利用这个性质可以求出所有原根)
6. m(若存在原根)的原根数目为 $\phi(\phi(m))$ .
7. $n有原根\Leftrightarrow n=2,4,p^e,2p^e(p为奇素数)$.
8. 设 $\phi(m)=p_1^{r_1}p_2^{r_2}\dots p_k^{r_k}$,则$g是m$的原根当且仅当对与所有的$p_i$.
   $$
   g^{\frac{\phi(m)}{p_i}}\neq 1(mod\ m)
   $$

## 求阶和原根的方法

上面的性质是非常容易证明的.随便找一本数论书籍都会有详细的证明.由上面的性质我们可以得到一个相对简单的求阶和原根的方法(暴力)

- **阶:** 我门可以对m先分解因子，设$m=p_1^{r_1}p_2^{r_2}\dots p_k^{r_k}$ ，然后将$r_i$逐个相减记为$p$直到再减一个之后$a^p\neq 1$
- **原根:** 这个就更加暴力了，我们可以用性质8逐一枚举与$m$互素的数然后对分解式进行验证就好.

这里有一份51nod模板题1135的代码
```c++
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<cmath>
#include <cstring>
#include <map>
#include <iomanip>
#define fi first
#define se second
#define INF 0x3f3f3f3f
using namespace std;
const int MOD = 1e9+7;
const int MAX_P = 2e4+10;
const int maxn =2e5+10;
const int MAX_V = 5e5+10;
const int maxv = 1e6+10;
typedef long long LL;
typedef long double DB;
typedef pair<int,int> Pair;
int p;
int prime[maxn],cnt;
int factor[maxn],fact_cnt;
void init_prime(){
    memset(prime,0,sizeof(prime));
    cnt = 0;
    for(int i = 2 ; i<maxn ; ++i){
        if(!prime[i]){
            prime[cnt++] = i;
        }
        for(int j =0 ; j<cnt && prime[j]*i<maxn ; ++j){
            prime[prime[j]*i] = 1;
            if(i % prime[j] == 0)break;
        }
    }
}
LL power_mod(LL x,LL n,LL mod){
    LL res =1;
    while (n) {
        if(n & 1)res = res*x % mod;
        x = x*x % mod;
        n >>= 1;
    }
    return res;
}
void get_fact(int n){
    fact_cnt = 0;
    for(int i = 0 ; i< cnt && prime[i]*prime[i] <=n ; ++i ){
        if(n % prime[i] == 0){
            factor[fact_cnt++] = prime[i];
            while (n%prime[i] == 0)n/=prime[i];
        }
    }
    if(n!=1)factor[fact_cnt++] = n;
}

bool check(int g){
    for(int i=0 ; i<fact_cnt ; ++i)
        if(power_mod(g,(p-1)/factor[i],p) ==1)return false;
    return true;
}

int proot(int p){
    get_fact(p-1);
    for(int i=2 ; i<p ; ++i)
        if(check(i))return i;
}

int main(int argc, char const *argv[]) {
    init_prime();
    cin>>p;
    std::cout << proot(p) << '\n';
  return 0;
}
```


# 离散对数

## bsgs algorithm

$A^x\equiv C (mod\ m)$
大步小步算法，这个算法有一定的局限性，只有当$gcd(a,m)=1时才可以用$.

## 原理
简单说一下它的原理.其实由上面的性质，我们知道$0\le x<ord_m(a)$,设$x=uT-v$则原方程转化为$a^{uT}\equiv Ca^v(a^{-1}存在)$ 我们可以预处理出每一个 $Ca^v$对每一个计算出的 $a^{uT}$ 找一下有没有等于 $Ca^v$ 的取($T=\sqrt m$)复杂度 $O(\sqrt {m}lg(m))$

## 扩展大步小步
上面的过程能求离散对数的前提是 $a^{-1}$ 存在即若 $gcd(a,m)=1$ 则大步小步是可用的，现在我们来扩展一下大步小步算法.使得即使对任意的 $m$ 都能求出$x$或者不存在时返回-1.
由于模方程$ax\equiv b(mod\ m)\Leftrightarrow \frac{a}{d}x\equiv \frac{b}{d}(mod\ \frac{m}{d}),d=gcd(a,m)$(证明见《初等数论及其应用》),我们可以对$a,m,b$ 不断消因子,直到 $(a,m)=1$ 设共进行 $\delta$ 次消因子操作，那么 $\delta$ 次操作以后就变成了 $a^{x-\delta}a^\delta\equiv b'(mod\ m')$,(若消因子中途遇见b不能整除返回-1,若中途遇见$b等于a^{\delta}$ , 直接返回 $\delta$).现在就可以用大步小步算法来求解了.详细内容请看代码.
模板题[spoj MOD - Power Modulo Inverted](http://www.spoj.com/problems/MOD/en/)

```c++
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<cmath>
#include <cstring>
#include <map>
#define fi first
#define se second
#define INF 0x3f3f3f3f
using namespace std;
const int MOD = 1e9+7;
const int MAX_P = 2e4+10;
const int maxn =500+10;
const int MAX_V = 5e5+10;
const int maxv = 1e6+10;
typedef long long LL;
typedef pair<int,int> Pair;

LL power_mod(LL x,LL n, int mod){
   LL res =1;
   while (n) {
      if(n&1)res = res*x % mod;
      x = x*x %mod;
      n >>=1;
   }
   return res;
}

LL bsgs(LL A,LL C,LL mod){
   A %= mod;C %= mod;
   if(C==1)return 0;
   LL cnt =0;
   LL tmp = 1;
   for(LL g = __gcd(A,mod) ; g != 1 ; g = __gcd(A,mod)){
      if(C % g)return -1;//不能整除
      C /=g ; mod/=g ; tmp = tmp*A/g%mod;
      ++cnt;
      if(C == tmp)return cnt;
   }
   //大步小步a^xa^cnt=C (mod m)a^cnt = tmp;
   LL T = (LL)sqrt(0.5+mod);
   LL b = C;
   map<LL,LL> hash;
   hash[b] = 0;
   for(int i=1 ; i<=T ; ++i){
      b = b*A%mod;//当mod为LL时注意溢出
      hash[b] = i;
   }
   A = power_mod(A,T,mod);
   for(int u =1 ; u<=T ; ++u){
      tmp = tmp*A %mod;
      if(hash.count(tmp))return u*T-hash[tmp]+cnt;
   }
   return -1;
}

int main(int argc, char const *argv[]) {
   LL x,y,z,k;
   while (scanf("%lld%lld%lld",&x,&z,&k ) && z) {
      y = bsgs(x,k,z);
      if(y==-1)std::cout << "No Solution" << '\n';
      else std::cout << y << '\n';
   }
   return 0;
}

```

# 积性函数

# 题目链接
[Count a * b](http://acm.hdu.edu.cn/showproblem.php?pid=5528)

# 分析

这是很有意思的积性函数问题

反过来定义
$$
\begin{align}
h(m) &= m^2 - f(m)\\
&=\sum_{a,b}[a*b\%m=0]\\
&=\sum_{a=1,b}^m gcd(a,m)|b\\
&=\sum_{a=1}^m gcd(a,m)\\
&=\sum_{d|m}d*\phi(m/d)
\end{align}
$$
即$h(m)$ 是恒等映射与Euler函数的狄利克雷卷积，所以它是积性函数
对于素数$p$
$h(p^k) = \sum_{i=0}^kp^i*\phi(p^{k-i})=p^k+\sum_{i=0}^{k-1}p^i(p^{k-i}-p^{k-i-1})=p^{k-1}(k*(p-1)+p)$

所以
$$
\begin{align}
g(n)&=\sum_{d|n}d^2-h(d)
\end{align}
$$
分别求
$$
g1(n) =\sum_{d|n}d^2\\
g2(n)=\sum_{d|n}h(d)
$$

$g1,g2$均是1和积性函数的狄利克雷卷积，所以他们都是积性函数.以$g2$举例$n=p_1^{r1}\dots p_k^{r_k}$
$$
\begin{align}
g2(n)&=\prod_{i=1}^k g2(p^r_i) \\
&=\prod_{i=1}^k(\sum_{j=0}^{r_i}h(p_i^j))
\end{align}
$$

# AC code

```
//Problem : 5528 ( Count a * b )     Judge Status : Accepted
//RunId : 22241701    Language : G++    Author : zouzhitao
//Code Render Status : Rendered By HDOJ G++ Code Render Version 0.01 Beta
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
#define sci(x) scanf("%d",&x );
#define scf(x) scanf("%lf",&x );
#define eps 1e-8
#define dcmp(x) (fabs(x) < eps? 0:((x) <0?-1:1))
#define lc o<<1
#define rc o<<1|1
using namespace std;
typedef unsigned long long ULL;
typedef long long LL;
typedef long double DB;
typedef pair<int,int> Pair;
const int maxn = 1e5+10;
int prime[maxn],cnt;//

void getPrime(/* arguments */) {
    cnt =0;
    ms(prime,0);
    for(int i=2;  i<maxn ; ++i){
        if(!prime[i]){prime[cnt++] = i;}
        for(int j=0 ; j<cnt&&prime[j]*i < maxn ; ++j){
            prime[i*prime[j]] =1;
            if(i%prime[j]==0)break;
        }
    }
}

ULL power_mod(ULL x,ULL n){
    ULL ret =1;
    while (n) {
        if(n&1)ret*=x;
        n>>=1;
        x=x*x;
    }
    return ret;
}

ULL H(ULL p,ULL k){
    return k==0?1 :power_mod(p,k-1)*(k*(p-1)+p);
}
ULL SQRT(ULL p,ULL k){
    return power_mod(p,2*k);
}

int main()
{
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);
    int T;
    getPrime();
    scanf("%d",&T );
    while (T--) {
        int n;
        cin>>n;
        int nn = n;
        ULL f1=1,f2=1;
        for(int i=0 ; i<cnt && prime[i]*prime[i]<=nn; ++i){
            if(n%prime[i]==0){
                int k=0;
                while (n%prime[i]==0) {
                    n/=prime[i];k++;
                }
                ULL val1 = 0;
                ULL val2 =0;
                ULL p = prime[i];
                for(int i=0 ; i<=k ;++i){
                    val1 += H(p,i);val2 += SQRT(p,i);
                }
                f1 *=val1;
                f2 *= val2;
            }
        }
        if(n!=1){
            f1 *= (H(n,0)+H(n,1));
            f2 *= (SQRT(n,0)+SQRT(n,1));
        }
        std::cout << f2-f1 << '\n';
    }
    //std::cout << "time "<< clock()/1000 <<"ms"<< '\n';
    return 0;
}
```

# 欧拉函数

# 问题
$x$已知，求
$$
\sum_{gcd(a,x)=1}a
$$
我们知道这样的　$a$ 只有$\phi(x)$ 个，我们想能否用经典的gauss求等差数列的方法来解决这个问题呢?
s设　$gcd(a,x)=1$，那麽有　$gcd(x-a,x)=1$因此对于任意的数　$a,gcd(a,x)=1$ 则有　对应的$x-a，满足gcd(x-a,x)=1$,因此我们有
$$
\begin{align}
&\sum_{gcd(a,x)=1}a\\
&=\frac{\phi(x)x}{2}
\end{align}
$$

# gauss消元

# gauss消元模板
# gauss_jordan对角消元
```c++
typedef double Matrix[maxn][maxn];
int n;
//消元为对角阵
void gauss_jordan(Matrix A,int n){
    //A增广矩阵，第n列是结果列
    for(int i=0 ; i<n ; ++i){
        int r = i;//元素最大列
        for(int j = i+1 ; j<n ; ++j)
            if(abs(A[j][i]) > abs(A[r][i]))r = j;
        if(abs(A[r][i]) < eps)continue;
        if(r!=i)for(int j = 0 ; j<=n; ++j)swap(A[r][j],A[i][j]);//交换
        //与i行以外的所有行消元，化为阶梯阵,与gauss消元的不同
        for(int k=0 ; k<n ; ++k)
            if(k!=i)
            for(int j = n ; j>=i ; --j)A[k][j] -=A[k][i]/A[i][i]*A[i][j];//精度.
    }
}
```

# 异或方程组消元求秩

```c++
int my_rank(Matrix &A, int m,int n){
    int i=0 ,j = 0,r;
    while (i<m && j < n) {
        int r =i ;
        for(int k =i ; k<m ; ++k)
            if(A[k][j]){r=k ; break;}
        if(A[r][j]){
            if(r != i)for(int k = 0 ; k<n ; ++k)swap(A[r][k],A[i][k]);
            for(int u= i+1 ; u<m ; ++u)
                if(A[u][j])
                    for(int k = j ; k<n ; ++k)
                        A[u][k] ^= A[i][k];
            ++i;
        }
        j++;
    }
    return i;
}
```
