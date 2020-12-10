#include <complex>  // std::complex
#include <iomanip>  // setprecsion
#include <iostream> // std::cout, std::endl, std::cin
#include <vector>   // std::vector
#include <fstream>  // fopen, fclose
#include <cstdio>   // printf
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
void Input(void);   //入力
std::vector<std::complex<double>> FFT(const std::vector<double> &x);
//ここまで

int main(void)
{
    setting();
    Input();
    answer = FFT(x);
    for (long long i = 0; i < answer.size(); i++)
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
    long double real = 0., j = 0.;
    long long count = 0;
    while (fscanf(fp1, "%Lf\t%Lf", &real, &j) != EOF)
    {
        x.push_back(real);
        count++;
    }
    fclose(fp1);
}

std::vector<std::complex<double>> FFT(const std::vector<double> &x)
{
    //虚数単位
    const std::complex<double> j(0, 1);
    //累乗を求める
    unsigned int exponent = int(std::ceil(std::log2(x.size())));

    //2の累乗の数
    unsigned int num = int(std::pow(2.0, exponent));

    //計算用バッファ
    std::vector<std::complex<double>> X(num, 0);

    //ビット反転
    std::vector<unsigned int> index(X.size());
    for (size_t i = 0; i < index.size(); ++i)
    {
        unsigned int tmp = i;
        for (unsigned int n = 0; n < exponent; ++n)
        {
            index[i] <<= 1;
            index[i] |= (tmp >> n) & 0x0001;
        }
        //渡されたデータの並びを変える
        if (index[i] < x.size())
        {
            X[i] = x[index[i]];
        }
        else
        {
            //データ数を超えたら0埋め
            X[i] = 0.0;
        }
    }

    //バタフライ演算
    for (unsigned int stage = 1; stage <= exponent; ++stage)
    {
        for (unsigned int i = 0; i < std::pow(2.0, exponent - stage); ++i)
        {
            for (unsigned int n = 0; n < std::pow(2.0, stage - 1); ++n)
            {
                std::complex<double> corre1 = std::exp(-j * 2.0 * std::acos(-1.0) * double(n) / std::pow(2.0, stage));
                std::complex<double> corre2 = std::exp(-j * 2.0 * std::acos(-1.0) * double(n + std::pow(2.0, stage - 1)) / std::pow(2.0, stage));

                unsigned int No1 = int(i * std::pow(2.0, stage) + n);
                unsigned int No2 = int(No1 + std::pow(2.0, stage - 1));

                std::complex<double> tmp1 = X[No1];
                std::complex<double> tmp2 = X[No2];

                X[No1] = tmp1 + (tmp2 * corre1);
                X[No2] = tmp1 + (tmp2 * corre2);
            }
        }
    }
    return X;
}
