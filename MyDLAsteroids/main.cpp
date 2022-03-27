#include "MyDLAsteroidsFramework.h"
#include "MyFramework.h"

int main(int argc, char *argv[])
{
    srand((unsigned int)time(0));
    return run(new MyDLAsteroidsFramework);
    //return run(new MyFramework);
}
