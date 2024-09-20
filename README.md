# Bài tập lớn Nguyên lý Hệ điều hành

<div align="center">
  <a href="https://git.io/typing-svg"><img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=30&duration=2000&pause=500&color=EE4E4E&background=FFFFFF00&center=true&vCenter=true&repeat=false&random=false&width=435&lines=Operating+System+Project;Tiny+Shell" alt="Typing SVG" /></a>
</div>

<div align="center">
  <img alt="Static Badge" src="https://img.shields.io/badge/HUST-course-blue?labelColor=EE4E4E&color=151515">
  <img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/HaiAu2501/Operating-System-Project?labelColor=EE4E4E&color=151515">
</div>

## Giới thiệu

Tiny Shell là một chương trình mô phỏng giao diện dòng lệnh đơn giản, được phát triển bằng ngôn ngữ lập trình C++. Chương trình này cung cấp các tính năng cơ bản giúp người dùng tương tác với hệ điều hành Windows thông qua các lệnh nhập từ bàn phím. Tiny Shell được thiết kế để hỗ trợ các thao tác với tệp, thư mục, tiến trình và một số tiện ích khác.

Tiny Shell là một dự án hữu ích cho những ai muốn tìm hiểu về lập trình hệ điều hành và các giao diện dòng lệnh, cũng như cách sử dụng các thư viện và API của hệ điều hành Windows để thao tác với hệ thống tệp tin.

## Thành viên

- Nguyễn Viết Tuấn Kiệt
- Bùi Quang Phong
- Lưu Thịnh Khang
- Nguyễn Thanh Tuyển
- Nguyễn Thái Hòa (Hỗ trợ kĩ thuật)

### Người đóng góp

<div align="center">
  <a href="https://github.com/HaiAu2501/Operating-System-Project/graphs/contributors">
    <img src="https://contrib.rocks/image?repo=HaiAu2501/Operating-System-Project" />
  </a>
</div>

## Cài đặt và triển khai

### Yêu cầu

- Hệ điều hành Windows 10 hoặc mới hơn.
- CMake phiên bản 3.10.2 trở lên.
- MSVC hoặc MinGW để biên dịch mã nguồn C++.

### Cài đặt

- **Bước 1:** Tạo bản sao của dự án trên máy tính của bạn.

```bash
git clone https://github.com/HaiAu2501/Operating-System-Projects.git
```

- **Bước 2:** Tạo folder build cho CMake và chuyển đến thư mục này.

```bash
mkdir build
cd build
```

- **Bước 3:** Sử dụng CMake để tạo file Makefile hoặc Visual Studio project.

```bash
cmake ..
```

- **Bước 4:** Biên dịch mã nguồn bằng trình biên dịch C++ mà bạn đã cài đặt.

```bash
cmake --build . --target install --config Debug
```

- **Bước 5:** Chạy chương trình `Operating-System-Project.exe` từ thư mục `install`. Bạn nên nhập lệnh `help` để xem danh sách các lệnh hỗ trợ.

```bash
cd install
Operating-System-Project.exe
```

Nếu không biên dịch thì cũng không sao, bạn có thể tải file thực thi từ [đây](https://github.com/HaiAu2501/Operating-System-Project/releases/download/1.0.0/Operating-System-Project.x64.zip). Nếu chạy bị lỗi, hãy cài đặt [Visual C++ Redistributable](https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads).

### Giải thích

- **Feature:** Thư mục chứa các file header của các tính năng mà Tiny Shell hỗ trợ.
  - `features.h`: Tổng hợp các file header của các tính năng.
  - `help.h`: Hiển thị thông tin hướng dẫn sử dụng Tiny Shell.
- **Process:** Thư mục chứa các chương trình có thể khởi chạy từ Tiny Shell.
  - `child_process.cpp`: Chương trình con đơn giản.
  - `countdown.cpp`: Chương trình đếm ngược.
  - `duck.cpp`: Chương trình vẽ hình con vịt.
  - `tictactoe.cpp`: Chương trình chơi cờ caro.
- **Testcase:** Thư mục chứa các kịch bản kiểm thử cho Tiny Shell nhằm đảm bảo tính ổn định và đúng đắn của chương trình.
  - Mỗi _kịch bản_ là dãy lệnh được lưu thành một file `.bat`.
  - Dãy lệnh sẽ có độ khó nhất định và là một quy trình hoàn toàn khép kín.
  - Tên file sẽ phản ánh nội dung tính năng kiểm thử của kịch bản.
  - Tiny Shell chạy kịch bản kiểm thử bằng cách nhập lệnh `run Testcase\<tên file>` từ bàn phím.
  - Hoặc đơn giản hơn là `add_path Testcase\` rồi nhập `run <tên file>` để chạy kịch bản kiểm thử.
