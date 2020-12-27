/***
 **
 * @filename : timer.h
 *
 * @brief    : timer Module Header File
 *
 * @Date     : 2020-12-10 11:16:29
 * @Author   : Junbo Zheng
 * @E-mail   : zheng_junbo@foxmail.com
 * @Version  : v1.0
 * @Company  : X Comm. Co., Ltd.
 * @Summary  :
 *
 * @Function : 1.
 *
 * @Log      : 1. 2020-12-10 11:16:29 : zhengjunbo - Create
 */

#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef void     (*timer_cb_t)(void *);
typedef void*    timer_argv_t;
typedef uint32_t timer_tick_ms;

typedef enum
{
    e_timer_type_oneshot = 0u,
    e_timer_type_periodic,
    e_timer_type_max
} timer_type_e;

typedef struct _timer_handle_t
{
    timer_t       timerid;    ///< timer id
    timer_type_e  type;       ///< timer options
    timer_cb_t    callback;   ///< timer callback
    timer_argv_t  argv;       ///< timer argument vector
} timer_handle_t;

timer_handle_t * fn_timer_create(timer_type_e type, timer_cb_t cb, timer_argv_t argv);

void fn_timer_start(timer_handle_t * timer_handle, timer_tick_ms tick);

void fn_timer_stop(timer_handle_t * timer_handle);

void fn_timer_delete(timer_handle_t * timer_handle);

#endif /* _TIMER_H_ */
