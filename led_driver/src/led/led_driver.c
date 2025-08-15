#include <stdio.h>
#include <stdlib.h>
#include <string.h> //sử dụng hàm memset 
#include "led_driver.h"

static uint32_t *g_led_buffer = NULL;
static size_t g_led_count = 0;
/**
 * @brief Khởi tạo chuỗi led với số lượng picxel (num_pixels) cho trước
 * @param num_pixels số lượng picxel
 * @return LED_OK nếu thành công, LED_ERR_INDEX nếu lỗi đầu vào, 
 * LED_ERR_ALOC nếu lỗi cấp phát.
 */
led_status_t led_init(size_t num_pixels) {
    //check input
    if (num_pixels == 0) {return LED_ERR_INDEX; }
    //Giải phóng vùng nhớ đưa con trỏ về NULL nếu con trỏ khác NULL trước khi khởi tạo
    led_shutdown();
    g_led_buffer = malloc(num_pixels * sizeof(uint32_t));
    if(g_led_buffer == NULL) { return LED_ERR_ALLOC; }
    //Lưu giá trị số lượng led đã được cấp phát
    g_led_count = num_pixels;
    //Ghi toàn bộ giá trị về 0
    memset(g_led_buffer, 0, num_pixels*sizeof(uint32_t));
    return LED_OK;
}
/**
 * @brief Giải phóng bộ nhớ đã cấp phát
 */
void led_shutdown() {
    if(g_led_buffer != NULL){
        free(g_led_buffer); // giải phóng vùng nhớ nhưng không đưa con trỏ về NULL
        g_led_buffer = NULL;
        g_led_count = 0;
    }
}

/**
 * @brief Lấy giá trị led buffer
 * @return Địa chỉ của led buffer
 */
const uint32_t* led_get_buffer() {
    return g_led_buffer;
}

/**
 * @brief Hàm set màu cho một led trong chuỗi
 * @param index số thứ tự của led trong chuỗi tính từ 0
 * r màu đỏ, g màu xanh, b màu xanh da trời thứ tự set là g-r-b
 * @return LED_ERR_INIT chưa khởi tạo mà đã gán
 * LED_ERR_INDEX số thức tự led trong chuỗi không hợp lệ
 * LED_OK set màu thành công
 */
led_status_t led_set_pixel_color (size_t index, uint8_t r, uint8_t g, uint8_t b) {
    if(g_led_buffer == NULL) { return LED_ERR_INIT; }
    if(index > g_led_count) { return LED_ERR_INDEX; }
    g_led_buffer[index] = ((uint32_t)g << 16) | ((uint32_t)r << 8) | (uint32_t)b;
    return LED_OK;
}

/**
 * @brief Set tất các các led cùng màu 
 */
led_status_t led_fill (uint8_t r, uint8_t g, uint8_t b) {
    if(g_led_buffer == NULL) { return LED_ERR_INIT; }
    uint32_t color = ((uint32_t)g << 16) | ((uint32_t)r << 8) | (uint32_t)b;
    for(size_t i = 0; i < g_led_count; i++) {
        g_led_buffer[i] = color;
    }
    return LED_OK;
}

/**
 * @brief Đưa tất các các led về màu đen
 */
led_status_t led_clear () {
    if(g_led_buffer == NULL) { return LED_ERR_INIT; }
    for(size_t i = 0; i < g_led_count; i++) {
        g_led_buffer[i] = 0x00000000;
    }
    return LED_OK;
}