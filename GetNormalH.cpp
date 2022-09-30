#include <iostream>
#include <math.h>
#include "IIRGenPass.h"
#include "Complex.h"
using namespace std;

//����(s - s_0)(s - s_1)...(s - s_order)��ϵ��
double* coefficientCalculation(int order, Complex s[]) {
    Complex* result = new Complex[order + 1]();
    Complex zero(0, 0);
    Complex one(1, 0);

    result[0] = zero - s[0];
    result[1] = one;

    for (int i = 1; i < order; i++) {
        for (int j = i; j >= 0; j--) {
            result[j + 1] = result[j];
        }
        result[0] = zero;

        for (int j = 0; j <= i; j++) {
            result[j] = result[j] - result[j + 1] * s[i];
        }
    }

    double* a = new double[order + 1];
    for (int i = 0; i <= order; i++) {
        a[i] = result[i].getReal();
    }

    return a;
}

//������˹�˲�����һ������ϵ��
double* butterGetNormalH(int order) {
    //���ü��������
    Complex* s = new Complex[order]();
    //�󼫵�
    for (int i = 0; i < order; i++) {
        double x = (1 / 2.0 + (2.0 * i + 1) / (2.0 * order)) * M_PI;
        s[i].setReal(cos(x));
        s[i].setImag(sin(x));
    }
    //���ݼ��������һ������ϵ��
    double* a = coefficientCalculation(order, s);
    delete[] s;
    return a;
}

double* cheby1GetNormalH(double ripple, int order) {
    double omega_p = 2.0 * M_PI * pow(10, 4);//ͨ����ֹƵ��
    double epsilon = sqrt(pow(10, 0.1 * ripple) - 1);
    double d1 = 1.0 / epsilon;
    double epsilon_2 = pow(10, 0.1 * ripple) - 1.0;
    double d2 = 1.0 / epsilon_2;
    double gamma = d1 + sqrt(1.0 + d2);
    double A = (pow(gamma, 1.0 / order) - pow(gamma, -1.0 / order)) / 2;//ʵ��ϵ��
    double B = (pow(gamma, 1.0 / order) + pow(gamma, -1.0 / order)) / 2;//�鲿ϵ��

    //���ü��������
    Complex* s = new Complex[order]();
    //�󼫵�
    for (int i = 0; i < order; i++) {
        double x = (1 / 2.0 + (2.0 * i + 1) / (2.0 * order)) * M_PI;
        s[i].setReal(-A * sin(((2.0 * i + 1) * M_PI) / (2 * order)));
        s[i].setImag(B * cos(((2.0 * i + 1) * M_PI) / (2 * order)));
    }
    //���ݼ��������һ������ϵ��
    double* a = coefficientCalculation(order, s);
    delete[] s;
    return a;
}
