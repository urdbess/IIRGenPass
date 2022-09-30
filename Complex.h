#pragma once

//复数类

class Complex {
public:
    //构造函数
    Complex(double r = 0, double i = 0);

    //获取、设置复数的实部和虚部
    double getReal();
    double getImag();
    void setReal(double real);
    void setImag(double imag);

    //重载运算符 +-*
    Complex operator+(const Complex& op2) const;
    Complex operator-(const Complex& op2) const;
    Complex operator*(const Complex& op2) const;

private:
    double real;//实部
    double imag;//虚部
};

