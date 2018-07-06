#include <json-c/json.h>

#include "logging.h"
#include "lunaApiGesture.h"

lunaApiGesture* lunaApiGesture::pInstance     = NULL;

const char* lunaApiGesture::gestureServiceId        = "com.webos.service.ai.gesture";

const LSMethod lunaApiGesture::rootCategory[] = {
    { "start",                  start,                  0},
    { "stop",                   stop,                   0},
    { "getState",               getState,               0},
    { "getResponse",            getResponse,            0},
    { NULL, NULL },
};

const lunaApiGesture::serviceApi lunaApiGesture::gestureApis[] = {
    { "/", rootCategory },
    { NULL, NULL },
};

lunaApiGesture::lunaApiGesture() {
    pApis       = gestureApis;
    serviceId   = gestureServiceId;
}

lunaApiGesture::~lunaApiGesture() {
}

// API implementations.
bool lunaApiGesture::start(LSHandle *sh, LSMessage *msg, void *data) {
    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (is_error(object)) {
        Instance()->LSMessageReplyErrorBadJSON(sh, msg);
        return true;
    }

    // ToDo : start gesture engine worker
    char *payload = g_strdup_printf("{\"returnValue\":false,\"errorText\":\"Not supported.\"}");

    Instance()->LSMessageReplySuccess(sh, msg, payload);

    g_free(payload);

    return true;
}

bool lunaApiGesture::stop(LSHandle *sh, LSMessage *msg, void *data) {
    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (is_error(object)) {
        Instance()->LSMessageReplyErrorBadJSON(sh, msg);
        return true;
    }

    // ToDo : stop gesture engine worker
    char *payload = g_strdup_printf("{\"returnValue\":false,\"errorText\":\"Not supported.\"}");

    Instance()->LSMessageReplySuccess(sh, msg, payload);

    return true;
}

bool lunaApiGesture::getState(LSHandle *sh, LSMessage *msg, void *data) {
    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ), payload = %s", __FILE__, __LINE__, __FUNCTION__, LSMessageGetPayload(msg));

    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (is_error(object)) {
        Instance()->LSMessageReplyErrorBadJSON(sh, msg);
        return true;
    }

    // ToDo : getState from gesture engine worker
    char *payload = g_strdup_printf("{\"returnValue\":false,\"errorText\":\"Not supported.\"}");

    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ), payload = %s", __FILE__, __LINE__, __FUNCTION__, payload);

    Instance()->LSMessageReplySuccess(sh, msg, payload);

    g_free(payload);

    return true;
}

bool lunaApiGesture::getResponse(LSHandle *sh, LSMessage *msg, void *data) {
    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ) , payload = %s" , __FILE__ , __LINE__ , __FUNCTION__ , LSMessageGetPayload(msg));

    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (is_error(object)) {
        Instance()->LSMessageReplyErrorBadJSON(sh, msg);
        return true;
    }

    // ToDo : getResponse from gesture engine worker
    char *payload = g_strdup_printf("{\"returnValue\":false,\"errorText\":\"Not supported.\"}");

    AI_LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... ), payload = %s" , __FILE__, __LINE__, __FUNCTION__, payload);

    Instance()->LSMessageReplySuccess(sh, msg, payload);

    g_free(payload);

    return true;
}

void lunaApiGesture::postEvent(void *subscribeKey, void *payload) {
    lunaApiBase::postEvent(Instance()->pLSHandle, subscribeKey, payload);
}
