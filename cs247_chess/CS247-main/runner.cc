#include "runner.h"
#include "game.h"

#include <string>
#include <iostream>

using namespace std;

Runner::Runner(bool extraFeatures): extraFeatures{extraFeatures} {}

void Runner::run() {
    string cmd;

    while (cin >> cmd && cmd != "quit") {
        if (cmd == "game") {
            Game game{boardConfiguration};
            game.addPlayers();
            game.run();
        } else if (cmd == "setup") {
            boardConfiguration.setup();
            boardConfiguration.printBoard();
        } else {
            cout << "An unknown command was entered!" << endl;
        }
    }
}
