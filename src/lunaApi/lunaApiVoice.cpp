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
#include <json-c/json.h>

#include "logging.h"
#include "lunaApiVoice.h"

using namespace speechRecognition;

lunaApiVoice* lunaApiVoice::pInstance     = NULL;

const char* lunaApiVoice::voiceServiceId        = "com.webos.service.ai.voice";

const LSMethod lunaApiVoice::rootCategory[] = {
    { "start",                  start,                  0},
    { "stop",                   stop,                   0},
    { "getState",               getState,               0},
    { "getResponse",            getResponse,            0},
    { NULL, NULL },
};

const lunaApiVoice::serviceApi lunaApiVoice::voiceApis[] = {
    { "/", rootCategory },
    { NULL, NULL },
};

lunaApiVoice::lunaApiVoice() {
    pApis       = voiceApis;
    serviceId   = voiceServiceId;

    mSrw.register_event_Callback(postEvent);
}

lunaApiVoice::~lunaApiVoice() {
}

// API implementations.
bool lunaApiVoice::start(LSHandle *sh, LSMessage *msg, void *data) {
    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (!object) {
        Instance()->LSMessageReplyErrorBadJSON(sh, msg);
        return true;
    }

    const char *mode        = json_object_get_string(json_object_object_get(object, "mode"));
    json_object *keyword    = json_object_object_get(object, "keywordDetect");
    const bool useKeyword   = json_object_get_boolean(keyword);
    const char *clientName  = LSMessageGetSenderServiceName(msg);
    const char *clientId    = LSMessageGetUniqueToken(msg);
    const char *appId       = LSMessageGetApplicationID(msg);

    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ) clientName = %s, applicationId = %s, clientId = %s, mode = %s, useKeyword = %d", __FILE__, __LINE__, __FUNCTION__, clientName, appId, clientId, mode, useKeyword);

    ERROR_CODE ret = INVALID_PARAM;
    if (mode != NULL && keyword != NULL) ret = Instance()->mSrw.start(mode, useKeyword);

    char *payload = NULL;
    if (ret == NONE) payload = g_strdup_printf("{\"returnValue\":true}");
    else payload = g_strdup_printf("{\"returnValue\":false,\"errorCode\":%d,\"errorText\":\"%s\"}", ret, errorStr(ret));

    Instance()->LSMessageReplySuccess(sh, msg, payload);
    g_free(payload);

    return true;
}

bool lunaApiVoice::stop(LSHandle *sh, LSMessage *msg, void *data) {
    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (!object) {
        Instance()->LSMessageReplyErrorBadJSON(sh, msg);
        return true;
    }

    const bool subscribe    = json_object_get_boolean(json_object_object_get(object, "subscribe"));
    const char *clientName  = LSMessageGetSenderServiceName(msg);
    const char *clientId    = LSMessageGetUniqueToken(msg);
    const char *appId       = LSMessageGetApplicationID(msg);

    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ) clientName = %s, applicationId = %s, clientId = %s", __FILE__, __LINE__, __FUNCTION__, clientName, appId, clientId);

    ERROR_CODE ret = Instance()->mSrw.stop();

    char *payload = NULL;
    if (ret == NONE) payload = g_strdup_printf("{\"returnValue\":true}");
    else payload = g_strdup_printf("{\"returnValue\":false,\"errorCode\":%d,\"errorText\":\"%s\"}", ret, errorStr(ret));

    Instance()->LSMessageReplySuccess(sh, msg, payload);
    g_free(payload);

    return true;
}

bool lunaApiVoice::getState(LSHandle *sh, LSMessage *msg, void *data) {
    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ), payload = %s", __FILE__, __LINE__, __FUNCTION__, LSMessageGetPayload(msg));

    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (!object) {
        Instance()->LSMessageReplyErrorBadJSON(sh, msg);
        return true;
    }

    const bool subscribe    = json_object_get_boolean(json_object_object_get(object, "subscribe"));
    const char *clientName  = LSMessageGetSenderServiceName(msg);
    const char *clientId    = LSMessageGetUniqueToken(msg);
    const char *appId       = LSMessageGetApplicationID(msg);

    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ) clientName = %s, applicationId = %s, clientId = %s", __FILE__, __LINE__, __FUNCTION__, clientName, appId, clientId);

    if (subscribe) {
        LSError lserror;
        LSErrorInit(&lserror);

        if (!LSSubscriptionAdd(sh, subscription_key_state, msg, &lserror)) {
            LSErrorPrint(&lserror, stderr);
            LSErrorFree(&lserror);
            return true;
        }
    }

    char *state     = stateStr(Instance()->mSrw.getState());
    char *payload   = g_strdup_printf("{\"returnValue\":true,\"subscribed\":%s,\"state\":\"%s\"}", subscribe ? "true" : "false", state);

    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ), state = %s, payload = %s", __FILE__, __LINE__, __FUNCTION__, state, payload);

    Instance()->LSMessageReplySuccess(sh, msg, payload);

    g_free(payload);

    return true;
}

bool lunaApiVoice::getResponse(LSHandle *sh, LSMessage *msg, void *data) {
    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ) , payload = %s" , __FILE__ , __LINE__ , __FUNCTION__ , LSMessageGetPayload(msg));

    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (!object) {
        Instance()->LSMessageReplyErrorBadJSON(sh, msg);
        return true;
    }

    const bool subscribe            = json_object_get_boolean(json_object_object_get(object, "subscribe"));
    const char *clientName          = LSMessageGetSenderServiceName(msg);
    const char *clientId            = LSMessageGetUniqueToken(msg);
    const char *appId               = LSMessageGetApplicationID(msg);

    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ) clientName = %s, applicationId = %s, clientId = %s", __FILE__, __LINE__, __FUNCTION__, clientName, appId, clientId);

    if (subscribe) {
        LSError lserror;
        LSErrorInit(&lserror);

        if (!LSSubscriptionAdd(sh, subscription_key_response, msg, &lserror)) {
            LSErrorPrint(&lserror, stderr);
            LSErrorFree(&lserror);
            return true;
        }
    }

    char *subscribed = subscribe ? "true" : "false";
    char *payload    = g_strdup_printf("{\"returnValue\":true,\"subscribed\":%s}", subscribed);

    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ), payload = %s" , __FILE__, __LINE__, __FUNCTION__, payload);

    Instance()->LSMessageReplySuccess(sh, msg, payload);

    g_free(payload);

    return true;
}

void lunaApiVoice::postEvent(void *subscribeKey, void *payload) {
    lunaApiBase::postEvent(Instance()->pLSHandle, subscribeKey, payload);
}
