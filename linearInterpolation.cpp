#include"linearInterpolation.h"

linInterpolation::linInterpolation()
    :m_maxX(INT_MIN), m_minX(INT_MAX)
{}
void linInterpolation::add(double x, double y) 
{
    //
    // Edge case: adding duplicates.
    //
    if (m_points.find(x) == m_points.end()) {
        m_points.insert({ x, y });
    }
    else {
        m_points.at(x) = y;
    }

    if (x < m_minX) {
        m_minX = x;
    }
    else if (x > m_maxX) {
        m_maxX = x;
    }
}
double linInterpolation::value(double x)
{
    //
    // Edge case: too few data points.
    // 
    if (m_points.size() > 1) {
        //
        // Edge case: requesting existing point.
        // 
        if (m_points.find(x) != m_points.end()) {
            return m_points.at(x);
        }
        //
        // Edge case: Extrapolation attempt.
        //
        if (x<m_maxX && x>m_minX) {

            auto it1 = std::lower_bound(m_points.begin(), m_points.end(), std::make_pair(x, 0));
            it1--;
            auto it2 = std::upper_bound(m_points.begin(), m_points.end(), std::make_pair(x, 0));

            double x0 = it1->first;
            double y0 = it1->second;
            double x1 = it2->first;
            double y1 = it2->second;

            return ((x - x0) * ((y1 - y0) / (x1 - x0))) + y0;
        }
        else {
            throw std::runtime_error("Error in linInterpolation::value(). Attempted extrapolation.");
        }
    }
    else {
        throw std::runtime_error("Error in linInterpolation::value(). Attempted interpolation with too few data points.");
    }

}