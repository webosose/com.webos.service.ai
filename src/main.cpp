// Copyright (c) 2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

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
