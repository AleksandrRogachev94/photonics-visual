/*...........................................................................................................

clRowMatr,clRows

...........................................................................................................*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Класс столбца матрицы.

class clRowMatr {

public:
int N; complex *Vect;

clRowMatr(void); // Конструктор.
clRowMatr(const clRowMatr &); // Копирующий конструктор.
~clRowMatr(void); // Деструктор.
BYTE operator =(const clRowMatr &); // Оператор копирования.
void Zero(void); // Обнуление переменных.
void Free(void); // Освобождение памяти.
BYTE Alloc(int N_); // Выделение памяти для массива.
BYTE IsOK(void) const; // Проверки.
BYTE operator =(complex); // Оператор заполнения одинаковым числом.
clRowMatr operator -(); // Знак минус.
clRowMatr &operator +=(clRowMatr const &); // Прибавление столбца.
clRowMatr &operator -=(clRowMatr const &); // Вычитание столбца.
clRowMatr &operator +=(complex); // Прибавление единичной матрицы с множителем 'c'.
clRowMatr &operator -=(complex); // Вычитание единичной матрицы с множителем 'c'.
clRowMatr &operator *=(complex); // Умножение на комплексное число.
clRowMatr &operator /=(complex); // Деление на комплексное число.
clRowMatr &operator *=(double); // Умножение на действительное число.
clRowMatr &operator /=(double); // Деление на действительное число.
BYTE SetZero(void); // Обнуление вектора.
BYTE SetRand(double Lim); // Заполнение случайными числами в пределах Re,Im от -Lim до +Lim.
double GetAbsMax(void); // Получение максимального значения.
double GetNorm(void); // Получение нормы вектора.
BYTE Norm(void); // Нормировка вектора столбца.
BYTE Write(FILE *fp); // Запись столбца в файл.
BYTE Read(FILE *fp); // Чтение столбца из файла.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Операторы и функции для класса столбца.

clRowMatr operator +(const clRowMatr &,const clRowMatr &); // Сложение.
clRowMatr operator -(const clRowMatr &,const clRowMatr &); // Вычитание.
clRowMatr operator *(const clRowMatr &,complex); // Умножение на число.
clRowMatr operator /(const clRowMatr &,complex); // Деление на число.
clRowMatr operator *(complex,const clRowMatr &); // Умножение на число.
clRowMatr operator +(const clRowMatr &RM_,complex c); // Прибавление единичной матрицы с множителем 'c'.
clRowMatr operator +(complex c,const clRowMatr &RM_); // Прибавление единичной матрицы с множителем 'c'.
clRowMatr operator -(const clRowMatr &RM_,complex c); // Вычитание единичной матрицы с множителем 'c'.
clRowMatr operator *(const clRowMatr &,const clRowMatr &); // Умножение диагональных матриц.
clRowMatr operator !(const clRowMatr &); // Обратная диагональная матрица.
clRowMatr conj(clRowMatr const &); // Комплексное сопряжение.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Класс массива столбцов clRowMatr.

class clRows
{
public:

int Nx,Ny; clRowMatr *Rows;

clRows(void); // Конструктор.
clRows(const clRows &); // Копирующий конструктор.
~clRows(void); // Деструктор.
BYTE operator =(const clRows &); // Оператор копирования. 
void Zero(void); // Обнуление переменных.
void Free(void); // Освобождение памяти.
BYTE Alloc(int Nx_,int Ny_); // Выделение памяти для массива.
BYTE IsOK(void) const; // Проверки.
clRowMatr *Get(int num); // Получение указателя на столбец с номером 'num'.
BYTE Write(FILE *fp); // Запись матрицы в файл.
BYTE Read(FILE *fp); // Чтение матрицы из файла.
};