#ifndef RVO_EXPORT_H_
#define RVO_EXPORT_H_

#ifdef RVO_STATIC_DEFINE
#define RVO_EXPORT
#else
#ifdef _WIN32
#ifdef RVO_EXPORTS
#define RVO_EXPORT __declspec(dllexport)
#else
#define RVO_EXPORT __declspec(dllimport)
#endif
#else
#define RVO_EXPORT __attribute__((visibility("default")))
#endif
#endif

#endif /* RVO_EXPORT_H_ */