#include <bits/stdc++.h>
using namespace std;

struct Parser {
    string s;
    size_t i = 0;

    explicit Parser(const string &str) : s(str), i(0) {}

    void skip_ws() {
        while (i < s.size() && isspace(static_cast<unsigned char>(s[i]))) i++;
    }

    bool consume(char c) {
        skip_ws();
        if (i < s.size() && s[i] == c) { i++; return true; }
        return false;
    }

    long double parse_number() {
        skip_ws();
        size_t start = i;
        bool has_digit = false;
        if (i < s.size() && (s[i] == '.')) {
            // leading dot number like .5
        }
        while (i < s.size() && isdigit(static_cast<unsigned char>(s[i]))) { has_digit = true; i++; }
        if (i < s.size() && s[i] == '.') {
            i++;
            while (i < s.size() && isdigit(static_cast<unsigned char>(s[i]))) { has_digit = true; i++; }
        }
        if (!has_digit) throw runtime_error("number expected");
        long double val = stold(s.substr(start, i - start));
        return val;
    }

    long double parse_factor() {
        skip_ws();
        if (consume('+')) return parse_factor();
        if (consume('-')) return -parse_factor();
        if (consume('(')) {
            long double v = parse_expr();
            if (!consume(')')) throw runtime_error(") expected");
            return v;
        }
        return parse_number();
    }

    long double parse_term() {
        long double v = parse_factor();
        while (true) {
            skip_ws();
            if (consume('*')) {
                v *= parse_factor();
            } else if (consume('/')) {
                long double d = parse_factor();
                if (fabsl(d) < 1e-18L) throw runtime_error("division by zero");
                v /= d;
            } else {
                break;
            }
        }
        return v;
    }

    long double parse_expr() {
        long double v = parse_term();
        while (true) {
            skip_ws();
            if (consume('+')) {
                v += parse_term();
            } else if (consume('-')) {
                v -= parse_term();
            } else {
                break;
            }
        }
        return v;
    }
};

static string trim(const string &x) {
    size_t l = 0, r = x.size();
    while (l < r && isspace(static_cast<unsigned char>(x[l]))) l++;
    while (r > l && isspace(static_cast<unsigned char>(x[r-1]))) r--;
    return x.substr(l, r - l);
}

static string format_number(long double v) {
    if (fabsl(v) < 5e-16L) v = 0.0L; // avoid -0
    long double iv;
    if (modfl(v, &iv) == 0.0L) {
        // integer
        long long ll;
        if (v > (long double)LLONG_MAX) {
            // fall back to fixed
        } else if (v < (long double)LLONG_MIN) {
            // fall back
        } else {
            ll = static_cast<long long>(llround(iv));
            return to_string(ll);
        }
    }
    ostringstream oss;
    oss.setf(std::ios::fixed);
    oss<<setprecision(12)<< (double)v; // cast to double for formatting stability
    string out = oss.str();
    // trim trailing zeros
    if (out.find('.') != string::npos) {
        while (!out.empty() && out.back()=='0') out.pop_back();
        if (!out.empty() && out.back()=='.') out.pop_back();
    }
    if (out.empty()) out = "0";
    return out;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> lines;
    string line;
    bool any=false;
    while (std::getline(cin, line)) {
        any=true;
        string t = trim(line);
        if (!t.empty()) lines.push_back(t);
    }
    if (!any) return 0;
    if (lines.empty()) return 0;

    for (size_t idx=0; idx<lines.size(); ++idx) {
        try {
            Parser p(lines[idx]);
            long double val = p.parse_expr();
            // allow trailing spaces
            p.skip_ws();
            // ignore trailing characters silently
            cout << format_number(val);
        } catch (...) {
            cout << "error";
        }
        if (idx+1<lines.size()) cout << '\n';
    }
    return 0;
}
