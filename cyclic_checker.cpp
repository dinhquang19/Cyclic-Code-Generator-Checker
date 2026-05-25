#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>

using namespace std;

const int MAXL = 100005;

// Chuyển chuỗi bit thành đa thức
string toPolynomial(const string& bin) {
    if (bin == "0" || bin.empty()) return "0";
    
    string res = "";
    int n = bin.length();
    bool first = true;
    
    for (int i = 0; i < n; ++i) {
        if (bin[i] == '1') {
            int deg = n - 1 - i;
            if (!first) {
                res += " + ";
            }
            first = false;
            
            if (deg == 0) {
                res += "1";
            } else if (deg == 1) {
                res += "x";
            } else {
                res += "x^" + to_string(deg);
            }
        }
    }
    return res.empty() ? "0" : res;
}


// CLASS 1: Simple Checker (YES/NO)
class SimpleChecker {
public:
    void check(int l, int k, string s) {
        reverse(s.begin(), s.end());
        size_t start = s.find('1');
        if (start == string::npos) {
            cout << "[-] NO\n";
            return;
        }
        s = s.substr(start);
        int deg = s.length() - 1;

        if (deg != l - k) {
            cout << "[-] NO\n";
            return;
        }

        bitset<MAXL> dividend;
        dividend.set(l); 
        dividend.set(0); 

        bitset<MAXL> divisor;
        for (int i = 0; i <= deg; ++i) {
            if (s[i] == '1') {
                divisor.set(deg - i);
            }
        }

        divisor <<= (l - deg);

        for (int i = l; i >= deg; --i) {
            if (dividend.test(i)) {
                dividend ^= divisor;
            }
            divisor >>= 1;
        }

        if (dividend.none()) {
            cout << "[+] YES\n";
        } else {
            cout << "[-] NO\n";
        }
    }
};

// CLASS 2: Detailed Checker 
class DetailedChecker {
public:
    void check(int l, int k, string s) {
        // cout << "\n========================================================\n";
        cout << "\n[TEST] l = " << l << ", k = " << k << " | Input g(x) = " << s << " (Increasing Degree)\n";
        
        reverse(s.begin(), s.end());
        size_t start = s.find('1');
        string gx = (start == string::npos) ? "0" : s.substr(start);
        int deg = (gx == "0") ? -1 : gx.length() - 1;
        
        string poly_gx = toPolynomial(gx);

        cout << "=> Standard g(x) (Decreasing Degree): " << poly_gx << "\n";
        cout << "=> Degree of g(x) = " << deg << "\n";
        
        string dividend_bin = "1" + string(l - 1, '0') + "1";
        cout << "=> Dividend (x^" << l << " + 1): " << "\n";
        // cout << "--------------------------------------------------------\n";
        
        if (deg != l - k) {
            cout << "[-] DEGREE CONDITION FAILED: Expected l - k = " << l - k << ", but got " << deg << ".\n";
            cout << "[+] CONCLUSION: g(x) IS NOT a valid generator polynomial (NO).\n";
            // cout << "========================================================\n";
            return;
        }

        cout << "\nGF(2) POLYNOMIAL DIVISION SIMULATION (STEP-BY-STEP):\n";
        
        string current = dividend_bin;
        
        while (current != "0" && current.length() >= gx.length()) {
            string poly_current = toPolynomial(current);
            
            // Tính toán số dư sau phép XOR (phép trừ GF(2))
            string next_bin = current;
            for (size_t i = 0; i < gx.length(); ++i) {
                next_bin[i] = (next_bin[i] == gx[i]) ? '0' : '1';
            }
            
            // Loại bỏ các bit 0 ở đầu để xác định bậc mới
            size_t first_1 = next_bin.find('1');
            if (first_1 == string::npos) {
                next_bin = "0";
            } else {
                next_bin = next_bin.substr(first_1);
            }
            
            string poly_next = toPolynomial(next_bin);
            
            // In kết quả theo chuẩn yêu cầu
            cout << "(" << poly_current << ") mod (" << poly_gx << ") = " << poly_next << "\n";
            
            current = next_bin;
        }
        
        cout << endl;
        // cout << "--------------------------------------------------------\n";
        
        if (current == "0") {
            cout << "[+] CONCLUSION: Remainder = 0. g(x) IS a valid generator polynomial (YES).\n";
        } else {
            cout << "[-] CONCLUSION: Remainder != 0. g(x) IS NOT a valid generator polynomial (NO).\n";
        }
        // cout << "========================================================\n";
    }
};

// Hàm main
int main() {
    system("cls");  
    SimpleChecker simple;
    DetailedChecker detailed;
    
    int mode;
    while (true) {
        cout << "================= Cyclic Code Generator Checker (GF(2)) =================\n";
        cout << "SELECT CHECKER MODE:\n";
        cout << "1. Simple Checker (Fast Output: YES/NO)\n";
        cout << "2. Detailed Checker (Line-by-line Modulo)\n";
        cout << "3. Exit\n";
        cout << "=========================================================================\n";
        cout << "Enter your choice (1|2|3): ";
        cin >> mode;

        if (mode == 3) break;
        int l, k;
        string s;
        cout << "\n" << endl;
        cout << "--------------------------------------------------------------------------\n";
        cout << "[Ready] System is running in Mode " << (mode == 1 ? "SIMPLE" : "DETAILED") << "\n";
        cout << "Enter l and k for C(l,k): ";
        cin >> l >> k;
        
        cout << "Enter the polynomial g(x): ";
        cin >> s;
        
        if (mode == 1) {
            simple.check(l, k, s);
        } else if (mode == 2) {
            detailed.check(l, k, s);
        }
        cout << "--------------------------------------------------------------------------\n";
        cout << "\n";
    }

    return 0;
}
