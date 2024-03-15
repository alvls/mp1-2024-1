#include <iostream>
#include <stdexcept> // для использования std::out_of_range и std::invalid_argument


class Taylor_Series
{
private:
    int terms; // число членов ряда
    double x; // точка расчета ряда Тейлора
    double (*function)(double); // указатель на функцию
public:
    Taylor_Series () // конструктор по умолчанию
    {
        terms = 1;
        
        function = &my_sin;
    }
    Taylor_Series (int terms_2, double x_2, double (*function_2)(double)) // конструктор-инициализатор
    {
        terms = terms_2;
        if ((x_2 <= 1) && (x_2 >= -1))
            x = x_2;
        else
            throw std::out_of_range("The x value must be between -1 and 1 ");
        function = function_2;
    }
    Taylor_Series (const Taylor_Series& source) // конструктор копирования
    {
        terms = source.terms;
        x = source.x;
        function = source.function;
    }
    ~Taylor_Series() // деструктор
    {
        
    }
    
    
    void setFunction(double (*function_2)(double)) // функция, задающая математическую функцию
    {
        if (function_2 != &my_sin && function_2 != &my_cos && function_2 != &my_exp && function_2 != &my_ln)
            throw std::invalid_argument("Unsupported function");
        function = function_2;
    }
    
    
    double (*getFunction())(double) // функция, возвращающая текущую математическую функцию (как указатель)
    {
        return function;
    }
    
    
    void setTerms(int terms_2) // функция, задающая число членов ряда Тейлора
    {
        if (terms_2 < 0)
            throw std::invalid_argument("Number of terms must be non-negative");
        terms = terms_2;
    }
    
    
    int getTerms() // функция, возвращающая текущее число членов ряда Тейлора
    {
        return terms;
    }
    
    
    void setX(double x_2) // функция, задающая точку x на отрезке [-1,1] - в окрестности 0
    {
        if ((x_2 <= 1) && (x_2 >= -1))
            x = x_2;
        else
            throw std::out_of_range("The x value must be between -1 and 1 ");
    }
    
    
    double getX() // функция, возвращающая точку x
    {
        return x;
    }
    
    
    // В C++ стандартные математические функции не могут быть использованы напрямую как указатели на функции.
    // Поэтому созданы функции-обертки, вызывающие стандартные математические функции.
    // Cтатические функции-члены класса могут быть вызваны без создания экземпляра класса и могут быть использованы как указатели на функции.
    static double my_sin(double x)
    {
        return sin(x);
    }
    static double my_cos(double x)
    {
        return cos(x);
    }
    static double my_exp(double x)
    {
        return exp(x);
    }
    static double my_ln(double x)
    {
        return log(x);
    }
    
    
    void getFormula() // функция, выдающая формулу ряда Тейлора для выбранной функции
    {
        if (function == &my_sin)
            // static_cast<double (*)(double)> нужен для преобразования функции к виду указателя на функцию
            std::cout << "sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ..." << std::endl;
        else if (function == &my_cos)
            std::cout << "cos(x) = 1 - x^2/2! + x^4/4! - x^6/6! + ..." << std::endl;
        else if (function == &my_exp)
            std::cout << "exp(x) = 1 + x + x^2/2! + x^3/3! + ..." << std::endl;
        else if (function == &my_ln) // 'ln(x + 1)' = 'log(x + 1)'
            std::cout << "ln(1 + x) = x - x^2/2! + x^3/3! - x^4/4! + ..." << std::endl;
    }
    
    
    double factorial(int n) // факториал
    {
        double fact = 1;
        for (int i = 1; i <= n; i++)
            fact *= i;
        return fact;
    }
    
    
    double getTermValue(int n) // функция, возвращающая значение заданного члена ряда
    {
        double termValue = 0.0;
        if (function == &my_sin)
            termValue = pow(-1, n) * pow(x, 2*n + 1) / factorial(2*n + 1);
        else if (function == &my_cos)
            termValue = pow(-1, n) * pow(x, 2*n) / factorial(2*n);
        else if (function == &my_exp)
            termValue = pow(x, n) / factorial(n);
        else if (function == &my_ln)
            termValue = pow(-1, n) * pow(x - 1, n + 1) / (n + 1);
            // т.к. ln(1 + x) = x - x^2/2! + x^3/3! - x^4/4! + ...
        return termValue;
    }
    
    
    double calculateSeriesValue() // функция, высчитывающая значение ряда в точке x
    {
        double seriesValue = 0.0;
        for (int n = 0; n < terms; n++)
        {
            seriesValue += getTermValue(n);
        }
        return seriesValue;
    }
    

    void printDeviation() // функция, выводящая отклонение значения ряда в точке x
    {
        double seriesValue = calculateSeriesValue(); // значение ряда в точке x, вычисленное методами класса
        double referenceValue = (*function)(x); // эталонное значение ряда в точке x
        std::cout << "Deviation: " << std::abs(seriesValue - referenceValue) << std::endl;
    }
};


int main(int argc, const char * argv[]) {
    try { // весь код main() заключим в блок try-catch
        Taylor_Series pol;
        pol.getFormula();
        // для передачи в функцию будем статическую член-функцию
        pol.setFunction(Taylor_Series::my_ln);
        double a = pol.getX();
        std::cout << "x = " << a << std::endl;
        pol.setTerms(7);
        pol.setX(0.8);
        std::cout << "x = " << pol.getX() << std::endl;
        double res = pol.calculateSeriesValue();
        std::cout << "res = " << res << std::endl;
        pol.printDeviation();
    } catch (const std::out_of_range& e) { // значение выходит за пределы допустимого диапазона
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) { // аргумент недопустимого типа или значения
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}

