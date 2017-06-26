#include "resource.h"
#include "Cmplx.h"
#include "Matrix.h"
#include "Cls.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ����� ���������� ������.

class clTask
{
public:

BYTE flPol; // ���� ���� ����������� �������� �����. 0 - p, 1 - s.
int L1,M1; // ����� ������������� � ������������� ��������. 
double wLength,wLen_St,wLen_Fin,dwLen; // ����� ����� ��������� �����.
double Theta,Th_St,Th_Fin,dTh; // ���� ������� ����� (� �������).
double dz; // ��� ��������� ����.
complex EpsInc,EpsOut; // ��������������� ������������� ����, ������ ������, � ���� ������ ����.

clTask(void); // �����������.
BYTE Read(FILE *fp); // ������ ������ �� �����.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ��������� ���������.

struct strMaterial
{
char *name; // �������� ���������.
char chr; // ������, ������������ ��� ����������� ������� ���������.
complex eps; // ��������������� ������������� ������� ���������.
int R,G,B; // ���������� �����.

strMaterial(void); // �����������.
~strMaterial(void); // ����������.
BYTE Read(FILE *fp); // ������ ������ � ��������� �� �����.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ����� ������� ���� ����������, ������������ � ��������� (���� ������ ����������).

class clMaterialAll
{
void Zero(void); // ��������� ����������.
void Free(void); // ������������ ������.

public:

int N; // ������ �������.
struct strMaterial *Mat; // ������ ���� ����������.

clMaterialAll(void); // �����������.
~clMaterialAll(void); // ����������.
BYTE Alloc(int N_); // ��������� ������ ��� �������.
BYTE IsOK(void) const; // ��������.
BYTE Read(FILE *fp); // ������ ������ � ���������� �� �����.
strMaterial *Get(int num); // ��������� ��������� �� ��������� ����������.
int GetNum(char chr) const; // ����� ������� ��������� � ����������� ��� ������ � ������ ����.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// C�������� ��������� ����� ������ ���������.

struct strSymbCol
{
int R,G,B; // ���� ���������.
char symb; // ������ ���������.

strSymbCol(void); // �����������.
void Zero(void); // ��������� ����������.
BYTE Read(FILE *fp); // ������ ��������� �� �����.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ����� ��������� ������ ��� ���� ������ ����������.

class clDB_SymbCol
{
void Zero(void); // ��������� ����������.
void Free(void); // ������������ ������.

public:

int N; // ������ �������.
struct strSymbCol *Arr; // ������ ���� ���������.

clDB_SymbCol(void); // �����������.
~clDB_SymbCol(void); // ����������.
BYTE Alloc(int N_); // ��������� ������ ��� �������.
BYTE IsOK(void) const; // ��������.
void Symb_to_RGB(char symb_,BYTE *R_,BYTE *G_,BYTE *B_); // ����� ������� � ��������� ������� R_,G_,B_.
BYTE Read(char *FName_SymbCol); // ������ ��������� �� �����.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ��������� ������ ���� �� ��� z ��������� ���������.

struct strLay
{
int nDiv; // ����� ��������� ���� ��� ���������� ������������� �����.
int laySize; // ������ ������� �� ��� x.
double depth; // ������� ���� � ����������.
double dz; // ������� ������� ���� ��� ���������� ���� ������ ����.
char *GeomSymbs; // ������ ��������� ��������� � �������� ����������.
clRows XDistr,YDistr,ZDistr; // ������������� ����� E � H � ���������.

strLay(void); // �����������.
~strLay(void); // ����������.
void Zero(void); // ��������� ����������.
void Free(void); // ������������ ������.
BYTE Alloc(int N); // ��������� ������.
BYTE IsOK(void); // ��������.
BYTE Read(FILE *fp); // ������ ���� �� �����.
BYTE ReadFieldDistr(FILE *file); // ������ �� ����� ������������� �����.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ����� ��������� ���������.

class clCrystal
{
void Zero(void); // ��������� ����������.

public:

int laysNum; // ����� �����.
double Period; // ������ ���� � ����������.
struct strLay *Lays; // ������ ���� �����.

clCrystal(void); // �����������.
~clCrystal(void); // ����������.
void Free(void); // ������������ ������.
BYTE Alloc(int laysNum_); // ��������� ������ ��� �������.
BYTE IsOK(void) const; // ��������.
BYTE IsOKLay(void) const; // ��������.
strLay *Get(int num); // ��������� ��������� �� ��������� ���� � ������� 'num'.
BYTE Read(FILE *fp); // ������ ���������� � ��������� �� �����.
BYTE ReadFieldDistr(FILE *file); // ������ ������������� ����.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ����� �������� ����.

class clMain {

BYTE flTypDraw,flTypNorm,flGrid,TypImage,TypScale,flCompDistr,flCurMouse,flAnglDisp;
int y0; // ��������� ���������, � �������� �������� ��������.
double AmpNormArr[nTypNorm]; // ��������� ����������.
RECT rc,rcCntrl; // ��������� ���������������.
BYTE flDistr,flChSizeImg,flDComp; // �����: ���������� �������������, ��������� �������� ���� � ���������� ������������� ��� ��������� ����.
double MashtabX,MashtabY; // ������� ������������� (��/����.) �� ���� X,Z.
double AnglMashtabX,AnglMashtabY; // ������� ������������� ������� ��������� �� ���� X,Z.
int xSizeD,ySizeD; // ������� �������������.
int xSizeAnglD,ySizeAnglD; // ������� ������������� ������� ���������.
int xSizeDM,ySizeDM; // ������� ������������� � ������ ��������� ������� ����.
complex *DistrX,*DistrY,*DistrZ; // ����������� ������������� ��������� �����.
double *DistrF,*DistrFAbs,*DistrSqE,*DistrSqH; // ������������� ��������� �����, ������ � �������� ���� 'E' � 'H'.
double *DistrFvFc; // ������������� 'Im([ExE*])' ��� 'Im([HxH*])'.
double *DistrPx,*DistrPz,*DistrPAbs,*DistrDivP; // ������������� ���������, ������ � ����������� ������� ���������.
double *DistrReEps,*DistrImEps,*DistrE2EpsIm; // ������������� �������������� � ������ ����� ��������������� ������������� � ������������� 'eps".E^2'.
clRows AnglDisp; // ������� ���������. ����������� ������ �� �������� ���������.
complex *AnglDispDistr; // ������������� ������� ��������� �� ��������.
double DepthCryst; // ������� ��������� (��).
double cx1,cz1,cx2,cz2; // ���������� ������ ��� ������ ������������� ����� ����� � ����.
double DistrStep; // ��� ������� ������������� ����� �����.
struct strPal PalDistrP,PalDistrN; // ������� ������������� ����� (+,-).
HCURSOR cur_wait; // �������.
char *FileName; // ��� ��������� �����.

void Zero(void); // ��������� ��������������� � ����������.
void Free(void); // ������������ ������.
BYTE Alloc(void); // ��������� ������.
void ZeroDlg(void); // ��������� �������� ��� ����������� ����.
void FreeDlg(void); // �������� �������� ��� ����������� ����.
void ZeroBrushes(void); // ��������� ������ ��� ������������ ����.
void FreeBrushes(void); // �������� ������ ��� ������������ ����.
BYTE CreateBrushes(void); // �������� ������ ��� ������������ ����.
void ZeroFonts(void); // ��������� �������.
void FreeFonts(void); // �������� �������.
void CreateFonts(void); // �������� �������.
void InitAmpNorm(void); // ������������� �������� ���������� � ��������� �� ��������� ����������.
void ZeroDistr(void); // ��������� ���������� �� �������������.
void FreeDistr(void); // �������� �������������.
BYTE AllocDistr(int xSizeD_,int ySizeD_); // ��������� ������ ��� �������������.
BYTE AllocAnglDispDistr(int xSizeD_,int ySizeD_); // ��������� ������ ��� ������������� ������� ���������.
void FreeAnglDispDistr(void); // ������������ ������ ��� ������������� ������� ���������.
BYTE IsOK_Distr(void); // �������� �������� �������������.
BYTE IsOK_DispAngl(void); // �������� ������� ���������.
double *GetDistr(void); // ��������� ��������� �� ������ �������������.
BYTE FillDistrComp(void); // ���������� ������� ������ ���������� ���� ��� ���������� ���� �������������.
void FreeBmpAll(void); // ������������ ������ ��� �����������.
BYTE FillListFiles(void); // ���������� ���������������� ������ ������� ������.
BYTE OpenFile(void); // �������� �����.
BYTE LoadFile(char *fName); // �������� ����� � ������������� ��������.
void CloseFile(void); // �������� ����������.
void DialogInfo(void); // �������� � �������� ����������� ���� ���������� � ���������.
BYTE CreateDlgCntrl(void); // �������� ����������� ������������ ����.
BYTE Command(WPARAM wParam); // �������.
BYTE CommandCntrl(WPARAM wParam); // ��������� ������ ���� ����������.
BYTE OnChangeTypDraw(void); // ��������� ���� ���������.
BYTE OnWriteDistr(void); // �������� ��� ������� �� ������� ������ ������������� ����� ����� � ����.
BYTE CompDistrLine(void); // ���������� � ������ � ���� ������������� ����� �����.
void SetTypNorm(void); // ��������� ���� ����������.
void OnChTypNorm(BYTE typNorm); // �������� ��� ��������� ���� ����������.
void SetNameValues(void); // ��������� ����� ��������� �������.
void SetDlgCntrlCombo(void); // ��������� �������� � combobox-�.
void SetDlgCntrl(void); // ��������� ���������� � ����������� ����.
void SetAmpNorm(void); // ��������� ��������� ���������� � ����.
BYTE FindMashtab(int xSize,int ySize); // ����������� ��������.
BYTE FindMashtabAngl(int xSize,int ySize); // ����������� ��������.
void CreateComputeDistrAll_(void); // ��������� ������� �������������, ���������� ��������, ��������� ������, ������ ���� ������������� � ����������� ����.
void CreateComputeDistrAll(void); // ��������� ������� �������������, ���������� ��������, ��������� ������ � ������ ���� �������������.
BYTE CreateComputeAnglDisp(void); // ��������� ������� ������������� �������� �������������, ���������� ��������, ������ � ����������� ����.
BYTE CreateDistrAll(void); // ��������� ������� �������������, ���������� ��������, ��������� ������ ��� �������������.
BYTE CreateAnglDisp(void); // ��������� ������� ������������� ������� ���������, ���������� ��������.
BYTE ComputeDistrAll(void); // ������ ���� �������������.
BYTE ComputeDistr(int xSize,int ySize,complex *Distr,BYTE typDistr); // ���������� ������� �������������.
BYTE ComputeDistrEps(int xSize,int ySize,double *DistrRe,double *DistrIm); // ���������� ������������� �������������� � ������ ����� ��������������� �������������.
BYTE ComputeAnglDispDistr(complex *AnglDispDistr); // ���������� ������� ������������� ������� ���������.
void DrawDistr_(void); // ��������� ������������� ����� � ������.
void DrawAnglDisp_(void); // ��������� ������� ��������� � ������.
BYTE DrawAnglDisp(void); // ��������� ������������� �����.
BYTE DrawDistr(void); // ��������� ������������� �����.
BYTE DrawPal(BYTE fl); // ��������� �������. fl=0 --> ������������� �������, fl=1 --> ������ �������.
BYTE DrawDistrVoid(void); // ��������� � ������ ������.
BYTE DrawAnglDispVoid(void); // ��������� � ������ ������.
BYTE DrawCrystGeom(void); // ��������� ��������� ���������.
void ChooseDraw(void); // ��������� ���� �������������, ���� ��������� ���������.
BYTE OnPaintDistr(HDC hdc); // ��������� � ������� ������������� �����.
BYTE OnPaintDistrDef(HDC hdc); // ������������ ������� ��������� ������������� �����.
BYTE DrawGrid(HDC hdc,int yShift,int xShift); // ��������� ����� �� ����� ���������.
BYTE DrawScalePal(HDC hdc,int x0,int y0,int dx,int dy,BYTE flPal); // ��������� ����� �� �������.
BYTE CheckSizeImg(void); // �������� ��������� �������� ����, ��������� ��������� ������ ����������� �����������.
void SetStateBtnRedraw(void); // ��������� ��������� ������ ����������� �����������.
BYTE ReadFile(char *File_Name); // ������ ������ �� �����.
BYTE ReadAnglDisp(BYTE fl); // ������ ����� ������� ���������.
void OnMouseDistr(LPARAM lParam,BYTE fl); // �������� ��� ����������� ������� ���� � ���� �������������.
void CheckCurPos(void); // �������� �������������� �������.
void ClearCoor1(void); // ������� ���� ���������.
void ClearCoor2(BYTE fl); // ������� ���� ���������.
void ClearVal(void); // ������� ���� �������.
void SetCoorMouse(int cx,int cy,BYTE fl); // ��������� ��������� �� �������������� �������.
BYTE SetValMouse(int cxM,int cyM); // ��������� ������� �� �������������� �������.

public:

double *pAmpNorm; HWND hwnd,hDlgCntrl; HBRUSH hBrushBkg,hBrushDial; HFONT hFontListLay;
clCrystal Cryst; clTask Task; clMaterialAll Matter; clDB_SymbCol SymbCols; 
clBmpPict *BmpDiag,*BmpAnglDisp,*BmpPalP,*BmpPalPN;

clMain(void); // �����������.
~clMain(void); // ����������.
BYTE OnCreate(HWND hwnd_); // �������� � ������ ������ ���������.
LRESULT MsgCommand(UINT msg,WPARAM wParam,LPARAM lParam,BYTE *flag); // ��������� ������� ��������� ����.
LRESULT MsgCommandCntrl(UINT msg,WPARAM wParam,LPARAM lParam,BYTE *flag); // ��������� ������� ��������� ���� ����������.
BYTE SetDlgInfo(HWND hDlg); // ��������� ���������� � ���������� ����.
};
