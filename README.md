# Cyclic Code Generator Checker (GF(2))

Dự án C++ cung cấp bộ công cụ kiểm tra tính hợp lệ của **Đa thức sinh (Generator Polynomial)** cho Mã vòng tuyến tính (Linear Cyclic Code) $C(l, k)$ trên trường Galois $GF(2)$. 

Dự án này được thiết kế dành cho sinh viên và kỹ sư Viễn thông/KHMT/CNTT học tập môn Lý thuyết Thông tin & Mã hóa.

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

### 1. `checker_simple.cpp` (Bản kiểm tra đơn giản)
- **Mục đích:** Dành cho việc kiểm tra các bộ test đơn giản hay submit lên các hệ thống chấm điểm tự động (CodePtit, v.v.).
- **Thuật toán:** Trượt và XOR (Mô phỏng Long Division bằng mảng).
- **Độ phức tạp:** $\approx O(\frac{L^2}{2})$.
- **Đầu ra:** Chỉ in ra `YES` hoặc `NO`.

### 2. `checker_detailed.cpp` (Bản báo cáo & Debug)
- **Mục đích:** Dành cho việc học thuật, làm báo cáo bài tập lớn hoặc debug.
- **Tính năng:** Tự động in ra toàn bộ quá trình đặt tính chia dọc đa thức trên Terminal, giúp người dùng theo dõi từng bước trượt bit và số dư trung gian.

### 3. `checker_bitset.cpp` (Bản Tối ưu hóa cao - Bitset Optimization)
- **Đầu ra:** Cũng in ra `YES` hoặc `NO` nhưng nâng cấp hơn so với phiên bản `checker_simple.cpp`.
- **Mục đích:** Xử lý các bộ test khổng lồ trong thời gian ngắn ~1s (Phù hợp khi yêu cầu tối ưu hóa cao/độ trễ thấp, hay trong các kì thi lớn ICPC, ...).
- **Thuật toán:** Khai thác tính chất Word-level Parallelism của CPU 64-bit thông qua thư viện `std::bitset`. Việc nhân đa thức với $x^k$ được thay bằng phép dịch trái (`<<`), và việc trừ đa thức được thay bằng duy nhất một lệnh XOR phần cứng.
- **Độ phức tạp:** $\approx O(\frac{L^2}{128})$.
- Đây là phương pháp tối ưu khi làm việc với các bài toán Lý thuyết mã hóa yêu cầu xử lý các chuỗi bit dài lên đến $10^5$ hoặc $10^6$ phần tử.

---

## Hướng dẫn Sử dụng

### Định dạng Input
Chương trình đọc dữ liệu liên tục từ luồng Standard Input. Mỗi dòng testcase gồm 3 giá trị:
- `l`: Chiều dài từ mã (Codeword length).
- `k`: Số lượng bit tin (Message bits).
- `s`: Chuỗi nhị phân biểu diễn $g(x)$ với hệ số mũ **TĂNG DẦN** (Từ $x^0$ đến $x^n$).

*Ví dụ:* `7 4 1101` (Tương ứng với $l=7, k=4$, và $g(x) = 1 + x + x^3$).

### Dưới đây là cách 2 phiên bản chương trình xử lý test case này:

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
## Logic thiết kế bộ dữ liệu thử nghiệm (Tests)

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

## Tổng kết
Bộ test này không chỉ đơn thuần là dữ liệu mẫu, mà là một hệ thống đánh giá toàn diện từ tính đúng đắn về mặt toán học đến hiệu năng thực thi của mã nguồn. Việc vượt qua trọn vẹn 20 bộ test này đồng nghĩa với việc thuật toán đã đạt tới tiêu chuẩn tối ưu và có thể ứng dụng thực tế.

Nếu bạn muốn thử submit với bộ test này, mình đã up lên Codeforces tại đây: [link](https://codeforces.com/group/YF7cqRzPwQ/contest/688579/problem/A)
