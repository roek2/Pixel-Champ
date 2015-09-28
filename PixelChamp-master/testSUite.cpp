#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <fstream>
#include "baseHeader.h"
#include "enemyHeader.h"
#include "chargerHeader.h"
#include "crawlerHeader.h"
#include "jumperHeader.h"
#include "Flyer.h"
#include "setupHeader.h"
#include "tileHeader.h"
#include "dotHeader.h"
#include "weaponHeader.h"
#include "swordHeader.h"
#include "gunHeader.h"
#include "converterHeader.h"
#include "LTextureHeader.h"
#include "particleHeader.h"
#include "charSelect.h"
#include "testSuite.h"
#include "generatorHeader.h"
#include "playerstatsHeader.h"

extern LTexture damage;
extern SDL_Rect camera;
extern LTexture dotT;
extern bool double_time;
testSuite:: testSuite()
{
    successRate = 0;
    failureRate = 0;
}

void testSuite:: testCrawler()
{
    int successEnemy = 0;
    int failureEnemy = 0;
    Setup setup;
    crawler crawl(500, 600, 70, 60, 60);
    Dot myDot;
    myDot.box.x = 200;
    if(crawl.xVel == 2)
    {
        successRate++;
        successEnemy++;

    }
    else
    {
        failureRate++;
        failureEnemy++;
    }

    if(crawl.box.x == 500)
    {
        successRate++;
        successEnemy++;

    }
    else
    {
        failureRate++;
        failureEnemy++;
    }
    crawl.collide();

    if(crawl.xVel < 0)
        crawl.direction = false;
    else
        crawl.direction = true;

    if(crawl.xVel == -2)
    {
        successEnemy++;
        successRate++;
    }
    else
    {
        failureRate++;
        failureEnemy++;
    }

     if(crawl.xVel < 0)
        crawl.direction = false;
     else
        crawl.direction = true;
    crawl.knockBack(myDot);

    if(crawl.xVel == 2 && crawl.yVel == -5)
    {
        successEnemy++;
        successRate++;
    }
    else
    {
        failureRate++;
        failureEnemy++;
    }

    if(crawl.xVel < 0)
        crawl.direction = false;
    else
        crawl.direction = true;
    crawl.animation(setup);

    if(crawl.spriteNumber == 13)
    {
        successEnemy++;
        successRate++;
        crawl.collide();
        if(crawl.xVel < 0)
            crawl.direction = false;
        else
            crawl.direction = true;
        crawl.animation(setup);
        if(crawl.spriteNumber == 11)
        {
            successEnemy++;
            successRate++;
        }

        else
        {
            failureRate++;
            failureEnemy++;
            printf("%d\n",crawl.spriteNumber );
        }
    }
    else
    {
        failureRate++;
        failureEnemy++;
    }

    crawl.die();

    if(crawl.dead == true)
    {
        successEnemy++;
        successRate++;
    }

    else
    {
        failureRate++;
        failureEnemy++;
    }

    if(crawl.particles[0] == NULL)
    {
        failureRate++;
        failureEnemy++;
    }

    else
    {
        successEnemy++;
        successRate++;
    }

    crawl.collatural_damage();
    if(crawl.he == (crawl.he - crawl.pain))
    {
        successEnemy++;
        successRate++;
    }

    else
    {
        failureRate++;
        failureEnemy++;
    }

    printf("Test Success: %d\n", successEnemy);
    printf("Test Failed: %d\n", failureEnemy);
}

void testSuite:: testJumper()
{
    int successEnemy = 0;
    int failureEnemy = 0;
    Setup setup;
    jumper jump(500, 600, 70, 60, 60);
    Dot myDot;
    myDot.box.x = 200;

    if(jump.box.x == 500)
    {
        successRate++;
        successEnemy++;

    }
    else
    {
        failureRate++;
        failureEnemy++;
    }
    jump.collide();
     if(jump.xVel < 0)
        jump.direction = false;
     else
        jump.direction = true;

    if(jump.xVel == 0)
    {
        successEnemy++;
        successRate++;
    }
    else
    {
        failureRate++;
        failureEnemy++;
    }

     if(jump.xVel < 0)
        jump.direction = false;
     else
        jump.direction = true;
    jump.knockBack(myDot);

    if(jump.yVel == -6)
    {
        successEnemy++;
        successRate++;
    }
    else
    {

        failureRate++;
        failureEnemy++;
    }

    if(jump.xVel < 0)
        jump.direction = false;
    else
        jump.direction = true;
    jump.animation(setup);

    if(jump.spriteNumber == 7)
    {
        successEnemy++;
        successRate++;
        jump.collide();
        if(jump.xVel < 0)
            jump.direction = false;
        else
            jump.direction = true;
        jump.animation(setup);
        if(jump.spriteNumber == 8)
        {
            successEnemy++;
            successRate++;
        }

        else
        {
            failureRate++;
            failureEnemy++;
            printf("%d\n",jump.spriteNumber );
        }
    }
    else
    {
        failureRate++;
        failureEnemy++;
    }

    jump.die();

    if(jump.dead == true)
    {
        successEnemy++;
        successRate++;
    }

    else
    {
        failureRate++;
        failureEnemy++;
    }

    if(jump.particles[0] == NULL)
    {
        failureRate++;
        failureEnemy++;
    }

    else
    {
        successEnemy++;
        successRate++;
    }

    jump.collatural_damage();
    if(jump.he == (jump.he - jump.pain))
    {
        successEnemy++;
        successRate++;
    }

    else
    {
        failureRate++;
        failureEnemy++;
    }

    jump.collide_down();
    if(jump.yVel == 5)
    {
        successEnemy++;
        successRate++;
    }

    else
    {
        failureRate++;
        failureEnemy++;
    }


    printf("Test Success: %d\n", successEnemy);
    printf("Test Failed: %d\n", failureEnemy);
}

void testSuite:: testCharger()
{
    int successEnemy = 0;
    int failureEnemy = 0;
    Setup setup;
    charger charge(500, 600, 70, 60, 60);
    Dot myDot;
    myDot.box.x = 200;

    if(charge.box.x == 500)
    {
        successRate++;
        successEnemy++;

    }
    else
    {
        failureRate++;
        failureEnemy++;
    }
    charge.collide();
     if(charge.xVel < 0)
        charge.direction = false;
     else
        charge.direction = true;

    if(charge.xVel == 0)
    {
        successEnemy++;
        successRate++;
    }
    else
    {
        failureRate++;
        failureEnemy++;
    }

     if(charge.xVel < 0)
        charge.direction = false;
     else
        charge.direction = true;
    charge.knockBack(myDot);

    if(charge.yVel == -6)
    {
        successEnemy++;
        successRate++;
    }
    else
    {

        failureRate++;
        failureEnemy++;
    }

    if(charge.xVel < 0)
        charge.direction = false;
    else
        charge.direction = true;
    charge.animation(setup);

    if(charge.spriteNumber == 14)
    {
        successEnemy++;
        successRate++;
        charge.collide();
        if(charge.xVel < 0)
            charge.direction = false;
        else
            charge.direction = true;
        charge.animation(setup);
        if(charge.spriteNumber == 14)
        {
            successEnemy++;
            successRate++;
        }

        else
        {
            failureRate++;
            failureEnemy++;
            printf("%d\n",charge.spriteNumber );
        }
    }
    else
    {
        failureRate++;
        failureEnemy++;
    }

    charge.die();

    if(charge.dead == true)
    {
        successEnemy++;
        successRate++;
    }

    else
    {
        failureRate++;
        failureEnemy++;
    }

    if(charge.particles[0] == NULL)
    {
        failureRate++;
        failureEnemy++;
    }

    else
    {
        successEnemy++;
        successRate++;
    }

    charge.collatural_damage();
    if(charge.he == (charge.he - charge.pain))
    {
        successEnemy++;
        successRate++;
    }

    else
    {
        failureRate++;
        failureEnemy++;
    }

    charge.collide_down();
    if(charge.xVel == 5)
    {
        successEnemy++;
        successRate++;
    }

    else
    {
        failureRate++;
        failureEnemy++;
    }


    printf("Test Success: %d\n", successEnemy);
    printf("Test Failed: %d\n", failureEnemy);
}

void testSuite:: testFlyer()
{
    int successEnemy = 0;
    int failureEnemy = 0;
    Setup setup;
    Flyer fly(500, 600, 70, 60, 60);
    Dot myDot;
    myDot.box.x = 200;

    if(fly.box.x == 500)
    {
        successRate++;
        successEnemy++;

    }
    else
    {
        failureRate++;
        failureEnemy++;
    }
    fly.collide();
     if(fly.xVel < 0)
        fly.direction = false;
     else
        fly.direction = true;

    if(fly.xVel == 0)
    {
        successEnemy++;
        successRate++;
    }
    else
    {
        failureRate++;
        failureEnemy++;
    }

     if(fly.xVel < 0)
        fly.direction = false;
     else
        fly.direction = true;
    fly.knockBack(myDot);

    if( fly.detect == false)
    {
        successEnemy++;
        successRate++;
    }
    else
    {

        failureRate++;
        failureEnemy++;
        printf("%d\n",fly.yVel );
    }

    if(fly.xVel < 0)
        fly.direction = false;
    else
        fly.direction = true;
    fly.animation(setup);

    if(fly.spriteNumber == 5)
    {
        successEnemy++;
        successRate++;
        fly.collide();
        if(fly.xVel < 0)
            fly.direction = false;
        else
            fly.direction = true;
        fly.animation(setup);
        if(fly.spriteNumber == 5)
        {
            successEnemy++;
            successRate++;
        }

        else
        {
            failureRate++;
            failureEnemy++;
            printf("%d\n",fly.spriteNumber );
        }
    }
    else
    {
        failureRate++;
        failureEnemy++;
        printf("%d\n",fly.spriteNumber );
    }

    fly.die();

    if(fly.dead == true)
    {
        successEnemy++;
        successRate++;
    }

    else
    {
        failureRate++;
        failureEnemy++;
    }

    if(fly.particles[0] == NULL)
    {
        failureRate++;
        failureEnemy++;
    }

    else
    {
        successEnemy++;
        successRate++;
    }

    fly.collatural_damage();
    if(fly.he == (fly.he - fly.pain))
    {
        successEnemy++;
        successRate++;
    }

    else
    {
        failureRate++;
        failureEnemy++;
    }

    fly.collide_down();
    if(fly.yVel == 5)
    {
        successEnemy++;
        successRate++;
    }

    else
    {
        failureRate++;
        failureEnemy++;
    }


    printf("Test Success: %d\n", successEnemy);
    printf("Test Failed: %d\n", failureEnemy);
}

void testSuite:: testcharSelect()
{
    CharSelect cs;
    cs.loadCharChoice(1);
    cs.chooseInputFile(1,1);
}


void testSuite:: testGenerator()
{
    Converter conv;
    conv.construct();
    conv.widthMaker(10);
}

void testSuite:: testPlayer()
{
    int characterSuccess = 0;
    int characterfailure = 0;
    Dot myDot;
    myDot.stats->energy = 200;
    myDot.xVel = 5;
    if(!myDot.is_onGround())
    {
        successRate++;
        characterSuccess++;
    }

    else
    {
        failureRate++;
        characterfailure++;
    }


    myDot.set_camera();
    if(camera.x == 0)
    {
        successRate++;
        characterSuccess++;
    }

    else
    {
        failureRate++;
        characterfailure++;
    }

    if(dotT.getAlpha() == -1)
    {
        successRate++;
        characterSuccess++;
    }

    else
    {
        failureRate++;
        characterfailure++;
    }
    myDot.dash();
    myDot.show();
    if(myDot.xVel == 20 || myDot.xVel == -20)
    {
        successRate++;
        characterSuccess++;
    }

    else
    {
        failureRate++;
        characterfailure++;
    }
    myDot.makeJump();
    if(myDot.yVel >= 0)
    {
        successRate++;
        characterSuccess++;
    }

    else
    {
        failureRate++;
        characterfailure++;
    }

    myDot.double_jump();
    if(myDot.yVel >= 0)
    {
        successRate++;
        characterSuccess++;
    }

    else
    {
        failureRate++;
        characterfailure++;
    }

    double_time = true;
    myDot.second_jump = false;
    myDot.double_jump();
    if(myDot.yVel < 0)
    {
        successRate++;
        characterSuccess++;
    }

    else
    {
        failureRate++;
        characterfailure++;
    }

    if(myDot.yVel < 0)
    {
        successRate++;
        characterSuccess++;
    }

    else
    {
        failureRate++;
        characterfailure++;
    }

    myDot.bounce();
    if(myDot.yVel == -18)
    {
        successRate++;
        characterSuccess++;
    }

    else
    {
        failureRate++;
        characterfailure++;
    }

    printf("\nTest Success %d\n", characterSuccess);
    printf("Test failed %d\n", characterfailure);
}

//STICK DEBUG STUFF IN FOR PLAYER CREATOR AND GENERATOR


void testSuite:: testWeapons()
{
    gun bullet(128, 128);
    sword square(128, 128);
    Dot myDot;
    myDot.box.x = 500;
    Setup foo;
    square.get_position(myDot, foo);
    int weaponSuccess = 0;
    int weaponFailure = 0;
    if(square.box.x > 200)
    {
        weaponSuccess++;
        successRate++;
    }

    else
    {
        weaponFailure++;
        failureRate++;
    }

    bullet.get_position(myDot, foo);
    if(bullet.box.x > 200)
    {
        weaponSuccess++;
        successRate++;
    }

    else
    {
        weaponFailure++;
        failureRate++;
    }

    bullet.weaponControl(myDot);
    if(bullet.particles[0] > 0)
    {
        weaponSuccess++;
        successRate++;
    }

    else
    {
        weaponFailure++;
        failureRate++;
    }

    printf("\nTest Success %d\n", weaponSuccess);
    printf("Test failed %d\n", weaponFailure);

    printf("\nTotal Test Success %d\n", successRate);
    printf("Total Test failed %d\n", failureRate);


}

