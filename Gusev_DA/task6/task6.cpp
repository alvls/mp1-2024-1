#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <set>
#include <limits>

using namespace std;

#ifdef _WIN32
#include <windows.h>
void clearConsole() {
    system("CLS");
}
#else
void clearConsole() {
    system("clear");
}
#endif

enum CellState {
    EMPTY,
    SHIP,
    HIT,
    MISS
};

class Cell {
public:
    Cell() : state(EMPTY) {} // Конструктор класса Cell, устанавливающий начальное состояние ячейки как EMPTY
    CellState getState() const { return state; } // Метод для получения текущего состояния ячейки
    void setState(CellState newState) { state = newState; } // Метод для установки нового состояния ячейки

private:
    CellState state; // Переменная для хранения состояния ячейки
};

class Ship {
public:
    Ship(int size, vector<pair<int, int>> positions)
        : size(size), positions(positions), hits(0) {} // Конструктор класса Ship, принимающий размер корабля и его позиции

    bool isSunk() const { return hits == size; } // Метод для проверки, потоплен ли корабль
    bool containsPosition(pair<int, int> pos) const { // Метод для проверки, содержится ли позиция в позициях корабля
        return find(positions.begin(), positions.end(), pos) != positions.end();
    }
    void hit() { hits++; } // Метод для увеличения счетчика попаданий

    vector<pair<int, int>> getPositions() const { // Метод для получения позиций корабля
        return positions;
    }

private:
    int size; // Размер корабля
    int hits; // Количество попаданий по кораблю
    vector<pair<int, int>> positions; // Позиции корабля
};

class Board {
public:
    Board() {
        cells = vector<vector<Cell>>(10, vector<Cell>(10)); // Создание доски 10x10 и заполнение ее пустыми ячейками
    }

    bool placeShip(Ship ship) {
        for (const auto& pos : ship.getPositions()) { // Проверка, можно ли разместить корабль на доске
            if (!isValidPosition(pos.first, pos.second) || cells[pos.first][pos.second].getState() != EMPTY) {
                return false;
            }
        }
        for (const auto& pos : ship.getPositions()) { // Размещение корабля на доске
            cells[pos.first][pos.second].setState(SHIP);
        }
        ships.push_back(ship); // Добавление корабля в список кораблей на доске
        return true;
    }

    bool isValidPosition(int row, int col) const { // Метод для проверки, является ли позиция валидной
        if (row < 0 || row >= 10 || col < 0 || col >= 10) return false;
        for (int i = row - 1; i <= row + 1; ++i) {
            for (int j = col - 1; j <= col + 1; ++j) {
                if (i >= 0 && i < 10 && j >= 0 && j < 10 && cells[i][j].getState() == SHIP) {
                    return false;
                }
            }
        }
        return true;
    }

    pair<bool, bool> shoot(int row, int col) {
        if (row < 0 || row >= 10 || col < 0 || col >= 10) return make_pair(false, false);

        Cell& cell = cells[row][col];
        if (cell.getState() == SHIP) { // Проверка, попал ли выстрел по кораблю
            cell.setState(HIT);
            for (auto& ship : ships) {
                if (ship.containsPosition(make_pair(row, col))) {
                    ship.hit();
                    return make_pair(true, ship.isSunk());
                }
            }
        }
        else if (cell.getState() == EMPTY) { // Если попадание было мимо
            cell.setState(MISS);
        }
        return make_pair(false, false);
    }

    void display(bool showShips = false, bool showHitsAndMisses = false, bool hideShips = false) const { // Вывод доски на экран
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                char symbol = '.';
                if (cells[i][j].getState() == SHIP && showShips && !hideShips) { // Отображение кораблей
                    symbol = 'S';
                }
                else if (cells[i][j].getState() == HIT && showHitsAndMisses) { // Отображение попаданий
                    symbol = 'X';
                }
                else if (cells[i][j].getState() == MISS && showHitsAndMisses) { // Отображение промахов
                    symbol = 'O';
                }
                cout << symbol << ' ';
            }
            cout << '\n';
        }
    }

    char getOpponentCellSymbol(int row, int col) const { // Получение символа для ячейки противника
        switch (cells[row][col].getState()) {
        case HIT: return 'X';
        case MISS: return 'O';
        default: return '.';
        }
    }

    bool allShipsSunk() const { // Проверка, все ли корабли на доске потоплены
        for (const auto& ship : ships) {
            if (!ship.isSunk()) return false;
        }
        return true;
    }

private:
    vector<vector<Cell>> cells; // Ячейки доски
    vector<Ship> ships; // Корабли на доске
};

class Player {
public:
    Player(const string& name, bool isComputer = false)
        : name(name), isComputer(isComputer) {}

    void placeShips() { // Размещение кораблей на доске
        if (isComputer) {
            placeShipsRandomly();
        }
        else {
            placeShipsManually();
        }
    }

    pair<int, int> makeMove() { // Сделать ход
        if (isComputer) { // Если игрок - компьютер
            pair<int, int> move;
            do {
                move = make_pair(rand() % 10, rand() % 10);
            } while (shots.find(move) != shots.end()); // Проверка, делался ли уже такой ход
            shots.insert(move); // Добавление сделанного хода в множество сделанных выстрелов
            return move;
        }
        else { // Если игрок - человек
            int row, col;
            do {
                cout << "Введите координаты для выстрела (строка и столбец): ";
                while (!(cin >> row >> col) || row < 1 || row > 10 || col < 1 || col > 10) {
                    cin.clear(); // Очистка флага ошибки ввода
                    cin.ignore(INT_MAX, '\n'); // Очистка буфера ввода
                    cout << "Некорректный ввод. Пожалуйста, введите числа от 1 до 10.\n";
                    cout << "Введите координаты для выстрела (строка и столбец): ";
                }
                row--; // Преобразование индекса строки к внутреннему индексу
                col--; // Преобразование индекса столбца к внутреннему индексу
            } while (shots.find(make_pair(row, col)) != shots.end()); // Проверка, делался ли уже такой ход
            shots.insert(make_pair(row, col)); // Добавление сделанного хода в множество сделанных выстрелов
            return make_pair(row, col);
        }
    }

    const string& getName() const { return name; } // Получение имени игрока
    Board& getOwnBoard() { return ownBoard; } // Получение собственной доски игрока
    Board& getOpponentBoard() { return opponentBoard; } // Получение доски противника

private:
    string name; // Имя игрока
    bool isComputer; // Флаг, является ли игрок компьютером
    Board ownBoard; // Собственная доска игрока
    Board opponentBoard; // Доска противника
    set<pair<int, int>> shots; // Множество сделанных выстрелов

    void placeShipsRandomly() { // Размещение кораблей на доске случайным образом
        vector<int> shipSizes = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
        for (int size : shipSizes) {
            bool placed = false;
            while (!placed) {
                int row = rand() % 10;
                int col = rand() % 10;
                bool horizontal = rand() % 2;
                vector<pair<int, int>> positions;
                bool isValid = true;
                for (int i = 0; i < size; ++i) {
                    int newRow = horizontal ? row : row + i;
                    int newCol = horizontal ? col + i : col;
                    if (!ownBoard.isValidPosition(newRow, newCol)) {
                        isValid = false;
                        break;
                    }
                    positions.push_back(make_pair(newRow, newCol));
                }
                if (!isValid) continue;
                Ship ship(size, positions);
                placed = ownBoard.placeShip(ship);
            }
        }
    }


    void placeShipsManually() { // Размещение кораблей на доске вручную
        vector<int> shipSizes = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
        for (int size : shipSizes) {
            bool placed = false;
            while (!placed) {
                clearConsole();
                cout << "Ваше поле:\n";
                ownBoard.display(true);
                int row, col;
                char orientation;
                cout << "Разместите корабль размером " << size << "\n";
                cout << "Введите начальную координату (строка и столбец) и ориентацию (h/v): ";
                cin >> row >> col >> orientation;
                row--; // Преобразование индекса строки к внутреннему индексу
                col--; // Преобразование индекса столбца к внутреннему индексу
                vector<pair<int, int>> positions;
                bool isValid = true;
                for (int i = 0; i < size; ++i) {
                    if (orientation == 'h') { // Если ориентация горизонтальная
                        if (!ownBoard.isValidPosition(row, col + i)) { // Проверка, можно ли разместить корабль на данной позиции
                            isValid = false;
                            break;
                        }
                        positions.push_back(make_pair(row, col + i));
                    }
                    else { // Если ориентация вертикальная
                        if (!ownBoard.isValidPosition(row + i, col)) { // Проверка, можно ли разместить корабль на данной позиции
                            isValid = false;
                            break;
                        }
                        positions.push_back(make_pair(row + i, col));
                    }
                }
                if (!isValid) {
                    cout << "Некорректное размещение. Попробуйте снова.\n";
                }
                else {
                    Ship ship(size, positions);
                    placed = ownBoard.placeShip(ship);
                    if (placed) {
                        clearConsole();
                        cout << "Ваше поле:\n";
                        ownBoard.display(true);
                    }
                    else {
                        cout << "Некорректное размещение. Попробуйте снова.\n";
                    }
                }
            }
        }
    }
};

class Game {
public:
    Game(Player& player1, Player& player2)
        : player1(player1), player2(player2), currentPlayer(&player1) { // Конструктор класса Game, принимающий двух игроков
        player1.placeShips(); // Размещение кораблей для игрока 1
        player2.placeShips(); // Размещение кораблей для игрока 2
    }

    void play() { // Начало игры
        while (true) {
            clearConsole();
            displayBoards();
            cout << getCurrentPlayer().getName() << " ходит:\n"; // Вывод текущего игрока, который делает ход

            pair<int, int> move = getCurrentPlayer().makeMove(); // Получение хода от текущего игрока
            int row = move.first;
            int col = move.second;

            pair<bool, bool> result = getCurrentOpponent().getOwnBoard().shoot(row, col); // Выстрел по доске противника
            bool hit = result.first;
            bool sunk = result.second;

            if (hit) {
                cout << "Попадание!\n"; // Сообщение о попадании
                getCurrentPlayer().getOpponentBoard().shoot(row, col); // Отметка выстрела на доске противника текущего игрока
                if (sunk) {
                    cout << "Корабль потоплен!\n"; // Сообщение о том, что корабль потоплен
                }
            }
            else {
                cout << "Промах.\n"; // Сообщение о промахе
                getCurrentPlayer().getOpponentBoard().shoot(row, col); // Отметка выстрела на доске противника текущего игрока
                switchPlayer(); // Смена текущего игрока
            }

            if (isGameOver()) { // Проверка, завершилась ли игра
                clearConsole();
                displayBoards();
                cout << "Игра окончена! Победил " << getCurrentPlayer().getName() << "!\n"; // Вывод сообщения о победителе
                break;
            }

            this_thread::sleep_for(chrono::seconds(2)); // Пауза между ходами
        }
    }

private:
    Player& player1; // Игрок 1
    Player& player2; // Игрок 2
    Player* currentPlayer; // Текущий игрок

    Player& getCurrentPlayer() const { // Получение текущего игрока
        return *currentPlayer;
    }

    Player& getCurrentOpponent() const { // Получение противника текущего игрока
        return (currentPlayer == &player1) ? player2 : player1;
    }

    void switchPlayer() { // Смена текущего игрока
        currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
    }

    bool isGameOver() const { // Проверка, завершилась ли игра
        return player1.getOwnBoard().allShipsSunk() || player2.getOwnBoard().allShipsSunk();
    }

    void clearConsole() const { // Очистка консоли
#ifdef _WIN32
        system("CLS");
#else
        system("clear");
#endif
    }

    void displayBoards() const { // Отображение досок игроков
        cout << "Поле " << player1.getName() << ":\n";
        player1.getOwnBoard().display(true, true);
        cout << "\nПоле " << player2.getName() << ":\n";
        player2.getOwnBoard().display(true, true, true);
    }
};

int main() {

#ifdef _WIN32
    system("chcp 1251"); // Установка кодовой страницы Windows-1251 для корректного отображения русских символов
#endif

    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

    Player player1("Игрок 1"); // Создание игрока 1
    Player computer("Компьютер", true); // Создание компьютера
    Game game(player1, computer); // Создание игры между игроком 1 и компьютером
    game.play(); // Начало игры
    system("pause"); // Пауза перед завершением программы
    return 0;
}


