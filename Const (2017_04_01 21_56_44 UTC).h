//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Типы поляризаций падающей волны.

#define nPol 2 // Число поляризаций.
#define p_wave_Pol 0 // Поле E лежит в плоскости падения.
#define s_wave_Pol 1 // Поле E перпендикулярно плоскости падения.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Константы типов визуализации.

#define nTypDraw 14 // Количество выводимых параметров.

#define TypDraw_X     0 // Визуализация поля 'Ex' ('p') или 'Hx' ('s').
#define TypDraw_Y     1 // Визуализация поля 'Hy' ('p') или 'Ey' ('s').
#define TypDraw_Z     2 // Визуализация поля 'Ez' ('p') или 'Hz' ('s').
#define TypDraw_Full  3 // Визуализация поля 'E' ('p') или 'H' ('s').
#define TypDraw_SqE   4 // Квадрат амплитуды поля 'E'.
#define TypDraw_SqH   5 // Квадрат амплитуды поля 'H'.
#define TypDraw_FvFc  6 // Векторное произведение 'ExE*' или 'HxH*'.
#define TypDraw_Px    7 // X-я компонента вектора Пойнтинга.
#define TypDraw_Pz    8 // Z-я компонента вектора Пойнтинга.
#define TypDraw_PAbs  9 // Модуль вектора Пойнтинга.
#define TypDraw_DivP  10 // Дивергенция вектора Пойнтинга.
#define TypDraw_EImE2 11 // Распределение мощности потерь 'eps".E^2'.
#define TypDraw_ReEps 12 // Распределение действительной части 'eps'.
#define TypDraw_ImEps 13 // Распределение мнимой части 'eps'.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Число типов нормировок.

#define nTypNorm 10 // Число типов нормировок.

#define typNorm_E     0 // Поле 'E'.
#define typNorm_H     1 // Поле 'H'.
#define typNorm_E2    2 // Квадрат поля 'E'.
#define typNorm_H2    3 // Квадрат поля 'H'.
#define typNorm_FvFc  4 // Векторное произведение 'ExE*' или 'HxH*'.
#define typNorm_Poynt 5 // Компоненты и модуль вектора Пойнтинга.
#define typNorm_EImE2 6 // Распределение мощности потерь 'eps".E^2'.
#define typNorm_ReEps 7 // Действительная часть 'eps'.
#define typNorm_ImEps 8 // Мнимая часть 'eps'.
#define typNorm_AnglDisp 9 // Угловая дисперсия.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Определение типов.

typedef unsigned char BYTE;
typedef unsigned int UINT;
typedef signed char SCHAR;
typedef short int SHRT;
typedef unsigned short int USHRT;
typedef unsigned long U_LONG;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Константы.

#define szNameSubst 64 // Размер строки для названия вещества.
#define laySize_Max 1000 // Максимально допустимый размер слоя по оси x.
#define strL_Path 256 // Длина пути.
#define strL_Txt 256 // Длина вспомогательной строки.

#define MB_EX (MB_OK|MB_ICONEXCLAMATION|MB_APPLMODAL|MB_TOPMOST) // Восклицание.
#define MB_IN (MB_OK|MB_ICONINFORMATION|MB_APPLMODAL|MB_TOPMOST) // Информация.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Макросы.

#define SAFE_DELETE(Obj) { if(Obj!=NULL) { delete Obj; Obj=NULL;}} // Безопасное удаление.
#define SAFE_DELETE_ARR(Arr) { if(Arr!=NULL) { delete[] Arr; Arr=NULL;}} // Безопасное удаление массива.
#define SAFE_DELETE_OBJECT(Obj) { if(Obj!=NULL) { DeleteObject(Obj); Obj=NULL;}} // Безопасное удаление объекта.
#define SAFE_CLOSE(file) { if(file!=NULL) { fclose(file); file=NULL;}} // Безопасное закрытие файла.
#define SAFE_CLOSE_FIND(Handle) { if(Handle!=INVALID_HANDLE_VALUE) { FindClose(Handle); Handle=INVALID_HANDLE_VALUE;}} // Закрытие поиска.
#define MAX(x,y) (x>y?x:y) // Нахождение максимума.
#define MIN(x,y) (x<y?x:y) // Нахождение минимума.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Стандартные цвета.

#define COL_WHITE    RGB(255,255,255)
#define COL_BLACK    RGB(0,0,0)
#define COL_GRAY     RGB(127,127,127)
#define COL_LT_GRAY  RGB(192,192,192)

#define COL_RED      RGB(255,0,0)
#define COL_GREEN    RGB(0,255,0)
#define COL_BLUE     RGB(0,0,255)
#define COL_SKY_BLUE RGB(0,255,255)
#define COL_YELLOW   RGB(255,255,0)
#define COL_VIOLET   RGB(255,0,255)

#define COL_DK_RED      RGB(128,0,0)
#define COL_DK_GREEN    RGB(0,128,0)
#define COL_DK_BLUE     RGB(0,0,128)
#define COL_DK_SKY_BLUE RGB(0,128,128)
#define COL_DK_YELLOW   RGB(128,128,0)
#define COL_DK_VIOLET   RGB(128,0,128)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Постоянные для палитры цветов.

#define nColB 9 // Число основных цветов.
#define nPalStep 200 // Число цветов между основными цветами.
#define nColSmoothPal ((nColB-1)*nPalStep+1) // Число цветов сглаженной палитры.
#define PalPixSize 50 // Толщина окошка для вывода палитры в пикселях.
#define GapSize 15 // Размер щели между распределением и палитрой.
#define TextLen 40 // Длина области для чисел у палитры.
#define ColGap COL_WHITE // Цвет закрашивания щели между распределением и палитрой
#define ColTextBkg COL_WHITE // Цвет фона, на котором рисуются числа.
#define nScls_Pal 3 // Число типов шкал по формату.
#define AmpMin 0.1 // Минимальная амплитуда нормировки для вывода чисел.
#define MajDivWid_Pal 3 // Толщина основных рисок.
#define MinDivWid_Pal 1 // Толщина вспомогательных рисок.
#define MajDivLen_Pal 0.4 // Длина основных основных рисок в о.е. (с обоих сторон).
#define AvDivLen_Pal 0.25 // Длина центральных вспомогательных рисок в о.е. (с обоих сторон).
#define MinDivLen_Pal 0.2 // Длина вспомогательных рисок в о.е. (с обоих сторон).

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Постоянные для шкалы распределения угловой дисперсии.

#define nSclsAnglDisp_Y 1 // Число типов шкал по формату.
#define nSclsAnglDisp_X 1 // Число типов шкал по формату.
#define MajDivWid_Angl 3 // Толщина основных рисок.
#define MinDivWid_Angl 1 // Толщина вспомогательных рисок.
#define MajDivLen_Angl 0.02 // Длина основных основных рисок в о.е. (с обоих сторон).
#define AvDivLen_Angl 0.015 // Длина центральных вспомогательных рисок в о.е. (с обоих сторон).
#define MinDivLen_Angl 0.01 // Длина вспомогательных рисок в о.е. (с обоих сторон).

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Типы изображений DIB.

#define typBmp_24 0 // True Color.
#define typBmp_16 1 // 16 bits.
#define typBmp_8  2 // 8 bits (256 colors).
#define typBmp_4  3 // 4 bits (16 colors).
#define typBmp_1  4 // 1 bits (monochrome image).
#define typBmp_32 5 // 32 bits.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Коды сообщений.

#define messRet   255 // Возврат.
#define messNoMem 254 // Недостаточно памяти.
#define messLrgAr 253 // Большой размер массива.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Разные константы.

#define szMemMax 0xFFFFFFFF // Максимальный размер массива.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Названия файлов.

#define FName_SymbCol_Stand "SymbCol.txt" // Название файла кодировок цветов.
#define FName_DistrLine_X "DistrAlongLine_X.txt" // Название файла распределения физ. величины вдоль линии (по оси X).
#define FName_DistrLine_Z "DistrAlongLine_Z.txt" // Название файла распределения физ. величины вдоль линии (по оси Z).
#define FName_AnglDisp_T "DispAngl.outtad"
#define FName_AnglDisp_R "DispAngl.outrad"
#define FName_AnglDisp_A "DispAngl.outaad" // Название файла угловой дисперсии.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Фундаментальные константы.

#define M_PI 3.1415926535897932384626433832795 // Число "Пи".

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Стандартные амплитуды нормировки.

#define AmpNormE_Stand 2.0F // Амплитуда нормировки распределения поля 'E' по умолчанию.
#define AmpNormH_Stand 2.0F // Амплитуда нормировки распределения поля 'H' по умолчанию.
#define AmpNormE2_Stand 4.0F // Амплитуда нормировки распределения квадрата поля 'E' по умолчанию.
#define AmpNormH2_Stand 4.0F // Амплитуда нормировки распределения квадрата поля 'H' по умолчанию.
#define AmpNormFvFc_Stand 1.0F // Векторное произведение 'ExE*' или 'HxH*'.
#define AmpNormPoynt_Stand 4.0F // Амплитуда нормировки распределения вектора Пойнтинга по умолчанию.
#define AmpNormEImE2_Stand 0.5F // Распределение мощности потерь 'eps".E^2'.
#define AmpNormReEps_Stand 3.0F // Действительная часть 'eps'.
#define AmpNormImEps_Stand 0.1F // Мнимая часть 'eps'.
#define AmpNormAnglDisp_Stand 1.F // Угловая дисперсия.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Различные параметры.

// Цвета закрашивания фона окна.
#define ColBkg COL_BLACK
#define ColBkgErr RGB(100,100,100)

#define numStrFileMin 5 // Минимальный размер списка файлов.
#define flScanf_S 0 // Флаг использования 'scanf_s'.
