//
// Created by max on 18.07.24.
//

#include "Ui_Bar.h"



Ui_Bar::Ui_Bar()
        : _size({200, 20}),
          _backgroundClip({0, 0, 1280, 100}),
          _fillerClip({_size.x, 0, 0, 100}),
          _backgroundRect({_size.x , (SCREEN_HEIGHT - _size.y) , _size.x, _size.y}),
          _fillerRect({_size.x , (SCREEN_HEIGHT - _size.y), _size.x, _size.y})
{
}


Ui_Bar::Ui_Bar(Point size, int offsetX,int offsetY)
        : _size(size),
          offsetX(offsetX),
          offsetY(offsetY)
{
}

void Ui_Bar::setUIBarDrawFillerPercent(int percent)
{
    _fillerClip.x = _backgroundClip.w;
    _fillerClip.w = (_backgroundClip.w / 10) * percent;
    _fillerRect.w = (_backgroundRect.w / 10) * percent;

}
