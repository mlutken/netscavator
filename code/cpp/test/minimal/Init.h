#ifndef __PCF_XULRUNNER_INIT_H__
#define __PCF_XULRUNNER_INIT_H__

#include "nscore.h"

nsresult init_xulrunner(const char* xul_dir, const char* app_dir);
nsresult init_xulrunner();
void shutdown_xulrunner();
void addref(void* object);
void release(void* object);

#endif /* __PCF_XULRUNNER_INIT_H__ */
