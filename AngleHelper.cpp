//
// Created by max on 10.07.24.
//
#include "AngleHelper.h"


//Useful enum to track facing directions of game objects in 45 degree angles
    eFacingAngle operator+(eFacingAngle a1, eFacingAngle a2) {
        int sum = static_cast<int>(a1) + static_cast<int>(a2);

        sum %= 360;


        switch (sum) {
            case 0:
                return eFacingAngle::Up;
            case 45:
                return eFacingAngle::UpRight;
            case 90:
                return eFacingAngle::Right;
            case 135:
                return eFacingAngle::DownRight;
            case 180:
                return eFacingAngle::Down;
            case 225:
                return eFacingAngle::DownLeft;
            case 270:
                return eFacingAngle::Left;
            case 315:
                return eFacingAngle::UpLeft;
            default:
                throw std::invalid_argument("Invalid angle sum");
        }
    }


    eFacingAngle &operator+=(eFacingAngle &a1, eFacingAngle a2) {
        a1 = a1 + a2;
        return a1;
    }


    eFacingAngle operator-(eFacingAngle a1, eFacingAngle a2) {
        int diff = static_cast<int>(a1) - static_cast<int>(a2);

        diff = (diff + 360) % 360;

        switch (diff) {
            case 0:
                return eFacingAngle::Up;
            case 45:
                return eFacingAngle::UpRight;
            case 90:
                return eFacingAngle::Right;
            case 135:
                return eFacingAngle::DownRight;
            case 180:
                return eFacingAngle::Down;
            case 225:
                return eFacingAngle::DownLeft;
            case 270:
                return eFacingAngle::Left;
            case 315:
                return eFacingAngle::UpLeft;
            default:
                throw std::invalid_argument("Invalid angle difference");
        }
    }

    eFacingAngle &operator-=(eFacingAngle &a1, eFacingAngle a2) {
        a1 = a1 - a2;
        return a1;
    }


