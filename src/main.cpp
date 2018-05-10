#include "logging.h"
#include "lunaApiVoice.h"
#include "lunaApiFace.h"
#include "lunaApiGesture.h"

GMainLoop *mainLoop;

void signalHandler(int signal) {
    switch(signal) {
        case SIGSTOP:
            AI_KMSG_DEBUG_MSG(1, "[%s] %s( ... ) , case SIGSTOP\n" , MSGID_LUNASERVICE, __FUNCTION__);
            break;

        case SIGCONT:
            AI_KMSG_DEBUG_MSG(1, "[%s] %s( ... ) , case SIGCONT\n" , MSGID_LUNASERVICE, __FUNCTION__);
            break;

        case SIGTERM:
            AI_KMSG_DEBUG_MSG(1, "[%s] %s( ... ) , case SIGTERM\n" , MSGID_LUNASERVICE, __FUNCTION__);
            if (g_main_loop_is_running(mainLoop)) g_main_loop_quit(mainLoop);
            g_main_loop_unref(mainLoop);
            break;

        case SIGINT:
            AI_KMSG_DEBUG_MSG(1, "[%s] %s( ... ) , case SIGINT\n" , MSGID_LUNASERVICE, __FUNCTION__);
            if (g_main_loop_is_running(mainLoop)) g_main_loop_quit(mainLoop);
            g_main_loop_unref(mainLoop);
            break;
    }
}

void registSignalHandler() {
    /*
    * Register a function to be able to gracefully handle termination signals
    * from the OS or other processes.
    */
    signal(SIGSTOP, signalHandler);
    signal(SIGCONT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGINT,  signalHandler);
}

int main(int argc, char **argv) {
    registSignalHandler();

    mainLoop = g_main_loop_new(NULL, FALSE);

    lunaApiFace::Instance()->runService(mainLoop);
    lunaApiGesture::Instance()->runService(mainLoop);
    lunaApiVoice::Instance()->runService(mainLoop);

    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "%s( ... ) , aiservice daemon started" , __FUNCTION__);
    g_main_loop_run(mainLoop);

    return 0;
}
