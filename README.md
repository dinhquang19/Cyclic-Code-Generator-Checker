# Cyclic Code Generator Checker (GF(2))

Project kiểm tra tính hợp lệ của một đa thức sinh $g(x)$ cho Mã vòng tuyến tính (Linear Cyclic Code) $C(l, k)$ trên trường Galois GF(2).

## Yêu cầu bài toán
Một đa thức $g(x)$ được coi là đa thức sinh của mã vòng $C(l, k)$ nếu thỏa mãn ĐỒNG THỜI 2 điều kiện:
1. Bậc của đa thức $g(x)$ phải đúng bằng $l - k$.
2. Đa thức $g(x)$ phải là ước số của đa thức $x^l + 1$ trên GF(2). (Tức là phép chia đa thức lấy phần dư bằng $0$).

## Định dạng Input / Output
- **Input:** Liên tục gồm các dòng, mỗi dòng chứa 3 thông số: `l` (chiều dài từ mã), `k` (số bit bản tin), và `s` (chuỗi nhị phân biểu diễn đa thức theo **hệ số mũ tăng dần**, từ $x^0$ đến $x^n$).
  - *Ví dụ:* `7 4 1101` (đại diện cho $l = 7$, $k = 4$, đa thức $g(x) = 1 + x + x^3$)
- **Output:** Tùy thuộc vào phiên bản chương trình mà bạn chạy (xem chi tiết bên dưới).

---

## Cấu trúc Project

Project cung cấp 2 phiên bản mã nguồn C++ riêng biệt phục vụ cho các mục đích khác nhau:

### 1. Phiên bản tối giản chấm tự động (`checker_simple.cpp`)
- **Mục đích:** Dành cho việc nộp bài trên các hệ thống chấm điểm tự động (như CodePTIT).
- **Hoạt động:** Chạy thuật toán ngầm một cách nhanh chóng.
- **Output:** Chỉ in ra duy nhất `YES` (nếu hợp lệ) hoặc `NO` (nếu không hợp lệ) trên mỗi dòng.

### 2. Phiên bản mô phỏng trực quan (`checker_detailed.cpp`)
- **Mục đích:** Dành cho việc debug, làm báo cáo bài tập lớn, hoặc học tập để hiểu rõ bản chất thuật toán.
- **Hoạt động:** In ra toàn bộ quá trình đảo ngược đa thức, kiểm tra bậc, và đặc biệt là **Mô phỏng phép chia đa thức theo hàng dọc** (Long Division) trên hệ GF(2) bằng các phép toán XOR.
- **Output:** Các dòng log tiếng Anh chuyên ngành mô tả chi tiết từng bước trượt đa thức và tính phần dư.

---

## Bộ Test mẫu (Test Cases)
Bạn có thể thử nghiệm chương trình với bộ test đa dạng góc cạnh sau:

**Dữ liệu nhập (test.in):**
```text
7 4 1101
7 4 1011
7 4 1111
7 3 1101
15 11 11001
15 11 10011
3 1 111
