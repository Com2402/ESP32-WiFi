![Logo](https://i.gyazo.com/566d62fd25cf0867e0033fb1b9b47927.png)

## 🔗 Links

[![vietqr.vn|vietqr.com]()](https://vietqr.vn)

## 📄 Tính năng

- WiFiManager:
  - _Cho phép lưu tối đa 4 cấu hình WiFi._
  - _Tự động kết nối với WiFi có độ mạnh cao nhất trong danh sách._
- Smart Payment:
  - _Hiển thị QR tĩnh, cho phép người mua nhập số tiền khi thanh toán qua app banking hoặc ví điện tử._
  - \*Hiển thị QR động, số tiền cần thanh toán được đính kèm trong mã QR, người dùng không cần nhập số tiền."
  - _Thông báo biến động số dư._

## Installation

**1. Cài đặt các công cụ cần thiết** - [Cài đặt Visual Code IDE và Platform IO](https://khuenguyencreator.com/huong-dan-cai-dat-visual-studio-code-vs-code/) - [Cài đặt git](https://viblo.asia/p/cai-dat-git-E375zeL6lGW)
**2. Clone source code**

```bash
  git clone https://github.com/nhoc20170861/vietqr_box.git
```

Source code tải về nằm trong thư mục **vietqr_box**. Mở thư mục bằng Visual Code IDE:

![image.png](https://github.com/nhoc20170861/vietqr_box/blob/main/asserts/image1.png)

**3. Build firmware:** - B1: Click vào biểu tượng Platform IO - B2: Nhấn vào nút **build** để build firmware cho ESP32 - B3: kết quả build source code sẽ được hiển thị ở terminal
![image.png](https://github.com/nhoc20170861/vietqr_box/blob/main/asserts/image2.png)

**4. Build system file :**
Build các file trong thư mục **_/data_**, các file này để lưu trữ các file cấu hình, giao diện web. - B1: Chọn **Build Filesystem Image** - B2: Kết quả build thành công được hiển thị bên dưới
![image.png](https://github.com/nhoc20170861/vietqr_box/blob/main/asserts/image3.png)

**5. Nạp code vào mạch** - B1: Chọn **Upload Filesystem Image** để nạp filesystem - B2: Chọn **Upload and Monitor** để nạp firmware và xem log

![image.png](https://github.com/nhoc20170861/vietqr_box/blob/main/asserts/image4.png)

## Note

Theo default, firmware build cho mạch sử dụng module I2S. Để build firmware cho mạch sử dung DAC 8bit, cần comment line dưới dây trong file [platformio.ini](https://github.com/nhoc20170861/vietqr_box/blob/main/platformio.ini)

![image.png](https://github.com/nhoc20170861/vietqr_box/blob/main/asserts/image5.png)
