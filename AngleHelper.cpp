//
// Created by max on 10.07.24.
//
#include "AngleHelper.h"


//Useful enum to track facing directions of game objects in 45 degree angles


// Overload the + operator to add two angles
    Angle operator+(Angle a1, Angle a2) {
        int sum = static_cast<int>(a1) + static_cast<int>(a2);
        // Normalize the angle to be within [0, 360)
        sum %= 360;

        // Convert the sum back to an Angle enum
        switch (sum) {
            case 360:
                return Angle::Up;
            case 45:
                return Angle::UpRight;
            case 90:
                return Angle::Right;
            case 135:
                return Angle::DownRight;
            case 180:
                return Angle::Down;
            case 225:
                return Angle::DownLeft;
            case 270:
                return Angle::Left;
            case 315:
                return Angle::UpLeft;
            default:
                throw std::invalid_argument("Invalid angle sum");
        }
    }

// Overload the += operator to add an angle to the current angle
    Angle &operator+=(Angle &a1, Angle a2) {
        a1 = a1 + a2;
        return a1;
    }

// Overload the - operator to subtract two angles
    Angle operator-(Angle a1, Angle a2) {
        int diff = static_cast<int>(a1) - static_cast<int>(a2);
        // Normalize the angle to be within [0, 360)
        diff = (diff + 360) % 360;

        // Convert the diff back to an Angle enum
        switch (diff) {
            case 0:
                return Angle::Up;
            case 45:
                return Angle::UpRight;
            case 90:
                return Angle::Right;
            case 135:
                return Angle::DownRight;
            case 180:
                return Angle::Down;
            case 225:
                return Angle::DownLeft;
            case 270:
                return Angle::Left;
            case 315:
                return Angle::UpLeft;
            default:
                throw std::invalid_argument("Invalid angle difference");
        }
    }

// Overload the -= operator to subtract an angle from the current angle
    Angle &operator-=(Angle &a1, Angle a2) {
        a1 = a1 - a2;
        return a1;
    }


