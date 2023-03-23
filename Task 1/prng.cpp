#include "iostream"
#include "string"
#include "vector"
#include "fstream"
#include "cmath"
#include "stdlib.h"
#include "time.h"
#include "utility"

using namespace std;
int nod(int x, int y) {
    int r = y % x;
    if (r == 0)
        return x;
    else
        nod(r, x);
}


int pow(int x, int n) {
    int res = 1;
    for (int i = 0; i < n; i++)
        res *= x;
    return res;
}


//Возведение в степень по модулю
int powClosed(int x, int n, int mod) {
    int res = 1;
    for (int i = 0; i < n; i++)
        res = (res * x) % mod;
    return res;
}


//Представляем число в 2 СС
string binForm(int x) {
    string bitter = "";
    while (x != 0) {
        bitter = to_string(x % 2) + bitter;
        x /= 2;
    }
    return bitter;
}


//Представляем число в 10 СС
int decForm(string x) {
    int res = 0, deg = 1;
    if (x[x.length() - 1] == '1')
        res += 1;
    for (int i = 1; i < x.length(); i++) {
        deg = deg * 2;
        if (x[x.length() - i - 1] == '1')
            res += deg;
    }
    return res;
}


//Мануал
void __help() {
    cout << "/g:<код_метода> - параметр указывает на метод генерации ПСЧ, при этом код_метода может быть одним из следующих: \n";
    cout << "  lc - линейный конгруэнтный метод (вектор инициализации: m, a, c, x0); \n";
    cout << "  add - аддитивный метод (вектор инициализации: модуль, ст.индекс, мл.индекс, последовательность начальных значений); \n";
    cout << "  5p - пятипараметрический метод (вектор инициализации: p, q1, q2, q3, w); \n";
    cout << "  lfsr - регистр сдвига с обратной связью (вектор инициализации: вектор коэффициентов в 2 СС, x0) \n";
    cout << "  nfsr - нелинейная комбинация РСЛОС (вектор инициализации: R1, R2, R3 - все в 2 СС); \n";
    cout << "  mt - вихрь Мерсенна (вектор инициализации: m, x0); \n";
    cout << "  rc4 - RC4 (вектор инициализации: 256 начальных значений); \n";
    cout << "  rsa - ПСЧ на основе RSA (вектор инициализации: модуль n, число e, начальное значение x); \n";
    cout << "  bbs - алгоритм Блюма-Блюма-Шуба (вектор инициализации: начальоне число x (вз-пр с n = 16637). \n";
    cout << "/i:<число> - инициализационный вектор генератора. \n";
    cout << "/n:<длина> - количество генерируемых чисел. Если параметр не указан, - генерируется 10000 чисел. \n";
    cout << "/f:<полное_имя_файла> - полное имя файла, в который будут выводиться данные.";
    cout << "Если параметр не указан, данные должны записываться в файл с именем rnd.dat. \n";
    cout << "/h – информация о допустимых параметрах командной строки программы. \n";
}


//Линейный когнруэнтный метод
void algLC(vector <int> init, int count, string outFile) {
    ofstream fout;
    fout.open(outFile);

    long long x0 = rand() % 1000, a = 1103515245, c = 12345, m = 2147483647, mod = 1000;
    if (!init.empty())
        m = init[0], a = init[1], c = init[2], x0 = init[3], mod = init[0];

    if (m <= 0 || a < 0 || a > m || c < 0 || c > m || x0 < 0 || x0 > m) { //Проверка на дурака
        cout << "Некорректный ввод данных! \n";
        return;
    }

    fout << x0 << endl;
    for (int i = 2; i <= count; i++) {
        x0 = (a * x0 + c) % m;
        fout << x0 % mod << endl;

        if (i / (float)count * 100 == 1)  cout << " 1%... \n";
        if (i / (float)count * 100 == 25)  cout << "25%... \n";
        if (i / (float)count * 100 == 50)  cout << "50%... \n";
        if (i / (float)count * 100 == 75)  cout << "75%... \n";
        if (i / (float)count * 100 == 100)  cout << "Последовательность сгенерирована! \n";
    }

    fout.close();
}


//Аддитивный метод
void algADD(vector <int> init, int count, string outFile) {
    ofstream fout;
    fout.open(outFile);

    int m, iYoung, iOld; //Инициализируем начальные значения
    vector <int> startVal;
    if (init.empty()) {
        m = 1000, iYoung = 55, iOld = 24;
        for (int i = 0; i < 56; i++) {
            startVal.push_back(rand() % 1000);
            fout << startVal[i] << endl;
        }
    }
    else {
        m = init[0], iYoung = init[1], iOld = init[2];
        for (int i = 3; i < init.size(); i++) {
            startVal.push_back(init[i] % m);
            fout << startVal[i - 3] << endl;
        }
    }

    for (int i = startVal.size(); i <= count; i++) {
        int xNew = (startVal[iOld - 1] + startVal[iYoung - 1]) % m;
        fout << xNew  << endl;
        startVal.push_back(xNew);
        startVal.erase(startVal.begin());

        if (i / (float)count * 100 == 1)  cout << " 1%... \n";
        if (i / (float)count * 100 == 25)  cout << "25%... \n";
        if (i / (float)count * 100 == 50)  cout << "50%... \n";
        if (i / (float)count * 100 == 75)  cout << "75%... \n";
        if (i / (float)count * 100 == 100)  cout << "Последовательность сгенерирована! \n";
    }

    fout.close();
}


//Пятипараметрический метод
void alg5P(vector <int> init, int count, string outFile) {
    ofstream fout;
    fout.open(outFile);

    int p = 607, q1 = 167, q2 = 307, q3 = 461, w = 15;
    if (!init.empty())
        p = init[0], q1 = init[1], q2 = init[2], q3 = init[3], w = init[4];

    if (q1 > p || q2 > p || q3 > p || w > p) { //Проверка на дурака
        cout << "Некорректный ввод данных: q1/q2/q3/w > p! \n";
        return;
    }

    vector <int> buffer(p); //Инициализируем рандомный вектор
    for (int i = 0; i < p; i++)
        buffer[i] = rand() % 2;

    for (int i = 1; i <= count; i++) {
        int bit = 0;
        if (buffer[q1] == 1)    bit += 1; //Вычисляем новый бит
        if (buffer[q2] == 1)    bit += 1;
        if (buffer[q3] == 1)    bit += 1;
        bit = bit & 1;
        buffer.push_back(bit);
        buffer.erase(buffer.begin());

        int x = 0, deg = 1; //Вычисляем сгенерированное число размером w
        if (buffer[0] == 1)
            x += 1;
        for (int j = 1; j < w; j++) {
            deg = (deg * 2) % 1000;
            if (buffer[j] == 1)
                x += deg;
        }

        fout << x % 1000 << endl;

        if (i / (float)count * 100 == 1)  cout << " 1%... \n";
        if (i / (float)count * 100 == 25)  cout << "25%... \n";
        if (i / (float)count * 100 == 50)  cout << "50%... \n";
        if (i / (float)count * 100 == 75)  cout << "75%... \n";
        if (i / (float)count * 100 == 100)  cout << "Последовательность сгенерирована! \n";
    }

    fout.close();
}


//Регистр сдвига с обратной связью (РСЛОС)
void algLFSR(vector <int> init, int count, string outFile, string polynom) {
    ofstream fout;
    fout.open(outFile);

    int x0 = rand() % 1000; //Задаём начальное значение
    if (!init.empty())
        x0 = init[0];

    for (int i = 1; i <= count; i++) {
        string bitter = binForm(x0); //Бинарная форма значения регистра
        while (bitter.length() < polynom.length())
            bitter = "0" + bitter;

        int bit = 0; //Сложение битов, указанных в полиноме
        for (int j = 0; j < polynom.length(); j++)
            if (polynom[polynom.length() - j - 1] == '1' && bitter[bitter.length() - j - 1] == '1')
                bit++;

        x0 = x0 >> 1; //Вычисляем новое значение последовательности
        if (bit % 2 == 1) {
            int bits = polynom.length();
            x0 = (x0 + pow(2, bits - 1)) % pow(2, bits);
        }
        fout << x0 % 1000 << endl;

        if (i / (float)count * 100 == 1)  cout << " 1%... \n";
        if (i / (float)count * 100 == 25)  cout << "25%... \n";
        if (i / (float)count * 100 == 50)  cout << "50%... \n";
        if (i / (float)count * 100 == 75)  cout << "75%... \n";
        if (i / (float)count * 100 == 100)  cout << "Последовательность сгенерирована! \n";
    }

    fout.close();
}


//Вспомогательная функция для нелинейной комбинации РСЛОС
int lfsrHelp(int x0, int polynom) {
    string binX = binForm(x0), binPoly = binForm(polynom);
    while (binX.length() < binPoly.length())
        binX = "0" + binX;

    int bit = 0; //Сложение битов, указанных в полиноме
    for (int i = 0; i < binPoly.size(); i++)
        if (binX[binX.length() - i - 1] == '1' && binPoly[binPoly.length() - i - 1] == '1')
            bit++;

    x0 = x0 >> 1;
    if (bit % 2 == 1) {
        int bits = binPoly.length();
        x0 = (x0 + pow(2, bits - 1)) % pow(2, bits);
    }

    return x0;
}


//Нелинейная комбинация РСЛОС
void algNFSR(vector <string> polynoms, int count, string outFile) {
    ofstream fout;
    fout.open(outFile);

    int R1 = 65581, R2 = 285, R3 = 4179, x0;
    if (!polynoms.empty())
        R1 = decForm(polynoms[0]), R2 = decForm(polynoms[1]), R3 = decForm(polynoms[2]);
    int R1Start = R1, R2Start = R2, R3Start = R3;

    for (int i = 1; i <= count; i++) {
        x0 = (R1 ^ R2) + (R2 ^ R3) + R3 % 1000000000;
        R1 = lfsrHelp(R1, R1Start);
        R2 = lfsrHelp(R2, R2Start);
        R3 = lfsrHelp(R3, R3Start);

        fout << x0 % 1000 << endl;

        if (i / (float)count * 100 == 1)  cout << " 1%... \n";
        if (i / (float)count * 100 == 25)  cout << "25%... \n";
        if (i / (float)count * 100 == 50)  cout << "50%... \n";
        if (i / (float)count * 100 == 75)  cout << "75%... \n";
        if (i / (float)count * 100 == 100)  cout << "Последовательность сгенерирована! \n";
    }

    fout.close();
}


//Вихрь Мерсенна
void algMT(vector <int> init, int count, string outFile) {
    ofstream fout;
    fout.open(outFile);

    int mod = 1000, x0 = 5489;
    if (!init.empty())
        mod = init[0], x0 = init[1];

    int p = 624; //Параметры, наилучшие для генератора
    int q = 397;
    unsigned int u = 2147483648; //1000 0000 0000 0000 0000 0000 0000 0000
    unsigned int h = 2147483647; //0111 1111 1111 1111 1111 1111 1111 1111
    unsigned int a = 2567483615;

    vector <long long> X(p); //Создаём начальные значения
    X[0] = x0;
    for (int i = 1; i < p; i++)
        X[i] = abs(1812433253 * (X[i - 1] ^ (X[i - 1] >> 30)) + i);

    unsigned int matrixA[2] = { 0, a };
    for (int i = 1; i <= count; i++) {
        long long y = (X[0] & u) | (X[1] & h);

        long long xn = X[q % p] ^ (y >> 1) ^ (matrixA[y & 1]);
        X.push_back(xn);
        X.erase(X.begin());

        y = xn;
        y = y ^ (y >> 11);
        y = y ^ ((y << 7) * 2636928640);
        y = y ^ ((y << 15) * 4022730752);
        long long z = y ^ (y >> 18);
        fout << z % mod << endl;

        if (i / (float)count * 100 == 1)  cout << " 1%... \n";
        if (i / (float)count * 100 == 25)  cout << "25%... \n";
        if (i / (float)count * 100 == 50)  cout << "50%... \n";
        if (i / (float)count * 100 == 75)  cout << "75%... \n";
        if (i / (float)count * 100 == 100)  cout << "Последовательность сгенерирована! \n";
    }
}


//Генератор RC4
void algRC4(vector <int> init, int count, string outFile) {
    ofstream fout;
    fout.open(outFile);

    vector <int> S(256), K(256); //Создаём и заполняем массивы
    for (int i = 0; i < 256; i++)
        S[i] = i;
    if (init.empty())
        for (int i = 0; i < 256; i++)
            K[i] = i;
    else
        K = init;

    int i = 0, j = 0; //Перемешиваем значения в таблице S
    for (i = 0; i < 256; i++) {
        j = (j + S[i] + K[i]) % 256;
        swap(S[i], S[j]);
    }

    for (int n = 1; n <= count; n++) { //Генерируем последовательность
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        int a = (S[i] + S[j]) % 256;

        fout << S[a] << endl;

        if (n / (float)count * 100 == 1)  cout << " 1%... \n";
        if (n / (float)count * 100 == 25)  cout << "25%... \n";
        if (n / (float)count * 100 == 50)  cout << "50%... \n";
        if (n / (float)count * 100 == 75)  cout << "75%... \n";
        if (n / (float)count * 100 == 100)  cout << "Последовательность сгенерирована! \n";
    }

    fout.close();
}


//ГПСЧ на основе RSA
void algRSA(vector <int> init, int count, string outFile) {
    ofstream fout;
    fout.open(outFile);

    int n = 7191817, e = 151, x0 = 69;
    if (!init.empty()) {
        n = init[0], e = init[1], x0 = init[2];
    }

    if (x0 < 1 || x0 > n) { //Проверка на дурака
        cout << "Начальное значенеи превышает модуль!\n";
        return;
    }

    for (int i = 1; i <= count; i++) {
        string z = "";
        int x = x0;
        for (int j = 0; j < 10; j++) {
            x = powClosed(x, e, n);
            z = z + binForm(x).back();
        }
        x0 = x;

        fout << decForm(z) << endl;

        if (i / (float)count * 100 == 1)  cout << " 1%... \n";
        if (i / (float)count * 100 == 25)  cout << "25%... \n";
        if (i / (float)count * 100 == 50)  cout << "50%... \n";
        if (i / (float)count * 100 == 75)  cout << "75%... \n";
        if (i / (float)count * 100 == 100)  cout << "Последовательность сгенерирована! \n";
    }

    fout.close();
}


//Алгоритм Блюма-Блюма-Шуба (BBS)
void algBBS(vector <int> init, int count, string outFile) {
    ofstream fout;
    fout.open(outFile);

    int p = 127, q = 131, n = 16637, x0 = 3137; //Начальные значения
    if (!init.empty()) {
        if (nod(init[0], n) == 1)
            x0 = init[0];
        else {
            cout << "Начальное значение не взаимно простое с n = 16637! \n";
            return;
        }
    }

    for (int i = 1; i <= count; i++) {
        string z = "";
        int x = (x0 * x0) % n;

        for (int j = 0; j < 10; j++) {
            x = (x * x) % n;
            z = z + binForm(x).back();
        }
        x0 = x;

        fout << decForm(z) << endl;

        if (i / (float)count * 100 == 1)  cout << " 1%... \n";
        if (i / (float)count * 100 == 25)  cout << "25%... \n";
        if (i / (float)count * 100 == 50)  cout << "50%... \n";
        if (i / (float)count * 100 == 75)  cout << "75%... \n";
        if (i / (float)count * 100 == 100)  cout << "Последовательность сгенерирована! \n";
    }

    fout.close();
}


//Главная функция
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru");
    srand(time(NULL));

    string method = "lfsr";
    string strInit = "";
    int count = 10000;
    string outFile = "rnd.dat";

    //Считываем параметры
    for (int i = 1; i < argc; i++) {
        string str = argv[i];
        switch (argv[i][1]) {
        case 'g':
            method = str.erase(0, 3);
            break;
        case 'i':
            strInit = str.erase(0, 3);
            break;
        case 'n':
            count = stoi(str.erase(0, 3));
            break;
        case 'f':
            outFile = str.erase(0, 3);
            break;
        case 'h':
            __help();
            return 0;
        default:
            cout << str << " - неверный параметр \n";
            return 0;
        }
    }

    //Разбиваем вектор инициализации на элементы
    vector <int> init;
    string polynomLFSR = "";
    vector <string> polynomNFSR;
    string num = "";
    for (int i = 0; i <= strInit.length(); i++) {
        if (isdigit(strInit[i]))
            num += strInit[i];
        else if (num != "") {
            if (method == "lfsr" && polynomLFSR.empty())
                polynomLFSR = num;
            else if (method == "nfsr")
                polynomNFSR.push_back(num);
            else
                init.push_back(stoi(num));
            num = "";
        }
    }
    if (method == "lfsr" && polynomLFSR.empty())
        polynomLFSR = "10000000000101101";

    //Генерируем последовательность
    if (method == "lc" && (init.size() == 4 || init.empty()))
        algLC(init, count, outFile);
    else if (method == "add" && (init.empty() || init.size() >= init[2] + 3))
        algADD(init, count, outFile);
    else if (method == "5p" && (init.size() == 5 || init.empty()))
        alg5P(init, count, outFile);
    else if (method == "lfsr" && (init.size() == 1 || init.empty()))
        algLFSR(init, count, outFile, polynomLFSR);
    else if (method == "nfsr" && (polynomNFSR.size() == 3 || polynomNFSR.empty()))
        algNFSR(polynomNFSR, count, outFile);
    else if (method == "rc4" && (init.size() == 256 || init.empty()))
        algRC4(init, count, outFile);
    else if (method == "mt" && (init.size() == 2 || init.empty()))
        algMT(init, count, outFile);
    else if (method == "rsa" && (init.size() == 3 || init.empty()))
        algRSA(init, count, outFile);
    else if (method == "bbs" && (init.size() == 1 || init.empty()))
        algBBS(init, count, outFile);
    else
        cout << "Некорректный алгоритм или его вектор инициализации! \n";

    return 0;
}