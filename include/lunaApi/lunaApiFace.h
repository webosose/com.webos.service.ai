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
