#include "logAxis.h"
#include <algorithm>

#include <cmath>
#include <iostream>

LogAxis::LogAxis() : Axis() {}

std::vector<float> LogAxis::convert(QList<double> points) const
{
    std::vector<float> result(points.length());

    auto min = log(minimum());
    auto max = log(maximum());

    std::transform(points.begin(), points.end(), result.begin(),
                   [min, max](const auto x) { return -1.0f + 2 * (log(x) - min) / (max - min); });

    return result;
}

double LogAxis::tick(int index) const
{
    int count = 7;
    auto min = log(minimum());
    auto max = log(maximum());

    return exp(min + (double)index / ((double)count - 1.0) * (max - min));
}
