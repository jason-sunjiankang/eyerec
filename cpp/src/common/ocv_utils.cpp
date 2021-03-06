#include "ocv_utils.hpp"

static const float sinTable[] = { 0.0000000f, 0.0174524f, 0.0348995f,
    0.0523360f, 0.0697565f, 0.0871557f, 0.1045285f, 0.1218693f, 0.1391731f,
    0.1564345f, 0.1736482f, 0.1908090f, 0.2079117f, 0.2249511f, 0.2419219f,
    0.2588190f, 0.2756374f, 0.2923717f, 0.3090170f, 0.3255682f, 0.3420201f,
    0.3583679f, 0.3746066f, 0.3907311f, 0.4067366f, 0.4226183f, 0.4383711f,
    0.4539905f, 0.4694716f, 0.4848096f, 0.5000000f, 0.5150381f, 0.5299193f,
    0.5446390f, 0.5591929f, 0.5735764f, 0.5877853f, 0.6018150f, 0.6156615f,
    0.6293204f, 0.6427876f, 0.6560590f, 0.6691306f, 0.6819984f, 0.6946584f,
    0.7071068f, 0.7193398f, 0.7313537f, 0.7431448f, 0.7547096f, 0.7660444f,
    0.7771460f, 0.7880108f, 0.7986355f, 0.8090170f, 0.8191520f, 0.8290376f,
    0.8386706f, 0.8480481f, 0.8571673f, 0.8660254f, 0.8746197f, 0.8829476f,
    0.8910065f, 0.8987940f, 0.9063078f, 0.9135455f, 0.9205049f, 0.9271839f,
    0.9335804f, 0.9396926f, 0.9455186f, 0.9510565f, 0.9563048f, 0.9612617f,
    0.9659258f, 0.9702957f, 0.9743701f, 0.9781476f, 0.9816272f, 0.9848078f,
    0.9876883f, 0.9902681f, 0.9925462f, 0.9945219f, 0.9961947f, 0.9975641f,
    0.9986295f, 0.9993908f, 0.9998477f, 1.0000000f, 0.9998477f, 0.9993908f,
    0.9986295f, 0.9975641f, 0.9961947f, 0.9945219f, 0.9925462f, 0.9902681f,
    0.9876883f, 0.9848078f, 0.9816272f, 0.9781476f, 0.9743701f, 0.9702957f,
    0.9659258f, 0.9612617f, 0.9563048f, 0.9510565f, 0.9455186f, 0.9396926f,
    0.9335804f, 0.9271839f, 0.9205049f, 0.9135455f, 0.9063078f, 0.8987940f,
    0.8910065f, 0.8829476f, 0.8746197f, 0.8660254f, 0.8571673f, 0.8480481f,
    0.8386706f, 0.8290376f, 0.8191520f, 0.8090170f, 0.7986355f, 0.7880108f,
    0.7771460f, 0.7660444f, 0.7547096f, 0.7431448f, 0.7313537f, 0.7193398f,
    0.7071068f, 0.6946584f, 0.6819984f, 0.6691306f, 0.6560590f, 0.6427876f,
    0.6293204f, 0.6156615f, 0.6018150f, 0.5877853f, 0.5735764f, 0.5591929f,
    0.5446390f, 0.5299193f, 0.5150381f, 0.5000000f, 0.4848096f, 0.4694716f,
    0.4539905f, 0.4383711f, 0.4226183f, 0.4067366f, 0.3907311f, 0.3746066f,
    0.3583679f, 0.3420201f, 0.3255682f, 0.3090170f, 0.2923717f, 0.2756374f,
    0.2588190f, 0.2419219f, 0.2249511f, 0.2079117f, 0.1908090f, 0.1736482f,
    0.1564345f, 0.1391731f, 0.1218693f, 0.1045285f, 0.0871557f, 0.0697565f,
    0.0523360f, 0.0348995f, 0.0174524f, 0.0000000f, -0.0174524f, -0.0348995f,
    -0.0523360f, -0.0697565f, -0.0871557f, -0.1045285f, -0.1218693f,
    -0.1391731f, -0.1564345f, -0.1736482f, -0.1908090f, -0.2079117f,
    -0.2249511f, -0.2419219f, -0.2588190f, -0.2756374f, -0.2923717f,
    -0.3090170f, -0.3255682f, -0.3420201f, -0.3583679f, -0.3746066f,
    -0.3907311f, -0.4067366f, -0.4226183f, -0.4383711f, -0.4539905f,
    -0.4694716f, -0.4848096f, -0.5000000f, -0.5150381f, -0.5299193f,
    -0.5446390f, -0.5591929f, -0.5735764f, -0.5877853f, -0.6018150f,
    -0.6156615f, -0.6293204f, -0.6427876f, -0.6560590f, -0.6691306f,
    -0.6819984f, -0.6946584f, -0.7071068f, -0.7193398f, -0.7313537f,
    -0.7431448f, -0.7547096f, -0.7660444f, -0.7771460f, -0.7880108f,
    -0.7986355f, -0.8090170f, -0.8191520f, -0.8290376f, -0.8386706f,
    -0.8480481f, -0.8571673f, -0.8660254f, -0.8746197f, -0.8829476f,
    -0.8910065f, -0.8987940f, -0.9063078f, -0.9135455f, -0.9205049f,
    -0.9271839f, -0.9335804f, -0.9396926f, -0.9455186f, -0.9510565f,
    -0.9563048f, -0.9612617f, -0.9659258f, -0.9702957f, -0.9743701f,
    -0.9781476f, -0.9816272f, -0.9848078f, -0.9876883f, -0.9902681f,
    -0.9925462f, -0.9945219f, -0.9961947f, -0.9975641f, -0.9986295f,
    -0.9993908f, -0.9998477f, -1.0000000f, -0.9998477f, -0.9993908f,
    -0.9986295f, -0.9975641f, -0.9961947f, -0.9945219f, -0.9925462f,
    -0.9902681f, -0.9876883f, -0.9848078f, -0.9816272f, -0.9781476f,
    -0.9743701f, -0.9702957f, -0.9659258f, -0.9612617f, -0.9563048f,
    -0.9510565f, -0.9455186f, -0.9396926f, -0.9335804f, -0.9271839f,
    -0.9205049f, -0.9135455f, -0.9063078f, -0.8987940f, -0.8910065f,
    -0.8829476f, -0.8746197f, -0.8660254f, -0.8571673f, -0.8480481f,
    -0.8386706f, -0.8290376f, -0.8191520f, -0.8090170f, -0.7986355f,
    -0.7880108f, -0.7771460f, -0.7660444f, -0.7547096f, -0.7431448f,
    -0.7313537f, -0.7193398f, -0.7071068f, -0.6946584f, -0.6819984f,
    -0.6691306f, -0.6560590f, -0.6427876f, -0.6293204f, -0.6156615f,
    -0.6018150f, -0.5877853f, -0.5735764f, -0.5591929f, -0.5446390f,
    -0.5299193f, -0.5150381f, -0.5000000f, -0.4848096f, -0.4694716f,
    -0.4539905f, -0.4383711f, -0.4226183f, -0.4067366f, -0.3907311f,
    -0.3746066f, -0.3583679f, -0.3420201f, -0.3255682f, -0.3090170f,
    -0.2923717f, -0.2756374f, -0.2588190f, -0.2419219f, -0.2249511f,
    -0.2079117f, -0.1908090f, -0.1736482f, -0.1564345f, -0.1391731f,
    -0.1218693f, -0.1045285f, -0.0871557f, -0.0697565f, -0.0523360f,
    -0.0348995f, -0.0174524f, -0.0000000f, 0.0174524f, 0.0348995f, 0.0523360f,
    0.0697565f, 0.0871557f, 0.1045285f, 0.1218693f, 0.1391731f, 0.1564345f,
    0.1736482f, 0.1908090f, 0.2079117f, 0.2249511f, 0.2419219f, 0.2588190f,
    0.2756374f, 0.2923717f, 0.3090170f, 0.3255682f, 0.3420201f, 0.3583679f,
    0.3746066f, 0.3907311f, 0.4067366f, 0.4226183f, 0.4383711f, 0.4539905f,
    0.4694716f, 0.4848096f, 0.5000000f, 0.5150381f, 0.5299193f, 0.5446390f,
    0.5591929f, 0.5735764f, 0.5877853f, 0.6018150f, 0.6156615f, 0.6293204f,
    0.6427876f, 0.6560590f, 0.6691306f, 0.6819984f, 0.6946584f, 0.7071068f,
    0.7193398f, 0.7313537f, 0.7431448f, 0.7547096f, 0.7660444f, 0.7771460f,
    0.7880108f, 0.7986355f, 0.8090170f, 0.8191520f, 0.8290376f, 0.8386706f,
    0.8480481f, 0.8571673f, 0.8660254f, 0.8746197f, 0.8829476f, 0.8910065f,
    0.8987940f, 0.9063078f, 0.9135455f, 0.9205049f, 0.9271839f, 0.9335804f,
    0.9396926f, 0.9455186f, 0.9510565f, 0.9563048f, 0.9612617f, 0.9659258f,
    0.9702957f, 0.9743701f, 0.9781476f, 0.9816272f, 0.9848078f, 0.9876883f,
    0.9902681f, 0.9925462f, 0.9945219f, 0.9961947f, 0.9975641f, 0.9986295f,
    0.9993908f, 0.9998477f, 1.0000000f };
void sincos(int angle, float& cosval, float& sinval)
{
    angle += (angle < 0 ? 360 : 0);
    sinval = sinTable[angle];
    cosval = sinTable[450 - angle];
}
std::vector<cv::Point> ellipse2Points(
    const cv::RotatedRect& ellipse, const int& delta)
{
    int angle = ellipse.angle;

    // make sure angle is within range
    while (angle < 0)
        angle += 360;
    while (angle > 360)
        angle -= 360;

    float alpha, beta;
    sincos(angle, alpha, beta);

    double x, y;
    std::vector<cv::Point> points;
    int par = -angle;
    for (int i = 0 + par; i < 360 + par; i += delta) {
        int corrected = i % 360;
        if (corrected < 0) corrected = 360 + corrected;
        x = 0.5 * ellipse.size.width * sinTable[450 - corrected];
        y = 0.5 * ellipse.size.height * sinTable[corrected];
        points.push_back(
            cv::Point(roundf(ellipse.center.x + x * alpha - y * beta),
                roundf(ellipse.center.y + x * beta + y * alpha)));
    }
    return points;
}

void distFromPoints(const cv::RotatedRect& ellipse,
    std::vector<cv::Point> points, std::vector<double>& distances)
{
    /* Based on Swirski et al. "A fully-automatic, temporal approach to single
     * camera, glint-free 3D eye model fitting": "Calculating the true Euclidean
     * distance of a point to an ellipse is computationally expensive, requiring
     * the solution of a quartic. Instead, we transform the image space so that
     * the ellipse becomes the unit circle, find the signed distance to this
     * circle, and scale by the major radius of the ellipse to get an
     * approximate pixel distance.
     */
    float sin, cos;
    sincos(ellipse.angle, cos, sin);
    auto axes = std::minmax(ellipse.size.height, ellipse.size.height);
    auto minor = 0.5 * axes.first;
    auto major = 0.5 * axes.second;
    cv::Matx21d center(ellipse.center.x, ellipse.center.y);
    cv::Matx22d rA(cos, sin, -major * sin / minor, major * cos / minor);
    cv::Matx21d rAt = rA * center;
    distances.clear();
    for (auto& p : points) {
        auto rAxt((rA(0, 0) * p.x + rA(0, 1) * p.y) - rAt(0));
        auto rAyt((rA(1, 0) * p.x + rA(1, 1) * p.y) - rAt(1));
        distances.push_back(major - std::sqrt(pow(rAxt, 2) + pow(rAyt, 2)));
    }
}
