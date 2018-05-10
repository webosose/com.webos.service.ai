#ifndef __SERVICE_LOGGING_H__
#define __SERVICE_LOGGING_H__

#include <PmLogLib.h>

#define AI_LOG_CRITICAL(msgid, kvcount, ...) \
        PmLogCritical(getServiceContext(), msgid, kvcount, ##__VA_ARGS__)

#define AI_LOG_ERROR(msgid, kvcount, ...) \
        PmLogError(getServiceContext(), msgid, kvcount, ##__VA_ARGS__)

#define AI_LOG_WARNING(msgid, kvcount, ...) \
        PmLogWarning(getServiceContext(), msgid, kvcount, ##__VA_ARGS__)

#define AI_LOG_INFO(msgid, kvcount, ...) \
        PmLogInfo(getServiceContext(), msgid, kvcount, ##__VA_ARGS__)

#define AI_LOG_DEBUG(...) \
        PmLogDebug(getServiceContext(), ##__VA_ARGS__)

void logKmsg(const char *fmt, ...);
#define AI_KMSG_DEBUG_MSG(b, fmt, arg...)   if( (b) ) logKmsg(fmt, ##arg)

extern PmLogContext getServiceContext();

#define MSGID_LUNASERVICE   "AI_LUNASERVICE"

#endif
