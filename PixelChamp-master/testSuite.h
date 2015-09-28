#ifndef TESTSUITE
#define TESTSUITE

class charger;
class crawler;
class flyer;
class jumper;
class testSuite
{
    public:
    testSuite();
    void testCharger();
    void testCrawler();
    void testJumper();
    void testFlyer();
    void testcharSelect();
    void testGenerator();
    void testPlayer();
    void testWeapons();
    int successRate;
    int failureRate;

};

#endif
