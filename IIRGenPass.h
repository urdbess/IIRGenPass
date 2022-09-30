#pragma once
#include <vector>
#include "Complex.h"
using namespace std;

#define M_PI 3.1415926535897932384626433832795028841971

//����������Ҫ����Ķ���ʽ�ķ���
enum Symbol { SYMBOL_ADD, SYMBOL_SUB };
//�˲�������
enum IIRFilterType { Butterworth , Chebyshev1 };
//�˲���Ϊ��/��ͨ
enum PassType { HIGH, LOW };
//�˲�������״̬
enum Status{ StsNoErr, StsNullPtrErr, StsIIRGenOrderErr, StsFilterFrequencyErr };

////Butterworth�˲�������ʽϵ����
////ע�⣺����ͨ����������ϵ��
//static vector<vector<double>> butterTable = { 
//	{1, 1},
//	{1, 1.4142136, 1}, 
//	{1, 2, 2, 1}, 
//	{1, 2.6131259, 3.4142136, 2.6131259, 1},
//	{1, 3.236068, 5.236068, 5.236068, 3.236068, 1}, 
//	{1, 3.8637033, 7.4641016, 9.1416202, 7.4641016, 3.8637033, 1},
//	{1, 4.4939592, 10.0978347, 14.5917939, 14.5917939, 10.0978347, 4.4939592, 1},
//	{1, 5.1258309, 13.1370712, 21.8461510, 25.6883559, 21.8461510, 13.1370712, 5.1258309, 1},
//	{1, 5.7587705, 16.5817187, 31.1634375, 41.9863857, 41.9863857, 31.1634375, 16.5817187, 5.7587705, 1},
//	{1, 6.3924532, 20.4317291, 42.8020611, 64.8823963, 74.2334292, 64.8823963, 42.8020611, 20.4317291, 6.3924532, 1} };
//
////Chebyshev1�˲�������ʽϵ����
////ע�⣺�ñ�����ڲ��ԣ���������ݲ��ƴ�Сʵʱ����ϵ��
//static vector<vector<double>> cheby1Table = {//����Ϊ0.5dB
//	{2.8627752, 1},
//	{1.5162026, 1.4256245, 1},
//	{0.7156938, 1.5348954, 1.2529130, 1},
//	{0.3790506, 1.0254553, 1.7168662, 1.1973856, 1},
//	{0.1789234, 0.7525181, 1.3095747, 1.9373675, 1.1724909, 1},
//	{0.0947626, 0.4323669, 1.1718613, 1.5897635, 2.1718446, 1.1591761, 1},
//	{0.0447309, 0.2820722, 0.7556511, 1.6479029, 1.8694079, 2.4126510, 1.1512176, 1},
//	{0.0236907, 0.1525444, 0.5735604, 1.1485894, 2.1840154, 2.1492173, 2.6567498, 1.1460801, 1},
//	{0.0111827, 0.0941198, 0.3408193, 0.9836199, 1.6113880, 2.7814990, 2.4293297, 2.9027337, 1.1425705, 1},
//	{0.0059227, 0.0492855, 0.2372688, 0.6269689, 1.5274307, 2.1442372, 3.4409268, 2.7097415, 3.1498757, 1.1400664, 1} };

//�����͸�ͨ�˲���ϵ�����ɺ���
Status IIRGenHighpass(double rFreq, double ripple, int order, double* pTaps, IIRFilterType filterType);
//�����͵�ͨ�˲���ϵ�����ɺ���
Status IIRGenLowpass(double rFreq, double ripple, int order, double* pTaps, IIRFilterType filterType);

//Butterworth�˲���ϵ�����ɺ���
Status IIRGenPass_Butter(double rFreq, int order, double* pTaps, PassType passType);
//Chebyshev1�˲���ϵ�����ɺ���
Status IIRGenPass_Cheby1(double rFreq, double ripple, int order, double* pTaps, PassType passType);

//��ֹƵ��omega_c���㷽��
double omegaCalculation(double rFreq, PassType passType);
//����(s - s_0)(s - s_1)...(s - s_order)��ϵ��
double* coefficientCalculation(int order, Complex s[]);
//Butterworth�˲�����һ������ϵ��
double* butterGetNormalH(int order);
//Chebyshev1�˲�����һ������ϵ��
double* cheby1GetNormalH(double ripple, int order);
//������Ǽ���(1 + x)^N �� (1 - x)^N
void pascalTriangle(int	N, Symbol symbol, int* vector);
//����(1 + x)^N * (1 - x)^M��ϵ��
void coefficientEquation(int* originalCoef, int	N, int* nextCoef, int nextN);