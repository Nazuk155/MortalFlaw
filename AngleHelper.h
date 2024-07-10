#ifndef ANGLE_HELPER_H
#define ANGLE_HELPER_H
#include <global.h>

enum class Angle {
    Up = 0,
    UpRight = 45,
    Right = 90,
    DownRight = 135,
    Down = 180,
    DownLeft = 225,
    Left = 270,
    UpLeft = 315
};

Angle operator+(Angle a1, Angle a2);
Angle& operator+=(Angle& a1, Angle a2);
Angle operator-(Angle a1, Angle a2);
Angle& operator-=(Angle& a1, Angle a2);

#endif // ANGLE_HELPER_H
