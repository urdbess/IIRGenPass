#include <iostream>
#include <math.h>
#include "IIRGenPass.h"
using namespace std;

//pTaps[] = {b_0, ..., b_order, a_0, ..., a_order}
Status IIRGenPass_Butter(double rFreq, int order, double* pTaps, PassType passType) {
    
    //计算截止频率omega_c
    double omega_c = omegaCalculation(rFreq, passType);

    int length = order + 1; //a、b的系数组长度

    //计算Butterworth滤波器归一化函数系数
    double* a = butterGetNormalH(order);

    double* denominator = new double[length]; //存放分母系数
    double* numerator = new double[length]; //存放分子系数
    for (int i = 0; i < length; i++) {
        denominator[i] = 0;
        numerator[i] = 0;
    }

    //存放中间系数的临时数组
    int* tempCoef1 = new int[length];
    int* tempCoef2 = new int[length];

    //计算分子、分母的系数
    for (int i = 0; i <= order; i++) {
        for (int j = 0; j <= order; j++) {
            tempCoef1[j] = 0;     //tempCoef1和tempCoef2进行初始化
            tempCoef2[j] = 0;
        }

        //i ：1 + z^(-1)幂次数
        //otherN : 1 - z^(-1)幂次数
        int otherN = order - i;

        if (passType == HIGH) {
            pascalTriangle(i, SYMBOL_ADD, tempCoef1);      //利用杨辉三角计算1 + z^(-1)幂的系数
            pascalTriangle(otherN, SYMBOL_SUB, tempCoef2); //利用杨辉三角计算1 - z^(-1)幂的系数
        }
        else {
            pascalTriangle(i, SYMBOL_SUB, tempCoef1);      
            pascalTriangle(otherN, SYMBOL_ADD, tempCoef2); 
        }
        
        //tempCoef数组中的系数排列为[x^N, ..., x^0]
        coefficientEquation(tempCoef1, i + 1, tempCoef2, otherN + 1); //两个多项式相乘，求其系数

        //当otherN = order 即i = 0 时，tempCoef2中的多项式系数可用于计算分子系数
        if (i == 0) {
            for (int i = 0; i <= order; i++) {
                numerator[i] = pow(omega_c, order) * (double)tempCoef2[order - i];
            }
        }

        //计算分母系数
        for (int j = 0; j <= order; j++) {
            //将(1 + z^(-1))^i * (1 - z^(-1))^otherN的各系数依次加上
            denominator[j] += pow(omega_c, order - i) * (double)tempCoef1[order - j] * a[i];
        }
    }
    ////打印分母
    //cout << "分母系数：";
    //for (int i = 0; i < length; i++) {
    //    cout << denominator[i] << ", ";
    //}
    //cout << endl;
    

    ////打印分子
    //cout << "分子系数：";
    //for (int i = 0; i < length; i++) {
    //    cout << numerator[i] << ", ";
    //}
    //cout << endl;
    //cout << "omega_c " << omega_c;

    //系数归一化并统一放到pTaps数组中
    for (int i = 0; i <= order; i++) {
        pTaps[i] = numerator[i] / denominator[0];
        pTaps[i + order + 1] = denominator[i] / denominator[0];
    }

    delete[] tempCoef1;
    delete[] tempCoef2;
    delete[] denominator;
    delete[] numerator;

    return StsNoErr;
}
