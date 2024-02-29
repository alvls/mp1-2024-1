#include <iostream>

class String
{
private:
    char* data; // указатель на строку
    size_t sz; // размер строки
public:
    String() // конструктор по умолчанию
    {
        sz = 0; // строка пустая, её размер 0
        data = nullptr; // нулевой указатель (не указывает не указывает на какой-либо объект или данные)
    }
    String(const char* str) // конструктор-инициализатор
    {
        sz = mystrlen(str); // размер строки
        data = new char[sz + 1]; // создание новой строки
        mystrcpy(data, str); // копирует из строки по указателю str в строку по указателю data
    }
    String(const String& str_source) // конструктор копирования
    {
        sz = str_source.sz; // тот же размер, что и копируемой строки
        data = new char [sz + 1]; // создание новой  строки
        mystrcpy(data, str_source.data); // копирует из строки по указателю data по ссылке str_source в строку по указателю data (yjde/)
    }
    ~String() // деструктор
    {
        delete[] data; // освобождение памяти
    }
    
    
    void setString(const char* str) // функция, задающая новую строку
    {
        if (str == nullptr)
        {
            delete[] data; // освобождение памяти
            data = nullptr; // установление указателя в nullptr
            sz = 0;
        }
        else
        {
            delete[] data; // освобождение памяти от старой строки
            sz = mystrlen(str); // освобождение памяти от старой строки
            data = new char [sz + 1]; // выделение памяти под новую строку
            mystrcpy(data, str); // копирует из строки по указателю str в строку по указателю data
        }
    }
    
    
    int mystrlen(const char *str) // функция, возвращающий длины строки
    {
        int len = 0;
        while (str[len] != '\0')
            len++;
        return len;
    }
    
    
    void mystrcpy(char* dst, const char* src) // функция, копирующая строку
    {
        int i;
        for (i = 0; src[i] != '\0'; i++)
            dst[i] = src[i];
        dst[i] = src[i];
    }
    
    
    void mystrncpy(char* dst, const char* src, size_t n) // функция, копирующая n символов строки
    {
        int i;
        for (i = 0; i < n && src[i] != '\0'; i++)
            dst[i] = src[i];
        while (i < n) // n больше длины строки src
            dst[i++] = '\0';
    }
    
        
    char SymByInd(size_t ind) // функция, возвращающая символ строки по его индексу
    {
        if ((ind >= 0) && (ind < sz)) // поверка, что индекс находится в пределах размера строки
            return data[ind];
        else
            //throw std::out_of_range("Index out of range"); // или обработка исключения
            std::cout << "Index out of range" << std::endl;
            return '\0'; // или возвращает специальный символ (символ возврата строки)
    }
    
    
    void NewSymByInd(size_t ind, char sym) // функция, изменяющая символ строки по его индексу
    {
        if ((ind >= 0) && (ind < sz)) // проверка, что индекс находится в пределах строки
        {
            data[ind] = sym;
        }
        else
        {
            std::cout << "Index out of range" << std::endl;
        }
    }
    
        
    String subString(size_t pos, size_t len) // функция, возвращающая подстроку из строки
    {
        if ((pos > sz) || (len == 0)) // позиция за пределами строки или длина подстроки равна 0
        {
            std::cout << "Invalid position or length" << std::endl;
            return String(); // возвращаем пустую строку
        }
        if (pos + len > sz) // подстрока выходит за пределы исходной строки
            len = sz - pos; // ограничиваем длину подстроки
        
        char* subStrData = new char[len + 1]; // выделяем память под новую строку
        mystrncpy(subStrData, data + pos, len); // копируем часть длиной len исходной строки по указателю data, сдвинутому на позицию pos для нужного индекса, в новую по указателю subStrData
        subStrData[len] = '\0'; // добавляем нулевой символ в конец новой строки
        String result(subStrData); // создаем конструктором новый объект String  с нужной подстрокой
        delete[] subStrData; // освобождаем выделенную память
        return result;
    }
    
    
    bool isPalindrom() // функция, проверяющая является ли строка палиндромом
    {
        char* left = data; // указатель на начало строки
        char* right = data  + sz - 1; // указатель на конец строки
        while (left < right)
        {
            if (*left != *right) // сравниваем символы, разыменовав оба указателя
                return false; // не совпали символы - не палиндром
            left++;
            right--;
        }
        return true; // все символы совпали - палиндром
    }
    
    
    int countDiffSym() // функция, считающая число разных символов латинского алфавита в строке
    {
        int uniqueChars = 0;
        int charCount[26] = {0}; // массив для подсчета символов
        for (int i = 0; i < sz; i++)
        {
            if ((data[i] >= 'a' && data[i] <= 'z') || (data[i] >= 'A' && data[i] <= 'Z')) // не требуется проверка на другие символы, поскольку коды символов одного алфавита идут друг за другом в таблице кодировки (в одном отрезке), что проверено в условии
            {
                char lowerChar = tolower(data[i]); // преобразуем все символы алфавита в нижний регистр
                int index = lowerChar - 'a'; // высчитываем индекс символа в массиве через позицию символа в таблице ASCII
                if (charCount[index] == 0)
                {
                    uniqueChars++;
                }
                charCount[index]++;
            }
        }
        return uniqueChars;
    }
    
    
    void showString() // функция вывода строки на консоль
    {
        std::cout << data << std::endl;
    }
};

int main(int argc, const char * argv[]) {
    String strOBJ("Hello");
    const char* str1 = "Hello 1"; // const используется чтобы указать, что "Hello 1" - строковый литерал
    // или
    char str2[] = "Hello 2"; // "Hello 2" - строковый литерал, скопированный в массив
    int a = strOBJ.mystrlen(str1);
    int b = strOBJ.mystrlen(str2);
    int sym_count = strOBJ.countDiffSym();
    char symbol = strOBJ.SymByInd(1);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << sym_count << std::endl;
    std::cout << symbol << std::endl;
    std::cout << str2 << std::endl;
    String substr = strOBJ.subString(0, 4);
    substr.showString();
    strOBJ.NewSymByInd(1, 'A');
    strOBJ.showString();
    strOBJ.setString("AbccbA");
    bool is = strOBJ.isPalindrom();
    std::cout << is << std::endl;
    return 0;
}

