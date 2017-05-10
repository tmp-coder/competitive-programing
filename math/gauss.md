gauss消元模板
#gauss_jordan对角消元
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
