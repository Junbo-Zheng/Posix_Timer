/***
 **
 * @filename : main.c
 *
 * @brief    : main Module Source File
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
#include <unistd.h>
#include "timer.h"

static void _timer_test(timer_argv argv)
{
    printf("timer callback is running, argv = 0x%08x\r\n", *(uint32_t *)argv);

    *(uint32_t *)argv += 1;
}

int main()
{
    printf("This is a demo for posix timer\r\n");

    static uint32_t argv = 0x00;

    timer_handle_t *p_timer = fn_timer_create(e_timer_type_cycle, _timer_test, &argv);

    if (NULL == p_timer)
    {
        printf("Timer create failed\r\n");
        return -1;
    }

    fn_timer_start(p_timer, 500);   // 500ms

    for (;;)
    {
        sleep(1);
    }

    return 0;
}
