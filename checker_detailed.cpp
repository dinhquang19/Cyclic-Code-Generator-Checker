#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Hàm in với khoảng trắng bên trái để căn chỉnh thẳng hàng dọc
void printAligned(const string& str, int padding) {
    for (int i = 0; i < padding; ++i) cout << " ";
    cout << str << "\n";
}

void checkCyclicGenerator(int l, int k, string s) {
    // 1. Xử lý đầu vào: Đảo ngược chuỗi vì đầu vào hệ số mũ TĂNG DẦN (x^0 -> x^n)
    // Chuyển về dạng GIẢM DẦN (x^n -> x^0) để thực hiện phép chia
    string g_str = s;
    reverse(g_str.begin(), g_str.end());

    // Loại bỏ các số 0 vô nghĩa ở bậc cao nhất 
    int start_idx = 0;
    while (start_idx < g_str.length() && g_str[start_idx] == '0') start_idx++;
    if (start_idx == g_str.length()) g_str = "0";
    else g_str = g_str.substr(start_idx);

    int deg_g = g_str.length() - 1;

    cout << "========================================================\n";
    cout << "[TEST] l = " << l << ", k = " << k << " | Input g(x) = " << s << " (Increasing Degree)\n";
    cout << "=> Standard g(x) (Decreasing Degree): " << g_str << "\n";
    cout << "=> Degree of g(x) = " << deg_g << "\n";

    // Điều kiện 1: Bậc của g(x) phải đúng bằng l - k
    if (deg_g != l - k) {
        cout << "[!] CONCLUSION: REJECTED.\n";
        cout << "    Reason: Degree of g(x) is not equal to l - k (" << l - k << ").\n";
        cout << "========================================================\n\n";
        return;
    }

    // Điều kiện 2: g(x) phải là ước của x^l + 1 trên GF(2)
    string dividend = "1";
    for (int i = 0; i < l - 1; i++) dividend += "0";
    dividend += "1";

    cout << "=> Dividend (x^" << l << " + 1): " << dividend << "\n";
    cout << "--------------------------------------------------------\n";
    cout << "GF(2) POLYNOMIAL DIVISION SIMULATION:\n\n";

    vector<int> div(dividend.length());
    for (int i = 0; i < dividend.length(); ++i) div[i] = dividend[i] - '0';

    vector<int> g(g_str.length());
    for (int i = 0; i < g_str.length(); ++i) g[i] = g_str[i] - '0';

    // In đa thức bị chia ban đầu
    printAligned(dividend, 0);

    // Bắt đầu quá trình chia đa thức (Mô phỏng đặt tính chia dọc)
    for (int i = 0; i <= l - deg_g; i++) {
        if (div[i] == 1) {
            // In đa thức chia gióng thẳng cột
            printAligned(g_str, i);
            
            // In đường gạch ngang
            string dash(g.size(), '-');
            printAligned(dash, i);

            // Phép trừ trên GF(2) chính là phép XOR
            for (int j = 0; j < g.size(); j++) {
                div[i+j] ^= g[j];
            }

            // Tìm và in số dư trung gian cho đúng lề
            string rem_str = "";
            int next_one = i + 1;
            while (next_one < div.size() && div[next_one] == 0) next_one++;

            if (next_one == div.size()) {
                printAligned("0", div.size() - 1);
            } else {
                for (int j = next_one; j < div.size(); j++) {
                    rem_str += to_string(div[j]);
                }
                printAligned(rem_str, next_one);
            }
        }
    }

    // Kiểm tra phần dư cuối cùng
    bool isValid = true;
    for (int i = 0; i < div.size(); i++) {
        if (div[i] != 0) {
            isValid = false;
            break;
        }
    }

    cout << "--------------------------------------------------------\n";
    if (isValid) {
        cout << "[+] CONCLUSION: Remainder = 0. g(x) IS a valid generator polynomial (YES).\n";
    } else {
        cout << "[-] CONCLUSION: Remainder != 0. g(x) is NOT a valid generator polynomial (NO).\n";
    }
    cout << "========================================================\n\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int l, k;
    string s;
    
    while (cin >> l >> k >> s) {
        checkCyclicGenerator(l, k, s);
    }
    return 0;
}