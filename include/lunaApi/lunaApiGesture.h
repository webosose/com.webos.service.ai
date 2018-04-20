#ifndef __LUNAAPIGESTURE_H__
#define __LUNAAPIGESTURE_H__

#include <lunaApiBase.h>

class lunaApiGesture : public lunaApiBase {
public:
    ~lunaApiGesture();

    static const char *serviceName;

    static const char *subscribtionState;
    static const char *subscribtionResponse;

    static lunaApiGesture* Instance() {
        if (!pInstance) pInstance = new lunaApiGesture;
        return (lunaApiGesture *)pInstance;
    }

    virtual void runService(GMainLoop *mainLoop) override;

private:
    lunaApiGesture();

    static const LSMethod     rootCategory[];
    static const serviceApi   gesturePrivApi[];
    static const serviceApi   gesturePubApi[];

private:
    static bool start(LSHandle *sh, LSMessage *msg, void *data);
    static bool stop(LSHandle *sh, LSMessage *msg, void *data);
    static bool getState(LSHandle *sh, LSMessage *msg, void *data);
    static bool getResponse(LSHandle *sh, LSMessage *msg, void *data);
};

#endif
