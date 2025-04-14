#ifndef BASEREG_HPP
#define BASEREG_HPP

#include <vector>
#include <iostream>

class BaseRegression {

    public:

        BaseRegression();
        BaseRegression(const std::vector<std::vector<float>>& x, const std::vector<float>& y);

        void fit(const std::vector<std::vector<float>>& x, const std::vector<float>& y);
        virtual std::vector<float> predict(const std::vector<std::vector<float>>&) const = 0;

        std::vector<float> getSlope() const;
        float getIntercept() const;
        void print() const;

        virtual ~BaseRegression() = default;

    protected:
    
        std::vector<float> slope;
        float intercept;

        float calculateSlope(const std::vector<float>& x, const std::vector<float>& y);

        static float calculateMean(const std::vector<float>&);
        static std::vector<std::vector<float>> transpose(const std::vector<std::vector<float>>& matrix);
};

#endif