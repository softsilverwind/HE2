#ifndef __SERROR_H__
#define __SERROR_H__

#define SE_NOTIFY 1
#define SE_WARNING 2
#define SE_ERROR 3
#define SE_INTERNAL 4

#ifdef __unix__
#define SE_COLOR_GREEN  "\e[01;32m"
#define SE_COLOR_YELLOW "\e[01;33m"
#define SE_COLOR_RED    "\e[01;31m"
#define SE_COLOR_BLUE   "\e[01;34m"
#define SE_COLOR_WHITE  "\e[0m"
#else
#define SE_COLOR_GREEN  ""
#define SE_COLOR_YELLOW ""
#define SE_COLOR_RED    ""
#define SE_COLOR_BLUE   ""
#define SE_COLOR_WHITE  ""
#endif /* operating system */

#ifdef __DEBUG__
#define DEBUG($1) do {$1} while(0)
#define TAG($1) (tag = $1)
#else
#define DEBUG($1)
#define TAG($1)
#endif /* __DEBUG__ */

void serror(int severity, const char *message);

#endif /* __SERROR_H__ */
