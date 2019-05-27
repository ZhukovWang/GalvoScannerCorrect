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
const double parallelogram_factor_x = 0.5;

/// <summary>
/// 平行四边形y补偿因子
/// </summary>
const double parallelogram_factor_y = 0.5;

/// <summary>
/// 梯形偏移x补偿因子
/// </summary>
const double trapezoidal_factor_x = 0.5;

/// <summary>
/// 梯形偏移y补偿因子
/// </summary>
const double trapezoidal_factor_y = 0.5;

/// <summary>
/// x的最大位置
/// </summary>
const double x_max = 32000;

/// <summary>
/// y的最大位置
/// </summary>
const double y_max = 32000;

const double x_axis_plat_x_start = -21000;
const double x_axis_plat_x_interval = 21000;
const int x_axis_plat_x_num = 3;
const double x_axis_plat_y_start = -21000;
const double x_axis_plat_y_interval = 21000;
const int x_axis_plat_y_num = 3;
const double x_axis_plat_correct[3][3] = { {-1000,-1000,-1000}, {0,0,0}, {1000,1000,1000} };//第一组y=-21000, x从-21000到21000，其后类推

const double y_axis_plat_x_start = -21000;
const double y_axis_plat_x_interval = 21000;
const int y_axis_plat_x_num = 3;
const double y_axis_plat_y_start = -21000;
const double y_axis_plat_y_interval = 21000;
const int y_axis_plat_y_num = 3;
const double y_axis_plat_correct[3][3] = { {-1000,0,1000}, {-500,0,500}, {-1000,0,1000} };//第一组y=-21000, x从-21000到21000，其后类推

/// <summary>
/// 得到二次曲线的补偿位置
/// </summary>
/// <param name="x">position x</param>
/// <param name="y">position y</param>
/// <param name="correct_delta_x">correct delta x</param>
/// <param name="correct_delta_y">correct delta y</param>
void GetConicCorrection(double x, double y, double* correct_delta_x, double* correct_delta_y)
{
    //double a_x = std::pow(y_max, 2) / x;
    //*correct_delta_x = (x - std::pow(y, 2) / (-a_x)) * conic_factor_x;

    //double a_y = std::pow(x_max, 2) / y;
    //*correct_delta_y = (y - std::pow(x, 2) / (-a_y)) * conic_factor_y;

    if (x < 1 && x > -1)
    {
        *correct_delta_x = 0;
    }
    else
    {
        double a_x = y_max * y_max / x;
        *correct_delta_x = (x - y * y / (-a_x)) * conic_factor_x;
    }

    if (y < 1 && y > -1)
    {
        *correct_delta_y = 0;
    }
    else
    {
        double a_y = x_max * x_max / y;
        *correct_delta_y = (y - x * x / (-a_y)) * conic_factor_y;
    }
}

/// <summary>
/// 得到平行四边形补偿位置
/// </summary>
/// <param name="x">position x</param>
/// <param name="y">position y</param>
/// <param name="correct_delta_x">correct delta x</param>
/// <param name="correct_delta_y">correct delta y</param>
void GetParallelogramCorrection(double x, double y, double* correct_delta_x, double* correct_delta_y)
{
    *correct_delta_x = -y * parallelogram_factor_x;
    *correct_delta_y = -x * parallelogram_factor_y;
}

/// <summary>
/// 得到梯形补偿位置
/// </summary>
/// <param name="x">position x</param>
/// <param name="y">position y</param>
/// <param name="correct_delta_x">correct delta x</param>
/// <param name="correct_delta_y">correct delta y</param>
void GetTrapezoidalCorrection(double x, double y, double* correct_delta_x, double* correct_delta_y)
{
    *correct_delta_x = x * ((y_max + y) / (2 * y_max)) * trapezoidal_factor_x;
    *correct_delta_y = y * ((x_max + x) / (2 * x_max)) * trapezoidal_factor_y;
}

void GetWeightedAverageCorrection(double x, double y, double* correct_delta_x, double* correct_delta_y)
{
    if (x < x_axis_plat_x_start)
    {
        x = x_axis_plat_x_start;
    }
    if (x > x_axis_plat_x_start + x_axis_plat_x_interval * (x_axis_plat_x_num - 1))
    {
        x = x_axis_plat_x_start + x_axis_plat_x_interval * (x_axis_plat_x_num - 1);
    }

    if (x < y_axis_plat_x_start)
    {
        x = y_axis_plat_x_start;
    }
    if (x > y_axis_plat_x_start + y_axis_plat_x_interval * (y_axis_plat_x_num - 1))
    {
        x = y_axis_plat_x_start + y_axis_plat_x_interval * (y_axis_plat_x_num - 1);
    }

    if (y < x_axis_plat_y_start)
    {
        y = x_axis_plat_y_start;
    }
    if (y > x_axis_plat_y_start + x_axis_plat_y_interval * (x_axis_plat_y_num - 1))
    {
        y = x_axis_plat_y_start + x_axis_plat_y_interval * (x_axis_plat_y_num - 1);
    }

    if (y < y_axis_plat_y_start)
    {
        y = y_axis_plat_y_start;
    }
    if (y > y_axis_plat_y_start + y_axis_plat_y_interval * (y_axis_plat_y_num - 1))
    {
        y = y_axis_plat_y_start + y_axis_plat_y_interval * (y_axis_plat_y_num - 1);
    }

    int x_index_x1 = (int)((x - x_axis_plat_x_start) / x_axis_plat_x_interval);
    if (x_index_x1 >= x_axis_plat_x_num - 1)
    {
        x_index_x1 = x_axis_plat_x_num - 2;
    }
    int x_index_x2 = x_index_x1 + 1;

    int x_index_y1 = (int)((y - x_axis_plat_y_start) / x_axis_plat_y_interval);
    if (x_index_y1 >= x_axis_plat_y_num - 1)
    {
        x_index_y1 = x_axis_plat_y_num - 2;
    }
    int x_index_y2 = x_index_y1 + 1;

    int y_index_x1 = (int)((x - y_axis_plat_x_start) / y_axis_plat_x_interval);
    if (y_index_x1 >= y_axis_plat_x_num - 1)
    {
        y_index_x1 = y_axis_plat_x_num - 2;
    }
    int y_index_x2 = y_index_x1 + 1;

    int y_index_y1 = (int)((y - y_axis_plat_y_start) / y_axis_plat_y_interval);
    if (y_index_y1 >= y_axis_plat_y_num - 1)
    {
        y_index_y1 = y_axis_plat_y_num - 2;
    }
    int y_index_y2 = y_index_y1 + 1;

    double x_board_left_top_x = x_axis_plat_x_start + x_index_x1 * x_axis_plat_x_interval;
    double x_board_left_top_y = x_axis_plat_y_start + x_index_y2 * x_axis_plat_y_interval;

    double x_board_left_bottom_x = x_board_left_top_x;
    double x_board_left_bottom_y = x_axis_plat_y_start + x_index_y1 * x_axis_plat_y_interval;

    double x_board_right_top_x = x_axis_plat_x_start + x_index_x2 * x_axis_plat_x_interval;
    double x_board_right_top_y = x_board_left_top_y;

    double x_board_right_bottom_x = x_board_right_top_x;
    double x_board_right_bottom_y = x_board_left_bottom_y;

    double y_board_left_top_x = y_axis_plat_x_start + y_index_x1 * y_axis_plat_x_interval;
    double y_board_left_top_y = y_axis_plat_y_start + y_index_y2 * y_axis_plat_y_interval;

    double y_board_left_bottom_x = y_board_left_top_x;
    double y_board_left_bottom_y = y_axis_plat_y_start + y_index_y1 * y_axis_plat_y_interval;

    double y_board_right_top_x = y_axis_plat_x_start + y_index_x2 * y_axis_plat_x_interval;
    double y_board_right_top_y = y_board_left_top_y;

    double y_board_right_bottom_x = y_board_right_top_x;
    double y_board_right_bottom_y = y_board_left_bottom_y;

    double x_internal_left_x = x_board_left_bottom_x;
    double x_internal_left_y = y;
    double x_internal_right_x = x_board_right_bottom_x;
    double x_internal_right_y = y;

    double x_internal_left_correct = x_axis_plat_correct[x_index_x1][x_index_y2] -
        (x_board_left_top_y - x_internal_left_y) / (x_board_left_top_y - x_board_left_bottom_y) * (x_axis_plat_correct[x_index_x1][x_index_y2] - x_axis_plat_correct[x_index_x1][x_index_y1]);

    double x_internal_right_correct = x_axis_plat_correct[x_index_x2][x_index_y2] -
        (x_board_right_top_y - x_internal_right_y) / (x_board_right_top_y - x_board_right_bottom_y) * (x_axis_plat_correct[x_index_x2][x_index_y2] - x_axis_plat_correct[x_index_x2][x_index_y1]);

    double x_internal_correct = x_internal_right_correct - (x_internal_right_x - x) / (x_internal_right_x - x_internal_left_x) * (x_internal_right_correct - x_internal_left_correct);

    double y_internal_left_x = y_board_left_bottom_x;
    double y_internal_left_y = y;
    double y_internal_right_x = y_board_right_bottom_x;
    double y_internal_right_y = y;

    double y_internal_left_correct = y_axis_plat_correct[y_index_x1][y_index_y2] -
        (y_board_left_top_y - y_internal_left_y) / (y_board_left_top_y - y_board_left_bottom_y) * (y_axis_plat_correct[y_index_x1][y_index_y2] - y_axis_plat_correct[y_index_x1][y_index_y1]);

    double y_internal_right_correct = y_axis_plat_correct[y_index_x2][y_index_y2] -
        (y_board_right_top_y - y_internal_right_y) / (y_board_right_top_y - y_board_right_bottom_y) * (y_axis_plat_correct[y_index_x2][y_index_y2] - y_axis_plat_correct[y_index_x2][y_index_y1]);

    double y_internal_correct = y_internal_right_correct - (y_internal_right_x - x) / (y_internal_right_x - y_internal_left_x) * (y_internal_right_correct - y_internal_left_correct);

    *correct_delta_x = x_internal_correct;
    *correct_delta_y = y_internal_correct;
}
