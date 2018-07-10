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

    static void postEvent(LSHandle *handle, void *subscribeKey, void *payload);

protected:
    char        *serviceId;
    LSHandle    *pLSHandle;
};

#endif
