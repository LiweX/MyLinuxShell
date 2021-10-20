#include "myFuncs.h"

void switchOffSignals(void){
    signal(SIGINT,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    signal(SIGQUIT,SIG_IGN);
}
void switchOnSignals(void){
    signal(SIGINT,SIG_DFL);
    signal(SIGTSTP,SIG_DFL);
    signal(SIGQUIT,SIG_DFL); 
}