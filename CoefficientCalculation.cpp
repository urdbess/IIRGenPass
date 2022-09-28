#include <math.h>
#include "IIRGenPass.h"

double omegaCalculation(double rFreq, PassType passType) {
    if (passType == HIGH) {
        return (1 / tan(M_PI * rFreq));
    }
    else {
        return (tan(M_PI * rFreq));
    }
}

//利用杨辉三角计算(x + 1)^N或(x - 1)^N的系数
void pascalTriangle(int	N, Symbol symbol, int* vector) {
    vector[0] = 1;
    if (N == 0) {
        return;
    }
    else if (N == 1) {
        if (symbol == SYMBOL_ADD) {
            vector[1] = 1;
        }
        else {
            vector[0] = -1; //如果是减号，则第二项系数是-1
            vector[1] = 1;
        }
        return;
    }
    int length = N + 1; //数组长度

    int* temp = new int[length];
    /*
    int temp[length];   //定义中间变量
    */

    temp[0] = 1;
    temp[1] = 1;

    for (int i = 2; i <= N; i++) {
        vector[i] = 1;
        for (int j = 1; j < i; j++) {
            vector[j] = temp[j - 1] + temp[j]; //x[m] = x[m-1][n-1] + x[m-1]
        }
        if (i == N) { //最后一次不需要给中间变量赋值
            if (symbol == SYMBOL_SUB) {//运算符为减号
                for (int k = 0; k < length; k++) {
                    vector[k] = vector[k] * pow((float)-1, length - 1 - k);
                }
            }
            return;
        }
        for (int j = 1; j <= i; j++) {
            temp[j] = vector[j];
        }
    }

    if (temp != NULL)
        delete[] temp;
}

//计算多项式相乘的系数
// originalCoef - 原来的系数数组，计算后的系数也存储在该数组内
// N - 上面系数数组对应的多项式系数个数
// nextCoef - 与原数组相乘的数组的系数
// nextN - 上面系数数组对应的多项式系数个数
void coefficientEquation(int* originalCoef, int	N, int* nextCoef, int nextN) {
    int* tempCoef = new int[N + nextN - 1];
    /*
    double tempCoef[N + nextN - 1];    //中间变量
    */
    for (int i = 0; i < N + nextN - 1; i++) {
        tempCoef[i] = originalCoef[i]; //中间变量初始化
        originalCoef[i] = 0;
    }

    for (int j = 0; j < nextN; j++) {
        for (int i = j; i < N + nextN - 1; i++) {
            originalCoef[i] += tempCoef[i - j] * nextCoef[j];
        }
    }
    if (tempCoef != NULL)
        delete[] tempCoef;
}