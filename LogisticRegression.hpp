#include "BaseRegression.hpp"
#include <iostream>

#include <cmath>
#include <cstdint>
#include <vector>

class LogisticRegression : public BaseRegression {

    public:

        LogisticRegression();
        LogisticRegression(const std::vector<std::vector<float>>& x, const std::vector<float>& y);
        
        std::vector<float> predict(const std::vector<std::vector<float>>& x) const override;
        std::vector<float> predict_proba(const std::vector<std::vector<float>>& x) const;

    private:

        static float sigmoid(float z);
};
