//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Класс комплексных чисел.

class complex {

public:

double re,im;

complex(); // Конструктор.
complex(double re_,double im_); // Конструктор.
complex operator +(); // Знак плюс.
complex operator -(); // Знак минус.
complex operator +=(complex &); // Прибавление комплексного числа.
complex operator -=(complex &); // Вычитание комплексного числа.
complex operator *=(complex &); // Умножение на комплексное число.
complex operator /=(complex &); // Деление на комплексное число.
complex operator =(double); // Присваивание действительного числа.
complex operator *=(double); // Умножение на число.
complex operator /=(double); // Деление на число.
};

complex operator +(complex &,complex &); // Сложение.
complex operator -(complex &,complex &); // Вычитание.
complex operator *(complex &,complex &); // Умножение.
complex operator /(complex &,complex &); // Деление.
complex operator *(complex &,double); // Умножение на число.
complex operator *(double,complex &); // Умножение на число.
complex operator /(complex &,double); // Деление на число.
complex operator /(double,complex &); // Деление на число.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Функции для комплексных чисел.

complex polar(double Abs,double Phase); // Создание комплексного числа по амплитуде и фазе.
complex conj(complex c); // Комплексное сопряжение.
double real(complex c); // Действительная часть.
double imag(complex c); // Мнимая часть.
double absSq(complex c); // Квадрат модуля комплексного числа.
double abs(complex c); // Модуль комплексного числа.
double arg(complex c); // Аргумент комплексного числа.
complex sqrt(complex c); // Квадратный корень.
complex pow(complex c,double p); // Возведение в степень.
complex exp(complex c); // Экспонента.
complex log(complex c); // Логарифм.
complex Inv(complex c); // Обратное число.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Константы.

#define Cmplx_0 complex(0.,0.)
#define Cmplx_1 complex(1.,0.)
#define Cmplx_I complex(0.,1.)
