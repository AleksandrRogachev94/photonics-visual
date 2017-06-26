/*...........................................................................................................
clBmpPict,clImgMem,strPal

...........................................................................................................*/

#include "Const.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Класс для вывода изображения типа DIB и считывания изображения с экрана.

class clBmpPict {

HDC hdc; HBITMAP hBitmap,hBitmapOld; HFONT hFont;

void Zero(void); // Обнуление указателей и инициализация параметров.
void ZeroDC(void); // Обнуление указателей на старый битовый образ и DC.
void ZeroBmp(void); // Обнуление указателей и инициализация параметров для битового изображения.
void FreeBmp(void); // Освобождение памяти от битового изображения.
BYTE SetPix(int cx,int cy,BYTE *CC); // Рисование пиксела.

public:

BYTE typBmp,*pvBits; int dx,dy; UINT dxB;

clBmpPict(void);
~clBmpPict(void);
BYTE IsOK(void); // Проверки битового изображения и параметров.
BYTE IsOKB(void); // Проверки битового изображения и параметров.
BYTE Clear(void); // Заполнение битового изображения нулевым цветом.
BYTE Clear(COLORREF Col); // Заполнение битового изображения заданным цветом.
HDC GetDC(HDC hdc_); // Создание DC и выбор битового изображения в этом DC.
void FreeDC(void); // Выбор старого битового изображения и уничтожение DC.
void Free(void); // Освобождение памяти.
BYTE Init(int dx_,int dy_,HFONT hFont_); // Задание параметров.
BYTE Image(HDC hdc_,int xi_,int yi_,int dx_,int dy_,BYTE stretch); // Вывод изображения.
BYTE GetImg(HDC hdc_,int xi_,int yi_,int dx_,int dy_); // Получение изображения.
BYTE Save(HANDLE File); // Сохранение изображения в файле '*.bmp'.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Изображение в памяти.

class clImgMem {

HBITMAP hBitmap,hBitmapOld;

void Zero(void); // Обнуление указателей и инициализация параметров.
void Free(void); // Освобождение памяти.
void FreeDC(void); // Удаление 'hdc' из памяти.
void ZeroBmp(void); // Обнуление указателей и инициализация параметров.
void FreeBmp(void); // Удаление битового изображения 'hBitmap' из 'hdc' и из памяти.
BYTE CreateBmp(int dx_,int dy_); // Создание битового изображения 'hBitmap'.
BYTE SelectBmp(void); // Выбор битового образа 'hBitmap' в 'hdc'.
void UnSelectBmp(void); // Удаление битового образа 'hBitmap' из 'hdc'.
BYTE IsOK(void); // Проверка параметров.

public:

HDC hdc; int dx,dy; UINT dxB;

clImgMem(void);
~clImgMem(void);
BYTE Create(HDC hdc_,int dx_,int dy_,HFONT hFont,BYTE mess); // Создание 'hdc' и выбор битового изображения 'hBitmap' в 'hdc'.
BYTE SetPar(HFONT hFont); // Установка параметров в 'hdc' и закрашивание цветом по умолчанию.
BYTE IsOKImg(void); // Проверка параметров и того, что битовое изображение выбрано в 'hdc'.
BYTE SetBitsTrCol(int dx_,int dy_,BYTE *Bits); // Установка бит в формате 'True color'.
BYTE SetBitsGrayCol(int dx_,int dy_,BYTE *Bits); // Установка бит в формате чёрно-серо-белого изображения с 1 байтом на пиксел.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Структура массивов палитры.

struct strPal {

BYTE MasRGB[nColSmoothPal][3];

strPal(void); // Конструктор.
void Zero(void); // Обнуление массива.
BYTE FillColor(DWORD *ColBase); // Нахождение цветов сглаженной палитры.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Структура рисования шкалы на палитре с поределенным интервалом амплитуды нормировки.

struct strParScale {

double ValMin,ValMax; // Максимально и минимально допустимые значения величины.
double Step; // Шаг в физических единицах.
int NumTics; // Число делений между основными.
int NumMinStep; // Шаг по вырисовке чисел на шкале.
char *form; // Формат записи числа у деления.
};