#include <stdio.h>
#include <stdint.h>
#include "led_driver.h"

int main() {
    size_t num_pixels = 10;
    led_status_t status;

    printf("===== START LED DRIVER TESTS =====\n");

    // 1. Test led_init
    status = led_init(num_pixels);
    if (status != LED_OK) {
        printf("[FAIL] led_init() failed\n");
        return -1;
    }
    printf("[PASS] led_init() succeeded\n");

    // Check buffer is initialized to 0
    const uint32_t* buf = led_get_buffer();
    int all_zero = 1;
    for (size_t i = 0; i < num_pixels; i++) {
        if (buf[i] != 0) {
            all_zero = 0;
            break;
        }
    }
    printf(all_zero ? "[PASS] Buffer initialized to 0\n" : "[FAIL] Buffer not zero\n");

    // 2. Test led_set_pixel_color
    status = led_set_pixel_color(0, 255, 0, 0); // Red
    status |= led_set_pixel_color(4, 255, 255, 255); // White
    status |= led_set_pixel_color(9, 0, 0, 255); // Blue

    printf("[INFO] Pixel 0: 0x%08X\n", buf[0]); // Expected 0x0000FF00
    printf("[INFO] Pixel 4: 0x%08X\n", buf[4]); // Expected 0x00FFFFFF
    printf("[INFO] Pixel 9: 0x%08X\n", buf[9]); // Expected 0x000000FF

    // 3. Test led_fill
    status = led_fill(0, 255, 0); // Green
    int all_green = 1;
    for (size_t i = 0; i < num_pixels; i++) {
        if (buf[i] != 0x00FF0000) {
            all_green = 0;
            break;
        }
    }
    printf(all_green ? "[PASS] led_fill() works\n" : "[FAIL] led_fill() failed\n");

    // 4. Test led_clear
    status = led_clear();
    int all_clear = 1;
    for (size_t i = 0; i < num_pixels; i++) {
        if (buf[i] != 0x00000000) {
            all_clear = 0;
            break;
        }
    }
    printf(all_clear ? "[PASS] led_clear() works\n" : "[FAIL] led_clear() failed\n");

    // 5. Test out-of-bound pixel
    status = led_set_pixel_color(10, 123, 123, 123); // Index = num_pixels, should ignore
    printf(status == LED_OK ? "[PASS] Out-of-bound pixel ignored\n" : "[FAIL] Out-of-bound handling\n");

    // 6. Test led_shutdown
    led_shutdown();
    printf("[PASS] led_shutdown() called\n");

    printf("===== END LED DRIVER TESTS =====\n");
    return 0;
}
