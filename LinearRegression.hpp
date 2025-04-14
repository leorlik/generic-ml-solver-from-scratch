#ifndef LINREG_HPP
#define LINREG_HPP

#include "BaseRegression.hpp"
#include <vector>
#include <iostream>

class LinearRegression : public BaseRegression {

    public:
    
        LinearRegression();
        LinearRegression(const std::vector<std::vector<float>>& x, const std::vector<float>& y);
    
        std::vector<float> predict(const std::vector<std::vector<float>>& x) const override;
};

#endif