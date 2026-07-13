#include <iostream>
#include <iomanip>
#include <cmath>
#include <clocale>
#include <windows.h>

using namespace std;

struct Result {
    long long g, a, b;
};

Result extended_binary_gcd(long long x, long long y) {
    if (x == 0 && y == 0)
        return {0, 0, 0};

    int sign_x = (x >= 0) ? 1 : -1;
    int sign_y = (y >= 0) ? 1 : -1;
    x = llabs(x);
    y = llabs(y);

    if (x == 0) return {y, 0, sign_y};
    if (y == 0) return {x, sign_x, 0};

    int shift = 0;
    while (((x | y) & 1) == 0) {
        x >>= 1;
        y >>= 1;
        shift++;
    }
    cout << "Наибольшая общая степень двойки: " << shift << endl;

    long long u = x, v = y;
    long long a = 1, b = 0, c = 0, d = 1;
    int i = 0;

    cout << left << setw(10) << "i"
         << setw(20) << "a" << setw(20) << "b"
         << setw(20) << "alpha" << setw(20) << "beta"
         << setw(20) << "gamma" << setw(20) << "delta" << endl;

    cout << left << setw(10) << i
         << setw(20) << u << setw(20) << v
         << setw(20) << a << setw(20) << b
         << setw(20) << c << setw(20) << d << endl;

    while (v != 0) {
        while ((v & 1) == 0) {
            v >>= 1;
            if (((c & 1) == 0) && ((d & 1) == 0)) {
                c >>= 1;
                d >>= 1;
            } else {
                c = (c + y) >> 1;
                d = (d - x) >> 1;
            }
            i++;
            cout << left << setw(10) << i
                 << setw(20) << u << setw(20) << v
                 << setw(20) << a << setw(20) << b
                 << setw(20) << c << setw(20) << d << endl;
        }
        if (u > v) {
            swap(u, v);
            swap(a, c);
            swap(b, d);
            i++;
            cout << left << setw(10) << i
                 << setw(20) << u << setw(20) << v
                 << setw(20) << a << setw(20) << b
                 << setw(20) << c << setw(20) << d << endl;
        }
        v = v - u;
        c = c - a;
        d = d - b;
        i++;
        cout << left << setw(10) << i
             << setw(20) << u << setw(20) << v
             << setw(20) << a << setw(20) << b
             << setw(20) << c << setw(20) << d << endl;
    }

    long long g = u << shift;
    return {g, a * sign_x, b * sign_y};
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU");
    long long x, y;
    cout << "Введите первое число: ";
    if (!(cin >> x)) {
        cout << "Введённое значение не является целым числом\n";
        return 0;
    }
    cout << "Введите второе число: ";
    if (!(cin >> y)) {
        cout << "Введённое значение не является целым числом\n";
        return 0;
    }

    Result res = extended_binary_gcd(x, y);
    if (res.g == 0) {
        cout << "НОД не определён\n";
        return 0;
    }

    cout << "Ответ: D(" << x << ", " << y << ") = "
         << x << " * " << ((res.a >= 0) ? to_string(res.a) : "(" + to_string(res.a) + ")")
         << " + " << y << " * " << ((res.b >= 0) ? to_string(res.b) : "(" + to_string(res.b) + ")")
         << " = " << (x * res.a + y * res.b) << endl;

    return 0;
}
