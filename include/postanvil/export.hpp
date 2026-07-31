#pragma once

#if defined(_WIN32) || defined(__CYGWIN__)
#  if defined(POSTANVIL_STATIC)
#    define POSTANVIL_API
#  elif defined(POSTANVIL_BUILD_SHARED)
#    define POSTANVIL_API __declspec(dllexport)
#  else
#    define POSTANVIL_API __declspec(dllimport)
#  endif
#elif defined(__GNUC__) && __GNUC__ >= 4
#  define POSTANVIL_API __attribute__((visibility("default")))
#else
#  define POSTANVIL_API
#endif
