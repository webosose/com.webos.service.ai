#ifndef __LUNAAPIGESTURE_H__
#define __LUNAAPIGESTURE_H__

#include <lunaApiBase.h>

class lunaApiGesture : public lunaApiBase {
public:
    ~lunaApiGesture();

    static const char *gestureServiceId;

    static const char *subscribtionState;
    static const char *subscribtionResponse;

    static lunaApiGesture* Instance() {
        if (!pInstance) pInstance = new lunaApiGesture;
        return pInstance;
    }

private:
    lunaApiGesture();

    static const LSMethod     rootCategory[];
    static const serviceApi   gestureApis[];

private:
    static bool start(LSHandle *sh, LSMessage *msg, void *data);
    static bool stop(LSHandle *sh, LSMessage *msg, void *data);
    static bool getState(LSHandle *sh, LSMessage *msg, void *data);
    static bool getResponse(LSHandle *sh, LSMessage *msg, void *data);
    
    static void postEvent(char *subscribeKey, char *payload);

private: 
    static lunaApiGesture *pInstance;
};

#endif
