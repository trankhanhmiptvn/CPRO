# SPWS_C Project

## Giới thiệu
Dự án **SPWS_C** mô phỏng hệ thống tưới cây thông minh, bao gồm các thành phần:
- **Config**: Cấu hình hệ thống
- **Button**: Xử lý nút bấm (chế độ và bơm)
- **Led**: Điều khiển LED hiển thị trạng thái
- **Sensor**: Mô phỏng cảm biến nhiệt độ và độ ẩm
- **Pump**: Điều khiển bơm
- **State Machine**: Quản lý trạng thái hệ thống

Cấu trúc được tổ chức theo thư mục rõ ràng để hỗ trợ tách biệt mã nguồn chính và mã test.

---

## Cấu trúc thư mục
```
.
├── app/                 # Mã nguồn chính của ứng dụng
│   └── app_main/         # Thư mục chứa main.c hoặc entry point
├── include/             # Header dùng chung
├── src/                 # Mã nguồn của các component
│   ├── Config/
│   ├── Button/
│   ├── Led/
│   ├── Sensor/
│   ├── Pump/
│   └── State_Machine/
├── tests/               # Mã nguồn kiểm thử (unit test)
├── build/               # Thư mục chứa file build (tự sinh)
│   ├── obj/             # File .o
│   └── bin/             # File thực thi (.exe hoặc binary)
├── Makefile
└── README.md
```

---

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
Ví dụ test `test_pump.c`:
```bash
make test_pump
./build/bin/test_pump
```
Ví dụ test `test_button.c`:
```bash
make test_button
./build/bin/test_button
```

---

## Lưu ý
- Tất cả file test nằm trong thư mục `tests/` và sẽ build thành binary riêng.
- Có thể thêm cờ `-DTESTING` để kích hoạt đoạn mã chỉ dành cho test.
- Makefile đã hỗ trợ build một test riêng lẻ, tránh mất thời gian build toàn bộ.

---

## Yêu cầu môi trường
- **GCC** hoặc trình biên dịch C tương thích
- **Make** (GNU Make)
- Hệ điều hành: Linux, macOS hoặc Windows với môi trường hỗ trợ Make

---

## Tác giả
- **TVK** 
