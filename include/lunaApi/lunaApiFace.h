#ifndef __LUNAAPIFACE_H__
#define __LUNAAPIFACE_H__

#include <lunaApiBase.h>

class lunaApiFace : public lunaApiBase {
public:
    ~lunaApiFace();

    static const char *faceServiceId;

    static const char *subscribtionState;
    static const char *subscribtionResponse;

    static lunaApiFace* Instance() {
        if (!pInstance) pInstance = new lunaApiFace;
        return pInstance;
    }

private:
    lunaApiFace();

    static const LSMethod     rootCategory[];
    static const serviceApi   faceApis[];

private:
    static bool start(LSHandle *sh, LSMessage *msg, void *data);
    static bool stop(LSHandle *sh, LSMessage *msg, void *data);
    static bool getState(LSHandle *sh, LSMessage *msg, void *data);
    static bool getResponse(LSHandle *sh, LSMessage *msg, void *data);

    static void postEvent(void *subscribeKey, void *payload);

private:
    static lunaApiFace *pInstance;
};

#endif
