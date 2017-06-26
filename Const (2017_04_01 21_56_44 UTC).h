//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ���� ����������� �������� �����.

#define nPol 2 // ����� �����������.
#define p_wave_Pol 0 // ���� E ����� � ��������� �������.
#define s_wave_Pol 1 // ���� E ��������������� ��������� �������.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ��������� ����� ������������.

#define nTypDraw 14 // ���������� ��������� ����������.

#define TypDraw_X     0 // ������������ ���� 'Ex' ('p') ��� 'Hx' ('s').
#define TypDraw_Y     1 // ������������ ���� 'Hy' ('p') ��� 'Ey' ('s').
#define TypDraw_Z     2 // ������������ ���� 'Ez' ('p') ��� 'Hz' ('s').
#define TypDraw_Full  3 // ������������ ���� 'E' ('p') ��� 'H' ('s').
#define TypDraw_SqE   4 // ������� ��������� ���� 'E'.
#define TypDraw_SqH   5 // ������� ��������� ���� 'H'.
#define TypDraw_FvFc  6 // ��������� ������������ 'ExE*' ��� 'HxH*'.
#define TypDraw_Px    7 // X-� ���������� ������� ���������.
#define TypDraw_Pz    8 // Z-� ���������� ������� ���������.
#define TypDraw_PAbs  9 // ������ ������� ���������.
#define TypDraw_DivP  10 // ����������� ������� ���������.
#define TypDraw_EImE2 11 // ������������� �������� ������ 'eps".E^2'.
#define TypDraw_ReEps 12 // ������������� �������������� ����� 'eps'.
#define TypDraw_ImEps 13 // ������������� ������ ����� 'eps'.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ����� ����� ����������.

#define nTypNorm 10 // ����� ����� ����������.

#define typNorm_E     0 // ���� 'E'.
#define typNorm_H     1 // ���� 'H'.
#define typNorm_E2    2 // ������� ���� 'E'.
#define typNorm_H2    3 // ������� ���� 'H'.
#define typNorm_FvFc  4 // ��������� ������������ 'ExE*' ��� 'HxH*'.
#define typNorm_Poynt 5 // ���������� � ������ ������� ���������.
#define typNorm_EImE2 6 // ������������� �������� ������ 'eps".E^2'.
#define typNorm_ReEps 7 // �������������� ����� 'eps'.
#define typNorm_ImEps 8 // ������ ����� 'eps'.
#define typNorm_AnglDisp 9 // ������� ���������.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ����������� �����.

typedef unsigned char BYTE;
typedef unsigned int UINT;
typedef signed char SCHAR;
typedef short int SHRT;
typedef unsigned short int USHRT;
typedef unsigned long U_LONG;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ���������.

#define szNameSubst 64 // ������ ������ ��� �������� ��������.
#define laySize_Max 1000 // ����������� ���������� ������ ���� �� ��� x.
#define strL_Path 256 // ����� ����.
#define strL_Txt 256 // ����� ��������������� ������.

#define MB_EX (MB_OK|MB_ICONEXCLAMATION|MB_APPLMODAL|MB_TOPMOST) // �����������.
#define MB_IN (MB_OK|MB_ICONINFORMATION|MB_APPLMODAL|MB_TOPMOST) // ����������.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// �������.

#define SAFE_DELETE(Obj) { if(Obj!=NULL) { delete Obj; Obj=NULL;}} // ���������� ��������.
#define SAFE_DELETE_ARR(Arr) { if(Arr!=NULL) { delete[] Arr; Arr=NULL;}} // ���������� �������� �������.
#define SAFE_DELETE_OBJECT(Obj) { if(Obj!=NULL) { DeleteObject(Obj); Obj=NULL;}} // ���������� �������� �������.
#define SAFE_CLOSE(file) { if(file!=NULL) { fclose(file); file=NULL;}} // ���������� �������� �����.
#define SAFE_CLOSE_FIND(Handle) { if(Handle!=INVALID_HANDLE_VALUE) { FindClose(Handle); Handle=INVALID_HANDLE_VALUE;}} // �������� ������.
#define MAX(x,y) (x>y?x:y) // ���������� ���������.
#define MIN(x,y) (x<y?x:y) // ���������� ��������.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ����������� �����.

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
// ���������� ��� ������� ������.

#define nColB 9 // ����� �������� ������.
#define nPalStep 200 // ����� ������ ����� ��������� �������.
#define nColSmoothPal ((nColB-1)*nPalStep+1) // ����� ������ ���������� �������.
#define PalPixSize 50 // ������� ������ ��� ������ ������� � ��������.
#define GapSize 15 // ������ ���� ����� �������������� � ��������.
#define TextLen 40 // ����� ������� ��� ����� � �������.
#define ColGap COL_WHITE // ���� ������������ ���� ����� �������������� � ��������
#define ColTextBkg COL_WHITE // ���� ����, �� ������� �������� �����.
#define nScls_Pal 3 // ����� ����� ���� �� �������.
#define AmpMin 0.1 // ����������� ��������� ���������� ��� ������ �����.
#define MajDivWid_Pal 3 // ������� �������� �����.
#define MinDivWid_Pal 1 // ������� ��������������� �����.
#define MajDivLen_Pal 0.4 // ����� �������� �������� ����� � �.�. (� ����� ������).
#define AvDivLen_Pal 0.25 // ����� ����������� ��������������� ����� � �.�. (� ����� ������).
#define MinDivLen_Pal 0.2 // ����� ��������������� ����� � �.�. (� ����� ������).

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ���������� ��� ����� ������������� ������� ���������.

#define nSclsAnglDisp_Y 1 // ����� ����� ���� �� �������.
#define nSclsAnglDisp_X 1 // ����� ����� ���� �� �������.
#define MajDivWid_Angl 3 // ������� �������� �����.
#define MinDivWid_Angl 1 // ������� ��������������� �����.
#define MajDivLen_Angl 0.02 // ����� �������� �������� ����� � �.�. (� ����� ������).
#define AvDivLen_Angl 0.015 // ����� ����������� ��������������� ����� � �.�. (� ����� ������).
#define MinDivLen_Angl 0.01 // ����� ��������������� ����� � �.�. (� ����� ������).

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ���� ����������� DIB.

#define typBmp_24 0 // True Color.
#define typBmp_16 1 // 16 bits.
#define typBmp_8  2 // 8 bits (256 colors).
#define typBmp_4  3 // 4 bits (16 colors).
#define typBmp_1  4 // 1 bits (monochrome image).
#define typBmp_32 5 // 32 bits.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ���� ���������.

#define messRet   255 // �������.
#define messNoMem 254 // ������������ ������.
#define messLrgAr 253 // ������� ������ �������.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ������ ���������.

#define szMemMax 0xFFFFFFFF // ������������ ������ �������.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// �������� ������.

#define FName_SymbCol_Stand "SymbCol.txt" // �������� ����� ��������� ������.
#define FName_DistrLine_X "DistrAlongLine_X.txt" // �������� ����� ������������� ���. �������� ����� ����� (�� ��� X).
#define FName_DistrLine_Z "DistrAlongLine_Z.txt" // �������� ����� ������������� ���. �������� ����� ����� (�� ��� Z).
#define FName_AnglDisp_T "DispAngl.outtad"
#define FName_AnglDisp_R "DispAngl.outrad"
#define FName_AnglDisp_A "DispAngl.outaad" // �������� ����� ������� ���������.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ��������������� ���������.

#define M_PI 3.1415926535897932384626433832795 // ����� "��".

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ����������� ��������� ����������.

#define AmpNormE_Stand 2.0F // ��������� ���������� ������������� ���� 'E' �� ���������.
#define AmpNormH_Stand 2.0F // ��������� ���������� ������������� ���� 'H' �� ���������.
#define AmpNormE2_Stand 4.0F // ��������� ���������� ������������� �������� ���� 'E' �� ���������.
#define AmpNormH2_Stand 4.0F // ��������� ���������� ������������� �������� ���� 'H' �� ���������.
#define AmpNormFvFc_Stand 1.0F // ��������� ������������ 'ExE*' ��� 'HxH*'.
#define AmpNormPoynt_Stand 4.0F // ��������� ���������� ������������� ������� ��������� �� ���������.
#define AmpNormEImE2_Stand 0.5F // ������������� �������� ������ 'eps".E^2'.
#define AmpNormReEps_Stand 3.0F // �������������� ����� 'eps'.
#define AmpNormImEps_Stand 0.1F // ������ ����� 'eps'.
#define AmpNormAnglDisp_Stand 1.F // ������� ���������.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ��������� ���������.

// ����� ������������ ���� ����.
#define ColBkg COL_BLACK
#define ColBkgErr RGB(100,100,100)

#define numStrFileMin 5 // ����������� ������ ������ ������.
#define flScanf_S 0 // ���� ������������� 'scanf_s'.
