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

#include <string.h>

#include "logging.h"
#include "lunaApiBase.h"

lunaApiBase::lunaApiBase():
pApis(NULL),
serviceId(NULL),
pLSHandle(NULL) {
}

lunaApiBase::~lunaApiBase() {
}

void lunaApiBase::runService(GMainLoop *mainLoop) {
    LSError lserror;
    LSErrorInit(&lserror);

    if (serviceId) {
        // Register service as the com.webos.service.ai.voice
        bool retVal = LSRegister(serviceId, &pLSHandle, &lserror);

        if (retVal) {
            // Attach the service to main loop for IPC.
            retVal = LSGmainAttach(pLSHandle, mainLoop, &lserror);

            if (retVal) {
                initLunaService();
                return ;
            }
        }
    }

    AI_LOG_CRITICAL(MSGID_LUNASERVICE, 1, PMLOGKS("ERRTEXT", lserror.message), "Could not initialize %s" , serviceId);
    LSErrorFree(&lserror);

    exit(-1);
}

bool lunaApiBase::initLunaService() {
    LSError lserror;
    LSErrorInit(&lserror);

    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... )", __FILE__, __LINE__, __FUNCTION__);

    // Registe methods
    for (serviceApi *p = pApis; p->category != NULL; p++) {
        if( !LSRegisterCategory(pLSHandle, p->category, p->methods, NULL, NULL, &lserror) ) {
            LSErrorPrint(&lserror, stderr);
            LSErrorFree(&lserror);
            return false;
        }
    }

    return true;
}

void lunaApiBase::LSMessageReplyErrorInvalidParams(LSHandle *sh, LSMessage *msg) {
    LSError lserror;
    LSErrorInit(&lserror);

    bool retVal = LSMessageReply(sh, msg, "{\"returnValue\":false,\"errorText\":\"Invalid parameters.\"}", NULL);
    if (!retVal) {
        LSErrorPrint(&lserror, stderr);
        LSErrorFree(&lserror);
    }
}

void lunaApiBase::LSMessageReplyErrorBadJSON(LSHandle *sh, LSMessage *msg) {
    LSError lserror;
    LSErrorInit(&lserror);

    bool retVal = LSMessageReply(sh, msg, "{\"returnValue\":false,\"errorText\":\"Malformed json.\"}", NULL);
    if (!retVal) {
        LSErrorPrint(&lserror, stderr);
        LSErrorFree(&lserror);
    }
}

void lunaApiBase::LSMessageReplySuccess(LSHandle *sh, LSMessage *msg, char *payload) {
    LSError lserror;
    LSErrorInit(&lserror);

    bool retVal;

    if (payload == NULL) {
        retVal = LSMessageReply(sh, msg, "{\"returnValue\":true}", NULL);
    } else {
        retVal = LSMessageReply(sh, msg, payload, NULL);
    }

    if (!retVal) {
        LSErrorPrint(&lserror, stderr);
        LSErrorFree(&lserror);
    }
}

void lunaApiBase::postEvent(LSHandle *handle, void *subscribeKey, void *payload) {
    LSError lserror;
    LSErrorInit(&lserror);

    // Post event message to the clients
    bool retVal = LSSubscriptionReply(
        handle,
        (char *)subscribeKey,
        (char *)payload,
        &lserror
    );

    if (!retVal) {
        LSErrorPrint(&lserror, stderr);
        LSErrorFree(&lserror);
    }
}
