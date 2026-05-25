# Cyclic Code Generator Checker (GF(2))

## 1. Mô tả chung về dự án

**Cyclic Code Generator Checker** là một công cụ dòng lệnh (CLI) được phát triển bằng C++ nhằm kiểm tra tính hợp lệ của đa thức sinh (Generator Polynomial) $g(x)$ đối với Mã vòng tuyến tính (Linear Cyclic Code) $C(l, k)$ trên trường Galois GF(2).

Dự án cung cấp giải pháp toàn diện từ việc kiểm tra tốc độ cao cho các bài toán quy mô lớn và mô phỏng chi tiết từng bước tính toán đại số (Line-by-line Modulo) phục vụ cho mục đích học tập, viết báo cáo hoặc debug.

Đa thức $g(x)$ được xác định là hợp lệ khi thỏa mãn 2 điều kiện:

1. **Điều kiện bậc:** Bậc của $g(x)$ bằng đúng $l - k$.
2. **Điều kiện chia hết:** Đa thức $x^l + 1$ chia hết cho $g(x)$ trên trường GF(2).

## 2. Thiết kế hệ thống

Chương trình được thiết kế theo hướng đối tượng (OOP) chia thành 2 lớp xử lý độc lập, được điều khiển bởi một menu tương tác tại hàm `main()`:

* **Lớp `SimpleChecker` (Phiên bản tối ưu):** Được thiết kế để bỏ qua các khâu định dạng hiển thị phức tạp. Đầu ra duy nhất là `YES` hoặc `NO`.
* **Lớp `DetailedChecker` (Phiên bản học thuật):** Thiết kế chuyên biệt để mô phỏng lại chi tiết quá trình chia đa thức. Đầu ra hiển thị chuỗi các phép tính modulo tuần tự dưới dạng đại số chứa biến $x$, ví dụ: `(x^7 + 1) mod (x^3 + x + 1) = x^4 + 1`.
* **Module Helper `toPolynomial`:** Hàm độc lập chịu trách nhiệm chuyển đổi luồng dữ liệu bit nhị phân (ví dụ: `1011`) sang định dạng đa thức đại số toán học (ví dụ: `x^3 + x + 1`) một cách linh hoạt.

## 3. Thuật toán cốt lõi

### Thuật toán lớp SimpleChecker (Tối ưu hóa)

* **Bitset Optimization:** Sử dụng cấu trúc `std::bitset` để biểu diễn đa thức.
* **Word-level Parallelism:** Thay vì mảng vòng lặp thông thường, phép nhân đa thức với $x^k$ được thực hiện bằng phép dịch bit trái (`<<`). Phép trừ đa thức được thay thế hoàn toàn bằng duy nhất một lệnh XOR bitwise (`^`) trên toàn bộ chuỗi.
* **Độ phức tạp:** Giảm từ $O(L^2)$ xuống xấp xỉ $O(\frac{L^2}{128})$ trên kiến trúc máy tính 64-bit hiện đại.

### Thuật toán lớp DetailedChecker (Xử lý in ra chi tiết từng bước)

* **Đồng bộ hóa mảng:** Sử dụng `std::string` để lưu trạng thái của số dư tại từng bước.
* **Triệt tiêu bậc cao:** Tại mỗi vòng lặp, xác định đa thức bị chia hiện tại, thực hiện XOR chuỗi bit hiện tại với đa thức sinh $g(x)$, sau đó loại bỏ toàn bộ các bit `0` ở đầu (leading zeros) để cập nhật bậc mới của số dư.
* **Xuất luồng:** Gọi hàm `toPolynomial` để dịch ngược mảng bit số dư trung gian ra dạng chuỗi đại số và in ngay lập tức lên Terminal, tạo thành cấu trúc hạ bậc liên tục đến khi kết thúc vòng lặp.

## 4. Hướng dẫn cài đặt

Chương trình không phụ thuộc vào bất kỳ thư viện bên thứ ba (third-party) nào ngoài thư viện chuẩn của C++ (STL).

**Yêu cầu hệ thống:**

* Hệ điều hành: Windows, Linux, hoặc macOS.
* Trình biên dịch: GCC/G++ (hỗ trợ chuẩn C++11 trở lên).

**Các bước cài đặt:**

Chỉ cần tạo một file bất kì có đuôi `.cpp` và dán toàn bộ đoạn code C++ vào file này.

## 5. Cách thức triển khai và chạy thử

### Biên dịch chương trình

Có thể biên dịch chương trình trực tiếp trên Terminal của `DevC, CodeBlock, VSCode, ...`

Hoặc bạn có thể chạy trên Command Prompt như sau:

Đầu tiên tạo file `main.cpp` chứa code C++ của dự án này.

Mở Terminal (hoặc Command Prompt) tại thư mục chứa file `main.cpp` và chạy lệnh sau để biên dịch:

```bash
g++ -O3 -o cyclic_checker main.cpp

```

*(Tham số `-O3` giúp bật mức tối ưu hóa cao nhất của trình biên dịch).*

### Khởi chạy chương trình

Sau khi biên dịch thành công, chạy file thực thi:

* **Trên Linux/macOS:** `./cyclic_checker`
* **Trên Windows:** `cyclic_checker.exe`

## 6. Hướng dẫn sử dụng 

Khi chương trình chạy, màn hình sẽ hiện ra:
```text
========= Cyclic Code Generator Checker (GF(2)) =========
SELECT CHECKER MODE:
1. Simple Checker (Fast Output: YES/NO)
2. Detailed Checker (Line-by-line Modulo)
===========================================
Enter your choice (1 or 2):
```
Tiếp theo, bạn nhập `1` hoặc `2` để chọn chế độ hoạt động. Sau đó nhập dữ liệu theo đúng định dạng:

* `l` và `k` cách nhau bởi khoảng trắng.
* Nhập chuỗi bit tương ứng với các hệ số của $g(x)$ theo bậc **TĂNG DẦN** (từ $x^0, x^1, x^2, ...$).

**Ví dụ Test Case Kiểm tra mã Hamming(7,4):**

1. Chọn chế độ: Nhập `2` (Detailed Checker).
2. Khi màn hình hiện `Enter l and k for C(l,k):`, nhập: `7 4`
3. Khi màn hình hiện `Enter the polynomial g(x):`, nhập: `1101` (Tương ứng với $1 + x + x^3$)

**Đầu ra (Expected Output):**
Màn hình sẽ hiển thị chính xác các bước như sau:

```text
(x^7 + 1) mod (x^3 + x + 1) = x^5 + x^4 + 1
(x^5 + x^4 + 1) mod (x^3 + x + 1) = x^4 + x^3 + x^2 + 1
(x^4 + x^3 + x^2 + 1) mod (x^3 + x + 1) = x^3 + x + 1
(x^3 + x + 1) mod (x^3 + x + 1) = 0

[+] CONCLUSION: Remainder = 0. g(x) IS a valid generator polynomial (YES).

```
## 7. Logic thiết kế bộ dữ liệu thử nghiệm (Tests)

Bộ test gồm 20 trường hợp, được chia thành 4 nhóm:

### Nhóm 1: Kiểm thử cơ bản (Small Cases)
* **Mục tiêu:** Xác minh các kiến thức nền tảng về Lý thuyết mã hóa.
* **Nội dung:** Sử dụng các đa thức sinh kinh điển như Hamming(7,4) ($1+x+x^3$) hoặc các mã vòng kích thước nhỏ ($l \le 15$). Nếu sai ở đây, thuật toán chắc chắn có lỗi logic trong việc đảo chuỗi hoặc phép chia GF(2).

### Nhóm 2: Xử lý các trường hợp đặc biệt (Edge Cases)
Nhóm này tập trung vào các tình huống có thể gây lỗi runtime hoặc logic sai lệch:
* **Trailing Zeros:** Người dùng nhập thừa số `0` ở bậc cao nhất. Thuật toán cần cắt bỏ những số này để xác định đúng bậc thực tế của $g(x)$.
* **Bậc đa thức bằng 0 ($k=l$):** Khi $g(x) = 1$, đa thức này luôn là ước của $x^l + 1$. Thuật toán cần xử lý được trường hợp bậc thấp nhất này.
* **Sai Điều kiện 1:** Đa thức chia hết nhưng có bậc không đúng bằng $l-k$. Đây là "cái bẫy" phổ biến cho những ai chỉ tập trung vào phép chia mà quên điều kiện bậc.

### Nhóm 3: Kiểm thử hiệu năng (Large Constraints)
* **Mục tiêu:** Thử thách tốc độ xử lý và khả năng quản lý bộ nhớ.
* **Nội dung:** Các test case với $l = 10^5$. 
* **Tư duy thiết kế:** Sử dụng các đa thức có dạng $1 + x^d$. Theo định lý Freshman's Dream trên GF(2), $(x^d + 1)^{2^n} = x^{2^n \cdot d} + 1$, giúp ta tạo ra các đa thức sinh hợp lệ ở quy mô cực lớn mà không cần tính toán thủ công.

### Nhóm 4: Phân tích độ phủ (Random & Tricky)
* **Nội dung:** Các đa thức có bậc đúng chuẩn $l-k$ nhưng các hệ số được sinh ngẫu nhiên.
* **Mục tiêu:** Đảm bảo không có sự thiên kiến (bias) trong kết quả và kiểm tra tính ổn định của phép XOR trên mảng bit lớn.

Bộ test này không chỉ đơn thuần là dữ liệu mẫu, mà là một hệ thống đánh giá toàn diện từ tính đúng đắn về mặt toán học đến hiệu năng thực thi của mã nguồn. Việc vượt qua trọn vẹn 20 bộ test này đồng nghĩa với việc thuật toán đã đạt tới tiêu chuẩn tối ưu và có thể ứng dụng thực tế.
