#ifndef __LUNAAPIBASE_H__
#define __LUNAAPIBASE_H__

#include <luna-service2/lunaservice.h>

// luna-api base class

class lunaApiBase {
public:
    ~lunaApiBase();

    void runService(GMainLoop *);

protected:
    lunaApiBase();

    typedef struct {
        const char  *category;
        LSMethod    *methods;
    } serviceApi;

    serviceApi  *pApis;

protected:
    bool initLunaService();

    void LSMessageReplyErrorInvalidParams(LSHandle *sh, LSMessage *msg);
    void LSMessageReplyErrorBadJSON(LSHandle *sh, LSMessage *msg);
    void LSMessageReplySuccess(LSHandle *sh, LSMessage *msg, char *payload);

    static void postEvent(LSHandle *handle, char *subscribeKey, char *payload);

protected:
    char        *serviceId;
    LSHandle    *pLSHandle;
};

#endif
