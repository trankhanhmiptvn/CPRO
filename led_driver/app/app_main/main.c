#include <stdio.h>
#include <stdint.h>
#include "led_driver.h"

int main() {
    size_t num_pixels = 10;

    printf("===== LED DRIVER SIMULATION =====\n");

    // 1. Khởi tạo dải LED
    if (led_init(num_pixels) != LED_OK) {
        printf("[ERROR] led_init() failed\n");
        return -1;
    }
    printf("[PASS] led_init() succeeded\n");

    const uint32_t* buf = led_get_buffer();

    // 2. Kiểm tra buffer khởi tạo về 0
    int all_zero = 1;
    for (size_t i = 0; i < num_pixels; i++) {
        if (buf[i] != 0) {
            all_zero = 0;
            break;
        }
    }
    printf(all_zero ? "[PASS] Buffer initialized to 0\n" : "[FAIL] Buffer not zero\n");

    // 3. Đặt màu các pixel
    led_set_pixel_color(0, 255, 0, 0);    // Pixel 0: Red
    led_set_pixel_color(4, 255, 255, 255); // Pixel 4: White
    led_set_pixel_color(9, 0, 0, 255);    // Pixel 9: Blue

    // 4. In giá trị hex của các pixel quan trọng
    printf("Pixel 0: 0x%08X (expected 0x0000FF00)\n", buf[0]);
    printf("Pixel 4: 0x%08X (expected 0x00FFFFFF)\n", buf[4]);
    printf("Pixel 9: 0x%08X (expected 0x000000FF)\n", buf[9]);

    // 5. Sử dụng led_fill() để điền màu Xanh lá (0, 255, 0)
    led_fill(0, 255, 0);

    // 6. Kiểm tra toàn bộ buffer
    int all_green = 1;
    for (size_t i = 0; i < num_pixels; i++) {
        if (buf[i] != 0x00FF0000) {
            all_green = 0;
            break;
        }
    }
    printf(all_green ? "[PASS] led_fill() works, all green\n" : "[FAIL] led_fill() failed\n");

    // 7. Giải phóng bộ nhớ
    led_shutdown();
    printf("[PASS] led_shutdown() called\n");

    printf("===== LED DRIVER SIMULATION END =====\n");
    return 0;
}
