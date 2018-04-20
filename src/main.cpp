#include "logging.h"
#include "lunaApiVoice.h"
#include "lunaApiFace.h"
#include "lunaApiGesture.h"

GMainLoop *mainLoop;

void signalHandler(int signal) {
    switch(signal) {
        case SIGSTOP:
            KMSG_DEBUG_MSG(1, "[%s] %s( ... ) , case SIGSTOP\n" , MSGID_LUNASERVICE, __FUNCTION__);
            break;

        case SIGCONT:
            KMSG_DEBUG_MSG(1, "[%s] %s( ... ) , case SIGCONT\n" , MSGID_LUNASERVICE, __FUNCTION__);
            break;

        case SIGTERM:
            KMSG_DEBUG_MSG(1, "[%s] %s( ... ) , case SIGTERM\n" , MSGID_LUNASERVICE, __FUNCTION__);
            if (g_main_loop_is_running(mainLoop)) g_main_loop_quit(mainLoop);
            g_main_loop_unref(mainLoop);
            break;

        case SIGINT:
            KMSG_DEBUG_MSG(1, "[%s] %s( ... ) , case SIGINT\n" , MSGID_LUNASERVICE, __FUNCTION__);
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

    lunaApiVoice::Instance()->runService(mainLoop);
    // Todo : resolve the 'ls-hubd LS_OLD_PALM_SERVICE_DETECTED Old Palm services are deprecated. You should not LSRegister twice.'
    //lunaApiFace::Instance()->runService(mainLoop);
    //lunaApiGesture::Instance()->runService(mainLoop);
    
    LOG_INFO(MSGID_LUNASERVICE, 0, "%s( ... ) , aiservice daemon started" , __FUNCTION__);
    g_main_loop_run(mainLoop);

    return 0;
}
