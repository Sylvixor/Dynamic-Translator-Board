#include "printmsg.h"
#include <iostream>
#include <stdio.h>

using namespace std;

void printmsg(int msg){
    switch (msg)
    {
    case 1:
        std::cout << R"(
/******************************************************** */
/*   _________ __                 __  .__                 */
/*  /   _____//  |______ ________/  |_|__| ____    ____   */
/*  \_____  \\   __\__  \\_  __ \   __\  |/    \  / ___\  */
/*  /        \|  |  / __ \|  | \/|  | |  |   |  \/ /_/  > */
/* /_______  /|__| (____  /__|   |__| |__|___|  /\___  /  */
/*         \/           \/                    \//_____/   */
/******************************************************** */)" << endl;
        break;
    case 2:
        std::cout << "/****************/" << endl;
    std::cout << "/* Starting I2C */" << endl;
    std::cout << "/*   Scanner    */" << endl;
    std::cout << "/****************/" << endl;
    case 3:
        std::cout << "--------------------------------------" << endl;
    std::cout << "+++device info end+++" << endl;
    std::cout << "/***************/" << endl;
    std::cout << "/* I2C Scanner */" << endl;
    std::cout << "/*  Finished   */" << endl;
    std::cout << "/***************/" << endl;
    case 4:
        std::cout << "/*********/" << endl;
    std::cout << "/* Setup */" << endl;
    std::cout << "/*********/" << endl;
    default:
        break;
    }
}