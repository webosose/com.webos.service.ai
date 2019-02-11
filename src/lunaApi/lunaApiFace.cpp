// Copyright (c) 2018-2019 LG Electronics, Inc.
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

#include <json-c/json.h>

#include "logging.h"
#include "lunaApiFace.h"

lunaApiFace* lunaApiFace::pInstance = NULL;

const LSMethod lunaApiFace::rootCategory[] = {
    { "start",                  start,                  LUNA_METHOD_FLAGS_NONE},
    { "stop",                   stop,                   LUNA_METHOD_FLAGS_NONE},
    { "getState",               getState,               LUNA_METHOD_FLAGS_NONE},
    { "getResponse",            getResponse,            LUNA_METHOD_FLAGS_NONE},
    { NULL, NULL },
};

const lunaApiFace::serviceApi lunaApiFace::faceApis[] = {
    { "/", (LSMethod *)rootCategory },
    { NULL, NULL },
};

lunaApiFace::lunaApiFace() {
    static const char *faceServiceId = "com.webos.service.ai.face";

    pApis       = (serviceApi *)faceApis;
    serviceId   = faceServiceId;
}

lunaApiFace::~lunaApiFace() {
}

// API implementations.
bool lunaApiFace::start(LSHandle *sh, LSMessage *msg, void *data) {
    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (!object) {
        Instance()->LSMessageReplyErrorBadJSON(sh, msg);
        return true;
    }

    // ToDo : start face engine worker
    char *payload = g_strdup_printf("{\"returnValue\":false,\"errorText\":\"Not supported.\"}");

    Instance()->LSMessageReplySuccess(sh, msg, payload);

    g_free(payload);

    return true;
}

bool lunaApiFace::stop(LSHandle *sh, LSMessage *msg, void *data) {
    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (!object) {
        Instance()->LSMessageReplyErrorBadJSON(sh, msg);
        return true;
    }

    // ToDo : stop face engine worker
    char *payload = g_strdup_printf("{\"returnValue\":false,\"errorText\":\"Not supported.\"}");

    Instance()->LSMessageReplySuccess(sh, msg, payload);

    return true;
}

bool lunaApiFace::getState(LSHandle *sh, LSMessage *msg, void *data) {
    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ), payload = %s", __FILE__, __LINE__, __FUNCTION__, LSMessageGetPayload(msg));

    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (!object) {
        Instance()->LSMessageReplyErrorBadJSON(sh, msg);
        return true;
    }

    // ToDo : getState from face engine worker
    char *payload = g_strdup_printf("{\"returnValue\":false,\"errorText\":\"Not supported.\"}");

    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ), payload = %s", __FILE__, __LINE__, __FUNCTION__, payload);

    Instance()->LSMessageReplySuccess(sh, msg, payload);

    g_free(payload);

    return true;
}

bool lunaApiFace::getResponse(LSHandle *sh, LSMessage *msg, void *data) {
    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ) , payload = %s" , __FILE__ , __LINE__ , __FUNCTION__ , LSMessageGetPayload(msg));

    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (!object) {
        Instance()->LSMessageReplyErrorBadJSON(sh, msg);
        return true;
    }


    // ToDo : getResopnse from face engine worker
    char *payload = g_strdup_printf("{\"returnValue\":false,\"errorText\":\"Not supported.\"}");

    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ), payload = %s" , __FILE__, __LINE__, __FUNCTION__, payload);

    Instance()->LSMessageReplySuccess(sh, msg, payload);

    g_free(payload);

    return true;
}

void lunaApiFace::postEvent(void *subscribeKey, void *payload) {
    lunaApiBase::postEvent(Instance()->pLSHandle, subscribeKey, payload);
}
