#include "iostream"
#include "string"
#include "vector"
#include "fstream"
#include "cmath"
#include "stdlib.h"
#include "time.h"
#include "utility"

#define PI 3.14

using namespace std;
int findMaxEl(string inFile) {
    int maxEl = 0;
    string str = "";
    char el;

    ifstream fin(inFile);

    while (fin.get(el)) { //Ищем наибольшой элемент
        if (isdigit(el))
            str = str + el;
        else if (stoi(str) > maxEl) {
            maxEl = stoi(str);
            str = "";
        }
        else
            str = "";
    }
    if (str != "" && stoi(str) > maxEl) {
        maxEl = stoi(str);
        str = "";
    }

    fin.close();
    return maxEl;
}


//Стандартное равномерное распределние с заданным интервалом
void distST(string inFile, int p1, int p2) {
    string str = "";
    char el;

    ifstream fin(inFile);
    if (!fin.is_open()) {
        cout << "Файл " << inFile << " не найден! \n";
        return;
    }

    double m = findMaxEl(inFile) + 1;
    ofstream fout("st.dat");
    while (fin.get(el)) { //Генерируем распределение
        if (isdigit(el))
            str = str + el;
        else {
            fout << round(p1 + (stoi(str) / m) * p2) << ",";
            str = "";
        }
    }
    if (str != "")
        fout << round(p1 + (stoi(str) / m) * p2);

    fin.close();
    fout.close();
}


//Треугольное распределение
void distTR(string inFile, int p1, int p2) {
    string str = "";
    char el;

    ifstream fin(inFile);
    if (!fin.is_open()) {
        cout << "Файл " << inFile << " не найден! \n";
        return;
    }

    double m = findMaxEl(inFile) + 1;
    int prev = 0;
    while (fin.get(el)) { //Первый элемент последовательности
        if (isdigit(el))
            str = str + el;
        else {
            prev = stoi(str);
            str = "";
            break;
        }
    }

    ofstream fout("tr.dat");
    while (fin.get(el)) { //Генерируем распределение
        if (isdigit(el))
            str = str + el;
        else {
            fout << round(p1 + p2 * (prev / m + stoi(str) / m - 1)) << ",";
            prev = stoi(str);
            str = "";
        }
    }
    if (str != "")
        fout << round(p1 + p2 * (prev / m + stoi(str) / m - 1));

    fin.close();
    fout.close();
}


//Общее экспоненциальное распределение
void distEX(string inFile, int p1, int p2) {
    string str = "";
    char el;

    ifstream fin(inFile);
    ofstream fout("ex.dat");
    if (!fin.is_open()) {
        cout << "Файл " << inFile << " не найден! \n";
        return;
    }

    double m = findMaxEl(inFile) + 1;
    while (fin.get(el)) { //Генерируем распределение
        if (isdigit(el))
            str = str + el;
        else if (str == "0")
            str = "";
        else {
            int res = -p2 * log(stoi(str) / m) + p1;
            fout << res << ",";
            str = "";
        }
    }
    if (str != "" && str != "0")
        fout << int(-p2 * log(stoi(str)) + p1);

    fin.close();
    fout.close();
}


//Нормальное распределение
void distNR(string inFile, int p1, int p2) {
    string str = "";
    char el;

    ifstream fin(inFile);
    ofstream fout("nr.dat");
    if (!fin.is_open()) {
        cout << "Файл " << inFile << " не найден! \n";
        return;
    }

    double m = findMaxEl(inFile) + 1;
    vector <double> nums;
    while (fin.get(el)) { //Генерируем распределение
        if (isdigit(el))
            str = str + el;
        else {
            nums.push_back(stoi(str) / m);
            if (nums.size() == 2) {
                fout << round(p1 + p2 * sqrt(-2 * log(1 - nums[0])) * cos(2 * PI * nums[1])) << ",";
                fout << round(p1 + p2 * sqrt(-2 * log(1 - nums[0])) * sin(2 * PI * nums[1])) << ",";
                nums.clear();
            }
            str = "";
        }
    }
    if (str != "" && nums.size() == 1) {
        fout << round(p1 + p2 * sqrt(-2 * log(1 - nums[0])) * cos(2 * PI * stoi(str) / m)) << ",";
        fout << round(p1 + p2 * sqrt(-2 * log(1 - nums[0])) * sin(2 * PI * stoi(str) / m));
    }

    fin.close();
    fout.close();
}


//Гамма распределение
void distGM(string inFile, int p1, int p2) {
    string str = "";
    char el;

    ifstream fin(inFile);
    ofstream fout("gm.dat");
    if (!fin.is_open()) {
        cout << "Файл " << inFile << "не найден! \n";
        return;
    }

    double m = findMaxEl(inFile) + 1;
    while (fin.get(el)) { //Генерируем распределение
        if (isdigit(el))
            str = str + el;
        else {
            fout << round(p1 - p2 * log(1 - stoi(str) / m)) << ",";
            str = "";
        }
    }
    if (str != "") {
        fout << round(p1 - p2 * log(1 - stoi(str) / m));
    }

    fin.close();
    fout.close();
}


//Логнормальное распределение
void distLN(string inFile, int p1, double p2) {
    string str = "";
    char el;

    ifstream fin(inFile);
    ofstream fout("ln.dat");
    if (!fin.is_open()) {
        cout << "Файл " << inFile << " не найден! \n";
        return;
    }
    
    double m = findMaxEl(inFile) + 1;
    vector <double> nums;
    while (fin.get(el)) { //Генерируем распределение
        if (isdigit(el))
            str = str + el;
        else {
            nums.push_back(stoi(str) / m);
            if (nums.size() == 2) {
                double nrNum = p1 + p2 * sqrt(-2 * log(1 - nums[0])) * cos(2 * PI * nums[1]);
                fout << round(p1 + exp(p2 - nrNum)) << ",";
                nrNum = p1 + p2 * sqrt(-2 * log(1 - nums[0])) * sin(2 * PI * nums[1]);
                fout << round(p1 + exp(p2 - nrNum)) << ",";
                nums.clear();
            }
            str = "";
        }
    }
    if (str != "" && nums.size() == 1) {
        int nrNum = p1 + p2 * sqrt(-2 * log(1 - nums[0])) * (int)cos(2 * PI * stoi(str) / m);
        fout << round(p1 + exp(p2 - nrNum)) << ",";
        nrNum = p1 + p2 * sqrt(-2 * log(1 - nums[0])) * (int)sin(2 * PI * stoi(str) / m);
        fout << round(p1 + exp(p2 - nrNum));
    }
    
    fin.close();
    fout.close();
}


//Логистическое распределение
void distLS(string inFile, int p1, int p2) {
    string str = "";
    char el;

    ifstream fin(inFile);
    ofstream fout("ls.dat");
    if (!fin.is_open()) {
        cout << "Файл " << inFile << "не найден! \n";
        return;
    }

    double m = findMaxEl(inFile) + 1;
    while (fin.get(el)) { //Генерируем распределение
        if (isdigit(el))
            str = str + el;
        else {
            double u = stoi(str) / m;
            int res = 0;
            if (str != "0")
                res = round(p1 + p2 * log(u / (1 - u)));
            fout << res << ",";
            str = "";
        }
    }
    if (str != "") {
        double u = stoi(str) / m;
        fout << round(p1 + p2 * log(u / (1 - u)));
    }

    fin.close();
    fout.close();
}


//Факториал
long long fact(int n) {
    long long res = 1;
    for (int i = 2; i <= n; i++)
        res *= i;
    return res;
}


//Биномиальное распределение
void distBI(string inFile, int n, double p) {
    string str = "";
    char el;

    ifstream fin(inFile);
    ofstream fout("bi.dat");
    if (!fin.is_open()) {
        cout << "Файл " << inFile << "не найден! \n";
        return;
    }

    vector <long long> bnc;
    for (int k = 0; k <= n; k++) { //Вычисляем все возможные биномиальные коэффициенты
        long long num = 1;
        for (int i = k + 1; i <= n; i++)
            num *= i;
        bnc.push_back(num / fact(n - k));
    }

    double m = findMaxEl(inFile) + 1;
    while (fin.get(el)) { //Генерируем распределение
        if (isdigit(el))
            str = str + el;
        else {
            double acc = 0, u = stoi(str) / m;
            for (int k = 0; k < n; k++) {
                acc += bnc[k] * pow(p, k) * pow((1 - p), n - k);
                if (u <= acc) {
                    fout << k << ",";
                    break;
                }
            }
            str = "";
        }
    }
    if (str != "") {
        double acc = 0, u = stoi(str) / m;
        for (int k = 0; k < n; k++) {
            acc += bnc[k] * pow(p, k) * pow((1 - p), n - k);
            if (u <= acc) {
                fout << k;
                break;
            }
        }
    }

    fin.close();
    fout.close();
}


//Главная функция
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru");
    srand(time(NULL));

    string file = "rnd.dat";
    string distribution = "bi";
    double p1 = 10, p2 = 0.25;

    //Считываем параметры
    for (int i = 1; i < argc; i++) {
        string str = argv[i];
        switch (argv[i][1]) {
        case 'f':
            file = str.erase(0, 3);
            break;
        case 'd':
            distribution = str.erase(0, 3);
            break;
        case 'p':
            if (argv[i][2] == '1')
                p1 = stoi(str.erase(0, 4));
            else if (argv[i][2] == '2') {
                int len = str.length();
                char* strP2 = new char[len - 4];
                for (int i = 0; i <= len - 4; i++)
                    strP2[i] = str[i + 4];
                p2 = atof(strP2);
            }
            else {
                cout << "Некорректно задан параметр " << str << "!";
                return 0;
            }
            break;
        default:
            cout << str << " - неверный параметр \n";
            return 0;
        }
    }

    //Преобразуем ПСЧ к распределению
    if (distribution == "st")
        distST(file, p1, p2);
    else if (distribution == "tr")
        distTR(file, p1, p2);
    else if (distribution == "ex")
        distEX(file, p1, p2);
    else if (distribution == "nr")
        distNR(file, p1, p2);
    else if (distribution == "gm")
        distGM(file, p1, p2);
    else if (distribution == "ln")
        distLN(file, p1, p2);
    else if (distribution == "ls")
        distLS(file, p1, p2);
    else if (distribution == "bi")
        distBI(file, p1, p2);
    else
        cout << "Неверный параметр /d \n";

    return 0;
}