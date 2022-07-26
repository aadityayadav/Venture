#ifndef CS247_CHESS_RUNNER_H
#define CS247_CHESS_RUNNER_H

#include "board.h"

class Runner {
    bool extraFeatures;
    Board boardConfiguration;
public:
    Runner(bool);
    void run();
};


#endif //CS247_CHESS_RUNNER_H
