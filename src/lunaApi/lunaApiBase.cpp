#include <string.h>

#include "logging.h"
#include "lunaApiBase.h"

lunaApiBase::serviceApi* lunaApiBase::pPrivateApi   = NULL;
lunaApiBase::serviceApi* lunaApiBase::pPublicApi    = NULL;

lunaApiBase*             lunaApiBase::pInstance     = NULL;

lunaApiBase::lunaApiBase() {
}

lunaApiBase::~lunaApiBase() {
}

void lunaApiBase::initLunaService() {
    LSError lserror;
    LSErrorInit(&lserror);

    LOG_INFO(MSGID_LUNASERVICE, 0, "[ %s : %d ] %s( ... )", __FILE__, __LINE__, __FUNCTION__);

    // Get private/public bus for aiservice.
    LSHandle *pPrivateHandle  = LSPalmServiceGetPrivateConnection(pLSPalmService);
    LSHandle *pPublicHandle   = LSPalmServiceGetPublicConnection(pLSPalmService);

    // Registe private method
    for (serviceApi *p = pPrivateApi; p->category != NULL; p++) {
        if( !LSRegisterCategory(pPrivateHandle, p->category, p->methods, NULL, NULL, &lserror) ) {
            LSErrorPrint(&lserror, stderr);
            LSErrorFree(&lserror);
            return;
        }
    }

    // Registe public method
    for (serviceApi *p = pPublicApi; p->category != NULL; p++) {
        fprintf(stderr, "%p\n", pPublicApi);
        if( !LSRegisterCategory(pPublicHandle, p->category, p->methods, NULL, NULL, &lserror) ) {
            LSErrorPrint(&lserror, stderr);
            LSErrorFree(&lserror);
            return;
        }
    }
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

void lunaApiBase::postEvent(char *subscribeKey, char *payload) {
    LSError lserror;
    LSErrorInit(&lserror);

    // Post event message to the subscribers
    bool retVal = LSSubscriptionRespond(
        lunaApiBase::pInstance->pLSPalmService,
        subscribeKey,
        payload,
        &lserror
    );

    if (!retVal) {
        LSErrorPrint(&lserror, stderr);
        LSErrorFree(&lserror);
    }
}
