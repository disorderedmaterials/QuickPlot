#include "logAxis.h"
#include <algorithm>

#include <cmath>
#include <iostream>
#include <vector>

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

void LogAxis::updateTicks_()
{
    std::vector<double> subTicks;
    tics_.clear();

    int orders = ceil(log(maximum_ / minimum_) / log(10.0));

    switch (orders)
    {
        case 0:
        case 1:
            subTicks = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
            break;
        case 2:
            subTicks = {1.0, 2.0, 3.0, 5.0, 8.0};
            break;
        case 3:
        case 4:
            subTicks = {1.0, 2.0, 5.0};
            break;
        case 5:
            subTicks = {1.0, 3.0};
            break;
        default:
            subTicks = {1.0};
    }

    double current = pow(10.0, floor(log(minimum_) / log(10.0)));

    while (current <= maximum_)
    {
        for (auto sub : subTicks)
        {
            if (sub * current >= minimum_ && sub * current <= maximum_)
                tics_.emplace_back(sub * current);
        }
        current *= 10.0;
    }
}

double LogAxis::tickCoord(int index) const
{
    double actual = log10(tics_[index]);
    double min = log10(minimum_);
    double max = log10(maximum_);

    return 2.0 * (actual - min) / (max - min);
}

void LogAxis::nudge(double delta)
{
    minimum_ = pow(10.0, log10(minimum_) + delta);
    maximum_ = pow(10.0, log10(maximum_) + delta);
    emit Axis::dataChanged();
}
