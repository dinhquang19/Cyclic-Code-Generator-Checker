#include <iostream>
#include <string>
#include <bitset>

using namespace std;

// Giới hạn chiều dài từ mã (Có thể tùy chỉnh theo giới hạn của bài toán)
// bitset yêu cầu kích thước phải được khai báo bằng hằng số tại compile-time
const int MAX_L = 100005; 

void solve() {
    int l, k;
    string s; // Đa thức nhập vào hệ số mũ tăng dần (vd: 1101 = 1 + x + x^3)
    
    // Đọc đầu vào cho đến khi hết file
    while (cin >> l >> k >> s) {
        // Xóa các số 0 vô nghĩa ở đuôi chuỗi (tương ứng bậc cao bị nhập thừa)
        while (s.length() > 1 && s.back() == '0') {
            s.pop_back();
        }
        
        int d = s.length() - 1; // Bậc của đa thức sinh g(x)
        
        // Điều kiện 1: Bậc phải đúng bằng l - k
        if (d != l - k) {
            cout << "NO\n";
            continue;
        }
        
        // Đa thức 1 (bậc 0) chia hết mọi x^l + 1
        if (d == 0) {
            cout << "YES\n";
            continue;
        }

        // Khởi tạo đa thức bị chia D(x) = x^l + 1
        bitset<MAX_L> D;
        D.set(l); // Bật bit thứ l (x^l)
        D.set(0); // Bật bit thứ 0 (x^0 = 1)

        // Khởi tạo đa thức sinh G(x)
        bitset<MAX_L> G;
        for (int i = 0; i <= d; ++i) {
            if (s[i] == '1') {
                G.set(i); // Bật bit tương ứng với số mũ
            }
        }

        // THUẬT TOÁN CHIA ĐA THỨC BẰNG BITSET
        // Duyệt từ bậc cao nhất l xuống đến bậc d
        for (int i = l; i >= d; --i) {
            // Nếu phát hiện hệ số bậc i của D(x) là 1
            if (D.test(i)) { 
                // Nhân g(x) với x^(i-d) bằng toán tử dịch trái (<<)
                // Sau đó trừ (XOR) trực tiếp vào D(x)
                D ^= (G << (i - d)); 
            }
        }

        // Điều kiện 2: Kiểm tra phần dư.
        // Hàm .none() trả về true nếu toàn bộ các bit trong D đều là 0
        if (D.none()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    // Tối ưu hóa I/O
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    solve();
    return 0;
}