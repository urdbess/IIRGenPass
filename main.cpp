#include <iostream>
#include <vector>
#include <iomanip>
#include "IIRGenPass.h"
using namespace std;

//�����˲���ϵ�����ɺ���
int main()
{
    //���ݽ���order���������˲���ϵ��������
    int order = 3;
    double* pTaps = new double[ 2 * ( order + 1)];

    //Status status = IIRGenHighpass(0.3, 0, order, pTaps, Butterworth);
    //Status status = IIRGenHighpass(0.3, 0.5, order, pTaps, Chebyshev1);
    //Status status = IIRGenLowpass(0.3, 0, order, pTaps, Butterworth);
    Status status = IIRGenLowpass(0.3, 0.5, order, pTaps, Chebyshev1);

    //��ӡ�˲���ϵ��
    if (status == StsNoErr) {
        /*int pTaps_len = _msize(pTaps) / sizeof(double);*/
        int pTaps_len = 2 * (order + 1);
        for (int i = 0; i < pTaps_len; i++) {
            if (i == pTaps_len / 2)
                cout << endl;
            cout << setprecision(15) << pTaps[i] << ", ";
        }
    }

    delete[] pTaps;

    return 0;
}