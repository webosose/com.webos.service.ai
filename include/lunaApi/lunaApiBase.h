#ifndef __LUNAAPIBASE_H__
#define __LUNAAPIBASE_H__

#include <luna-service2/lunaservice.h>

// luna-api base class

class lunaApiBase {
public:
    lunaApiBase();
    ~lunaApiBase();

    virtual void runService(GMainLoop *) = 0;

protected:
    typedef struct {
        const char  *category;
        LSMethod    *methods;
    } serviceApi;

    static serviceApi *pPrivateApi;
    static serviceApi *pPublicApi;

protected:
    void initLunaService();

    void LSMessageReplyErrorInvalidParams(LSHandle *sh, LSMessage *msg);
    void LSMessageReplyErrorBadJSON(LSHandle *sh, LSMessage *msg);
    void LSMessageReplySuccess(LSHandle *sh, LSMessage *msg, char *payload);

    static void postEvent(char *subscribeKey, char *payload);

protected:
    LSPalmService        *pLSPalmService;
   
protected: 
    static lunaApiBase   *pInstance;
};

#endif
