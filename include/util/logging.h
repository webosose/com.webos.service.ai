#ifndef __SERVICE_LOGGING_H__
#define __SERVICE_LOGGING_H__

#include <PmLogLib.h>

#define LOG_CRITICAL(msgid, kvcount, ...) \
        PmLogCritical(getServiceContext(), msgid, kvcount, ##__VA_ARGS__)

#define LOG_ERROR(msgid, kvcount, ...) \
        PmLogError(getServiceContext(), msgid, kvcount, ##__VA_ARGS__)

#define LOG_WARNING(msgid, kvcount, ...) \
        PmLogWarning(getServiceContext(), msgid, kvcount, ##__VA_ARGS__)

#define LOG_INFO(msgid, kvcount, ...) \
        PmLogInfo(getServiceContext(), msgid, kvcount, ##__VA_ARGS__)

#define LOG_DEBUG(...) \
        PmLogDebug(getServiceContext(), ##__VA_ARGS__)

void logKmsg(const char *fmt, ...);
#define KMSG_DEBUG_MSG(b, fmt, arg...)   if( (b) ) logKmsg(fmt, ##arg)

extern PmLogContext getServiceContext();

#define MSGID_LUNASERVICE   "AI_LUNASERVICE"

#endif
