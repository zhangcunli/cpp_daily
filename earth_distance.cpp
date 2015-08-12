#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

#define RADIX_NUM 2
#define PI  3.14159265
#define EARTH_RADIUS  6378137
#define RAD  (PI/180.0)

#define EARTH_RADIUS_IN_METERS  6378137.0
#define RATIO_0 0.9970707597894937
#define RATIO_1 0.0004532759255277588
#define RATIO_2  -0.00017587656744607181
#define RATIO_3 0.0000005028600490023173


// 经纬度求弧度
double radian(double d)
{
        return d * PI / 180.0;   //角度1? = π / 180
}


double get_distance_lbs(double lat1, double lng1, double lat2, double lng2)
{
        //1) 计算三个参数
        double dx = lng1 - lng2; // 经度差值
        double dy = lat1 - lat2; // 纬度差值
        double b = (lat1 + lat2) / 2.0; // 平均纬度
        //2) 计算东西方向距离和南北方向距离(单位：米)，东西距离采用三阶多项式
        double Lx = (RATIO_3 * b * b * b + RATIO_2 * b * b  + RATIO_1 * b + RATIO_0 ) * radian(dx) *EARTH_RADIUS_IN_METERS; // 东西距离
        double Ly = EARTH_RADIUS_IN_METERS * radian(dy); // 南北距离
        //3) 用平面的矩形对角距离公式计算总距离
        // return sqrt(Lx * Lx + Ly * Ly) / 1000;
        return sqrt(Lx * Lx + Ly * Ly);

}

int  get_distance(double lat1, double lng1, double lat2, double lng2) {
        double radLat1 = lat1 * RAD;
        double radLat2 = lat2 * RAD;
        double a = radLat1 - radLat2;
        double b = (lng1 - lng2) * RAD;
        double s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2)));
        s = s * EARTH_RADIUS;
        return static_cast<int>(s);
}

int main(int argc, char **argv)
{
        double flng = atof(argv[1]);
        double flat = atof(argv[2]);
        double tlng = atof(argv[3]);
        
        printf("flng=%.10f,flat=%.10f,tlng=%.10f,tlat=%.10f\n", flng, flat, tlng, tlat);
        double dis_lbs  = get_distance_lbs(flat, flng, tlat, tlng);
        int    dis_me   = get_distance(flat, flng, tlat, tlng);
        printf("dis_lbs=%.10f,dis_me=%d\n", dis_lbs, dis_me);

        return 0;
}

