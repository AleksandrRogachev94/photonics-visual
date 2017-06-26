#include "resource.h"
#include "Cmplx.h"
#include "Matrix.h"
#include "Cls.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Класс параметров задачи.

class clTask
{
public:

BYTE flPol; // Флаг типа поляризации падающей волны. 0 - p, 1 - s.
int L1,M1; // Число положительных и отрицательных гармоник. 
double wLength,wLen_St,wLen_Fin,dwLen; // Длина валны падающего света.
double Theta,Th_St,Th_Fin,dTh; // Угол падения волны (к нормали).
double dz; // Шаг разбиения слоя.
complex EpsInc,EpsOut; // Диэлектрическая проницаемость сред, откуда падает, и куда уходит свет.

clTask(void); // Конструктор.
BYTE Read(FILE *fp); // Чтение данных из файла.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Структура материала.

struct strMaterial
{
char *name; // Название материала.
char chr; // Символ, используемый при кодировании данного материала.
complex eps; // Диэлектрическая проницаемость данного материала.
int R,G,B; // Компоненты цвета.

strMaterial(void); // Конструктор.
~strMaterial(void); // Деструктор.
BYTE Read(FILE *fp); // Чтение данных о материале из файла.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Класс массива всех материалов, используемых в кристалле (база данных материалов).

class clMaterialAll
{
void Zero(void); // Обнуление переменных.
void Free(void); // Освобождение памяти.

public:

int N; // Размер массива.
struct strMaterial *Mat; // Массив всех материалов.

clMaterialAll(void); // Конструктор.
~clMaterialAll(void); // Деструктор.
BYTE Alloc(int N_); // Выделение памяти для массива.
BYTE IsOK(void) const; // Проверки.
BYTE Read(FILE *fp); // Чтение данных о материалах из файла.
strMaterial *Get(int num); // Получение указателя на структуру материалов.
int GetNum(char chr) const; // Поиск символа материала и возвращение его номера в списке сред.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Cтруктура кодировки цвета одного материала.

struct strSymbCol
{
int R,G,B; // Цвет материала.
char symb; // Символ материала.

strSymbCol(void); // Конструктор.
void Zero(void); // Обнуление переменных.
BYTE Read(FILE *fp); // Чтение кодировки из файла.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Класс кодировки цветов для базы данных материалов.

class clDB_SymbCol
{
void Zero(void); // Обнуление переменных.
void Free(void); // Освобождение памяти.

public:

int N; // Размер массива.
struct strSymbCol *Arr; // Массив всех кодировок.

clDB_SymbCol(void); // Конструктор.
~clDB_SymbCol(void); // Деструктор.
BYTE Alloc(int N_); // Выделение памяти для массива.
BYTE IsOK(void) const; // Проверки.
void Symb_to_RGB(char symb_,BYTE *R_,BYTE *G_,BYTE *B_); // Поиск символа и установка входных R_,G_,B_.
BYTE Read(char *FName_SymbCol); // Чтение кодировок из файла.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Структура одного слоя по оси z фотонного кристалла.

struct strLay
{
int nDiv; // Число разбиений слоя для нахождения распределения полей.
int laySize; // Размер периода по оси x.
double depth; // Толщина слоя в нанометрах.
double dz; // Дискрет деления слоя для нахождения поля внутри слоя.
char *GeomSymbs; // Массив геометрии кристалла в символах материалов.
clRows XDistr,YDistr,ZDistr; // Распределение полей E и H в кристалле.

strLay(void); // Конструктор.
~strLay(void); // Деструктор.
void Zero(void); // Обнуление переменных.
void Free(void); // Освобождение памяти.
BYTE Alloc(int N); // Выделение памяти.
BYTE IsOK(void); // Проверки.
BYTE Read(FILE *fp); // Чтение слоя из файла.
BYTE ReadFieldDistr(FILE *file); // Чтение из файла распределения полей.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Класс фотонного кристалла.

class clCrystal
{
void Zero(void); // Обнуление переменных.

public:

int laysNum; // Число слоев.
double Period; // Период слоя в нанометрах.
struct strLay *Lays; // Массив всех слоев.

clCrystal(void); // Конструктор.
~clCrystal(void); // Деструктор.
void Free(void); // Освобождение памяти.
BYTE Alloc(int laysNum_); // Выделение памяти для массива.
BYTE IsOK(void) const; // Проверки.
BYTE IsOKLay(void) const; // Проверки.
strLay *Get(int num); // Получение указателя на структуру слоя с номером 'num'.
BYTE Read(FILE *fp); // Чтение информации о кристалле из файла.
BYTE ReadFieldDistr(FILE *file); // Чтение распределения поля.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Класс главного окна.

class clMain {

BYTE flTypDraw,flTypNorm,flGrid,TypImage,TypScale,flCompDistr,flCurMouse,flAnglDisp;
int y0; // Начальное положение, с которого начинаем рисовать.
double AmpNormArr[nTypNorm]; // Амплитуды нормировки.
RECT rc,rcCntrl; // Структуры прямоугольников.
BYTE flDistr,flChSizeImg,flDComp; // Флаги: нахождения распределений, изменения размеров окна и заполнения распределения для компонент поля.
double MashtabX,MashtabY; // Масштаб распределений (нм/пикс.) по осям X,Z.
double AnglMashtabX,AnglMashtabY; // Масштаб распределений угловой дисперсии по осям X,Z.
int xSizeD,ySizeD; // Размеры распределений.
int xSizeAnglD,ySizeAnglD; // Размеры распределения угловой дисперсии.
int xSizeDM,ySizeDM; // Размеры распределений с учётом изменения размера окна.
complex *DistrX,*DistrY,*DistrZ; // Комплексные распределения компонент полей.
double *DistrF,*DistrFAbs,*DistrSqE,*DistrSqH; // Распределения компонент полей, модуля и квадрата поля 'E' и 'H'.
double *DistrFvFc; // Распределения 'Im([ExE*])' или 'Im([HxH*])'.
double *DistrPx,*DistrPz,*DistrPAbs,*DistrDivP; // Распределения компонент, модуля и дивергенции вектора Пойнтинга.
double *DistrReEps,*DistrImEps,*DistrE2EpsIm; // Распределение действительной и мнимой части диэлектрической проницаемости и распределение 'eps".E^2'.
clRows AnglDisp; // Угловая дисперсия. Комплексный массив из основной программы.
complex *AnglDispDistr; // Распределение угловой дисперсии по пикселям.
double DepthCryst; // Толщина кристалла (нм).
double cx1,cz1,cx2,cz2; // Координаты границ для вывода распределения вдоль линии в файл.
double DistrStep; // Шаг расчета распределения вдоль линии.
struct strPal PalDistrP,PalDistrN; // Палитры распределения полей (+,-).
HCURSOR cur_wait; // Курсоры.
char *FileName; // Имя открытого файла.

void Zero(void); // Обнуление идентификаторов и указателей.
void Free(void); // Освобождение памяти.
BYTE Alloc(void); // Выделение памяти.
void ZeroDlg(void); // Обнуление объектов для диалогового окна.
void FreeDlg(void); // Удаление объектов для диалогового окна.
void ZeroBrushes(void); // Обнуление кистей для закрашивания окон.
void FreeBrushes(void); // Удаление кистей для закрашивания окон.
BYTE CreateBrushes(void); // Создание кистей для закрашивания окон.
void ZeroFonts(void); // Обнуление шрифтов.
void FreeFonts(void); // Удаление шрифтов.
void CreateFonts(void); // Создание шрифтов.
void InitAmpNorm(void); // Инициализация амплитуд нормировки и указателя на амплитуду нормировки.
void ZeroDistr(void); // Обнуление указателей на распределения.
void FreeDistr(void); // Удаление распределений.
BYTE AllocDistr(int xSizeD_,int ySizeD_); // Выделение памяти для распределений.
BYTE AllocAnglDispDistr(int xSizeD_,int ySizeD_); // Выделение памяти для распределения угловой дисперсии.
void FreeAnglDispDistr(void); // Освобождение памяти для распределения угловой дисперсии.
BYTE IsOK_Distr(void); // Проверка массивов распределений.
BYTE IsOK_DispAngl(void); // Проверка угловой дисперсии.
double *GetDistr(void); // Получение указателя на массив распределения.
BYTE FillDistrComp(void); // Заполнение массива модуля компоненты поля для выбранного типа распределения.
void FreeBmpAll(void); // Освобождение памяти для изображений.
BYTE FillListFiles(void); // Заполнение комбинированного списка именами файлов.
BYTE OpenFile(void); // Открытие файла.
BYTE LoadFile(char *fName); // Загрузка файла и сопутствующие действия.
void CloseFile(void); // Удаление информации.
void DialogInfo(void); // Открытие и закрытие диалогового окна информации о кристалле.
BYTE CreateDlgCntrl(void); // Создание диалогового управляющего окна.
BYTE Command(WPARAM wParam); // Команды.
BYTE CommandCntrl(WPARAM wParam); // Обработка команд окна управления.
BYTE OnChangeTypDraw(void); // Изменение типа рисования.
BYTE OnWriteDistr(void); // Действия при нажатии на клавишу записи распределения вдоль линии в файл.
BYTE CompDistrLine(void); // Нахождение и запись в файл распределения вдоль линии.
void SetTypNorm(void); // Установка типа нормировки.
void OnChTypNorm(BYTE typNorm); // Действия при изменении типа нормировки.
void SetNameValues(void); // Установка имени выводимых величин.
void SetDlgCntrlCombo(void); // Установка значений в combobox-ы.
void SetDlgCntrl(void); // Установка параметров в управляющее окно.
void SetAmpNorm(void); // Установка амплитуды нормировки в окно.
BYTE FindMashtab(int xSize,int ySize); // Определение масштаба.
BYTE FindMashtabAngl(int xSize,int ySize); // Определение масштаба.
void CreateComputeDistrAll_(void); // Установка размера распределения, нахождение масштаба, выделение памяти, расчёт всех распределений и перерисовка окна.
void CreateComputeDistrAll(void); // Установка размера распределения, нахождение масштаба, выделение памяти и расчёт всех распределений.
BYTE CreateComputeAnglDisp(void); // Установка размера распределения углового распределения, нахождение масштаба, расчёт и перерисовка окна.
BYTE CreateDistrAll(void); // Установка размера распределения, нахождение масштаба, выделение памяти для распределений.
BYTE CreateAnglDisp(void); // Установка размера распределения угловой дисперсии, нахождение масштаба.
BYTE ComputeDistrAll(void); // Расчёт всех распределений.
BYTE ComputeDistr(int xSize,int ySize,complex *Distr,BYTE typDistr); // Нахождение массива распределения.
BYTE ComputeDistrEps(int xSize,int ySize,double *DistrRe,double *DistrIm); // Нахождение распределений действительной и мнимой части диэлектрической проницаемости.
BYTE ComputeAnglDispDistr(complex *AnglDispDistr); // Нахождение массива распределения угловой дисперсии.
void DrawDistr_(void); // Рисование распределения полей и палитр.
void DrawAnglDisp_(void); // Рисование угловой дисперсии и палитр.
BYTE DrawAnglDisp(void); // Рисование распределения полей.
BYTE DrawDistr(void); // Рисование распределения полей.
BYTE DrawPal(BYTE fl); // Рисование палитры. fl=0 --> положительная палитра, fl=1 --> полная палитра.
BYTE DrawDistrVoid(void); // Рисование в случае ошибки.
BYTE DrawAnglDispVoid(void); // Рисование в случае ошибки.
BYTE DrawCrystGeom(void); // Рисование геометрии кристалла.
void ChooseDraw(void); // Рисование либо распределения, либо геометрии кристалла.
BYTE OnPaintDistr(HDC hdc); // Рисование в области распределения полей.
BYTE OnPaintDistrDef(HDC hdc); // Закрашивание области рисования распределения полей.
BYTE DrawGrid(HDC hdc,int yShift,int xShift); // Рисование сетки на слоях кристалла.
BYTE DrawScalePal(HDC hdc,int x0,int y0,int dx,int dy,BYTE flPal); // Рисование шкалы на палитре.
BYTE CheckSizeImg(void); // Проверка изменения размеров окна, изменение состояния кнопки перерисовки изображения.
void SetStateBtnRedraw(void); // Установка состояния кнопки перерисовки изображения.
BYTE ReadFile(char *File_Name); // Чтение данных из файла.
BYTE ReadAnglDisp(BYTE fl); // Чтение файла угловой дисперсии.
void OnMouseDistr(LPARAM lParam,BYTE fl); // Действия при перемещении курсора мыши в окне распределения.
void CheckCurPos(void); // Проверка местоположения курсора.
void ClearCoor1(void); // Очистка окон координат.
void ClearCoor2(BYTE fl); // Очистка окон координат.
void ClearVal(void); // Очистка окон величин.
void SetCoorMouse(int cx,int cy,BYTE fl); // Установка координат по местоположению курсора.
BYTE SetValMouse(int cxM,int cyM); // Установка величин по местоположению курсора.

public:

double *pAmpNorm; HWND hwnd,hDlgCntrl; HBRUSH hBrushBkg,hBrushDial; HFONT hFontListLay;
clCrystal Cryst; clTask Task; clMaterialAll Matter; clDB_SymbCol SymbCols; 
clBmpPict *BmpDiag,*BmpAnglDisp,*BmpPalP,*BmpPalPN;

clMain(void); // Конструктор.
~clMain(void); // Деструктор.
BYTE OnCreate(HWND hwnd_); // Дейсвтия в начале работы программы.
LRESULT MsgCommand(UINT msg,WPARAM wParam,LPARAM lParam,BYTE *flag); // Обработка очереди сообщений окна.
LRESULT MsgCommandCntrl(UINT msg,WPARAM wParam,LPARAM lParam,BYTE *flag); // Обработка очереди сообщений окна управления.
BYTE SetDlgInfo(HWND hDlg); // Установка параметров в диалоговое окно.
};
