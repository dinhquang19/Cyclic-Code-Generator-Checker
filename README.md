# Cyclic Code Generator Checker (GF(2))

Dự án C++ cung cấp bộ công cụ kiểm tra tính hợp lệ của **Đa thức sinh (Generator Polynomial)** cho Mã vòng tuyến tính (Linear Cyclic Code) $C(l, k)$ trên trường Galois $GF(2)$. 

Dự án này được thiết kế dành cho sinh viên và kỹ sư Viễn thông/KHMT học tập môn Lý thuyết Thông tin & Mã hóa.

---

## Cơ sở Toán học

Một đa thức $g(x)$ được coi là đa thức sinh hợp lệ của mã vòng $C(l, k)$ nếu và chỉ nếu nó thỏa mãn đồng thời 2 điều kiện:

1. **Điều kiện bậc:** Bậc của $g(x)$ phải đúng bằng số bit kiểm tra.
   $$\text{deg}(g(x)) = l - k$$
2. **Điều kiện chia hết:** $g(x)$ phải là một ước số của đa thức $x^l + 1$ trên hệ GF(2), hay $$(x^l + 1) \pmod{g(x)} \equiv 0$$

*(Lưu ý: Trên GF(2), phép cộng và phép trừ là tương đương nhau và được thực hiện bằng phép toán bitwise XOR `^`).*

---

## Cấu trúc Dự án

Dự án cung cấp 3 phiên bản mã nguồn với các cấp độ tối ưu và mục đích sử dụng khác nhau:

### 1. `checker_simple.cpp` (Bản chấm tự động)
- **Mục đích:** Dành cho việc kiểm tra các bộ test đơn giản hay submit lên các hệ thống chấm điểm tự động (CodePtit, v.v.).
- **Thuật toán:** Trượt và XOR (Mô phỏng Long Division bằng mảng).
- **Độ phức tạp:** $O(L \times (L - K))$
- **Đầu ra:** Chỉ in ra `YES` hoặc `NO`.

### 2. `checker_detailed.cpp` (Bản báo cáo & Debug)
- **Mục đích:** Dành cho việc học thuật, làm báo cáo bài tập lớn hoặc debug.
- **Tính năng:** Tự động in ra toàn bộ quá trình đặt tính chia dọc đa thức trên Terminal, giúp người dùng theo dõi từng bước trượt bit và số dư trung gian.

### 3. `checker_bitset.cpp` (Bản Tối ưu hóa cao - Bitset Optimization)
- **Mục đích:** Xử lý các bộ test khổng lồ trong thời gian ngắn tiệm cận 0.1s (Phù hợp khi yêu cầu tối ưu hóa cao/độ trễ thấp, hay trong các kì thi lớn ICPC, ...).
- **Thuật toán:** Khai thác tính chất Word-level Parallelism của CPU 64-bit thông qua thư viện `std::bitset`. Việc nhân đa thức với $x^k$ được thay bằng phép dịch trái (`<<`), và việc trừ đa thức được thay bằng duy nhất một lệnh XOR phần cứng.
- **Độ phức tạp thực tế:** $\approx O\left(\frac{L \times (L-K)}{64}\right)$

---

## Hướng dẫn Sử dụng

### 1. Định dạng Input
Chương trình đọc dữ liệu liên tục từ luồng Standard Input. Mỗi dòng testcase gồm 3 giá trị:
- `l`: Chiều dài từ mã (Codeword length).
- `k`: Số lượng bit tin (Message bits).
- `s`: Chuỗi nhị phân biểu diễn $g(x)$ với hệ số mũ **TĂNG DẦN** (Từ $x^0$ đến $x^n$).

*Ví dụ:* `7 4 1101` (Tương ứng với $l=7, k=4$, và $g(x) = 1 + x + x^3$).

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

