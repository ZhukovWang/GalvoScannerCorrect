// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include "src/correct.h"

double origin_data[9][2] = { {-21000,21000},{-21000,0},{-21000,-21000},{0,21000}, {0,0},{0,-21000},{21000,21000},{21000,0},{21000,-21000} };

int main(int argc, char* argv[])
{
    std::ofstream origin_file("output\\origin_data.txt");
    std::ofstream conic_correction_file("output\\conic_correction_data.txt");
    std::ofstream parallelogram_correction_file("output\\parallelogram_correction_data.txt");
    std::ofstream trapezoidal_correction_file("output\\trapezoidal_correction_data.txt");
    std::ofstream weighted_average_correction_file("output\\weighted_average_correction_data.txt");

    double conic_correction[9][2] = { {0} };
    double parallelogram_correction[9][2] = { {0} };
    double trapezoidal_correction[9][2] = { {0} };
    double weighted_average_correction[9][2] = { {0} };

    for (int i = 0; i < 9; ++i)
    {
        origin_file << origin_data[i][0] << " " << origin_data[i][1] << "\n";

        GetConicCorrection(origin_data[i][0], origin_data[i][1], &conic_correction[i][0], &conic_correction[i][1]);
        conic_correction_file << origin_data[i][0] + conic_correction[i][0] << " " << origin_data[i][1] + conic_correction[i][1] << "\n";

        GetParallelogramCorrection(origin_data[i][0], origin_data[i][1], &parallelogram_correction[i][0], &parallelogram_correction[i][1]);
        parallelogram_correction_file << origin_data[i][0] + parallelogram_correction[i][0] << " " << origin_data[i][1] + parallelogram_correction[i][1] << "\n";

        GetTrapezoidalCorrection(origin_data[i][0], origin_data[i][1], &trapezoidal_correction[i][0], &trapezoidal_correction[i][1]);
        trapezoidal_correction_file << origin_data[i][0] + trapezoidal_correction[i][0] << " " << origin_data[i][1] + trapezoidal_correction[i][1] << "\n";

        GetWeightedAverageCorrection(origin_data[i][0], origin_data[i][1], &weighted_average_correction[i][0], &weighted_average_correction[i][1]);
        weighted_average_correction_file << origin_data[i][0] + weighted_average_correction[i][0] << " " << origin_data[i][1] + weighted_average_correction[i][1] << "\n";
    }

    origin_file.close();
    conic_correction_file.close();
    parallelogram_correction_file.close();
    trapezoidal_correction_file.close();
    weighted_average_correction_file.close();

    std::cout << "Done." << std::endl;

    return 0;
}
