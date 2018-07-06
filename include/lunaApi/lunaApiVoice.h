#ifndef __LUNAAPIVOICE_H__
#define __LUNAAPIVOICE_H__

#include <lunaApiBase.h>
#include <googleAssistant/speechRecognitionWorker.h>

class lunaApiVoice : public lunaApiBase {
public:
    ~lunaApiVoice();

    static const char *voiceServiceId;

    static lunaApiVoice* Instance() {
        if (!pInstance) pInstance = new lunaApiVoice;
        return pInstance;
    }

private:
    lunaApiVoice();

    static const LSMethod     rootCategory[];
    static const serviceApi   voiceApis[];

private:
    static bool start(LSHandle *sh, LSMessage *msg, void *data);
    static bool stop(LSHandle *sh, LSMessage *msg, void *data);
    static bool getState(LSHandle *sh, LSMessage *msg, void *data);
    static bool getResponse(LSHandle *sh, LSMessage *msg, void *data);

    static void postEvent(void *subscribeKey, void *payload);

private:
    static lunaApiVoice *pInstance;

    speechRecognitionWorker mSrw;
};

#endif
