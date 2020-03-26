// #    include <print.h>

RGB_MATRIX_EFFECT(SOURCEGRAPH_ORANGE)
RGB_MATRIX_EFFECT(SOURCEGRAPH_PURPLE)
RGB_MATRIX_EFFECT(SOURCEGRAPH_BLUE)
RGB_MATRIX_EFFECT(SOURCEGRAPH_WHITE)
RGB_MATRIX_EFFECT(SOURCEGRAPH_CYCLE_LEFT_RIGHT)
RGB_MATRIX_EFFECT(SOURCEGRAPH_RAINDROPS)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// static HSV CYCLE_LEFT_RIGHT_math(HSV hsv, uint8_t i, uint8_t time) {
//     hsv.h = g_led_config.point[i].x - time;
//     return hsv;
// }

bool SOURCEGRAPH_CYCLE_LEFT_RIGHT(effect_params_t* params) {
    if (params->init) {
    }
    return false;
}

static bool SOURCEGRAPH_ORANGE(effect_params_t* params) {
    if (params->init) {
        rgb_matrix_set_color_all(0xf9, 0x63, 0x16);
    }
    return false;
}

static bool SOURCEGRAPH_PURPLE(effect_params_t* params) {
    if (params->init) {
        rgb_matrix_set_color_all(0xb2, 0x00, 0xf8);
    }
    return false;
}

static bool SOURCEGRAPH_BLUE(effect_params_t* params) {
    if (params->init) {
        rgb_matrix_set_color_all(0x00, 0xb4, 0xf2);
    }
    return false;
}

static bool SOURCEGRAPH_WHITE(effect_params_t* params) {
    if (params->init) {
        rgb_matrix_set_color_all(0xff, 0xff, 0xff);
    }
    return false;
}

RGB colors[] = {
    {.r = 0xf9, .g = 0x63, .b = 0x16},
    {.r = 0xb2, .g = 0x00, .b = 0xf8},
    {.r = 0x00, .g = 0xb4, .b = 0xf2},
};

static void sourcegraph_raindrops_set_color(int i, effect_params_t* params) {
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) return;
    RGB rgb = colors[rand() % (sizeof(colors) / sizeof(colors[0]))];
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

uint32_t nextRaindrop;

bool SOURCEGRAPH_RAINDROPS(effect_params_t* params) {
    if (!params->init) {
        if (g_rgb_counters.tick >= nextRaindrop) {
            uint32_t delay = scale16by8(1000, rgb_matrix_config.speed);
            nextRaindrop   = g_rgb_counters.tick + delay;
            // uprintf("tick %u, speed %u, %u\n", g_rgb_counters.tick, rgb_matrix_config.speed, sizeof(colors));
            sourcegraph_raindrops_set_color(rand() % DRIVER_LED_TOTAL, params);
        }
        return false;
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (int i = led_min; i < led_max; i++) {
        sourcegraph_raindrops_set_color(i, params);
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
