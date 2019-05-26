#pragma once
void GetConicCorrection(double x, double y, double* correct_delta_x, double* correct_delta_y);
void GetParallelogramCorrection(double x, double y, double* correct_delta_x, double* correct_delta_y);
void GetTrapezoidalCorrection(double x, double y, double* correct_delta_x, double* correct_delta_y);
void GetWeightedAverageCorrection(double x, double y, double* correct_delta_x, double* correct_delta_y);
