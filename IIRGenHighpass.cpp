#include <iostream>
#include <math.h>
#include "IIRGenPass.h"
using namespace std;


//高通滤波器系数生成
//pTaps[] = {b_0, ..., b_order, a_0, ..., a_order}
Status IIRGenHighpass(double rFreq, double ripple, int order, double* pTaps, IIRFilterType filterType) {

    if (order <= 0 || order >= 13) {
        cerr << "the order is less than 1 or greater than 12." << endl;
        return StsIIRGenOrderErr;
    }

    if (pTaps == NULL) {
        cerr << "the pTaps pointer is NULL." << endl;
        return StsNullPtrErr;
    }

    if (rFreq <= 0 || rFreq >= 0.5) {
        cerr << "the rFreq is out of the range." << endl;
        return StsFilterFrequencyErr;
    }
    
    //函数返回状态
    Status status;

    if (filterType == Butterworth) {
        status = IIRGenPass_Butter(rFreq, order, pTaps, HIGH);
    }
    else {
        status = IIRGenPass_Cheby1(rFreq, ripple, order, pTaps, HIGH);
    }

    return status;
}