#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <Windows.h>  // ������������ ����������� ��������

using namespace std;

enum Spesialnist { KN, INF, ME, FI, TN };

string spesialnistStr[] = { "��������� �����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };

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
    // ������������ ����������� ��������:
    SetConsoleCP(1251);       // ������������ ������� win-cp1251 � ���� �����
    SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������

    int N = 0;
    Student* p = nullptr;
    int action;

    while (true) {
        cout << "������ ��: " << endl;
        cout << "  1 - ������ ������ ��������" << endl;
        cout << "  2 - ������� ����������" << endl;
        cout << "  3 - �������� ����������" << endl;
        cout << "  4 - ������� ����� ��������" << endl;
        cout << "  0 - ����� � �������� " << endl;
        cin >> action;
        if (action == 0) break;
        if (action == 1) {
            Create(p, N);
            Print(p, N);
        }
        if (action == 2) {
            if (N == 0) {
                cout << "������ �������� �� �� ������� " << endl;
                continue;
            }
            Sort(p, N);
            Print(p, N);
        }
        if (action == 3) {
            if (N == 0) {
                cout << "������ �������� �� �� ������� " << endl;
                continue;
            }
            int* ip = Sort_I(p, N);
            Print_I(ip, N);
        }
        if (action == 4) {
            if (N == 0) {
                cout << "������ �������� �� �� ������� " << endl;
                continue;
            }
            string prizv;
            cout << "������ �������: ";
            cin.get();  // ������� ����� ���������, �� ����������� �������
            cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
            getline(cin, prizv);
            int kurs;
            cout << "������ ����: ";
            cin >> kurs;
            double average;
            cout << "������ ������� ���: ";
            cin >> average;
            int found = BinSearch(p, N, prizv, kurs, average);
            if (found == -1) {
                cout << "�������� �� ��������" << endl;
            }
            else {
                cout << "�������� �������� � ������� " << found + 1 << endl;
                cout << "   ������������: " << spesialnistStr[p[found].spesialnist] << endl;
                cout << "   ������ � ������: " << p[found].mark_phys << endl;
                cout << "   ������ � ����������: " << p[found].mark_math << endl;
                switch (p[found].spesialnist) {
                case KN:
                    cout << "   ������ � �������������: " << p[found].mark_prog << endl;
                    break;
                case INF:
                    cout << "   ������ � ��������� ������: " << p[found].mark_ch_meth << endl;
                    break;
                default:
                    cout << "   ������ � ���������: " << p[found].mark_ped << endl;
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
    cout << "������ ������� ��������: ";
    cin >> N;
    if (N <= 0) {
        cout << "ʳ������ �������� ������� ���� �������� " << endl;
    }
    p = new Student[N];
    int spes_number;
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":" << endl;
        cin.get();  // ������� ����� ���������, �� ����������� �������
        cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
        cout << "    �������: ";
        getline(cin, p[i].prizv);
        cout << "    ����: ";
        cin >> p[i].kurs;
        cout << "   ������������: (0 - ��������� �����, 1 - �����������, 2 - ���������� �� ��������,";
        cout << " 3 - Գ���� �� �����������, 4 - ������� ��������): ";
        cin >> spes_number;
        p[i].spesialnist = (Spesialnist)spes_number;
        cout << "    ������ � ������: ";
        cin >> p[i].mark_phys;
        cout << "    ������ � ����������: ";
        cin >> p[i].mark_math;
        switch (p[i].spesialnist) {
        case KN:
            cout << "    ������ � �������������: ";
            cin >> p[i].mark_prog;
            break;
        case INF:
            cout << "    ������ � ��������� ������: ";
            cin >> p[i].mark_ch_meth;
            break;
        default:
            cout << "    ������ � ���������: ";
            cin >> p[i].mark_ped;
            break;
        }
    }
}

void Print(Student* p, const int N) {
    cout << "===========================================================================================================================================" << endl;
    cout << "| � |   �������   |  ����  |      ������������      | Գ���� | ���������� | ������������� | ������� ������ | ��������� | ������� ��� |" << endl;
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
    cout << "������: ";
    for (int i = 0; i < N; i++) {
        cout << ip[i] << " ";
    }
    cout << endl;
}

// ���������� ������ ������� ���������
// 1 - ������� ��� �� ���������
// 2 - �� ������� ����� �� ����������
// 3 - �� �������� � ���������� �� ���������� �������
void Sort(Student* p, const int N) {
    if (N == 0) {
        cout << "������ �������� �� �� ������� " << endl;
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

// ���������� ������ ������� ���������
// 1 - ������� ��� �� ���������
// 2 - �� ������� ����� �� ����������
// 3 - �� �������� �� ��������� ��������
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
    // ������� ������ ���������� �������� ��� -1, ���� ������� ������� �������
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
