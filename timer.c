/***
 **
 * @filename : timer.c
 *
 * @brief    : timer Module Source File
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
#include "timer.h"

static void __timer_handle(union sigval sigev)
{
    timer_handle_t *p_timer = (timer_handle_t *)(sigev.sival_ptr);

    p_timer->callback(p_timer->argv);
}

timer_handle_t *fn_timer_create(timer_type_e type, timer_cb_t cb, timer_argv argv)
{
    timer_handle_t *p_timer = (timer_handle_t *)calloc(sizeof(timer_handle_t), sizeof(uint8_t));

    if (NULL == p_timer)
    {
        printf("Timer creation failed, insufficient memory\r\n");
        return NULL;
    }

    p_timer->type = type;
    p_timer->argv = argv;
    p_timer->callback = cb;

    struct sigevent evp = {
        .sigev_notify = SIGEV_THREAD,
        .sigev_value.sival_ptr = (void *)p_timer,
        .sigev_notify_function = __timer_handle
    };

    if (-1 == timer_create(CLOCK_REALTIME, &evp, &(p_timer->timerid)))
    {
        printf("Timer create failed!!!\r\n");
        free(p_timer);
        p_timer = NULL;
        return NULL;
    }

    return p_timer;
}

void fn_timer_start(timer_handle_t *p_timer, timer_tick_ms tick)
{
    struct itimerspec it;

    if (e_timer_type_cycle == p_timer->type)
    {
        it.it_interval.tv_sec  = tick / 1000;
        it.it_interval.tv_nsec = tick % 1000 * 1000000;
    }
    else
    {
        it.it_interval.tv_sec  = 0x00;
        it.it_interval.tv_nsec = 0x00;
    }

    it.it_value.tv_sec  = tick / 1000;
    it.it_value.tv_nsec = tick % 1000 * 1000000;

    if (-1 == timer_settime(p_timer->timerid, 0, &it, NULL))
    {
        printf("Timer start failed\r\n");
        free(p_timer);
        p_timer = NULL;
    }
}

void fn_timer_stop(timer_handle_t *p_timer)
{
    struct itimerspec it;

    it.it_interval.tv_sec  = 0x00;
    it.it_interval.tv_nsec = 0x00;

    it.it_value.tv_sec  = 0x00;
    it.it_value.tv_nsec = 0x00;

    if (-1 == timer_settime(p_timer->timerid, 0, &it, NULL))
    {
        printf("Timer stop failed\r\n");
        free(p_timer);
        p_timer = NULL;
    }
}

void fn_timer_delete(timer_handle_t *p_timer)
{
    if (-1 == timer_delete(p_timer->timerid))
        printf("Timer delete failed\r\n");

    free(p_timer);
    p_timer = NULL;
}
