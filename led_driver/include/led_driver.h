#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    LED_OK        =  0, //Thành công
    LED_ERR_ALLOC = -1, //Lỗi cấp phát bộ nhớ
    LED_ERR_INDEX = -2, //Lỗi số lượng pixel không phù hợp
    LED_ERR_INIT  = -3  // Lỗi buffer chưa khởi tạo đã sử dụng
} led_status_t;

led_status_t led_init(size_t num_pixels);
void led_shutdown();
const uint32_t* led_get_buffer();
led_status_t led_set_pixel_color (size_t index, uint8_t r, uint8_t g, uint8_t b);
led_status_t led_fill (uint8_t r, uint8_t g, uint8_t b);
led_status_t led_clear ();


#endif
