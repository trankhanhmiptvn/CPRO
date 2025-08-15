# LED Driver Simulation

## 📌 Giới thiệu
Dự án này mô phỏng **trình điều khiển LED strip** đơn giản cho mục đích học tập và kiểm thử.  
Người dùng có thể:
- Khởi tạo dải LED với số pixel tùy chọn
- Đặt màu từng pixel theo định dạng **G-R-B**
- Lấy buffer dữ liệu LED để kiểm tra
- Điền màu cho toàn bộ dải LED
- Xóa toàn bộ LED
- Giải phóng tài nguyên khi không dùng

## 📂 Cấu trúc thư mục
```
.
├── app
│   ├── app_main           # Thư mục chứa main cho ứng dụng chính
│   │   └── main.c
│   └── main.c             # File main mẫu
├── build                  # Thư mục chứa file build
│   ├── bin                # Chứa file thực thi
│   │   └── led_driver
│   └── obj                # Chứa file .o
│       ├── app
│       │   └── app_main
│       │       └── main.o
│       └── led
│           └── led_driver.o
├── include
│   └── led_driver.h       # Khai báo API LED
├── Makefile               # Tự động build
├── README.md
├── src
│   └── led
│       └── led_driver.c   # Triển khai API LED
└── tests
    └── test_led_driver.c  # Testcase cho driver LED
```

## 🚀 API chính
```c
typedef enum {
    LED_OK = 0,
    LED_ERROR
} led_status_t;

// Khởi tạo dải LED
led_status_t led_init(size_t num_pixels);

// Giải phóng bộ nhớ
void led_shutdown(void);

// Lấy con trỏ tới buffer LED
const uint32_t* led_get_buffer(void);

// Đặt màu cho 1 pixel (định dạng G-R-B)
led_status_t led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b);

// Điền toàn bộ pixel cùng màu
led_status_t led_fill(uint8_t r, uint8_t g, uint8_t b);

// Xóa toàn bộ LED (tắt)
led_status_t led_clear(void);
```

## 📋 Kịch bản kiểm thử trong `app/app_main/main.c`
1. Khởi tạo 10 pixel: `led_init(10)`
2. Kiểm tra buffer ban đầu toàn `0`
3. Đặt màu:
   - Pixel 0 → Đỏ `(255, 0, 0)` → `0x0000FF00`
   - Pixel 4 → Trắng `(255, 255, 255)` → `0x00FFFFFF`
   - Pixel 9 → Xanh dương `(0, 0, 255)` → `0x000000FF`
4. Lấy buffer và in giá trị hex
5. Gọi `led_fill()` để tất cả pixel thành Xanh lá `(0, 255, 0)` → `0x00FF0000`
6. Kiểm tra buffer sau khi fill
7. Gọi `led_shutdown()` giải phóng bộ nhớ


## Cách build

### Build toàn bộ ứng dụng
```bash
make
```
File thực thi sẽ nằm ở:
```
build/bin/spws_c
```

### Chạy ứng dụng
```bash
make run
```

### Clean build
```bash
make clean
```

---

## Chạy test

### Build tất cả test
```bash
make tests
```
Kết quả:
```
build/bin/test_*
```

### Build và chạy một test cụ thể
Ví dụ test `test_led_driver.c`:
```bash
make test_led_driver
./build/bin/make test_led_driver
```


---

## Lưu ý
- Tất cả file test nằm trong thư mục `tests/` và sẽ build thành binary riêng.
- Có thể thêm cờ `-DTESTING` để kích hoạt đoạn mã chỉ dành cho test.
- Makefile đã hỗ trợ build một test riêng lẻ, tránh mất thời gian build toàn bộ.

- Màu được lưu trong `uint32_t` theo định dạng:
  ```
  [0x00][Green][Red][Blue]
  ```
- `led_get_buffer()` trả về **const pointer** để tránh sửa trực tiếp ngoài module.


---

---

## Yêu cầu môi trường
- **GCC** hoặc trình biên dịch C tương thích
- **Make** (GNU Make)
- Hệ điều hành: Linux, macOS hoặc Windows với môi trường hỗ trợ Make

---

## Tác giả 
