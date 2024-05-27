#include "Utils.h"

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    HANDLE  handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(handle, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &structCursorInfo);
}

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

void UpdateSettings(int width_, int height_, int max_len_, float snakeSpeed_,
    char snakeSymbol_, char wallSymbol_, char foodSymbol_) {
    int width, height, max_len;
    float snakeSpeed;
    char snakeSymbol, wallSymbol, foodSymbol;

    ifstream in(settings_file);
    if (!in.is_open()) {
        throw "Не удалось открыть файл для чтения настроек игры.";
    }
    in >> width >> height >> max_len >> snakeSpeed >> snakeSymbol >> wallSymbol >> foodSymbol;
    in.close();

    if (width_ != -1) width = width_;
    if (height_ != -1) height = height_;
    if (max_len_ != -1) max_len = max_len_;
    if (snakeSpeed_ != -1.0f) snakeSpeed = snakeSpeed_;
    if (snakeSymbol_ != '\0') snakeSymbol = snakeSymbol_;
    if (wallSymbol_ != '\0') wallSymbol = wallSymbol_;
    if (foodSymbol_ != '\0') foodSymbol = foodSymbol_;

    ofstream out("game_settings.txt");
    if (!out.is_open()) {
        throw "Не удалось открыть файл для записи настроек игры.";
    }
    out << width << ' ' << height << ' ' << max_len << ' ' << snakeSpeed << ' '
        << snakeSymbol << ' ' << wallSymbol << ' ' << foodSymbol;
    out.close();
}

void changeSize() {
    system("cls");
    int w, h;
    cout << "Введите размер поля (ширина >= 10, высота >= 5): ";
    cin >> w >> h;
    while (w < 10 || h < 5) {
        cout << "Размер поля должен быть хотя бы 10x5" << '\n';
        cout << "Введите размер ещё раз: ";
        cin >> w >> h;
    }
    UpdateSettings(w, h);
}

void changeWinSize() {
    system("cls");
    int cnt;
    cout << "Введите количество очков необходимых для победы (>= 5): ";
    cin >> cnt;
    while (cnt < 5) {
        cout << "Количество очков должно быть равно хотя бы 5" << '\n';
        cout << "Введите ещё раз: ";
        cin >> cnt;
    }
    UpdateSettings(-1, -1, cnt);
}

void changeDiff1() {
    UpdateSettings(-1, -1, -1, 0.5);
    cout << "Сложность изменена" << '\n';
    char c = _getch();
}

void changeDiff2() {
    UpdateSettings(-1, -1, -1, 0.35);
    cout << "Сложность изменена" << '\n';
    char c = _getch();
}

void changeDiff3() {
    UpdateSettings(-1, -1, -1, 0.25);
    cout << "Сложность изменена" << '\n';
    char c = _getch();
}

void changeSnakeSymbol() {
    system("cls");
    char c;
    cout << "Введите новый символ для отображения тела змейки: ";
    cin >> c;
    UpdateSettings(-1, -1, -1, -1.0f, c);
}

void changeWallSymbol() {
    system("cls");
    char c;
    cout << "Введите новый символ для отображения стен: ";
    cin >> c;
    UpdateSettings(-1, -1, -1, -1.0f, '\0', c);
}

void changeFoodSymbol() {
    system("cls");
    char c;
    cout << "Введите новый символ для отображения стен: ";
    cin >> c;
    UpdateSettings(-1, -1, -1, -1.0f, '\0', '\0', c);
}


void ResultsTable() {
    system("cls");
    ifstream file(results_file);
    if (!file.is_open()) {
        throw "Не удалось открыть файл для чтения результатов игр";
    }
    cout << "Последние 10 игр" << '\n';
    cout << "Ширина   Высота   Счёт   Время   Результат" << '\n';
    GameResult res;
    while (file >> res.width >> res.height >> res.score >> res.time >> res.isWin) {
        cout << "  " << res.width << "       " << res.height << "      " << res.score <<
            "     " << res.time << "   " << (res.isWin ? "Победа" : "Проигрыш") << '\n';
    }
    file.close();
    while (true) {
        if (_getch() == Esc) {
            break;
        }
    }
}


void writeGameResultToFile(const GameResult& result) {
    ofstream out(results_file, std::ios::app);
    if (out.is_open()) {
        out << result.width << ' ' << result.height << ' ' << result.score << ' ' << result.time << ' ';
        out << (result.isWin ? 1 : 0) << '\n';
    }
    else {
        throw "Не удалось открыть файл для записи результатов игры.";
    }
    out.close();
}

void SetSetting(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw "Не удалось открыть файл для записи настроек игры";
    }
    file << "20 10 144 0.5 O # *";
    file.close();
}

void ClearGameResults(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw "Не удалось открыть файл с результатами игр для обновления";
    }
    vector<GameResult> results;
    GameResult res;
    while (file >> res.width >> res.height >> res.score >> res.time >> res.isWin) {
        results.push_back(res);
    }
    file.close();

    ofstream out(filename);
    if (out.is_open()) {
        if (results.size() > 10) {
            for (int i = results.size() - 10; i < results.size(); i++) {
                out << results[i].width << ' ' << results[i].height << ' ' << results[i].score << ' ' << results[i].time << ' ';
                out << (results[i].isWin ? 1 : 0) << '\n';
            }
        }
        else {
            for (const GameResult& res : results) {
                out << res.width << ' ' << res.height << ' ' << res.score << ' ' << res.time << ' ';
                out << (res.isWin ? 1 : 0) << '\n';
            }
        }
    }
    else {
        throw "Не удалось открыть файл с результатами игр для обновления";
    }
    out.close();
}