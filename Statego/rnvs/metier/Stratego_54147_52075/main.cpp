#include <iostream>

#include "model/stratego.h"     // rnvs : ajout
#include "controller/controller.h"
#include "view/view.h"
#include "model/difficulty.h"
using namespace std;

int main()
{
    stratego::Stratego game{};
    stratego::View view{game};
    stratego::Controller controller{game, view};
    controller.start();
}
