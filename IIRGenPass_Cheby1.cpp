#include <iostream>
#include <math.h>
#include "IIRGenPass.h"
using namespace std;


//Chebyshev1�˲���ϵ������
//pTaps[] = {b_0, ..., b_order, a_0, ..., a_order}
Status IIRGenPass_Cheby1(double rFreq, double ripple, int order, double* pTaps, PassType passType) {

    double omega_c = omegaCalculation(rFreq, passType);
    double epsilon = sqrt(pow(10, 0.1 * ripple) - 1);//���ƶ�Ӧ��epsilon
    int length = order + 1; //a��b��ϵ���鳤��

    double* denominator = new double[length]; //��ŷ�ĸϵ��
    double* numerator = new double[length]; //��ŷ���ϵ��
    for (int i = 0; i < length; i++) {//��ʼ������
        denominator[i] = 0;
        numerator[i] = 0;
    }

    //����м�ϵ������ʱ����
    int* tempCoef1 = new int[length];
    int* tempCoef2 = new int[length];

    for (int i = 0; i <= order; i++) {
        for (int j = 0; j <= order; j++) {
            tempCoef1[j] = 0;     //tempCoef1��tempCoef2���г�ʼ��
            tempCoef2[j] = 0;
        }

        //i ��1 + z^(-1)�ݴ���
        //otherN : 1 - z^(-1)�ݴ���
        int otherN = order - i;

        if (passType == HIGH) {
            pascalTriangle(i, SYMBOL_ADD, tempCoef1);      //����������Ǽ���1 + z^(-1)�ݵ�ϵ��
            pascalTriangle(otherN, SYMBOL_SUB, tempCoef2); //����������Ǽ���1 - z^(-1)�ݵ�ϵ��
        }
        else {
            pascalTriangle(i, SYMBOL_SUB, tempCoef1);
            pascalTriangle(otherN, SYMBOL_ADD, tempCoef2);
        }

        //tempCoef�����е�ϵ������Ϊ[x^N, ..., x^0]
        coefficientEquation(tempCoef1, i + 1, tempCoef2, otherN + 1); //��������ʽ��ˣ�����ϵ��

        //��otherN = order ��i = 0 ʱ��tempCoef2�еĶ���ʽϵ�������ڼ������ϵ��
        if (i == 0) {
            for (int i = 0; i <= order; i++) {
                numerator[i] = pow(omega_c, order) * (double)tempCoef2[order - i] / (epsilon * pow(2, order - 1));
            }
        }

        ////��ӡ��i�ֶ���ʽ��˵Ľ��
        //printf("��%d�ֶ���ʽ��˽����", i);
        //for (int k = 0; k < length; k++) {
        //    cout << tempCoef1[k] << ", " ;
        //}
        //cout << endl;

        //�����ĸϵ��
        for (int j = 0; j <= order; j++) {
            //��(1 + z^(-1))^i * (1 - z^(-1))^otherN�ĸ�ϵ�����μ���
            denominator[j] += pow(omega_c, order - i) * (double)tempCoef1[order - j] * cheby1Table[order - 1][i];
        }
    }
    ////��ӡ��ĸ
    //cout << "��ĸϵ����";
    //for (int i = 0; i < length; i++) {
    //    cout << denominator[i] << ", ";
    //}
    //cout << endl;

    ////��ӡ����
    //cout << "����ϵ����";
    //for (int i = 0; i < length; i++) {
    //    cout << numerator[i] << ", ";
    //}
    //cout << endl;
    //cout << "omega_c " << omega_c;

    //ϵ����һ����ͳһ�ŵ�pTaps������
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
