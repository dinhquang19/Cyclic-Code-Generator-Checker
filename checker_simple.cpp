#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int l, k;
    string s; // s là đa thức sinh nhập vào (hệ số mũ tăng dần)
    
    // Đọc đầu vào cho đến khi hết file (EOF)
    while (cin >> l >> k >> s) {
        // 1. Đảo ngược chuỗi để đưa về bậc giảm dần (chuẩn toán học)
        string g_str = s;
        reverse(g_str.begin(), g_str.end());
        
        // Loại bỏ các số 0 vô nghĩa ở bậc cao
        int start_idx = 0;
        while (start_idx < g_str.length() && g_str[start_idx] == '0') start_idx++;
        if (start_idx == g_str.length()) g_str = "0";
        else g_str = g_str.substr(start_idx);
        
        int deg_g = g_str.length() - 1;
        
        // Điều kiện 1: Bậc của g(x) phải bằng l - k
        if (deg_g != l - k) {
            cout << "NO\n";
            continue;
        }
        
        // Điều kiện 2: Khởi tạo đa thức bị chia (x^l + 1)
        string dividend = "1";
        for (int i = 0; i < l - 1; i++) dividend += "0";
        dividend += "1";
        
        vector<int> div(dividend.length());
        for (int i = 0; i < dividend.length(); ++i) div[i] = dividend[i] - '0';
        
        vector<int> g(g_str.length());
        for (int i = 0; i < g_str.length(); ++i) g[i] = g_str[i] - '0';
        
        // Thực hiện phép chia đa thức GF(2) (Dùng XOR)
        for (int i = 0; i <= l - deg_g; i++) {
            if (div[i] == 1) {
                for (int j = 0; j < g.size(); j++) {
                    div[i+j] ^= g[j];
                }
            }
        }
        
        // Kiểm tra phần dư
        bool isValid = true;
        for (int i = 0; i < div.size(); i++) {
            if (div[i] != 0) {
                isValid = false; 
                break;
            }
        }
        
        // In kết quả
        if (isValid) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main() {
    // Tối ưu I/O cho C++
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    solve();
    return 0;
}