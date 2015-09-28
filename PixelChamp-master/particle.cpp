#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "baseHeader.h"
#include <fstream>
#include <cstdlib>
#include "particleHeader.h"
#include "LTextureHeader.h"
#include "tileHeader.h"

extern SDL_Surface *screen;
extern SDL_Surface *dot;
extern SDL_Surface *bits;
extern SDL_Rect camera;
extern LTexture partT;
extern SDL_Rect particleClips[];
extern int curX;
extern int curY;
extern int pixel_capacity;

Particle::Particle( int X, int Y, int C )
{
    //Set offsets
    x = X;
    y = Y;
    colour = C;
    done = false;

    //Initialize animation
    frame = rand() % 5;
   // type = green;
    //Set type
}

void Particle::PartLeft2()
{

        if(frame < 25)
            x -= rand() % 30;
        if(is_falling() == 0)
            y -= rand() % 30;
        else if(is_falling() == 1)
            y -= (rand() % 10);
        else if(is_falling () == 2)
            y += 10;
        else if(is_falling () == 3)
        {
            x += 5;
            y += 20;
        }

}

void Particle::PartRight2()
{

        if(frame < 25)
            x += rand() % 30;
        if(is_falling() == 0)
            y -= rand() % 30;
        else if(is_falling() == 1)
            y -= (rand() % 10);
        else if(is_falling () == 2)
            y += 10;
        else if(is_falling () == 3)
        {
            x -= 5;
            y += 20;
        }


}

void Particle::PartLeft()
{

        if(frame < 25)
            x -= rand() % 30;
        if(is_falling() == 0)
            y -= rand() % 30;
        else if(is_falling() == 1)
            y -= (rand() % 10);
        else if(is_falling () == 2)
            y += 10;
        else if(is_falling () == 3)
        {
            x += 5;
            y += 20;
        }
        else
        {
            to_player();
        }
}

void Particle::PartRight()
{

        if(frame < 25)
            x += rand() % 30;
        if(is_falling() == 0)
            y -= rand() % 30;
        else if(is_falling() == 1)
            y -= (rand() % 10);
        else if(is_falling () == 2)
            y += 10;
        else if(is_falling () == 3)
        {
            x -= 5;
            y += 20;
        }
        else if(is_falling () == 4 && x < 8000)
        {
            to_player();
        }

}

void Particle::show()
{
    if(x > camera.x && x < (camera.x + camera.w)&& y > camera.y && y < (camera.y + camera.h))
        partT.render(x - camera.x, y - camera.y, &particleClips[colour]);
    frame++;
}

void Particle:: orbit(SDL_Rect box)
{
    x = box.x;
    y = box.y + 60;
    x += rand() % 64;
    y -= rand() % 64;
}

void Particle:: orbit_start(SDL_Rect box)
{
    x = box.x;
    y = box.y + 64;
}

void Particle:: orbit2()
{
    if(frame >= 0 && frame < 20)
    {
        x = rand() % 10;
        y = rand() % 10;
    }

}

int Particle:: fallLeft()
{
    y+=10;
    x-=3;
}

int Particle::is_falling()
{
    if(frame > 25)
        return 4;
    if(frame > 15)
        return 3;
    if(frame > 10)
    {
        return 2;
    }
    if(frame > 5)
    {
        return 1;
    }
     return 0;
}


bool Particle::is_dead()
{
    if( frame > 20 )
    {
        return true;
    }

    return false;
}

int Particle::getFrame()
{
    return frame;
}

int Particle:: to_player()
{
    if(x < curX + 60)
        x += 15;
    else if (x > curX + 80)
        x -= 15;
    if(y < curY + 60)
        y += 5;
    else if (y > curY + 80)
        y -= 5;

    if(x > curX + 60 && x < curX + 90 && y > curY + 60 && y < curY + 90 && !done)
    {
        if(colour != 4)
            pixel_capacity++;
        x = 10000;
        delete this;
        done = true;
    }
}
