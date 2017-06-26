#include "stdafx.h"
#include "Cls.h"

//-----------------------------------------------------------------------------------------------------
// Программы.

BYTE InitImgBitmap(int dx,int dy,BYTE typBmp,UINT *dxB_,HBITMAP *hBitmap,BYTE **pvBits,DWORD *NCol,SHRT nCol); // Создание 'DIB'.
BYTE CreateInfoBMP(BITMAPINFO **BMInfo,int dx,int dy,BYTE typBmp,DWORD *NCol,SHRT nCol); // Получение структуры информации для битового изображения.
void DeleteInfoBMP(BITMAPINFO **BMInfo); // Удаление заголовка файла с изображением 'DIB'.
BYTE AllocDWORD(DWORD **dwpp,size_t ln); // Выделение памяти для массива 'DWORD'.
void FreeDWORD(DWORD **dwpp); // Освобождение памяти для массива 'DWORD'.

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Класс для вывода изображения типа DIB и считывания изображения с экрана.

//-----------------------------------------------------------------------------------------------------------

clBmpPict::clBmpPict(void)
{
Zero();
}

//-----------------------------------------------------------------------------------------------------------

clBmpPict::~clBmpPict(void)
{
Free();
}

//-----------------------------------------------------------------------------------------------------------
// Обнуление указателей и инициализация параметров.

void clBmpPict::Zero(void)
{
ZeroDC(); ZeroBmp(); hFont=NULL;
}

//-----------------------------------------------------------------------------------------------------------
// Освобождение памяти.

void clBmpPict::Free(void)
{
FreeDC(); FreeBmp(); hFont=NULL;
}

//-----------------------------------------------------------------------------------------------------------
// Проверки битового изображения и параметров.

BYTE clBmpPict::IsOK(void)
{
if(hBitmap==NULL) return 1; if(dx<=0||dy<=0) return 2; if(dxB==0) return 3; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Проверки битового изображения и параметров.

BYTE clBmpPict::IsOKB(void)
{
if(hBitmap==NULL) return 1; if(dx<=0||dy<=0) return 2; if(dxB==0) return 3; if(pvBits==NULL) return 4;
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Обнуление указателей и инициализация параметров для битового изображения.

void clBmpPict::ZeroBmp(void)
{
hBitmap=NULL; pvBits=NULL; dx=dy=0; dxB=0;
}

//-----------------------------------------------------------------------------------------------------------
// Освобождение памяти от битового изображения.

void clBmpPict::FreeBmp(void)
{
SAFE_DELETE_OBJECT(hBitmap); pvBits=NULL; dx=dy=0; dxB=0;
}

//-----------------------------------------------------------------------------------------------------------
// Заполнение битового изображения нулевым цветом.

BYTE clBmpPict::Clear(void)
{
if(IsOKB()!=0) return 1; ZeroMemory((PVOID)pvBits,(DWORD)dxB*(DWORD)dy); return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Заполнение битового изображения заданным цветом.

BYTE clBmpPict::Clear(COLORREF Col)
{
BYTE GetColComp(COLORREF Col,BYTE *CC); // Получение компонент цвета.

BYTE k,CC[3],Bpp; UINT i,j,l,dxB_;

if(IsOKB()!=0) return 1; if(GetColComp(Col,CC)!=0) return 2;
for(j=0;j<(UINT)dy;j++) { l=((UINT)dy-1-j)*dxB;
for(i=0;i<(UINT)dx;i++) { for(k=0;k<3;k++) pvBits[l+(UINT)k]=CC[2-k]; l+=3;}}
Bpp=3; dxB_=(UINT)dx*(UINT)Bpp;
if(dxB_<dxB) for(j=0;j<(UINT)dy;j++) { l=((UINT)dy-1-j)*dxB; for(i=dxB_;i<dxB;i++) pvBits[i+l]=0;}
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Рисование пиксела.

BYTE clBmpPict::SetPix(int cx,int cy,BYTE *CC)
{
U_LONG l;

if(IsOKB()!=0) return 1; if(cx<0||cx>=dx) return 2; if(cy<0||cy>=dy) return 3;
l=(U_LONG)(dy-1-cy)*(U_LONG)dxB;
l+=(U_LONG)cx*3; *(pvBits+l)=CC[2]; *(pvBits+l+1)=CC[1]; *(pvBits+l+2)=CC[0]; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Задание параметров.

BYTE clBmpPict::Init(int dx_,int dy_,HFONT hFont_)
{
BYTE GetBitPerPix(BYTE typ,BYTE *BitCount); // Получение числа бит на пиксел.

BYTE BitCount,be,ber; UINT dxB_;

if(dx_<=0||dy_<=0) return 1; if(GetBitPerPix(typBmp_24,&BitCount)!=0) return 3; if(BitCount%8!=0) return 4;
if((UINT)dx_>UINT_MAX/(BitCount/8)) return 5;
Free(); ber=0;
be=InitImgBitmap(dx_,dy_,typBmp_24,&dxB_,&hBitmap,&pvBits,NULL,0);
if(be==messLrgAr||be==messNoMem) { ber=be; goto end;} if(be!=0) { ber=6; goto end;}
if(hBitmap==NULL) { ber=7; goto end;}
dx=dx_; dxB=dxB_; dy=dy_; hFont=hFont_;
end: if(ber!=0) Free(); return ber;
}

//-----------------------------------------------------------------------------------------------------------
// Обнуление указателей на старый битовый образ и DC.

void clBmpPict::ZeroDC(void)
{
hBitmapOld=NULL; hdc=NULL;
}

//-----------------------------------------------------------------------------------------------------------
// Создание DC и выбор битового изображения в этом DC.

HDC clBmpPict::GetDC(HDC hdc_)
{
BYTE ber;

if(hdc!=NULL) return hdc; if(hdc_==NULL||hBitmap==NULL) return NULL; ber=0;
hdc=CreateCompatibleDC(hdc_); if(hdc==NULL) { ber=1; goto end;}
hBitmapOld=(HBITMAP)SelectObject(hdc,hBitmap); if(hBitmapOld==NULL) { ber=2; goto end;}
SetROP2(hdc,R2_COPYPEN); SetBkMode(hdc,TRANSPARENT); if(hFont!=NULL) SelectObject(hdc,hFont);
SelectObject(hdc,GetStockObject(WHITE_BRUSH));
SelectObject(hdc,GetStockObject(WHITE_PEN));
end: if(ber!=0) { FreeDC(); return NULL;} return hdc;
}

//-----------------------------------------------------------------------------------------------------------
// Выбор старого битового изображения и уничтожение DC.

void clBmpPict::FreeDC(void)
{
if(hdc==NULL) return; if(hBitmapOld!=NULL) { SelectObject(hdc,hBitmapOld); hBitmapOld=NULL;}
SelectObject(hdc,GetStockObject(SYSTEM_FONT)); DeleteDC(hdc); hdc=NULL;
}

//-----------------------------------------------------------------------------------------------------------
// Вывод изображения.

BYTE clBmpPict::Image(HDC hdc_,int xi_,int yi_,int dx_,int dy_,BYTE stretch)
{
BYTE bNew,ber; BOOL b;

if(hdc_==NULL) return 1; if(IsOK()!=0) return 2; if(dx_<=0||dy_<=0) return 3; ber=0;
if(hdc==NULL) { if(GetDC(hdc_)==NULL) { ber=4; goto end;} bNew=1;} else bNew=0;
if(stretch!=0) { if(SetStretchBltMode(hdc_,STRETCH_DELETESCANS)==0) { ber=5; goto end;}}
if(stretch==0) b=BitBlt(hdc_,xi_,yi_,MIN(dx_,dx),MIN(dy_,dy),hdc,0,0,SRCCOPY);
else b=StretchBlt(hdc_,xi_,yi_,dx_,dy_,hdc,0,0,dx,dy,SRCCOPY);
if(b==FALSE) { ber=6; goto end;}
end: if(bNew!=0) FreeDC(); return ber;
}

//-----------------------------------------------------------------------------------------------------------
// Получение изображения.

BYTE clBmpPict::GetImg(HDC hdc_,int xi_,int yi_,int dx_,int dy_)
{
BYTE bNew,ber;

if(hdc_==NULL) return 1; if(IsOK()!=0) return 2; if(dx_<=0||dy_<=0) return 3; ber=0;
if(hdc==NULL) { if(GetDC(hdc_)==NULL) { ber=4; goto end;} bNew=1;} else bNew=0;
if(BitBlt(hdc,0,0,MIN(dx_,dx),MIN(dy_,dy),hdc_,xi_,yi_,SRCCOPY)==FALSE) { ber=5; goto end;}
end: if(bNew!=0) FreeDC(); return ber;
}

//-----------------------------------------------------------------------------------------------------------
// Сохранение изображения в файле '*.bmp'.

BYTE clBmpPict::Save(HANDLE File)
{
BYTE GetBitPerPix(BYTE typ,BYTE *BitCount); // Получение числа бит на пиксел.
BYTE WriteDIB_FH(HANDLE File,DWORD *szFile,BYTE Bpp,int dx,int dy,BYTE *BytesDIB,DWORD *NCol,SHRT nCol); // Запись изображения 'DIB' в файл.

BYTE Bpp;

if(File==INVALID_HANDLE_VALUE) return 1; if(IsOKB()!=0) return 2;
if(GetBitPerPix(typBmp_24,&Bpp)!=0) return 3; Bpp/=8;
if(WriteDIB_FH(File,NULL,Bpp,dx,dy,pvBits,NULL,0)!=0) return 4; return 0;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Изображение в памяти.

//-----------------------------------------------------------------------------------------------------------

clImgMem::clImgMem(void)
{
Zero();
}

//-----------------------------------------------------------------------------------------------------------

clImgMem::~clImgMem(void)
{
Free();
}

//-----------------------------------------------------------------------------------------------------------
// Обнуление указателей и инициализация параметров.

void clImgMem::Zero(void)
{
hdc=NULL; ZeroBmp();
}

//-----------------------------------------------------------------------------------------------------------
// Освобождение памяти.

void clImgMem::Free(void)
{
FreeBmp(); FreeDC();
}

//-----------------------------------------------------------------------------------------------------------
// Удаление 'hdc' из памяти.

void clImgMem::FreeDC(void)
{
if(hdc==NULL) return; SelectObject(hdc,GetStockObject(SYSTEM_FONT)); DeleteDC(hdc); hdc=NULL;
}

//-----------------------------------------------------------------------------------------------------------
// Обнуление указателей и инициализация параметров.

void clImgMem::ZeroBmp(void)
{
hBitmap=hBitmapOld=NULL; dx=dy=0; dxB=0;
}

//-----------------------------------------------------------------------------------------------------------
// Удаление битового изображения 'hBitmap' из 'hdc' и из памяти.

void clImgMem::FreeBmp(void)
{
if(hBitmap!=NULL) UnSelectBmp(); SAFE_DELETE_OBJECT(hBitmap); dx=dy=0; dxB=0;
}

//-----------------------------------------------------------------------------------------------------------
// Создание битового изображения 'hBitmap'.

BYTE clImgMem::CreateBmp(int dx_,int dy_)
{
BYTE be; UINT dxB_;

if(dx_<=0||dy_<=0) return 1;
be=InitImgBitmap(dx_,dy_,typBmp_24,&dxB_,&hBitmap,NULL,NULL,0);
if(be==messLrgAr||be==messNoMem) return be; if(be!=0) return 2;
dx=dx_; dy=dy_; dxB=dxB_; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Создание 'hdc' и выбор битового изображения 'hBitmap' в 'hdc'.

BYTE clImgMem::Create(HDC hdc_,int dx_,int dy_,HFONT hFont,BYTE mess)
{
BYTE be,ber;

Free(); if(hdc_==NULL) return 1; ber=0;
hdc=CreateCompatibleDC(hdc_); if(hdc==NULL) { ber=2; goto end;}
be=CreateBmp(dx_,dy_); if(be!=0) {
if(be==messLrgAr||be==messNoMem) ber=be; else ber=3; goto end;}
if(SelectBmp()!=0) { ber=4; goto end;}
if(SetPar(hFont)!=0) { ber=5; goto end;}
end: if(ber!=0) Free(); return ber;
}

//-----------------------------------------------------------------------------------------------------------
// Выбор битового образа 'hBitmap' в 'hdc'.

BYTE clImgMem::SelectBmp(void)
{
if(IsOK()!=0) return 1; if(hBitmapOld!=NULL) return 2;
hBitmapOld=(HBITMAP)SelectObject(hdc,hBitmap); if(hBitmapOld==NULL) return 3; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Удаление битового образа 'hBitmap' из 'hdc'.

void clImgMem::UnSelectBmp(void)
{
if(hBitmapOld!=NULL&&hdc!=NULL) { SelectObject(hdc,hBitmapOld); hBitmapOld=NULL;}
}

//-----------------------------------------------------------------------------------------------------------
// Установка параметров в 'hdc' и закрашивание цветом по умолчанию.

BYTE clImgMem::SetPar(HFONT hFont)
{
if(IsOKImg()!=0) return 1; SetROP2(hdc,R2_COPYPEN); SetBkMode(hdc,TRANSPARENT);
if(hFont!=NULL) SelectObject(hdc,hFont); return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Проверка параметров.

BYTE clImgMem::IsOK(void)
{
if(hBitmap==NULL) return 1; if(hdc==NULL) return 2;
if(dx<=0||dy<=0) return 3; if(dx>SHRT_MAX||dy>SHRT_MAX) return 4;
if(dxB==0) return 5; if(dxB>USHRT_MAX) return 6; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Проверка параметров и того, что битовое изображение выбрано в 'hdc'.

BYTE clImgMem::IsOKImg(void)
{
if(IsOK()!=0) return 1; if(hBitmapOld==NULL) return 2; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Установка бит в формате 'True color'.

BYTE clImgMem::SetBitsTrCol(int dx_,int dy_,BYTE *Bits)
{
BYTE ber; BITMAPINFO *BMInfo;

if(dx_<=0||dy_<=0) return 1; if(IsOKImg()!=0) return 2; if(dx_!=dx||dy_!=dy) return 3;
if(Bits==NULL) return 4; BMInfo=NULL; ber=0;
if(CreateInfoBMP(&BMInfo,dx,dy,typBmp_24,NULL,0)!=0) { ber=5; goto end;}
if(SetDIBits(hdc,hBitmap,0,dy,Bits,BMInfo,DIB_RGB_COLORS)==0) { ber=6; goto end;}
end: DeleteInfoBMP(&BMInfo); return ber;
}

//-----------------------------------------------------------------------------------------------------------
// Создание объекта класса 'clImgMem'.

BYTE InitBmpMem_(HWND hwnd,clImgMem **Bmp,int dx,int dy,BYTE mess)
{
void DeleteBmpMem_(clImgMem **Bmp); // Удаление объекта класса 'clImgMem'.

BYTE be,ber; HDC hdc;

DeleteBmpMem_(Bmp); if(hwnd==NULL) return 1; if(Bmp==NULL) return 2; if(dx<=0||dy<=0) return 3;
hdc=GetDC(hwnd); if(hdc==NULL) return 4; ber=0;
*Bmp=new clImgMem(); if(*Bmp==NULL) { ber=5; goto end;}
be=(*Bmp)->Create(hdc,dx,dy,NULL,mess); if(*Bmp==NULL) { ber=5; goto end;}
if(be!=0) { if(be==messNoMem||be==messLrgAr) ber=messNoMem; else ber=6; goto end;}
end: ReleaseDC(hwnd,hdc); if(ber!=0) DeleteBmpMem_(Bmp); return ber;
}

//-----------------------------------------------------------------------------------------------------------
// Удаление объекта класса 'clImgMem'.

void DeleteBmpMem_(clImgMem **Bmp)
{
if(Bmp==NULL) return; SAFE_DELETE(*Bmp);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Структура массивов палитры.

//-----------------------------------------------------------------------------------------------------------
// Конструктор.

strPal::strPal(void)
{
Zero();
}

//-----------------------------------------------------------------------------------------------------------
// Обнуление массива.

void strPal::Zero(void)
{
BYTE k; UINT i;

for(i=0;i<nColSmoothPal;i++) for(k=0;k<3;k++) MasRGB[i][k]=0;
}

//-----------------------------------------------------------------------------------------------------------
// Нахождение цветов сглаженной палитры.

BYTE strPal::FillColor(DWORD *ColBase)
{
BYTE i,k,j,cI,cF; UINT p; DWORD ColI,ColF; double v;

if(ColBase==NULL) return 1;
v=1./(double)nPalStep;
for(j=0;j<nColB-1;j++) { ColI=ColBase[j]; ColF=ColBase[j+1];
for(k=0;k<nPalStep;k++) { p=(UINT)nPalStep*(UINT)j+(UINT)k;
for(i=0;i<3;i++) {
switch(i) { default:
case 0: cI=GetRValue(ColI); cF=GetRValue(ColF); break;
case 1: cI=GetGValue(ColI); cF=GetGValue(ColF); break;
case 2: cI=GetBValue(ColI); cF=GetBValue(ColF); break;
}
MasRGB[p][i]=(BYTE)(((double)(cF-cI)*v)*(double)k+(double)cI);}}}
j=nColB-1; p=(UINT)nPalStep*(UINT)j; ColI=ColBase[j];
for(i=0;i<3;i++) {
switch(i) {
case 0: cI=GetRValue(ColI); break;
case 1: cI=GetGValue(ColI); break;
case 2: cI=GetBValue(ColI); break;}
MasRGB[p][i]=cI;}
return 0;
}