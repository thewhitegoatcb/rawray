#define LOG_MODULE_NAME "RawRay"
#define LOG_TO_FILE "../rawray/rawray.log"
#ifdef _DEBUG
#define LOG_LEVEL LOG_SEV_DEBUG
#else
#define LOG_LEVEL LOG_SEV_INFO
#endif // _DEBUG