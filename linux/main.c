#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#if LV_USE_DEMO_BENCHMARK
#include "lvgl/demos/benchmark/lv_demo_benchmark.h"
#endif
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "export/ui.h"

static const char *lv_linux_get_video_card_node(const char *videocard_default)
{
    return getenv("LV_VIDEO_CARD") ? : videocard_default;
}

#if LV_USE_LINUX_FBDEV
static void lv_linux_disp_init(void)
{
    const char *videocard = lv_linux_get_video_card_node("/dev/fb0");
    lv_display_t * disp = lv_linux_fbdev_create();

    lv_linux_fbdev_set_file(disp, videocard);
}
#elif LV_USE_LINUX_DRM
static void lv_linux_disp_init(void)
{
    const char *videocard = lv_linux_get_video_card_node("/dev/dri/card0");
    lv_display_t * disp = lv_linux_drm_create();

    lv_linux_drm_set_file(disp, videocard, -1);
}
#elif LV_USE_SDL
static void lv_linux_disp_init(void)
{
    const int width = atoi(getenv("LV_VIDEO_WIDTH") ? : "800");
    const int height = atoi(getenv("LV_VIDEO_HEIGHT") ? : "480");

    lv_sdl_window_create(width, height);
}
#else
#error Unsupported configuration
#endif

int main(int argc, char *argv[])
{
    lv_init();

    /*Linux display device init*/
    lv_linux_disp_init();

    /*Create a Demo*/
//    lv_demo_widgets();
//    lv_demo_widgets_start_slideshow();
    if (argc <= 1) {
        ui_init();
    } else {
        if (!lv_demos_create(&argv[1], argc - 1)) {
            //lv_demos_usage();
            goto exit;
        }
    }

    /*Handle LVGL tasks*/
    while(1) {
        uint32_t delay = lv_timer_handler();
        if (delay < 1) {
            delay = 1;
        }
        usleep(delay * 1000);
    }

exit:
    lv_deinit();

    return 0;
}
