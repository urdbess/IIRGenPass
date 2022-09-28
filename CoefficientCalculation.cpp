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

//����������Ǽ���(x + 1)^N��(x - 1)^N��ϵ��
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
            vector[0] = -1; //����Ǽ��ţ���ڶ���ϵ����-1
            vector[1] = 1;
        }
        return;
    }
    int length = N + 1; //���鳤��

    int* temp = new int[length];
    /*
    int temp[length];   //�����м����
    */

    temp[0] = 1;
    temp[1] = 1;

    for (int i = 2; i <= N; i++) {
        vector[i] = 1;
        for (int j = 1; j < i; j++) {
            vector[j] = temp[j - 1] + temp[j]; //x[m] = x[m-1][n-1] + x[m-1]
        }
        if (i == N) { //���һ�β���Ҫ���м������ֵ
            if (symbol == SYMBOL_SUB) {//�����Ϊ����
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

//�������ʽ��˵�ϵ��
// originalCoef - ԭ����ϵ�����飬������ϵ��Ҳ�洢�ڸ�������
// N - ����ϵ�������Ӧ�Ķ���ʽϵ������
// nextCoef - ��ԭ������˵������ϵ��
// nextN - ����ϵ�������Ӧ�Ķ���ʽϵ������
void coefficientEquation(int* originalCoef, int	N, int* nextCoef, int nextN) {
    int* tempCoef = new int[N + nextN - 1];
    /*
    double tempCoef[N + nextN - 1];    //�м����
    */
    for (int i = 0; i < N + nextN - 1; i++) {
        tempCoef[i] = originalCoef[i]; //�м������ʼ��
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