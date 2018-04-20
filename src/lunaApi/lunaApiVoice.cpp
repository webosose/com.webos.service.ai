#include <string.h>
#include <json-c/json.h>

#include "logging.h"
#include "lunaApiVoice.h"

const char* lunaApiVoice::serviceName = "com.webos.service.ai.voice";

const char* lunaApiVoice::subscribtionState     = "AI_VOICE_STATE";
const char* lunaApiVoice::subscribtionResponse  = "AI_VOICE_RESPONSE";

const LSMethod lunaApiVoice::rootCategory[] = {
    { "start",                  start,                  0},
    { "stop",                   stop,                   0},
    { "getState",               getState,               0},
    { "getResponse",            getResponse,            0},
    { NULL, NULL },
};

const lunaApiVoice::serviceApi lunaApiVoice::voicePrivApi[] = {
    { "/", rootCategory },
    { NULL, NULL },
};

const lunaApiVoice::serviceApi lunaApiVoice::voicePubApi[] = {
    { NULL, NULL },
};

lunaApiVoice::lunaApiVoice() {
    pPrivateApi = voicePrivApi;
    pPublicApi  = voicePubApi;
}

lunaApiVoice::~lunaApiVoice() {
}

void lunaApiVoice::runService(GMainLoop *mainLoop) {
    LSError lserror;
    LSErrorInit(&lserror);

    // Register service as the com.webos.service.ai.voice
    bool retVal = LSRegisterPalmService(serviceName, &pLSPalmService, &lserror);

    if (retVal) {
        // Attach the service to main loop for IPC.
        retVal = LSGmainAttachPalmService(pLSPalmService, mainLoop, &lserror);

        if (retVal) {
            initLunaService();
            return ;
        }
    }

    LOG_CRITICAL(MSGID_LUNASERVICE, 1, PMLOGKS("ERRTEXT", lserror.message), "Could not initialize %s" , serviceName);
    LSErrorFree(&lserror);

    exit(-1);
}

// API implementations.
bool lunaApiVoice::start(LSHandle *sh, LSMessage *msg, void *data) {
    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (is_error(object)) {
        Instance()->LSMessageReplyErrorBadJSON(sh, msg);
        return true;
    }

    char *payload = NULL;

    // ToDo : start voice engine worker
    payload = g_strdup_printf("{\"returnValue\":true}");

    Instance()->LSMessageReplySuccess(sh, msg, payload);

    g_free(payload);

    return true;
}

bool lunaApiVoice::stop(LSHandle *sh, LSMessage *msg, void *data) {
    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (is_error(object)) {
        Instance()->LSMessageReplyErrorBadJSON(sh, msg);
        return true;
    }

    // ToDo : start voice engine worker

    Instance()->LSMessageReplySuccess(sh, msg, NULL);

    return true;
}

bool lunaApiVoice::getState(LSHandle *sh, LSMessage *msg, void *data) {
    LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ), payload = %s", __FILE__, __LINE__, __FUNCTION__, LSMessageGetPayload(msg));

    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (is_error(object)) {
        Instance()->LSMessageReplyErrorBadJSON(sh, msg);
        return true;
    }

    const bool subscribe    = json_object_get_boolean(json_object_object_get(object, "subscribe"));
    const char *clientName  = LSMessageGetSenderServiceName(msg);
    const char *clientId    = LSMessageGetUniqueToken(msg);
    const char *appId       = LSMessageGetApplicationID(msg);

    LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ) clientName = %s, applicationId = %s, clientId = %s", __FILE__, __LINE__, __FUNCTION__, clientName, appId, clientId);

    if (subscribe) {
        LSError lserror;
        LSErrorInit(&lserror);

        if (!LSSubscriptionAdd(sh, subscribtionState, msg, &lserror)) {
            LSErrorPrint(&lserror, stderr);
            LSErrorFree(&lserror);
            return true;
        }
    }

    // ToDo : getState voice engine worker
    char *stateStr = "idle";
    char *payload   = g_strdup_printf("{\"returnValue\":true,\"subscribed\":%s,\"state\":\"%s\"}", subscribe ? "true" : "false", stateStr);

    LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ), stateStr = %s, payload = %s", __FILE__, __LINE__, __FUNCTION__, stateStr, payload);

    Instance()->LSMessageReplySuccess(sh, msg, payload);

    g_free(payload);

    return true;
}

bool lunaApiVoice::getResponse(LSHandle *sh, LSMessage *msg, void *data) {
    LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ) , payload = %s" , __FILE__ , __LINE__ , __FUNCTION__ , LSMessageGetPayload(msg));

    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (is_error(object)) {
        Instance()->LSMessageReplyErrorBadJSON(sh, msg);
        return true;
    }

    const bool subscribe            = json_object_get_boolean(json_object_object_get(object, "subscribe"));
    const char *clientName          = LSMessageGetSenderServiceName(msg);
    const char *clientId            = LSMessageGetUniqueToken(msg);
    const char *appId               = LSMessageGetApplicationID(msg);

    LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ) clientName = %s, applicationId = %s, clientId = %s", __FILE__ ,__LINE__ ,__FUNCTION__ ,clientName ,appId , clientId);

    if (subscribe) {
        LSError lserror;
        LSErrorInit(&lserror);

        if (!LSSubscriptionAdd(sh, subscribtionResponse, msg, &lserror)) {
            LSErrorPrint(&lserror, stderr);
            LSErrorFree(&lserror);
            return true;
        }
    }

    char *subscribed = subscribe ? "true" : "false";
    char *payload   = g_strdup_printf("{\"returnValue\":true,\"subscribed\":%s}" ,subscribed);

    LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ), payload = %s" , __FILE__, __LINE__, __FUNCTION__, payload);

    Instance()->LSMessageReplySuccess(sh, msg, payload);

    g_free(payload);

    return true;
}
