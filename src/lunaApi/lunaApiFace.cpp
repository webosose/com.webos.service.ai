#include <json-c/json.h>

#include "logging.h"
#include "lunaApiFace.h"

lunaApiFace* lunaApiFace::pInstance     = NULL;

const char* lunaApiFace::faceServiceId          = "com.webos.service.ai.face";

const LSMethod lunaApiFace::rootCategory[] = {
    { "start",                  start,                  0},
    { "stop",                   stop,                   0},
    { "getState",               getState,               0},
    { "getResponse",            getResponse,            0},
    { NULL, NULL },
};

const lunaApiFace::serviceApi lunaApiFace::faceApis[] = {
    { "/", rootCategory },
    { NULL, NULL },
};

lunaApiFace::lunaApiFace() {
    pApis       = faceApis;
    serviceId   = faceServiceId;
}

lunaApiFace::~lunaApiFace() {
}

// API implementations.
bool lunaApiFace::start(LSHandle *sh, LSMessage *msg, void *data) {
    json_object *object = json_tokener_parse(LSMessageGetPayload(msg));
    if (is_error(object)) {
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
    if (is_error(object)) {
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
    if (is_error(object)) {
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
    if (is_error(object)) {
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
