//
// Created by max on 18.07.24.
//
#pragma once

#include "global.h"

/** UI is a mess. Still need to clean this class up as well. Does what i need it to do right now and not more.*/
class Ui_Bar {

public:

    Ui_Bar();

    int offsetY;
    int offsetX;

    Point _size = {200, 20};

    Rect _backgroundClip = {0, 0, 1280, 100};
    Rect _fillerClip = {_size.x, 0, 0, 100};
    Rect _backgroundRect = {_size.x / offsetX, (SCREEN_HEIGHT - _size.y) - _size.y * offsetY, _size.x, _size.y};
    Rect _fillerRect  = {_size.x / offsetX, (SCREEN_HEIGHT - _size.y) - _size.y * offsetY, _size.x, _size.y};

    Ui_Bar(Point _size,int offsetX,int offsetY);

    void setUIBarDrawFillerPercent(int percent);
};