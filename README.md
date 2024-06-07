# Bài tập lớn Nguyên lý Hệ điều hành

<div align="center">
<a href="https://git.io/typing-svg"><img src="https://readme-typing-svg.demolab.com?font=Fira+Code&pause=1000&color=EE4E4E&center=true&vCenter=true&random=false&width=435&lines=Operating+System+Projects" alt="Typing SVG" /></a>
</div>

<div align="center">
<img alt="Static Badge" src="https://img.shields.io/badge/HUST-course-blue?labelColor=EE4E4E&color=151515">
<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/HaiAu2501/Operating-System-Project?labelColor=EE4E4E&color=151515">
</div>

## Giới thiệu

Tiny Shell là một chương trình mô phỏng giao diện dòng lệnh đơn giản, được phát triển bằng ngôn ngữ lập trình C++. Chương trình này cung cấp các tính năng cơ bản giúp người dùng tương tác với hệ điều hành Windows thông qua các lệnh nhập từ bàn phím. Tiny Shell được thiết kế để hỗ trợ các thao tác với tệp, thư mục, tiến trình và một số tiện ích khác.

Tiny Shell là một dự án hữu ích cho những ai muốn tìm hiểu về lập trình hệ điều hành và các giao diện dòng lệnh, cũng như cách sử dụng các thư viện và API của hệ điều hành Windows để thao tác với hệ thống tệp tin.

## Thành viên

- Lưu Thịnh Khang
- Nguyễn Viết Tuấn Kiệt
- Bùi Quang Phong
- Nguyễn Thanh Tuyển
- Nguyễn Thái Hòa (Hỗ trợ kĩ thuật)

## Cài đặt và triển khai

### Yêu cầu

- Hệ điều hành Windows 10 hoặc mới hơn.
- C++ 17 hoặc mới hơn.

### Cài đặt

- **Bước 1:** Tạo bản sao của dự án trên máy tính của bạn.

```bash
git clone https://github.com/HaiAu2501/Operating-System-Projects.git
```

- **Bước 2:** Mở dự án bằng Visual Studio Code hoặc trình biên dịch C++ khác.

- **Bước 3:** Chuyển đến thư mục `Process` và biên dịch các file mã nguồn trong thư mục Process.

```bash
g++ -o -std=c++17 child_process child_process.cpp
g++ -o -std=c++17 countdown countdown.cpp -lgdi32 
g++ -o -std=c++17 duck duck.cpp
g++ -o -std=c++17 tictactoe tictactoe.cpp
```

Nếu không biên dịch thì cũng không sao, khi ấy Tiny Shell sẽ không thể chạy các chương trình con này (không ảnh hưởng đến các tính năng khác). Một số câu lệnh như: `start_child`, `start_countdown`, `duck`, `tictactoe` sẽ được Tiny Shell thông báo không tìm thấy chương trình con tương ứng.

- **Bước 4:** Chuyển đến thư mục `Practice Project 1 - Tiny Shell` và biên dịch file mã nguồn chính của chương trình.

```bash
g++ -o -std=c++17 main main.cpp
```

- **Bước 5:** Chạy chương trình `main.exe`, sau đó nhập các lệnh từ bàn phím để tương tác với Tiny Shell. Bạn nên nhập lệnh `help` để xem danh sách các lệnh hỗ trợ.

### Giải thích

- **Feature:** Thư mục chứa các file header của các tính năng mà Tiny Shell hỗ trợ.
  - `features.h`: Tổng hợp các file header của các tính năng.
  - `help.h`: Hiển thị thông tin hướng dẫn sử dụng Tiny Shell.
- **Process:** Thư mục chứa các chương trình có thể khởi chạy từ Tiny Shell.
  - `child_process.cpp`: Chương trình con đơn giản.
  - `countdown.cpp`: Chương trình đếm ngược.
  - `duck.cpp`: Chương trình vẽ hình con vịt.
  - `tictactoe.cpp`: Chương trình chơi cờ caro.

Chân thành cảm ơn ngài Hòa ạ!
