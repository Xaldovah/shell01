#include "shell.h"

volatile sig_atomic_t sigint_received = 0;

void sigint_handler(int signum)
{
    (void)signum;

    sigint_received = 1;
}
