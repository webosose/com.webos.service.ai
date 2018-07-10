// Copyright (c) 2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

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
