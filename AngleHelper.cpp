//
// Created by max on 10.07.24.
//
#include "AngleHelper.h"


//Useful enum to track facing directions of game objects in 45 degree angles


// Overload the + operator to add two angles
    eFacingAngle operator+(eFacingAngle a1, eFacingAngle a2) {
        int sum = static_cast<int>(a1) + static_cast<int>(a2);
        // Normalize the angle to be within [0, 360)
        sum %= 360;

        // Convert the sum back to an eFacingAngle enum
        switch (sum) {
            case 360:
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

// Overload the += operator to add an angle to the current angle
    eFacingAngle &operator+=(eFacingAngle &a1, eFacingAngle a2) {
        a1 = a1 + a2;
        return a1;
    }

// Overload the - operator to subtract two angles
    eFacingAngle operator-(eFacingAngle a1, eFacingAngle a2) {
        int diff = static_cast<int>(a1) - static_cast<int>(a2);
        // Normalize the angle to be within [0, 360)
        diff = (diff + 360) % 360;

        // Convert the diff back to an eFacingAngle enum
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

// Overload the -= operator to subtract an angle from the current angle
    eFacingAngle &operator-=(eFacingAngle &a1, eFacingAngle a2) {
        a1 = a1 - a2;
        return a1;
    }


