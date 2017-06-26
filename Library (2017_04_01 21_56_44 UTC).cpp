/*
//***************************************************************************************
// Библиотека программ.

// Работа с окнами редактирования.
SetByteEdt,GetByteEdt,SetUSHRT_Edt,GetUSHRT_Edt,SetUINT_Edt,GetUINT_Edt,SetDlEdt,GetDlEdt,
SetChBox,GetChBox,GetPosRadio,

// Получение целых чисел из других типов.
GetBYTE,GetSHRT_Test,GetUSHRT_Test,GetUSHRT_Test,GetUSHRT_Test,GetIntTest,GetIntTest,GetUINT_Test,GetUINT_Test,

// Работа со списками.
ClearList,SelItemList,

// Работа с окнами.
UpdateWindow_,SizeMovWin,CloseWin_,

// Рисование.
CrSelPen,CrSelPen_,UnSelDelPen,CrSelBrush,UnSelDelBrush,
DrawLine_,DrawRect_,ImgRectC,ImgWinC,DrawTri,DrawCross,

// Выделение и освобождение памяти.
AllocString,FreeString,AllocDWORD,FreeDWORD,

// Работа с изображениями.
InitImgBitmap,CreateHeaderBMP,CreateInfoBMP,DeleteInfoBMP,GetColComp,SetColArrRGBQuad,GetSzBmp,GetBitPerPix,
GetTypBMP,WriteDIB_FH,

// Работа со строками.
IsOKStr,StrCopy,StrCat,GetString,DupString,StrSymbConv,

// Работа с файлами и директориями.
WriteFile_,SeekFile,

// Работа с комбинированными списками.
SetSizeCombo,ClearCombo,FillStrCombo,GetSelCombo,SetSelCombo,Fill_CLB_Files,GetTxtStringSelCombo,
FindTxtStringCombo,

// Работа со шрифтами.
GetFontConstWid,SetFont,

// Сообщения.
ErrMessage,Message,Message_

//***************************************************************************************
*/

#include "stdafx.h"

#include "Const.h"
#include "Cmplx.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Программы.

BYTE AllocString(char **Str,size_t ln); // Выделение памяти для строки.
void FreeString(char **Str); // Освобождение памяти для строки.
SHRT GetSHRT_Test(float v); // Получение числа 'SHRT' из числа 'float' с проверкой выхода за пределы 'SHRT'.
USHRT GetUSHRT_Test(int iv); // Получение числа 'USHRT' из числа 'int' с проверкой выхода за пределы 'USHRT'.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Глобальные переменные.

extern HINSTANCE hInst; // Идентификатор приложения.
extern LRESULT LRes; // Вспомогательная переменная.

extern DWORD ColDial; // Цвет фона или диалогового окна.

extern char TxtStr[strL_Txt],TxtMem[strL_Txt]; // Вспомогательные строки.

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Работа с окнами редактирования.

//-----------------------------------------------------------------------------------------------------------
// Установка значения 'BYTE' в окно редактирования.

BYTE SetByteEdt(HWND hDlg,int id,BYTE bV)
{
if(hDlg==NULL) return 1; if(id<=0) return 2; sprintf(TxtStr,"%d",(int)bV);
if(SetDlgItemText(hDlg,id,TxtStr)==FALSE) return 3; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Получение значения 'BYTE' из окна редактирования.

BYTE GetByteEdt(HWND hDlg,int id,BYTE *bV)
{
int iv;

if(hDlg==NULL) return 1; if(bV==NULL) return 2; if(id<=0) return 3;
if(GetDlgItemText(hDlg,id,TxtStr,strL_Txt)==0) { *bV=0; return 4;} if(strlen(TxtStr)==0) { *bV=0; return 5;}
iv=atoi(TxtStr); if(iv<0) iv=0; if(iv>UCHAR_MAX) iv=UCHAR_MAX; *bV=(BYTE)iv; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Установка значения 'USHRT' в окно редактирования.

BYTE SetUSHRT_Edt(HWND hDlg,int id,USHRT Val)
{
if(hDlg==NULL) return 1; if(id<=0) return 2; sprintf(TxtStr,"%d",(int)Val);
if(SetDlgItemText(hDlg,id,TxtStr)==FALSE) return 3; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Получение значения 'USHRT' из окна редактирования.

BYTE GetUSHRT_Edt(HWND hDlg,int id,USHRT *pVal)
{
int iv;

if(hDlg==NULL) return 1; if(pVal==NULL) return 2; if(id<=0) return 3;
if(GetDlgItemText(hDlg,id,TxtStr,strL_Txt)==0) return 4; if(strlen(TxtStr)==0) return 5;
iv=atoi(TxtStr); *pVal=GetUSHRT_Test(iv); return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Установка значения 'UINT' в окно редактирования.

BYTE SetUINT_Edt(HWND hDlg,int id,UINT Val)
{
if(hDlg==NULL) return 1; if(id<=0) return 2; sprintf(TxtStr,"%u",Val);
if(SetDlgItemText(hDlg,id,TxtStr)==FALSE) return 3; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Получение значения 'UINT' из окна редактирования.

BYTE GetUINT_Edt(HWND hDlg,int id,UINT *pVal)
{
int iv;

if(hDlg==NULL) return 1; if(pVal==NULL) return 2; if(id<=0) return 3;
if(GetDlgItemText(hDlg,id,TxtStr,strL_Txt)==0) return 4; if(strlen(TxtStr)==0) return 5;
iv=atoi(TxtStr); if(iv<0) *pVal=0; else *pVal=(UINT)iv; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Установка значения с плавающей точкой в окно редактирования.

BYTE SetDlEdt(HWND hDlg,int id,double Val,char *Form)
{
if(hDlg==NULL) return 1; if(id<=0) return 2; if(Form==NULL) return 3;
if(sprintf(TxtStr,Form,Val)<=0) return 4; if(SetDlgItemText(hDlg,id,TxtStr)==FALSE) return 5; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Получение значения с плавающей точкой из окна редактирования.

BYTE GetDlEdt(HWND hDlg,int id,double *Val)
{
if(hDlg==NULL) return 1; if(Val==NULL) return 2; if(id<=0) return 3;
if(GetDlgItemText(hDlg,id,TxtStr,strL_Txt)==0) *Val=0.0F; else *Val=(double)atof(TxtStr); return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Установка флага в окне.

BYTE SetChBox(HWND hDlg,int id,BYTE flag)
{
int fl; HWND hwnd;

if(hDlg==NULL) return 1; if(id<=0) return 2; hwnd=GetDlgItem(hDlg,id); if(hwnd==NULL) return 3;
if(flag!=0) fl=BST_CHECKED; else fl=BST_UNCHECKED; CheckDlgButton(hDlg,id,fl); return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Получение флага из окна.

BYTE GetChBox(HWND hDlg,int id,BYTE *flag)
{
HWND hwnd;

if(hDlg==NULL) return 1; if(id<=0) return 2; if(flag==NULL) return 3;
hwnd=GetDlgItem(hDlg,id); if(hwnd==NULL) return 4;
if(IsDlgButtonChecked(hDlg,id)==BST_CHECKED) *flag=1; else *flag=0; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Получение положения в наборе переключателей 'Radio Buttons'.

BYTE GetPosRadio(HWND hDlg,int idI,int idF,BYTE *pVar)
{
BYTE k,j,nRB;

if(hDlg==NULL) return 1; if(idI<=0||idF<=0) return 2; if(idF<=idI) return 3;
if(idF-idI+1>UCHAR_MAX) return 4; nRB=(BYTE)(idF-idI+1); if(pVar==NULL) return 5;
j=messRet; for(k=0;k<nRB;k++) if(IsDlgButtonChecked(hDlg,idI+(int)k)==BST_CHECKED) { j=k; break;}
if(j==messRet) return 6; *pVar=j; return 0;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Получение целых чисел из других типов.

//-----------------------------------------------------------------------------------------------------------
// Получение числа 'BYTE' из числа 'float' с проверкой выхода за пределы 'BYTE'.

BYTE GetBYTE(float v)
{
float w;

if(v<=0.0F) return 0; w=v+0.5F; if(w>=(float)UCHAR_MAX) return UCHAR_MAX; return (BYTE)w;
}

//-----------------------------------------------------------------------------------------------------------
// Получение числа 'SHRT' из числа 'float' с проверкой выхода за пределы 'SHRT'.

SHRT GetSHRT_Test(float v)
{
float w;

if(v>=0.0F) w=v+0.5F; else w=v-0.5F;
if(w>=(float)SHRT_MAX) return SHRT_MAX-1; if(w<(float)(SHRT_MIN+1)) return SHRT_MIN+1; return (SHRT)w;
}

//-----------------------------------------------------------------------------------------------------------
// Получение числа 'USHRT' из числа 'int' с проверкой выхода за пределы 'USHRT'.

USHRT GetUSHRT_Test(int iv)
{
if(iv<0) return 0; if(iv>=USHRT_MAX) return USHRT_MAX; return (USHRT)iv;
}

//-----------------------------------------------------------------------------------------------------------
// Получение числа 'USHRT' из числа 'float' с проверкой выхода за пределы 'USHRT'.

USHRT GetUSHRT_Test(float v)
{
float w;

if(v<=0.0F) return 0; w=v+0.5F; if(w>=(float)USHRT_MAX) return USHRT_MAX; return (USHRT)w;
}

//-----------------------------------------------------------------------------------------------------------
// Получение числа 'USHRT' из числа 'double' с проверкой выхода за пределы 'USHRT'.

USHRT GetUSHRT_Test(double d)
{
double w;

if(d<=0.) return 0; w=d+0.5; if(w>=(double)USHRT_MAX) return USHRT_MAX; return (USHRT)w;
}

//-----------------------------------------------------------------------------------------------------------
// Получение числа 'int' из числа 'float' с проверкой выхода за пределы 'int'.

int GetIntTest(float v)
{
float w; int iM;

if(v>=0.0F) w=v+0.5F; else w=v-0.5F; iM=INT_MAX;
if(w>=(float)iM) return iM; if(w<=-(float)iM) return -iM; return (int)w;
}

//-----------------------------------------------------------------------------------------------------------
// Получение числа 'int' из числа 'double' с проверкой выхода за пределы 'int'.

int GetIntTest(double v)
{
double w; int iM;

if(v>=0.0) w=v+0.5; else w=v-0.5; iM=INT_MAX;
if(w>=(double)iM) return iM; if(w<=-(double)iM) return -iM; return (int)w;
}

//-----------------------------------------------------------------------------------------------------------
// Получение числа 'UINT' из числа 'float' с проверкой выхода за пределы 'UINT'.

UINT GetUINT_Test(float v)
{
float w;

if(v<=0.0F) return 0; w=v+0.5F; if(w>=(float)UINT_MAX) return UINT_MAX; return (UINT)w;
}

//-----------------------------------------------------------------------------------------------------------
// Получение числа 'UINT' из числа 'double' с проверкой выхода за пределы 'UINT'.

UINT GetUINT_Test(double d)
{
double w;

if(d<=0.0F) return 0; w=d+0.5F; if(w>=(double)UINT_MAX) return UINT_MAX; return (UINT)w;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Работа со списками.

//-----------------------------------------------------------------------------------------------------------
// Очистка списка.

BYTE ClearList(HWND hDlg,int id)
{
HWND hwnd;

if(hDlg==NULL) return 1; if(id<=0) return 2; hwnd=GetDlgItem(hDlg,id); if(hwnd==NULL) return 3;
SendMessage(hwnd,LB_RESETCONTENT,0,0); return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Установка выделенного элемента в списке.

BYTE SelItemList(HWND hDlg,int id,USHRT num)
{
HWND hwnd;

if(hDlg==NULL) return 1; if(id<=0) return 2; hwnd=GetDlgItem(hDlg,id); if(hwnd==NULL) return 3;
LRes=SendMessage(hwnd,LB_SETCURSEL,0,0); if(LRes==LB_ERR) return 4; return 0;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Работа с окнами.

//-----------------------------------------------------------------------------------------------------------
// Обновление окна.

void UpdateWindow_(HWND hwnd)
{
if(hwnd==NULL) return; InvalidateRect(hwnd,NULL,FALSE); UpdateWindow(hwnd);
}

//-----------------------------------------------------------------------------------------------------------
// Перемещение окна и изменение его размеров.

BYTE SizeMovWin(HWND hwnd,int shX,int shY,int dX,int dY,BYTE flChild)
{
int dx,dy; RECT rc; POINT pt; HWND hwndP;

if(hwnd==NULL) return 1; if(flChild!=0) { hwndP=GetParent(hwnd); if(hwndP==NULL) return 2;}
if(GetWindowRect(hwnd,&rc)==FALSE) return 3; 
pt.x=rc.left; pt.y=rc.top; if(flChild!=0) { if(ScreenToClient(hwndP,&pt)==FALSE) return 4;}
if(dX>0) dx=dX; else dx=(int)(rc.right-rc.left);
if(dY>0) dy=dY; else dy=(int)(rc.bottom-rc.top);
if(MoveWindow(hwnd,(int)pt.x+shX,(int)pt.y+shY,dx,dy,TRUE)==FALSE) return 5; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Закрытие окна.

void CloseWin_(HWND *hwnd)
{
if(hwnd==NULL) return; if(*hwnd==NULL) return; SendMessage(*hwnd,WM_CLOSE,0,0L); *hwnd=NULL;
}

//-----------------------------------------------------------------------------------------------------------
// Ввод и снятие блокировки дочернего окна.

void EnableChWin(HWND hDlg,int id,BYTE flag)
{
BOOL b; HWND hwnd;

if(hDlg==NULL||id<=0) return; hwnd=GetDlgItem(hDlg,id); if(hwnd==NULL) return;
if(flag!=0) b=TRUE; else b=FALSE; EnableWindow(hwnd,b);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Рисование.

//-----------------------------------------------------------------------------------------------------------
// Создание и выбор пера.

BYTE CrSelPen(HDC hdc,HPEN *hPen,HPEN *hPenP,BYTE Wid,DWORD Col)
{
BYTE CrSelPen_(HDC hdc,HPEN *hPen,HPEN *hPenP,int penStyle,BYTE Wid,DWORD Col); // Создание и выбор пера.

return CrSelPen_(hdc,hPen,hPenP,PS_SOLID,Wid,Col);
}

//-----------------------------------------------------------------------------------------------------------
// Создание и выбор пера.

BYTE CrSelPen_(HDC hdc,HPEN *hPen,HPEN *hPenP,int penStyle,BYTE Wid,DWORD Col)
{
BYTE fl;

if(hdc==NULL) return 1;
if(hPen==NULL) return 2; if(*hPen!=NULL) return 3;
if(hPenP==NULL) return 4; if(*hPenP!=NULL) return 5;
if(Wid==0) fl=1; else {
*hPen=CreatePen(penStyle,(int)Wid,(COLORREF)Col);
if(*hPen!=NULL) { fl=0; *hPenP=(HPEN)SelectObject(hdc,*hPen);} else fl=2;}
if(fl!=0) *hPenP=(HPEN)SelectObject(hdc,GetStockObject(NULL_PEN));
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Освобождение и удаление пера.

void UnSelDelPen(HDC hdc,HPEN *hPen,HPEN *hPenP)
{
if(hPenP!=NULL) { if(*hPenP!=NULL&&hdc!=NULL) SelectObject(hdc,*hPenP); *hPenP=NULL;}
if(hPen!=NULL) SAFE_DELETE_OBJECT(*hPen);
}

//-----------------------------------------------------------------------------------------------------------
// Создание и выбор кисти.

BYTE CrSelBrush(HDC hdc,HBRUSH *hBrush,HBRUSH *hBrushP,DWORD Col)
{
if(hdc==NULL) return 1;
if(hBrush==NULL) return 2; if(*hBrush!=NULL) return 3;
if(hBrushP==NULL) return 4; if(*hBrushP!=NULL) return 5;
*hBrush=CreateSolidBrush((COLORREF)Col);
if(*hBrush!=NULL) *hBrushP=(HBRUSH)SelectObject(hdc,*hBrush);
else *hBrushP=(HBRUSH)SelectObject(hdc,GetStockObject(NULL_BRUSH));
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Освобождение и удаление кисти.

void UnSelDelBrush(HDC hdc,HBRUSH *hBrush,HBRUSH *hBrushP)
{
if(hBrushP!=NULL) { if(*hBrushP!=NULL&&hdc!=NULL) SelectObject(hdc,*hBrushP); *hBrushP=NULL;}
if(hBrush!=NULL) SAFE_DELETE_OBJECT(*hBrush);
}

//-----------------------------------------------------------------------------------------------------------
// Рисование линии.

void DrawLine_(HDC hdc,int xI,int yI,int xF,int yF)
{
if(hdc==NULL) return; MoveToEx(hdc,xI,yI,NULL); LineTo(hdc,xF,yF);
}

//-----------------------------------------------------------------------------------------------------------
// Рисование прямоугольника.

BYTE DrawRect_(HDC hdc,RECT *rc)
{
if(hdc==NULL) return 1; if(rc==NULL) return 2;
if(Rectangle(hdc,(int)rc->left,(int)rc->top,(int)rc->right,(int)rc->bottom)==FALSE) return 3; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Закрашивание прямоугольника.

void ImgRectC(HDC hdc,RECT *rc,DWORD ColP,DWORD ColB,BYTE Wid)
{
HBRUSH hBrush,hBrushP; HPEN hPen,hPenP;

if(hdc==NULL||rc==NULL) return;
hBrush=hBrushP=NULL; hPen=hPenP=NULL;
CrSelBrush(hdc,&hBrush,&hBrushP,ColB);
CrSelPen(hdc,&hPen,&hPenP,Wid,ColP);
DrawRect_(hdc,rc);
UnSelDelBrush(hdc,&hBrush,&hBrushP);
UnSelDelPen(hdc,&hPen,&hPenP);
}

//-----------------------------------------------------------------------------------------------------------
// Закрашивание окна.

void ImgWinC(HWND hwnd,DWORD ColP,DWORD ColB)
{
void ImgRectC(HDC hdc,RECT *rc,DWORD ColP,DWORD ColB,BYTE Wid); // Закрашивание прямоугольника.

HDC hdc; RECT rc; PAINTSTRUCT ps;

if(hwnd==NULL) return;
hdc=BeginPaint(hwnd,&ps); if(hdc==NULL) goto end; if(GetClientRect(hwnd,&rc)==FALSE) goto end;
SetMapMode(hdc,MM_TEXT); SetROP2(hdc,R2_COPYPEN); SetBkMode(hdc,TRANSPARENT);
ImgRectC(hdc,&rc,ColP,ColB,1);
end: EndPaint(hwnd,&ps);
}

//-----------------------------------------------------------------------------------------------------------
// Рисование треугольника.

BYTE DrawTri(HDC hdc,RECT *rc,BYTE ax,BYTE dir)
{
BYTE ber; long l; POINT *pP;

if(hdc==NULL) return 1; if(rc==NULL) return 2;
pP=NULL; ber=0;
pP=new POINT[3]; if(pP==NULL) { ber=3; goto end;}
if(ax==0) {
if(dir==0) l=rc->left; else l=rc->right; pP->x=l; pP->y=(rc->top+rc->bottom)/2;
if(dir==0) l=rc->right; else l=rc->left; (pP+1)->x=(pP+2)->x=l; (pP+1)->y=rc->top; (pP+2)->y=rc->bottom;}
else {
if(dir==0) l=rc->top; else l=rc->bottom; pP->y=l; pP->x=(rc->left+rc->right)/2;
if(dir==0) l=rc->bottom; else l=rc->top; (pP+1)->y=(pP+2)->y=l; (pP+1)->x=rc->left; (pP+2)->x=rc->right;}
if(Polygon(hdc,pP,3)==FALSE) { ber=4; goto end;}
end: SAFE_DELETE_ARR(pP); return ber;
}

//-----------------------------------------------------------------------------------------------------------
// Рисование крестика.

void DrawCross(HDC hdc,int xM,int yM,int x,int y,BYTE sz,DWORD Col)
{
BYTE i;

if(hdc==NULL) return; if(xM<=0||yM<=0) return; if(x<0||x>=xM) return; if(y<0||y>=yM) return;
SetPixel(hdc,x,y,Col); if(sz==0) return;
for(i=0;i<sz;i++) {
SetPixel(hdc,x+i,y+i,Col); SetPixel(hdc,x-i,y-i,Col);
SetPixel(hdc,x+i,y-i,Col); SetPixel(hdc,x-i,y+i,Col);}
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Выделение и освобождение памяти.

//-----------------------------------------------------------------------------------------------------------
// Выделение памяти для строки.

BYTE AllocString(char **Str,size_t ln)
{
void FreeString(char **Str); // Освобождение памяти для строки.

if(Str==NULL) return 1; FreeString(Str);
*Str=new char[ln+1]; if(*Str==NULL) return messNoMem; *(*Str+ln)='\0'; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Освобождение памяти для строки.

void FreeString(char **Str)
{
if(Str==NULL) return; SAFE_DELETE_ARR(*Str);
}

//-----------------------------------------------------------------------------------------------------------
// Выделение памяти для массива 'DWORD'.

BYTE AllocDWORD(DWORD **dwpp,size_t ln)
{
void FreeDWORD(DWORD **dwpp); // Освобождение памяти для массива 'DWORD'.

if(dwpp==NULL) return 1; if(ln==0) return 2; FreeDWORD(dwpp);
*dwpp=new DWORD[ln]; if(*dwpp==NULL) return messNoMem; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Освобождение памяти для массива 'DWORD'.

void FreeDWORD(DWORD **dwpp)
{
if(dwpp==NULL) return; SAFE_DELETE_ARR(*dwpp);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Работа с изображениями.

//-----------------------------------------------------------------------------------------------------------
// Создание 'DIB'.

BYTE InitImgBitmap(int dx,int dy,BYTE typBmp,UINT *dxB_,HBITMAP *hBitmap,BYTE **pvBits,DWORD *NCol,SHRT nCol)
{
BYTE GetBitPerPix(BYTE typ,BYTE *BitCount); // Получение числа бит на пиксел.
UINT GetSzBmp(UINT Width,BYTE BitCount); // Получение ширины изображения в байтах с учётом выравнивания по границе, кратной 4 байтам.
BYTE CreateInfoBMP(BITMAPINFO **BMInfo,int dx,int dy,BYTE typBmp,DWORD *NCol,SHRT nCol); // Получение структуры информации для битового изображения.
void DeleteInfoBMP(BITMAPINFO **BMInfo); // Удаление заголовка файла с изображением 'DIB'.

BYTE BitCount,ber; UINT dxB; BITMAPINFO *BMInfo;

if(hBitmap==NULL) return 1; if(dx<=0||dy<=0) return 2; if(dx>SHRT_MAX||dy>SHRT_MAX) return messLrgAr;
if(GetBitPerPix(typBmp,&BitCount)!=0) return 3;
dxB=GetSzBmp((UINT)dx,BitCount); if(dxB==0) return 4;
if((UINT)dxB>szMemMax/(UINT)dy) return messLrgAr;

BMInfo=NULL; ber=0;
if(CreateInfoBMP(&BMInfo,dx,dy,typBmp,NCol,nCol)!=0) { ber=5; goto end;}
*hBitmap=CreateDIBSection(NULL,BMInfo,DIB_RGB_COLORS,(void **)pvBits,NULL,0);
if(*hBitmap==NULL) { ber=messNoMem; goto end;}
if(pvBits!=NULL) { if(*pvBits==NULL) { ber=6; goto end;}}
if(dxB_!=NULL) *dxB_=dxB;

end: DeleteInfoBMP(&BMInfo); return ber;
}

//-----------------------------------------------------------------------------------------------------------
// Создание заголовка файла с изображением 'DIB'.

BYTE CreateHeaderBMP(BITMAPINFOHEADER *Info,int dx,int dy,BYTE typ,SHRT nCol)
{
DWORD Comp,Clr; WORD BitCount;

if(Info==NULL) return 1;
switch(typ) { default: return 2;
// 32 бита.
case typBmp_32: BitCount=32; Clr=0; Comp=BI_RGB; break;
// True Color.
case typBmp_24: BitCount=24; Clr=0; Comp=BI_RGB; break;
// 16 бит.
case typBmp_16: BitCount=16; Clr=3; Comp=BI_BITFIELDS; break;
// 8 бит (256 цветов).
case typBmp_8: BitCount=8; if(nCol<=0||nCol>256) return 3; Clr=nCol; Comp=BI_RGB; break;
// 4 бит (16 цветов).
case typBmp_4: BitCount=4; if(nCol<=0||nCol>16) return 4; Clr=nCol; Comp=BI_RGB; break;
// 1 бит (монохромное изображение).
case typBmp_1: BitCount=1; Clr=2; Comp=BI_RGB; break;}

Info->biBitCount=BitCount; Info->biClrUsed=Clr; Info->biCompression=Comp;
if(typ==typBmp_16) Info->biSizeImage=(DWORD)sizeof(BITMAPINFOHEADER)+Clr*(DWORD)sizeof(RGBQUAD);
else Info->biSizeImage=0L;
Info->biSize=sizeof(BITMAPINFOHEADER);
Info->biWidth=(long)dx; Info->biHeight=(long)dy;
Info->biPlanes=1; Info->biXPelsPerMeter=Info->biYPelsPerMeter=0; Info->biClrImportant=0;
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Получение структуры информации для битового изображения.

BYTE CreateInfoBMP(BITMAPINFO **BMInfo,int dx,int dy,BYTE typBmp,DWORD *NCol,SHRT nCol)
{
BYTE CreateHeaderBMP(BITMAPINFOHEADER *Info,int dx,int dy,BYTE typ,SHRT nCol); // Создание заголовка файла с изображением 'DIB'.
BYTE SetColArrRGBQuad(DWORD *NCol,SHRT nCol,RGBQUAD *RGBCol); // Установка массива цветов.

BYTE i,bm,be,ber; SHRT nRGB_; size_t sizeRGB,len; DWORD dw,*NCol_; BITMAPINFOHEADER *Info;

if(BMInfo==NULL) return 1; if(*BMInfo!=NULL) { free((void *)*BMInfo); *BMInfo=NULL;}
if(dx<=0||dy<=0) return 2;

switch(typBmp) { default: return 3;
// 32 бита.
case typBmp_32: nRGB_=0; break;
// True Color.
case typBmp_24: nRGB_=0; break;
// 16 бит.
case typBmp_16: nRGB_=3; break;
// 8 бит (256 цветов).
case typBmp_8: if(nCol<=0||nCol>256) return 4; if(NCol==NULL) return 5; nRGB_=nCol; break;
// 4 бит (16 цветов).
case typBmp_4: if(nCol<=0||nCol>16) return 6; if(NCol==NULL) return 7; nRGB_=nCol; break;
// 1 бит (монохромное изображение).
case typBmp_1: nRGB_=2; break;}

Info=NULL; NCol_=NULL; ber=0;

Info=new BITMAPINFOHEADER; if(Info==NULL) { ber=5; goto end;}

sizeRGB=sizeof(RGBQUAD);
len=sizeof(BITMAPINFOHEADER); if(nRGB_>0) len+=(size_t)nRGB_*sizeRGB;
*BMInfo=(BITMAPINFO *)malloc(len); if(*BMInfo==NULL) { ber=6; goto end;}

if(CreateHeaderBMP(Info,dx,dy,typBmp,nRGB_)!=0) { ber=7; goto end;}
memcpy((void *)&(*BMInfo)->bmiHeader,(void *)Info,sizeof(BITMAPINFOHEADER));

switch(typBmp) { default: ber=8; goto end;
// 32 бита.
case typBmp_32: break;

// True Color.
case typBmp_24: break;

// 16 бит.
case typBmp_16: bm=31;
for(i=0;i<3;i++) { dw=(DWORD)bm; dw=dw<<((2-i)*5);
memcpy((void *)&(*BMInfo)->bmiColors[i],(void *)&dw,sizeRGB);} break;

// 8 бит (256 цветов) и 4 бита (16 цветов).
case typBmp_8: case typBmp_4:
if(SetColArrRGBQuad(NCol,nRGB_,(*BMInfo)->bmiColors)!=0) { ber=9; goto end;} break;

// 1 бит (монохромное изображение).
case typBmp_1:
if(AllocDWORD(&NCol_,2)!=0) { ber=10; goto end;}
NCol_[0]=COL_BLACK; NCol_[1]=COL_WHITE;
be=SetColArrRGBQuad(NCol_,2,(*BMInfo)->bmiColors); if(be!=0) { ber=11; goto end;}
FreeDWORD(&NCol_); break;}

end: SAFE_DELETE(Info); FreeDWORD(&NCol_); return ber;
}

//-----------------------------------------------------------------------------------------------------------
// Удаление заголовка файла с изображением 'DIB'.

void DeleteInfoBMP(BITMAPINFO **BMInfo)
{
if(BMInfo==NULL) return; if(*BMInfo!=NULL) { free((void *)*BMInfo); *BMInfo=NULL;}
}

//-----------------------------------------------------------------------------------------------------------
// Получение компонент цвета.

BYTE GetColComp(COLORREF Col,BYTE *CC)
{
if(CC==NULL) return 1; CC[0]=GetRValue(Col); CC[1]=GetGValue(Col); CC[2]=GetBValue(Col); return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Установка массива цветов.

BYTE SetColArrRGBQuad(DWORD *NCol,SHRT nCol,RGBQUAD *RGBCol)
{
SHRT i; DWORD Col; RGBQUAD *rgb;

if(NCol==NULL) return 1; if(nCol<=0) return 2; if(RGBCol==NULL) return 3;
for(i=0;i<nCol;i++) { Col=NCol[i]; rgb=RGBCol+i; rgb->rgbReserved=0;
rgb->rgbRed=GetRValue(Col); rgb->rgbGreen=GetGValue(Col); rgb->rgbBlue=GetBValue(Col);} return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Получение ширины изображения в байтах с учётом выравнивания по границе, кратной 4 байтам.

UINT GetSzBmp(UINT Width,BYTE BitCount)
{
if(BitCount==0) return 0; if(Width>(UINT_MAX-31)/BitCount) return 0;
return (((Width*(UINT)BitCount)+31)&~31)>>3;
}

//-----------------------------------------------------------------------------------------------------------
// Получение числа бит на пиксел.

BYTE GetBitPerPix(BYTE typ,BYTE *BitCount)
{
if(BitCount==NULL) return 1;

switch(typ) { default: return 2;
case typBmp_32: *BitCount=32; break; // 32 бита.
case typBmp_24: *BitCount=24; break; // True Color.
case typBmp_16: *BitCount=16; break; // 16 бит.
case typBmp_8: *BitCount=8; break; // 8 бит (256 цветов).
case typBmp_4: *BitCount=4; break; // 4 бит (16 цветов).
case typBmp_1: *BitCount=1; break; // 1 бит (монохромное изображение).
}

return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Получение типа битового изображения.

BYTE GetTypBMP(BYTE *typ,BYTE BitCount)
{
if(typ==NULL) return 1;
switch(BitCount) { default: return 2;
case 1: *typ=typBmp_1; break;
case 4: *typ=typBmp_4; break;
case 8: *typ=typBmp_8; break;
case 16: *typ=typBmp_16; break;
case 24: *typ=typBmp_24; break;
case 32: *typ=typBmp_32; break;}
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Запись изображения 'DIB' в файл.

BYTE WriteDIB_FH(HANDLE File,DWORD *szFile,BYTE Bpp,int dx,int dy,BYTE *BytesDIB,DWORD *NCol,SHRT nCol)
{
BYTE GetTypBMP(BYTE *typ,BYTE BitCount); // Получение типа битового изображения.
UINT GetSzBmp(UINT Width,BYTE BitCount); // Получение ширины изображения в байтах с учётом выравнивания по границе, кратной 4 байтам.
BYTE CreateHeaderBMP(BITMAPINFOHEADER *Info,int dx,int dy,BYTE typ,SHRT nCol); // Создание заголовка файла с изображением 'DIB'.
long SeekFile(HANDLE File,long offs,DWORD MoveMethod); // Позиционирование внутри файла.
BYTE WriteFile_(HANDLE File,LPVOID Buf,DWORD len); // Запись в файл.

BYTE typBmp,bm,ber; SHRT i; UINT dxB; DWORD lon,len,dw,Col; long offs,offsI; BITMAPFILEHEADER *Header;
BITMAPINFOHEADER *Info; RGBQUAD rgb;

if(File==INVALID_HANDLE_VALUE) return 1; if(dx<=0||dy<=0) return 2; if(BytesDIB==NULL) return 3;
if(GetTypBMP(&typBmp,Bpp*8)!=0) return 4;
if(typBmp==typBmp_8) { if(NCol==NULL) return 5; if(nCol<=0||nCol>256) return 6;}
dxB=GetSzBmp((UINT)dx,8*Bpp); if(dxB==0) return 7;

offsI=SeekFile(File,0L,FILE_CURRENT); if(offsI<0) return 8;

Info=NULL; Header=NULL; ber=0;
Info=new BITMAPINFOHEADER; if(Info==NULL) { ber=9; goto end;}
Header=new BITMAPFILEHEADER; if(Header==NULL) { ber=10; goto end;}

if(CreateHeaderBMP(Info,dx,dy,typBmp,nCol)!=0) { ber=11; goto end;}

Header->bfType='M'*256+'B'; Header->bfReserved1=Header->bfReserved2=0;
Header->bfOffBits=(DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+
(DWORD)sizeof(DWORD)*(DWORD)Info->biClrUsed;

len=(DWORD)dxB*(DWORD)dy;
Header->bfSize=Header->bfOffBits+len;

lon=(DWORD)sizeof(BITMAPFILEHEADER); if(WriteFile_(File,(LPVOID)Header,lon)!=0) { ber=12; goto end;}
if(szFile!=NULL) *szFile+=lon;
lon=(DWORD)sizeof(BITMAPINFOHEADER); if(WriteFile_(File,(LPVOID)Info,lon)!=0) { ber=13; goto end;}
if(szFile!=NULL) *szFile+=lon;

switch(typBmp) { default: break;
// 8 бит.
case typBmp_8: rgb.rgbReserved=0; lon=(DWORD)sizeof(rgb);
for(i=0;i<nCol;i++) { Col=NCol[i];
rgb.rgbRed=GetRValue(Col); rgb.rgbBlue=GetBValue(Col); rgb.rgbGreen=GetGValue(Col);
if(WriteFile_(File,(LPVOID)&rgb,lon)!=0) { ber=14; goto end;}
if(szFile!=NULL) *szFile+=lon;} break;

// 16 бит.
case typBmp_16: lon=(DWORD)sizeof(DWORD); bm=31;
for(i=0;i<3;i++) { dw=(DWORD)bm; dw=dw<<((2-i)*5);
if(WriteFile_(File,(LPVOID)&dw,lon)!=0) { ber=15; goto end;}
if(szFile!=NULL) *szFile+=lon;} break;}

offs=SeekFile(File,offsI+(long)Header->bfOffBits,FILE_BEGIN); if(offs<0) { ber=16; goto end;}
lon=len; if(WriteFile_(File,(LPVOID)BytesDIB,lon)!=0) { ber=17; goto end;}
if(szFile!=NULL) *szFile+=lon;

end: SAFE_DELETE(Info); SAFE_DELETE(Header); return ber;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Работа со строками.

//-----------------------------------------------------------------------------------------------------------
// Проверка строки.

BYTE IsOKStr(char *str)
{
if(str==NULL) return 1; if(strlen(str)==0) return 2; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Копирование строк.

BYTE StrCopy(char *Dst,size_t lnDst,char *Src)
{
size_t i,lnS;

if(Dst==NULL) return 1; if(lnDst==0) return 2; if(Src==NULL) return 3; lnS=strlen(Src); if(lnS>=lnDst) return 4;
if(lnS>0) for(i=0;i<lnS;i++) Dst[i]=Src[i]; Dst[lnS]='\0'; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Объединение строк.

BYTE StrCat(char *Dst,size_t lnDst,char *Src)
{
size_t i,lnD,lnS;

if(Dst==NULL) return 1; if(lnDst==0) return 2; if(Src==NULL) return 0;
lnS=strlen(Src); if(lnS==0) return 0; lnD=strlen(Dst); if(lnS+lnD>=lnDst) return 3;
for(i=0;i<lnS;i++) Dst[i+lnD]=Src[i]; Dst[lnS+lnD]='\0'; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Сборка строки из нескольких строк.

BYTE GetString(char **String,char **Items,BYTE n)
{
BYTE i; size_t ln,lns;

if(String==NULL) return 1; if(Items==NULL) return 2; if(n==0) return 3; lns=0;
for(i=0;i<n;i++) { if(Items[i]==NULL) continue; ln=strlen(Items[i]); if(szMemMax-ln<lns) return 4; lns+=ln;}
if(AllocString(String,lns)!=0) return 5; lns++; if(StrCopy(*String,lns,"")!=0) return 6;
for(i=0;i<n;i++) { if(Items[i]==NULL) continue; if(StrCat(*String,lns,Items[i])!=0) return 7;} return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Выделение памяти для строки и копирование.

BYTE DupString(char **Str,char *Src)
{
size_t ln;

if(Str==NULL) return 1; FreeString(Str); if(Src==NULL) return 2; ln=strlen(Src); if(ln==0) return 3;
if(AllocString(Str,ln)!=0) return 4; if(StrCopy(*Str,ln+1,Src)!=0) return 5; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Преобразование символов строки в большие или малые символы.

BYTE StrSymbConv(char *StrI,char *StrC,size_t szStrC,BYTE flag)
{
char sh,*c,*cC; SCHAR s; size_t i,sz;

if(StrI==NULL) return 1; sz=strlen(StrI); if(sz==0) return 2; if(StrC==NULL) return 3;
if(szStrC==0) return 4; if(sz+1>szStrC) return 5;
sh='A'-'a';
for(i=0;i<sz;i++) { c=StrI+i; cC=StrC+i; s=0;
if(flag!=0) { if(*c>='a'&&*c<='z') s=1;} else { if(*c>='A'&&*c<='Z') s=-1;}
if(s==0) *cC=*c; else if(s>0) *cC=char((SHRT)*c+(SHRT)sh); else *cC=char((SHRT)*c-(SHRT)sh);}
StrC[sz]='\0'; return 0;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Работа с файлами и директориями.

//-----------------------------------------------------------------------------------------------------------
// Запись в файл.

BYTE WriteFile_(HANDLE File,LPVOID Buf,DWORD len)
{
void ErrMessage(void); // Выдача сообщения об ошибке.

BOOL flag; DWORD lenW;

if(File==INVALID_HANDLE_VALUE) return 1; flag=WriteFile(File,Buf,len,&lenW,NULL);
if(flag==FALSE) { ErrMessage(); return 2;} if(flag!=FALSE&&lenW!=len) return 3; return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define Err_File 0xFFFFFFFF
//-----------------------------------------------------------------------------------------------------------
// Позиционирование внутри файла.

long SeekFile(HANDLE File,long offs,DWORD MoveMethod)
{
long Low,High; 

if(File==INVALID_HANDLE_VALUE) return -1; Low=offs; High=0L;
Low=SetFilePointer(File,Low,&High,MoveMethod); if(Low==(long)Err_File) return -2;
if(High!=0L) return -3; return Low;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Работа с комбинированными списками.

//-----------------------------------------------------------------------------------------------------------
// Получение числа строк в комбинированном списке.

BYTE GetNumStrCombo(HWND hDlg,int id,BYTE *num)
{
HWND hwnd;

if(hDlg==NULL) return 1; if(id<=0) return 2; if(num==NULL) return 3;
hwnd=GetDlgItem(hDlg,id); if(hwnd==NULL) return 4;
LRes=SendMessage(hwnd,CB_GETCOUNT,0,0L); if(LRes==CB_ERR) return 5; if(LRes>UCHAR_MAX) return 6;
*num=(BYTE)LRes; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Установка размера комбинированного списка по числу строк.

BYTE SetSizeCombo(HWND hDlg,int id,BYTE num)
{
BYTE SizeMovWin(HWND hwnd,int shX,int shY,int dX,int dY,BYTE flChild); // Перемещение окна и изменение его размеров.

SHRT Hei; HWND hwnd; RECT rc;

if(hDlg==NULL) return 1; if(id<=0) return 2; if(num==0) return 3;
hwnd=GetDlgItem(hDlg,id); if(hwnd==NULL) return 4;
if(GetWindowRect(hwnd,&rc)==FALSE) return 5;
Hei=(SHRT)(rc.bottom-rc.top);
LRes=SendMessage(hwnd,CB_GETITEMHEIGHT,0,0L); if(LRes!=CB_ERR) Hei+=((SHRT)LRes+1)*(SHRT)num;
if(SizeMovWin(hwnd,0,0,0,(int)Hei,1)!=0) return 6; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Очистка комбинированного списка.

BYTE ClearCombo(HWND hDlg,UINT id)
{
HWND hwnd;

if(hDlg==NULL) return 1; if(id<=0) return 2; hwnd=GetDlgItem(hDlg,id); if(hwnd==NULL) return 3;
if(SendMessage(hwnd,CB_RESETCONTENT,0,0)==CB_ERR) return 4; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Заполнение комбинированного списка.

BYTE FillStrCombo(HWND hDlg,UINT id,UINT *IDSArr,BYTE nArr,BYTE nSel)
{
BYTE SetSizeCombo(HWND hDlg,int id,BYTE num); // Установка размера комбинированного списка по числу строк.

BYTE i; char *cp; HWND hwnd;

if(hDlg==NULL) return 1; if(id==0) return 2; if(IDSArr==NULL) return 3; if(nArr==NULL) return 4;
if(hInst==NULL) return 5; hwnd=GetDlgItem(hDlg,id); if(hwnd==NULL) return 6;
SetSizeCombo(hDlg,(int)id,nArr);
for(i=0;i<nArr;i++) { if(LoadString(hInst,IDSArr[i],TxtStr,strL_Txt)!=0) cp=TxtStr; else cp="-";
SendMessage(hwnd,CB_ADDSTRING,0,(LPARAM)(LPSTR)TxtStr);
}
if(nSel<nArr) SendMessage(hwnd,CB_SETCURSEL,nSel,0); 
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Получение номера выбранной строки в комбинированном списке.

BYTE GetSelCombo(HWND hDlg,UINT id,BYTE *num)
{
HWND hwnd;

if(hDlg==NULL) return 1; if(id==0) return 2; if(num==NULL) return 3;
hwnd=GetDlgItem(hDlg,id); if(hwnd==NULL) return 4;
LRes=SendMessage(hwnd,CB_GETCURSEL,0,0L); if(LRes==CB_ERR) return 5; if(LRes>UCHAR_MAX) return 6;
*num=(BYTE)LRes; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Установка номера строки в комбинированном списке.

BYTE SetSelCombo(HWND hDlg,UINT id,BYTE num)
{
HWND hwnd;

if(hDlg==NULL) return 1; if(id==0) return 2; hwnd=GetDlgItem(hDlg,id); if(hwnd==NULL) return 3;
SendMessage(hwnd,CB_SETCURSEL,(WPARAM)num,0L); return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Заполнение списка (Combo/0 или List/!=0- boxes) именами файлов.

BYTE Fill_CLB_Files(HWND hDlg,int id,BYTE typCLB,char *Path,char *Dir,char *Ext,BYTE flExt)
{
BYTE IsOKStr(char *Str); // Проверка строки.

BYTE bFin,ber; UINT msg; HWND hwnd; HANDLE hSearch; char *cp,*cpv,*Items[4]; WIN32_FIND_DATA *FileData;

if(hDlg==NULL) return 1; if(id<=0) return 2; hwnd=GetDlgItem(hDlg,id); if(hwnd==NULL) return 3;
if(IsOKStr(Ext)!=0) return 4;
if(typCLB==0) msg=CB_RESETCONTENT; else msg=LB_RESETCONTENT; SendMessage(hwnd,msg,0,0);
if(typCLB==0) msg=CB_ADDSTRING; else msg=LB_ADDSTRING;

hSearch=INVALID_HANDLE_VALUE; cp=NULL; FileData=NULL; ber=0;

FileData=new WIN32_FIND_DATA; if(FileData==NULL) { ber=5; goto end;}
Items[0]=Path; Items[1]=Dir; Items[2]="*"; Items[3]=Ext;
if(GetString(&cp,Items,4)!=0) { ber=4; goto end;}
hSearch=(HANDLE)FindFirstFile((LPCTSTR)cp,FileData); if(hSearch==INVALID_HANDLE_VALUE) { ber=messRet; goto end;}
bFin=0; while(bFin==0) {
if((FileData->dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)==0L) {
if(flExt==0) { cpv=strchr(FileData->cFileName,'.'); if(cpv!=NULL) *cpv='\0';}
SendMessage(hwnd,msg,0,(LPARAM)(LPSTR)FileData->cFileName);
}
if(!FindNextFile(hSearch,FileData)) bFin=1;}

end: SAFE_CLOSE_FIND(hSearch); FreeString(&cp); SAFE_DELETE(FileData); return ber;
}

//-----------------------------------------------------------------------------------------------------------
// Получение выбранной строки в списке.

BYTE GetTxtStringSelCombo(HWND hDlg,int id,char *Str,USHRT nStr)
{
USHRT num; HWND hwnd;

if(hDlg==NULL) return 1; if(id<=0) return 2; if(Str==NULL) return 3; if(nStr==0) return 4;
hwnd=GetDlgItem(hDlg,id); if(hwnd==NULL) return 5;
LRes=SendMessage(hwnd,CB_GETCURSEL,0,0L); if(LRes==CB_ERR) return messRet; if(LRes>USHRT_MAX) return 6; num=(USHRT)LRes;
LRes=SendMessage(hwnd,CB_GETLBTEXTLEN,num,0L); if(LRes==CB_ERR) return 7; if(LRes>nStr) return 8;
LRes=SendMessage(hwnd,CB_GETLBTEXT,num,(LPARAM)(LPTSTR)Str); if(LRes==CB_ERR) return 9; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Нахождение строки в списке.

BYTE FindTxtStringCombo(HWND hDlg,int id,char *Str,BYTE *num)
{
HWND hwnd;

if(hDlg==NULL) return 1; if(id<=0) return 2; if(Str==NULL) return 3; if(num==NULL) return 4;
hwnd=GetDlgItem(hDlg,id); if(hwnd==NULL) return 5;
LRes=SendMessage(hwnd,CB_FINDSTRINGEXACT,0,(LPARAM)(LPCSTR)Str); if(LRes==CB_ERR) return 6;
if(LRes>UCHAR_MAX) return 7; *num=(BYTE)LRes; return 0;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Работа со шрифтами.

//-----------------------------------------------------------------------------------------------------------
// Загрузка шрифта.

HFONT GetFontConstWid(char *nameFont,SHRT Wid,SHRT Hei)
{
if(nameFont==NULL) return NULL;
return CreateFont((int)Hei,(int)Wid,0,0,FW_THIN|FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_RASTER_PRECIS,
CLIP_DEFAULT_PRECIS,PROOF_QUALITY,FIXED_PITCH|FF_MODERN,nameFont);
}

//-----------------------------------------------------------------------------------------------------------
// Установка шрифта в окне.

BYTE SetFont(HWND hwnd,HFONT hFont)
{
if(hwnd==NULL) return 1; if(hFont==NULL) return 2;
SendMessage(hwnd,WM_SETFONT,(WPARAM)hFont,(LPARAM)MAKELONG((WORD)TRUE,0)); return 0;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Сообщения.

//-----------------------------------------------------------------------------------------------------------
// Выдача сообщения об ошибке.

void ErrMessage(void)
{
LPVOID lpMsgBuf;

FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
NULL,GetLastError(),MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),(LPTSTR)&lpMsgBuf,0,NULL);
MessageBox(NULL,(LPCTSTR)lpMsgBuf,"Error",MB_IN); LocalFree(lpMsgBuf);
}

//-----------------------------------------------------------------------------------------------------------
// Вывод сообщения.

void Message(UINT StrID,UINT typ)
{
if(hInst==NULL) return; if(LoadString(hInst,StrID,TxtMem,strL_Txt)==0) return; MessageBox(NULL,TxtMem,"",typ);
}

//-----------------------------------------------------------------------------------------------------------
// Вывод сообщения.

void Message_(HWND hwnd,UINT StrID,char *txt,UINT typ)
{
if(hInst==NULL) return; if(LoadString(hInst,StrID,TxtMem,strL_Txt)==0) return;
if(txt!=NULL) MessageBox(hwnd,txt,TxtMem,typ); else MessageBox(hwnd,TxtMem,"",typ);
}
/*
//-----------------------------------------------------------------------------------------------------------
// Рисование шкалы. flDir=0 - вверх. flSign=0 - '+'.

BYTE DrawScale(HDC hdc,int x0,int y0,int dx,int dy,BYTE flDir,BYTE flSign,BYTE flShift0,double AmpNorm)
{
BYTE CrSelPen_(HDC hdc,HPEN *hPen,HPEN *hPenP,int penStyle,BYTE Wid,DWORD Col); // Создание и выбор пера.
void UnSelDelPen(HDC hdc,HPEN *hPen,HPEN *hPenP); // Освобождение и удаление пера.
void DrawLine_(HDC hdc,int xI,int yI,int xF,int yF); // Рисование линии.

BYTE i; int k,l,MajLen,MinLen,AvLen,x1_maj,x1_min,x1_Av,x2_maj,x2_min,x2_Av;
double yPosPhys,PhysStep,yPos,PixStep,PixStepTics; HPEN hPenMaj,hPenMin; HFONT font; RECT rc;
HGDIOBJ old; struct strParScale *ParScl;

if(flDir<0||flDir>1) return 1; if(flSign<0||flSign>1) return 2; if(hdc==NULL) return 3;
if(flShift0<0||flShift0>1) return 4; if(x0<0||y0<0||dx<0||dy<0) return 5;

// Проверки.
if(AmpNorm<AmpMin) return 6;  if(AmpNorm>ParScaleArr[nScls-1].AmpMax) return 7;

// Нахождение нужного типа вывода шкалы.
ParScl=NULL;
for(i=0;i<nScls;i++) if(AmpNorm<ParScaleArr[i].AmpMax) { ParScl=&ParScaleArr[i]; break;}
if(ParScl==NULL) return 8;

if(SetBkMode(hdc,OPAQUE)==0) return 9; if(SetBkColor(hdc,COL_WHITE)==CLR_INVALID) return 10;
font=CreateFont(-16,0,0,0,0,ANSI_CHARSET,0U,0U,0U,0U,0U,0U,0U,TEXT("Arial")); // Создание Фонта.
old=SelectObject(hdc,font); // Выбор фонта.

// Создание перьев основных рисок и вспомогательных рисок.
hPenMaj=hPenMin=NULL;
hPenMaj=CreatePen(PS_SOLID,(int)MajDivWid_Pal,COL_BLACK); hPenMin=CreatePen(PS_SOLID,(int)MinDivWid_Pal,COL_BLACK);
if(hPenMaj==NULL||hPenMin==NULL) return 11;

// Рисование всех рисок и чисел.
PixStep=(double)dy/(AmpNorm/ParScl->Step); PixStepTics=(double)PixStep/(ParScl->NumTics+1);
yPosPhys=0.; PhysStep=ParScl->Step; if(flSign==1) PhysStep*=-1.;
MajLen=int(PalPixSize*MajDivLen_Pal); MinLen=int(PalPixSize*MinDivLen_Pal); AvLen=int(PalPixSize*AvDivLen_Pal);
//aaa
// Вверх.
if(flDir==0) { yPos=y0+dy; k=0; l=0; while(yPos>=y0-1) {
for(i=0;i<2;i++) { if(i==0) { x1_maj=x1_min=x1_Av=x0; x2_maj=x0+MajLen; x2_min=x0+MinLen; x2_Av=x0+AvLen;}
if(i==1) { x2_maj=x2_min=x2_Av=x0+dx; x1_maj=x0+dx-MajLen; x1_min=x0+dx-MinLen; x1_Av=x0+dx-AvLen;}
if(k==ParScl->NumTics+1) { yPos+=k*PixStepTics; yPos-=PixStep; k=0;}
if(k==0) { SelectObject(hdc,hPenMaj); DrawLine_(hdc,x1_maj,int(yPos+0.5),x2_maj,int(yPos+0.5));}
if(ParScl->NumTics%2!=0) if(k==(ParScl->NumTics+1)/2&&k!=0) {
SelectObject(hdc,hPenMaj); DrawLine_(hdc,x1_Av,int(yPos+0.5),x2_Av,int(yPos+0.5));} 
if(k!=0&&(k!=(ParScl->NumTics+1)/2||(ParScl->NumTics%2==0&&k==(ParScl->NumTics+1)/2))) { SelectObject(hdc,hPenMin); DrawLine_(hdc,x1_min,int(yPos+0.5),x2_min,int(yPos+0.5));}
} // Конец цикла по "i".

if(l%ParScl->NumMinStep==0) { sprintf(TxtStr,ParScl->form,yPosPhys); rc.left=x0+dx; rc.right=x0+dx+TextLen; 
rc.top=int(yPos+0.5)-8; rc.bottom=int(yPos+0.5)+8;
if(flShift0==1&&rc.bottom>y0+dy) { rc.bottom=y0+dy; rc.top=rc.bottom-16;} 
if(rc.top<y0) { rc.top=y0; rc.bottom=rc.top+16;} // Проверки выхода за границу.
DrawText(hdc,TxtStr,strlen(TxtStr),&rc,DT_CENTER);}
k++; l++; yPos-=PixStepTics; yPosPhys+=PhysStep/(ParScl->NumTics+1);
}}

// Вниз.
if(flDir==1) { yPos=y0; k=0; l=0; while(yPos<=y0+dy+1) { 
for(i=0;i<2;i++) { if(i==0) { x1_maj=x1_min=x1_Av=x0; x2_maj=x0+MajLen; x2_min=x0+MinLen; x2_Av=x0+AvLen;}
if(i==1) { x2_maj=x2_min=x2_Av=x0+dx; x1_maj=x0+dx-MajLen; x1_min=x0+dx-MinLen; x1_Av=x0+dx-AvLen;}
if(k==ParScl->NumTics+1) { yPos+=k*PixStepTics; yPos-=PixStep; k=0;}
if(k==0) { SelectObject(hdc,hPenMaj); DrawLine_(hdc,x1_maj,int(yPos+0.5),x2_maj,int(yPos+0.5));}
if(ParScl->NumTics%2!=0) if(k==(ParScl->NumTics+1)/2&&k!=0) {
SelectObject(hdc,hPenMaj); DrawLine_(hdc,x1_Av,int(yPos+0.5),x2_Av,int(yPos+0.5));} 
if(k!=0&&(k!=(ParScl->NumTics+1)/2||(ParScl->NumTics%2==0&&k==(ParScl->NumTics+1)/2))) { SelectObject(hdc,hPenMin); DrawLine_(hdc,x1_min,int(yPos+0.5),x2_min,int(yPos+0.5));}
} // Конец цикла по "i".

if(l%ParScl->NumMinStep==0) { sprintf(TxtStr,ParScl->form,yPosPhys); rc.left=x0+dx; rc.right=x0+dx+TextLen; 
rc.top=int(yPos+0.5)-8; rc.bottom=int(yPos+0.5)+8;
if(flShift0==1&&rc.top<y0) { rc.top=y0; rc.bottom=rc.top+16;}
if(rc.bottom>y0+dy) { rc.bottom=y0+dy; rc.top=rc.bottom-20;} // Проверки выхода за границу.
DrawText(hdc,TxtStr,strlen(TxtStr),&rc,DT_CENTER);}
k++; l++; yPos+=PixStepTics; yPosPhys+=PhysStep/(ParScl->NumTics+1);
}}

DeleteObject(font); SelectObject(hdc,GetStockObject(NULL_PEN));
SAFE_DELETE_OBJECT(hPenMaj); SAFE_DELETE_OBJECT(hPenMin); // Освобождение памяти.
return 0; 
}
*/