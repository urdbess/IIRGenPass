#pragma once

//������

class Complex {
public:
    //���캯��
    Complex(double r = 0, double i = 0);

    //��ȡ�����ø�����ʵ�����鲿
    double getReal();
    double getImag();
    void setReal(double real);
    void setImag(double imag);

    //��������� +-*
    Complex operator+(const Complex& op2) const;
    Complex operator-(const Complex& op2) const;
    Complex operator*(const Complex& op2) const;

private:
    double real;//ʵ��
    double imag;//�鲿
};

