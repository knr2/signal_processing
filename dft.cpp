#include <complex>   // std::complex
#include <iomanip>   // setprecsion
#include <iostream>  // std::cout, std::endl, std::cin
#include <vector>    // std::vector
#include <fstream>   // fopen, fclose
#include <cstdio>    // printf
#include <cstdlib>
#include <cmath> // sin, cos, tan

const long double PI = acos(-1.0);
const std::complex<double> j(0, 1);

//変数定義
std::vector<double> x;
std::vector<std::complex<double>> answer(x.size(), 0);
//ここまで

//関数定義
void setting(void); //設定
void Input(void); //入力
std::vector<std::complex<double>> DFT(const std::vector<double> &x); //DFT
//ここまで

int main(void)
{
    setting();
    Input();
    answer = DFT(x);
    for(long long i = 0;i < answer.size();i++)
    {
        std::cout << answer[i] << std::endl;
    }
    return 0;
}

//設定
void setting(void)
{
    std::cout << std::fixed << std::setprecision(10); //少数は10桁まで表示するように設定
}

//入力
//実数のみ考慮
void Input(void)
{
    FILE *fp1;
    if ((fp1 = fopen("sound.txt", "r")) == NULL)
    {
        fprintf(stderr, "Can not find sound.txt\n");
        exit(1);
    }
    long double real = 0., imaginary = 0.;
    long long count = 0;
    while (fscanf(fp1, "%Lf\t%Lf", &real, &imaginary) != EOF)
    {
        x.push_back(real);
        count++;
    }
    fclose(fp1);
}

//DFT
std::vector<std::complex<double>> DFT(const std::vector<double> &x)
{
    std::vector<std::complex<double>> X(x.size(), 0);

    for (size_t i = 0; i < x.size(); ++i)
    {
        for (size_t n = 0; n < x.size(); ++n)
        {
            X[i] += x[n] * std::exp(-j * 2.0 * std::acos(-1.0) * double(i * n) / double(x.size()));
        }
    }
    return X;
}
