#ifndef __LUNAAPIVOICE_H__
#define __LUNAAPIVOICE_H__

#include <lunaApiBase.h>

class lunaApiVoice : public lunaApiBase {
public:
    ~lunaApiVoice();

    static const char *serviceName;

    static const char *subscribtionState;
    static const char *subscribtionResponse;

    static lunaApiVoice* Instance() {
        if (!pInstance) pInstance = new lunaApiVoice;
        return (lunaApiVoice *)pInstance;
    }

    virtual void runService(GMainLoop *mainLoop) override;

private:
    lunaApiVoice();

    static const LSMethod     rootCategory[];
    static const serviceApi   voicePrivApi[];
    static const serviceApi   voicePubApi[];

private:
    static bool start(LSHandle *sh, LSMessage *msg, void *data);
    static bool stop(LSHandle *sh, LSMessage *msg, void *data);
    static bool getState(LSHandle *sh, LSMessage *msg, void *data);
    static bool getResponse(LSHandle *sh, LSMessage *msg, void *data);
};

#endif
