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
- **Output:** Các dòng log tiếng Anh mô tả chi tiết từng bước trượt đa thức và tính phần dư.


## Ví dụ minh họa (Usage Examples)

Giả sử chúng ta cần kiểm tra xem đa thức $g(x) = 1 + x + x^3$ có phải là đa thức sinh hợp lệ cho mã vòng $C(7, 4)$ hay không.
- Chiều dài từ mã: $l = 7$
- Số bit tin: $k = 4$
- Đa thức hệ số mũ tăng dần: `1101`

Dưới đây là cách 2 phiên bản chương trình xử lý test case này:

### 1. Phiên bản Simple (`checker_simple.cpp`)

**Input:**
```text
7 4 1101
```

**Output:**

```text
YES
```

### 2. Phiên bản Detailed (`checker_detailed.cpp`)

**Input:**

```text
7 4 1101
```

**Output:**

```text
========================================================
[TEST] l = 7, k = 4 | Input g(x) = 1101 (Increasing Degree)
=> Standard g(x) (Decreasing Degree): 1011
=> Degree of g(x) = 3
=> Dividend (x^7 + 1): 10000001
--------------------------------------------------------
GF(2) POLYNOMIAL DIVISION SIMULATION:

10000001
1011
----
  110001
  1011
  ----
   11101
   1011
   ----
    1011
    1011
    ----
       0
--------------------------------------------------------
[+] CONCLUSION: Remainder = 0. g(x) IS a valid generator polynomial (YES).
========================================================

```

