#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <Windows.h>  // забезпечення відображення кирилиці

using namespace std;

enum Spesialnist { KN, INF, ME, FI, TN };

string spesialnistStr[] = { "Комп’ютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

struct Student {
    string prizv;
    int kurs;
    Spesialnist spesialnist;
    int mark_phys;
    int mark_math;
    union {
        int mark_prog;
        int mark_ch_meth;
        int mark_ped;
    };

};

void Create(Student*& p, int& N);
void Print(Student* p, const int N);
void Print_I(int* ip, const int N);
void Sort(Student* p, const int N);
int* Sort_I(Student* p, const int N);
int BinSearch(Student* p, const int N, const string prizv, const int kurs, const double average);
double Average_Mark(Student student);

int main() {
    // забезпечення відображення кирилиці:
    SetConsoleCP(1251);       // встановлення сторінки win-cp1251 в потік вводу
    SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

    int N = 0;
    Student* p = nullptr;
    int action;

    while (true) {
        cout << "Введіть дію: " << endl;
        cout << "  1 - ввести список студентів" << endl;
        cout << "  2 - фізичне сортування" << endl;
        cout << "  3 - індексне сортування" << endl;
        cout << "  4 - бінарний пошук студента" << endl;
        cout << "  0 - вихід з програми " << endl;
        cin >> action;
        if (action == 0) break;
        if (action == 1) {
            Create(p, N);
            Print(p, N);
        }
        if (action == 2) {
            if (N == 0) {
                cout << "Список студентів ще не заданий " << endl;
                continue;
            }
            Sort(p, N);
            Print(p, N);
        }
        if (action == 3) {
            if (N == 0) {
                cout << "Список студентів ще не заданий " << endl;
                continue;
            }
            int* ip = Sort_I(p, N);
            Print_I(ip, N);
        }
        if (action == 4) {
            if (N == 0) {
                cout << "Список студентів ще не заданий " << endl;
                continue;
            }
            string prizv;
            cout << "Введіть прізвище: ";
            cin.get();  // очищуємо буфер клавіатури, бо залишаються символи
            cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
            getline(cin, prizv);
            int kurs;
            cout << "Введіть курс: ";
            cin >> kurs;
            double average;
            cout << "Введіть середній бал: ";
            cin >> average;
            int found = BinSearch(p, N, prizv, kurs, average);
            if (found == -1) {
                cout << "Студента не знайдено" << endl;
            }
            else {
                cout << "Знайдено студента з номером " << found + 1 << endl;
                cout << "   спеціальність: " << spesialnistStr[p[found].spesialnist] << endl;
                cout << "   оцінка з фізики: " << p[found].mark_phys << endl;
                cout << "   оцінка з математики: " << p[found].mark_math << endl;
                switch (p[found].spesialnist) {
                case KN:
                    cout << "   оцінка з програмування: " << p[found].mark_prog << endl;
                    break;
                case INF:
                    cout << "   оцінка з чисельних методів: " << p[found].mark_ch_meth << endl;
                    break;
                default:
                    cout << "   оцінка з педагогіки: " << p[found].mark_ped << endl;
                    break;
                }
                cout << endl;
            }
        }
    }
    delete[] p;

    return 0;
}

void Create(Student*& p, int& N) {
    cout << "Введіть кількість студентів: ";
    cin >> N;
    if (N <= 0) {
        cout << "Кількість студентів повинна бути додатною " << endl;
    }
    p = new Student[N];
    int spes_number;
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get();  // очищуємо буфер клавіатури, бо залишаються символи
        cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
        cout << "    прізвище: ";
        getline(cin, p[i].prizv);
        cout << "    курс: ";
        cin >> p[i].kurs;
        cout << "   спеціальність: (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка,";
        cout << " 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> spes_number;
        p[i].spesialnist = (Spesialnist)spes_number;
        cout << "    оцінка з фізики: ";
        cin >> p[i].mark_phys;
        cout << "    оцінка з математики: ";
        cin >> p[i].mark_math;
        switch (p[i].spesialnist) {
        case KN:
            cout << "    оцінка з програмування: ";
            cin >> p[i].mark_prog;
            break;
        case INF:
            cout << "    оцінка з чисельних методів: ";
            cin >> p[i].mark_ch_meth;
            break;
        default:
            cout << "    оцінка з педагогіки: ";
            cin >> p[i].mark_ped;
            break;
        }
    }
}

void Print(Student* p, const int N) {
    cout << "===========================================================================================================================================" << endl;
    cout << "| № |   Прізвище   |  Курс  |      Спеціальність      | Фізика | Математика | Програмування | Чисельні методи | Педагогіка | Середній бал |" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << i + 1 << " ";
        cout << "| " << setw(12) << left << p[i].prizv << " ";
        cout << "|    " << p[i].kurs << "   ";
        cout << "| " << setw(23) << left << spesialnistStr[p[i].spesialnist] << " ";
        cout << "| " << setw(6) << right << p[i].mark_phys << " ";
        cout << "| " << setw(10) << right << p[i].mark_math << " ";
        switch (p[i].spesialnist) {
        case KN:
            cout << "| " << setw(13) << right << p[i].mark_prog << " ";
            cout << "|                 ";
            cout << "|            ";
            break;
        case INF:
            cout << "|               ";
            cout << "| " << setw(15) << right << p[i].mark_ch_meth << " ";
            cout << "|            ";
            break;
        default:
            cout << "|               ";
            cout << "|                 ";
            cout << "| " << setw(10) << right << p[i].mark_ped << " ";
            break;
        }
        cout << "| " << setw(12) << right << Average_Mark(p[i]) << " ";
        cout << "|" << endl;
    }
    cout << "===========================================================================================================================================" << endl;
}

void Print_I(int* ip, const int N) {
    cout << "Індекс: ";
    for (int i = 0; i < N; i++) {
        cout << ip[i] << " ";
    }
    cout << endl;
}

// сортування масиву методом бульбашки
// 1 - середній бал за спаданням
// 2 - за номером курсу за зростанням
// 3 - за прізвищем в зворотному до алфавітного порядку
void Sort(Student* p, const int N) {
    if (N == 0) {
        cout << "Список студентів ще не заданий " << endl;
        return;
    }
    Student tmp_student;
    for (int upper = N - 2; upper >= 0; upper--) {
        for (int k = 0; k <= upper; k++) {
            double average_k = Average_Mark(p[k]);
            double average_k_1 = Average_Mark(p[k + 1]);
            if (
                (average_k < average_k_1) ||
                ((average_k == average_k_1) && (p[k].kurs > p[k + 1].kurs)) ||
                ((average_k == average_k_1) && (p[k].kurs == p[k + 1].kurs) && (p[k].prizv < p[k + 1].prizv))
                ) {
                tmp_student = p[k];
                p[k] = p[k + 1];
                p[k + 1] = tmp_student;
            }
        }
    }
}

// сортування масиву методом бульбашки
// 1 - середній бал за спаданням
// 2 - за номером курсу за зростанням
// 3 - за прізвищем за алфавітним порядком
int* Sort_I(Student* p, const int N) {
    int* ip = new int[N];
    for (int i = 0; i < N; i++) {
        ip[i] = i;
    }
    int tmp_ip;
    for (int upper = N - 2; upper >= 0; upper--) {
        for (int k = 0; k <= upper; k++) {
            double average_k = Average_Mark(p[ip[k]]);
            double average_k_1 = Average_Mark(p[ip[k + 1]]);
            if (
                (average_k < average_k_1) ||
                ((average_k == average_k_1) && (p[ip[k]].kurs > p[ip[k + 1]].kurs)) ||
                ((average_k == average_k_1) && (p[ip[k]].kurs == p[ip[k + 1]].kurs) && (p[ip[k]].prizv > p[ip[k + 1]].prizv))
                ) {
                tmp_ip = ip[k];
                ip[k] = ip[k + 1];
                ip[k + 1] = tmp_ip;
            }
        }
    }
    return ip;
}

int BinSearch(Student* p, const int N, const string prizv, const int kurs, const double average) {
    // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        double average_m = Average_Mark(p[m]);
        if (p[m].prizv == prizv && p[m].kurs == kurs && average_m == average) {
            return m;
        }
        if (
            (average_m < average) ||
            ((average_m == average) && (p[m].kurs > kurs)) ||
            ((average_m == average) && (p[m].kurs == kurs) && (p[m].prizv < prizv))
            ) {
            R = m - 1;
        }
        else {
            L = m + 1;
        }
    } while (L <= R);
    return -1;
}

double Average_Mark(Student student) {
    if (student.spesialnist == KN) {
        return round((student.mark_phys + student.mark_math + student.mark_prog) / 3. * 100) / 100.;
    }
    if (student.spesialnist == INF) {
        return round((student.mark_phys + student.mark_math + student.mark_ch_meth) / 3. * 100) / 100.;
    }
   return round((student.mark_phys + student.mark_math + student.mark_ped) / 3. * 100) / 100.;
}
