#include "correct.h"

/// <summary>
/// 二次曲线的x补偿因子
/// </summary>
const double conic_factor_x = 0.02;

/// <summary>
/// 二次曲线的y补偿因子
/// </summary>
const double conic_factor_y = 0.02;

/// <summary>
/// 平行四边形x补偿因子
/// </summary>
const double parallelogram_factor_x = 0.01;

/// <summary>
/// 平行四边形y补偿因子
/// </summary>
const double parallelogram_factor_y = 0.01;

/// <summary>
/// 梯形偏移x补偿因子
/// </summary>
const double trapezoidal_factor_x = 0.01;

/// <summary>
/// 梯形偏移y补偿因子
/// </summary>
const double trapezoidal_factor_y = 0.01;

/// <summary>
/// x的最大位置
/// </summary>
const double x_max = 25;

/// <summary>
/// y的最大位置
/// </summary>
const double y_max = 25;

/// <summary>
/// 得到经过全部补偿后的位置
/// </summary>
/// <param name="x">position x</param>
/// <param name="y">position y</param>
/// <param name="correct_x">after correct x</param>
/// <param name="correct_y">after correct y</param>
void GetCorrection(double x, double y, double* correct_x, double* correct_y)
{
}

/// <summary>
/// 得到二次曲线的补偿位置
/// </summary>
/// <param name="x">position x</param>
/// <param name="y">position y</param>
/// <param name="correct_x">after correct x</param>
/// <param name="correct_y">after correct y</param>
void GetConicCorrection(double x, double y, double* correct_x, double* correct_y)
{
    double a_x = std::pow(y_max, 2) / x;
    double delta_x = (x - std::pow(y, 2) / (-a_x)) * conic_factor_x;

    double a_y = std::pow(x_max, 2) / y;
    double delta_y = (y - std::pow(x, 2) / (-a_y)) * conic_factor_y;

    *correct_x = x + delta_x;
    *correct_y = y + delta_y;
}

/// <summary>
/// 得到平行四边形补偿位置
/// </summary>
/// <param name="x">position x</param>
/// <param name="y">position y</param>
/// <param name="correct_x">after correct x</param>
/// <param name="correct_y">after correct y</param>
void GetParallelogramCorrection(double x, double y, double* correct_x, double* correct_y)
{
    double delta_x = y;
    double delta_y = x;

    *correct_x = x + delta_x;
    *correct_y = y + delta_y;
}

/// <summary>
/// 得到梯形补偿位置
/// </summary>
/// <param name="x">position x</param>
/// <param name="y">position y</param>
/// <param name="correct_x">after correct x</param>
/// <param name="correct_y">after correct y</param>
void GetTrapezoidalCorrection(double x, double y, double* correct_x, double* correct_y)
{
    double delta_x = std::abs(x) * ((y_max + y) / (2 * y_max)) * trapezoidal_factor_x;
    double delta_y = std::abs(y) * ((x_max + x) / (2 * x_max)) * trapezoidal_factor_y;

    *correct_x = x + delta_x;
    *correct_y = y + delta_y;
}
