/*...........................................................................................................
clBmpPict,clImgMem,strPal

...........................................................................................................*/

#include "Const.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ����� ��� ������ ����������� ���� DIB � ���������� ����������� � ������.

class clBmpPict {

HDC hdc; HBITMAP hBitmap,hBitmapOld; HFONT hFont;

void Zero(void); // ��������� ���������� � ������������� ����������.
void ZeroDC(void); // ��������� ���������� �� ������ ������� ����� � DC.
void ZeroBmp(void); // ��������� ���������� � ������������� ���������� ��� �������� �����������.
void FreeBmp(void); // ������������ ������ �� �������� �����������.
BYTE SetPix(int cx,int cy,BYTE *CC); // ��������� �������.

public:

BYTE typBmp,*pvBits; int dx,dy; UINT dxB;

clBmpPict(void);
~clBmpPict(void);
BYTE IsOK(void); // �������� �������� ����������� � ����������.
BYTE IsOKB(void); // �������� �������� ����������� � ����������.
BYTE Clear(void); // ���������� �������� ����������� ������� ������.
BYTE Clear(COLORREF Col); // ���������� �������� ����������� �������� ������.
HDC GetDC(HDC hdc_); // �������� DC � ����� �������� ����������� � ���� DC.
void FreeDC(void); // ����� ������� �������� ����������� � ����������� DC.
void Free(void); // ������������ ������.
BYTE Init(int dx_,int dy_,HFONT hFont_); // ������� ����������.
BYTE Image(HDC hdc_,int xi_,int yi_,int dx_,int dy_,BYTE stretch); // ����� �����������.
BYTE GetImg(HDC hdc_,int xi_,int yi_,int dx_,int dy_); // ��������� �����������.
BYTE Save(HANDLE File); // ���������� ����������� � ����� '*.bmp'.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ����������� � ������.

class clImgMem {

HBITMAP hBitmap,hBitmapOld;

void Zero(void); // ��������� ���������� � ������������� ����������.
void Free(void); // ������������ ������.
void FreeDC(void); // �������� 'hdc' �� ������.
void ZeroBmp(void); // ��������� ���������� � ������������� ����������.
void FreeBmp(void); // �������� �������� ����������� 'hBitmap' �� 'hdc' � �� ������.
BYTE CreateBmp(int dx_,int dy_); // �������� �������� ����������� 'hBitmap'.
BYTE SelectBmp(void); // ����� �������� ������ 'hBitmap' � 'hdc'.
void UnSelectBmp(void); // �������� �������� ������ 'hBitmap' �� 'hdc'.
BYTE IsOK(void); // �������� ����������.

public:

HDC hdc; int dx,dy; UINT dxB;

clImgMem(void);
~clImgMem(void);
BYTE Create(HDC hdc_,int dx_,int dy_,HFONT hFont,BYTE mess); // �������� 'hdc' � ����� �������� ����������� 'hBitmap' � 'hdc'.
BYTE SetPar(HFONT hFont); // ��������� ���������� � 'hdc' � ������������ ������ �� ���������.
BYTE IsOKImg(void); // �������� ���������� � ����, ��� ������� ����������� ������� � 'hdc'.
BYTE SetBitsTrCol(int dx_,int dy_,BYTE *Bits); // ��������� ��� � ������� 'True color'.
BYTE SetBitsGrayCol(int dx_,int dy_,BYTE *Bits); // ��������� ��� � ������� �����-����-������ ����������� � 1 ������ �� ������.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ��������� �������� �������.

struct strPal {

BYTE MasRGB[nColSmoothPal][3];

strPal(void); // �����������.
void Zero(void); // ��������� �������.
BYTE FillColor(DWORD *ColBase); // ���������� ������ ���������� �������.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ��������� ��������� ����� �� ������� � ������������ ���������� ��������� ����������.

struct strParScale {

double ValMin,ValMax; // ����������� � ���������� ���������� �������� ��������.
double Step; // ��� � ���������� ��������.
int NumTics; // ����� ������� ����� ���������.
int NumMinStep; // ��� �� ��������� ����� �� �����.
char *form; // ������ ������ ����� � �������.
};