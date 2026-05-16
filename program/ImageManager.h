#pragma once

#include "DxLib.h"
#include "HelpfulFunc.h"

class ImageManager
{
public:
    // singleton - only one exists in the whole game
    static ImageManager& GetInstance()
    {
        static ImageManager instance;
        return instance;
    }

    void LoadAll();  // call this once at game start

    //Ball images
    Image2 RedBall;
	Image2 GreenBall;
	Image2 BlueBall;
	Image2 YellowBall;

    //Background Images
	Image2 Background;

private:
    ImageManager() {};  // private so nobody can make a new one
};