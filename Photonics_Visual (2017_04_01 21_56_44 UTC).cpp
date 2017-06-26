//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// "Photonics_Visual".
// ������������ �����������, ���������� � ������� ��������� "Photonics"
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*............................................................................................................

Common: WinMain,MyRegisterClass,InitInstance,GetPath,

clTask: clTask,Read,

strMaterial: strMaterial,~strMaterial,Read,

clMaterialAll: clMaterialAll,~clMaterialAll,Zero,Free,Alloc,IsOK,Read,Get,GetNum,

strLay: strLay,~strLay,Zero,Free,Alloc,IsOK,Read,ReadFieldDistr,

clCrystal: clCrystal,~clCrystal,Zero,Free,Alloc,IsOK,IsOKLay,Get,Read,ReadFieldDistr,

clMain: clMain,~clMain,Zero,Free,Alloc,
ZeroDlg,FreeDlg,
ZeroBrushes,FreeBrushes,CreateBrushes,
ZeroFonts,FreeFonts,CreateFonts,
InitAmpNorm,
ZeroDistr,FreeDistr,AllocDistr,IsOK_Distr,GetDistr,FillDistrComp,FreeBmpAll,
OnCreate,CreateDlgCntrl,FillListFiles,OpenFile,LoadFile,MsgCommand,Command,MsgCommandCntrl,CommandCntrl,
DialogInfo,SetDlgInfo,SetDlgCntrlCombo,SetDlgCntrl,SetAmpNorm,OnChangeTypDraw,SetTypNorm,OnChTypNorm,
SetNameValues,FindMashtab,CreateComputeDistrAll_,CreateComputeDistrAll,CreateDistrAll,ComputeDistrAll,
ComputeDistr,ComputeDistrEps,DrawDistr_,DrawDistr,DrawDistrVoid,DrawCrystGeom,ChooseDraw,
OnPaintDistr,OnPaintDistrDef,DrawGrid,CheckSizeImg,SetStateBtnRedraw,ReadFile,OnMouseDistr,CheckCurPos,
ClearCoor,ClearVal,SetCoorMouse,SetValMouse,

WndProcMain,InitMain,DlgProcCntrlMain,DlgInfo,DlgAbout

............................................................................................................*/

#include "stdafx.h"
#include "Photonics_Visual.h"
#include "Const.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst; // Current instance.
TCHAR szTitle[MAX_LOADSTRING]; // The title bar text.
TCHAR szWindowClass[MAX_LOADSTRING]; // The main window class name.

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT LRes; // ��������������� ����������.
DWORD ColDial; // ���� ���� ��� ����������� ����.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ���������.

BYTE AllocString(char **Str,size_t ln); // ��������� ������ ��� ������.
void FreeString(char **Str); // ������������ ������ ��� ������.
BYTE DupString(char **Str,char *Src); // ��������� ������ ��� ������ � �����������.
void ImgRectC(HDC hdc,RECT *rc,DWORD ColP,DWORD ColB,BYTE Wid); // ������������ ��������������.
void ImgWinC(HWND hwnd,DWORD ColP,DWORD ColB); // ������������ ����.
void UpdateWindow_(HWND hwnd); // ���������� ����.
void CloseWin_(HWND *hwnd); // �������� ����.
void EnableChWin(HWND hdlg,int id,BYTE flag); // ���� � ������ ���������� ��������� ����.
BYTE SetDlEdt(HWND hDlg,int id,double Val,char *Form); // ��������� �������� � ��������� ������ � ���� ��������������.
BYTE GetDlEdt(HWND hDlg,int id,double *Val); // ��������� �������� � ��������� ������ �� ���� ��������������.
BYTE ClearCombo(HWND hDlg,UINT id); // ������� ���������������� ������.
BYTE FillStrCombo(HWND hDlg,UINT id,UINT *IDSArr,BYTE nArr,BYTE nSel); // ���������� ���������������� ������.
BYTE GetNumStrCombo(HWND hDlg,int id,BYTE *num); // ��������� ����� ����� � ��������������� ������.
BYTE SetSizeCombo(HWND hDlg,int id,BYTE num); // ��������� ������� ���������������� ������ �� ����� �����.
BYTE GetSelCombo(HWND hDlg,UINT id,BYTE *num); // ��������� ������ ��������� ������ � ��������������� ������.
BYTE SetSelCombo(HWND hDlg,UINT id,BYTE num); // ��������� ������ ������ � ��������������� ������.
BYTE GetTxtStringSelCombo(HWND hDlg,int id,char *Str,USHRT nStr); // ��������� ��������� ������ � ������.
BYTE FindTxtStringCombo(HWND hDlg,int id,char *Str,BYTE *num); // ���������� ������ � ������.
BYTE Fill_CLB_Files(HWND hDlg,int id,BYTE typCLB,char *Path,char *Dir,char *Ext,BYTE flExt); // ���������� ������ (Combo/0 ��� List/!=0- boxes) ������� ������.
BYTE SetChBox(HWND hDlg,int id,BYTE flag); // ��������� ����� � ����.
BYTE GetChBox(HWND hDlg,int id,BYTE *flag); // ��������� ����� �� ����.
BYTE GetPosRadio(HWND hDlg,int idI,int idF,BYTE *pVar); // ��������� ��������� � ������ �������������� 'Radio Buttons'.
int GetIntTest(double v); // ��������� ����� 'int' �� ����� 'double' � ��������� ������ �� ������� 'int'.
UINT GetUINT_Test(double d); // ��������� ����� 'UINT' �� ����� 'double' � ��������� ������ �� ������� 'UINT'.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ����� �������� ����.

clMain MW;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ������.

char TxtStr[strL_Txt],TxtMem[strL_Txt]; // ��������������� ������.
char PathToProgDir[strL_Path]; // ���� � ���������� ���������.
char *extFileDistr=".outd"; // ���������� ������ � ��������������.

// �������.
char *FormAmp="%7.4lf";
char *FormPhase="%8.3lf";
char *FormSqFieldAmp="%7.3lf";
char *FormPowLoss="%8.6lf";
char *FormPoynt="%8.4lf";
char *FormEps="%8.4lf";
char *FormCoor="%7.2lf";

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ������� �������� ������ ������ ��� ����������� ���������.

// ������������� ��������.
DWORD ColBaseDistrP[nColB]={COL_BLACK,COL_DK_BLUE,COL_BLUE,COL_DK_SKY_BLUE,COL_DK_GREEN,COL_GREEN,COL_YELLOW,COL_RED,COL_DK_RED};

// ������������� ��������.
DWORD ColBaseDistrN[nColB]={COL_BLACK,COL_GRAY,COL_DK_VIOLET,COL_VIOLET,COL_BLUE,COL_DK_BLUE,COL_DK_SKY_BLUE,COL_SKY_BLUE,COL_WHITE};

// ������ ���� �������.
struct strParScale ParScaleArr_Pal[nScls_Pal]={{0.,1.,0.1,9,5,"%.2lf"},{0.,10.,1.,9,5,"%.1lf"},{0.,100.,10.,9,5,"%.1lf"}};

// ������� ���� �������� �������������.
struct strParScale ScaleAnglDisp_Y[nSclsAnglDisp_Y]={{500.,1500.,100,3,2,"%.0lf"}};
struct strParScale ScaleAnglDisp_X[nSclsAnglDisp_X]={{0.,21.,5.,4,5,"%.0lf"}};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// �������������� ����� �������� ����� ��������� �������������.

UINT IDSArrTypDraw_p[nTypDraw]={IDS_Typ_ExField,IDS_Typ_HyField,IDS_Typ_EzField,IDS_Typ_E_FullField,IDS_Typ_SqE,
IDS_Typ_SqH,IDS_Typ_EvEc,IDS_Typ_PoyntX,IDS_Typ_PoyntZ,IDS_Typ_PoyntAbs,IDS_Typ_PoyntDiv,IDS_Typ_EImE2,
IDS_Typ_ReEps,IDS_Typ_ImEps};
UINT IDSArrTypDraw_s[nTypDraw]={IDS_Typ_HxField,IDS_Typ_EyField,IDS_Typ_HzField,IDS_Typ_H_FullField,IDS_Typ_SqE,
IDS_Typ_SqH,IDS_Typ_HvHc,IDS_Typ_PoyntX,IDS_Typ_PoyntZ,IDS_Typ_PoyntAbs,IDS_Typ_PoyntDiv,IDS_Typ_EImE2,
IDS_Typ_ReEps,IDS_Typ_ImEps};

//-------------------------------------------------------------------------------------------------------------

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
{
UNREFERENCED_PARAMETER(hPrevInstance); UNREFERENCED_PARAMETER(lpCmdLine);
BYTE GetPath(void); // ��������� ����� ����������.

MSG msg; HACCEL hAccelTable;

// Initialize global strings.
LoadString(hInstance,IDS_APP_TITLE,szTitle,MAX_LOADSTRING);
LoadString(hInstance,IDC_PHOTONICS_VISUAL,szWindowClass,MAX_LOADSTRING);
MyRegisterClass(hInstance);

ColDial=GetSysColor(COLOR_BTNFACE); // ��������� ����� ���� ��� ����������� ����.

// Perform application initialization:
if(!InitInstance(hInstance,nCmdShow)) return FALSE;
if(GetPath()!=0) return FALSE; // ��������� ����� ����������.

hAccelTable=LoadAccelerators(hInstance,MAKEINTRESOURCE(IDC_PHOTONICS_VISUAL));

// Main message loop:
while(GetMessage(&msg,NULL,0,0))
if(!TranslateAccelerator(msg.hwnd,hAccelTable,&msg)) { TranslateMessage(&msg); DispatchMessage(&msg);}
return (int)msg.wParam;
}

//-------------------------------------------------------------------------------------------------------------
// Registers the window class.

ATOM MyRegisterClass(HINSTANCE hInstance)
{
LRESULT CALLBACK WndProcMain(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

WNDCLASSEX wcex;

wcex.cbSize=sizeof(WNDCLASSEX); wcex.style=CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
wcex.lpfnWndProc=WndProcMain;
wcex.cbClsExtra=0; wcex.cbWndExtra=0;
wcex.hInstance=hInstance;
wcex.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_PHOTONICS_VISUAL));
wcex.hCursor=LoadCursor(NULL,IDC_ARROW);
wcex.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
wcex.lpszMenuName=MAKEINTRESOURCE(IDC_PHOTONICS_VISUAL);
wcex.lpszClassName=szWindowClass;
wcex.hIconSm=LoadIcon(wcex.hInstance,MAKEINTRESOURCE(IDI_SMALL));
return RegisterClassEx(&wcex);
}

//-------------------------------------------------------------------------------------------------------------
// Saves instance handle and creates main window.

BOOL InitInstance(HINSTANCE hInstance,int nCmdShow)
{
HWND hWnd;

hInst=hInstance;
hWnd=CreateWindow(szWindowClass,szTitle,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,0,CW_USEDEFAULT,0,NULL,NULL,hInstance,NULL);
if(!hWnd) return FALSE; ShowWindow(hWnd,nCmdShow); UpdateWindow(hWnd); return TRUE;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ����� ����������.

BYTE GetPath(void)
{
BYTE StrSymbConv(char *StrI,char *StrC,size_t szStrC,BYTE flag); // �������������� �������� ������ � ������� ��� ����� �������.
void ErrMessage(void); // ������ ��������� �� ������.

BYTE ber; size_t ln; char *cp,*str;

if(hInst==NULL) return 1;
if(GetModuleFileName(hInst,PathToProgDir,strL_Path)==0) { ErrMessage(); return 2;}
ln=strlen(PathToProgDir); if(ln==0) return 3;
str=NULL; ber=0;
if(AllocString(&str,ln)!=0) { ber=4; goto end;}
if(StrSymbConv(PathToProgDir,str,ln+1,1)!=0) { ber=5; goto end;}
cp=strstr(str,".EXE"); if(cp==NULL) { ber=6; goto end;} *cp='\0';
cp=strrchr(str,'\\'); if(cp==NULL) { ber=7; goto end;} cp++; *cp='\0';
ln=strlen(str); PathToProgDir[ln]='\0';
end: FreeString(&str); return ber;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� ���������� ������.

//-----------------------------------------------------------------------------------------------------------
// �����������.

clTask::clTask(void)
{
flPol=0; Theta=0.; L1=M1=0; dz=0.; EpsInc=EpsOut=Cmplx_1;
}

//-----------------------------------------------------------------------------------------------------------
// ������ ������ �� �����.

BYTE clTask::Read(FILE *fp)
{
if(fp==NULL) return 1;

if(fscanf(fp,"%lf\n",&wLength)==EOF) return 2; if(fscanf(fp,"%lf\n",&Theta)==EOF) return 3;
if(fscanf(fp,"%d\n",&flPol)==EOF) return 4; if(fscanf(fp,"%lf %lf\n",&EpsInc.re,&EpsInc.im)==EOF) return 5;
if(fscanf(fp,"%lf %lf\n",&EpsOut.re,&EpsOut.im)==EOF) return 6; if(fscanf(fp,"%d %d\n",&L1,&M1)==EOF) return 6;
if(fscanf(fp,"%lf\n",&dz)==EOF) return 6;
return 0;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ��������� ���������.

//-----------------------------------------------------------------------------------------------------------
// �����������.

strMaterial::strMaterial(void)
{
chr=' '; R=G=B=0; name=NULL; name=new char[szNameSubst];
}

//-----------------------------------------------------------------------------------------------------------
// ����������.

strMaterial::~strMaterial(void)
{
SAFE_DELETE_ARR(name);
}

//-----------------------------------------------------------------------------------------------------------
// ������ ������ � ��������� �� �����.

BYTE strMaterial::Read(FILE *fp)
{
if(fp==NULL) return 1; if(name==NULL) return 2;
if(fscanf(fp,"%s",name)==EOF) return 3;
if(fscanf(fp,"%lf%lf %c",&eps.re,&eps.im,&chr)==EOF) return 4;
return 0;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� ������� ���� ����������, ������������ � ���������.

//-----------------------------------------------------------------------------------------------------------
// �����������.

clMaterialAll::clMaterialAll(void)
{
Zero();
}

//-----------------------------------------------------------------------------------------------------------
// ����������.

clMaterialAll::~clMaterialAll(void)
{
Free();
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ����������.

void clMaterialAll::Zero(void)
{
Mat=NULL; N=0;
}

//-----------------------------------------------------------------------------------------------------------
// ������������ ������.

void clMaterialAll::Free(void)
{
SAFE_DELETE_ARR(Mat); N=0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������ ��� �������.

BYTE clMaterialAll::Alloc(int N_)
{
Free(); if(N_<=0) return 1; N=N_; Mat=new strMaterial[N]; if(Mat==NULL) return 2; return 0;
} 

//-----------------------------------------------------------------------------------------------------------
// ��������.

BYTE clMaterialAll::IsOK(void) const
{
if(N<=0) return 1; if(Mat==NULL) return 2; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ������ ������ � ���������� �� �����.

BYTE clMaterialAll::Read(FILE *fp)
{
int i,N_;

if(fp==NULL) return 1;
if(fscanf(fp,"%d",&N_)==EOF) return 2; if(Alloc(N_)!=0) return 3;
for(i=0;i<N;i++) if(Mat[i].Read(fp)!=0) return 4; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ��������� �� ��������� ����������.

strMaterial *clMaterialAll::Get(int num)
{
if(IsOK()!=0) return NULL; if(num<0||num>=N) return NULL; return Mat+num;
}

//-----------------------------------------------------------------------------------------------------------
// ����� ������� ��������� � ����������� ��� ������ � ������ ����.

int clMaterialAll::GetNum(char chr) const
{
int i,num;

if(IsOK()!=0) return -1; num=-2;
for(i=0;i<N;i++) { if(Mat[i].chr!=chr) continue; num=i; break;} return num;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// C�������� ��������� ����� ������ ���������.

//-----------------------------------------------------------------------------------------------------------
// �����������.

strSymbCol::strSymbCol(void)
{
Zero();
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ����������.

void strSymbCol::Zero(void)
{
R=G=B=0; symb=' ';
}

//-----------------------------------------------------------------------------------------------------------
// ������ ��������� �� �����.

BYTE strSymbCol::Read(FILE *fp)
{
if(fp==NULL) return 1;
if(fscanf(fp,"%c%d%d%d",&symb,&R,&G,&B)==EOF) return 2;
if(R>255) R=255; if(G>255) G=255; if(B>255) B=255;
if(R<0) R=0; if(G<0) G=0; if(B<0) B=0; // ��������.
return 0;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� ��������� ������ ��� ���� ������ ����������.

//-----------------------------------------------------------------------------------------------------------
// �����������.

clDB_SymbCol::clDB_SymbCol(void)
{
Zero();
}

//-----------------------------------------------------------------------------------------------------------
// �����������.

clDB_SymbCol::~clDB_SymbCol(void)
{
Free();
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ����������.

void clDB_SymbCol::Zero(void)
{
N=0; Arr=NULL;
}

//-----------------------------------------------------------------------------------------------------------
// ������������ ������.

void clDB_SymbCol::Free(void)
{
SAFE_DELETE_ARR(Arr); N=0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������ ��� �������.

BYTE clDB_SymbCol::Alloc(int N_)
{
Free(); if(N_<=0) return 1; N=N_;
Arr=new strSymbCol[N]; if(Arr==NULL) return 2; return 0;
} 

//-----------------------------------------------------------------------------------------------------------
// ��������.

BYTE clDB_SymbCol::IsOK(void) const
{
if(N<=0) return 1; if(Arr==NULL) return 2; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ����� ������� � ��������� ������� R_,G_,B_.

void clDB_SymbCol::Symb_to_RGB(char symb_,BYTE *R_,BYTE *G_,BYTE *B_)
{
BYTE flFound; int i; struct strSymbCol *pC;

if(R_==NULL||G_==NULL||B_==NULL) return; flFound=0;
for(i=0;i<N;i++) { pC=Arr+i; if(symb_==pC->symb) { *R_=pC->R; *G_=pC->G; *B_=pC->B; flFound=1; break;}}
if(flFound==0) { *R_=0; *G_=0; *B_=0;}
}

//-----------------------------------------------------------------------------------------------------------
// ������ ��������� �� �����.

BYTE clDB_SymbCol::Read(char *fname)
{
BYTE err; int i,N_; FILE *fp;

if(fname==NULL) return 1;

err=0;
fp=NULL; fp=fopen(fname,"r"); if(fp==NULL) return 2;

if(fscanf(fp,"%d",&N_)==EOF) { err=3; goto end;} if(Alloc(N_)!=0) { err=4; goto end;} 
for(i=0;i<N;i++) { fscanf(fp,"\n"); if(Arr[i].Read(fp)!=0) { err=5; goto end;}}

end: SAFE_CLOSE(fp); return err;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ��������� ������ ���� �� ��� z ��������� ���������.

//-----------------------------------------------------------------------------------------------------------
// �����������.

strLay::strLay(void)
{
Zero();
}

//-----------------------------------------------------------------------------------------------------------
// ����������.

strLay::~strLay(void)
{
Free();
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ����������.

void strLay::Zero(void)
{
depth=0.; dz=0.; nDiv=0; laySize=0; GeomSymbs=NULL;
}

//-----------------------------------------------------------------------------------------------------------
// ������������ ������.

void strLay::Free(void)
{
SAFE_DELETE_ARR(GeomSymbs); laySize=0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������.

BYTE strLay::Alloc(int N)
{
if(N<=0) return 1;

Free(); laySize=N; GeomSymbs=new char[laySize+1]; if(GeomSymbs==NULL) return 2;
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������.

BYTE strLay::IsOK(void)
{
if(depth<=0.) return 1; if(dz<=0.) return 2; if(nDiv<1) return 3; if(laySize<=0) return 4;
if(XDistr.IsOK()!=0) return 5;
if(YDistr.IsOK()!=0) return 6;
if(ZDistr.IsOK()!=0) return 7;
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ������ ���� �� �����.

BYTE strLay::Read(FILE *fp)
{
BYTE err; int num,i; char *str;

if(fp==NULL) return 1;

err=0;
// ��������� ������ ��� ��������������� ������.
str=NULL; str=new char[laySize_Max]; if(str==NULL) return 1;

// ������ � 'GeomSymbs'.
#if flScanf_S!=0
if(fscanf_s(fp,"%s",str,laySize_Max)==EOF) { err=2; goto end;}
#else
if(fscanf(fp,"%s",str)==EOF) { err=3; goto end;}
#endif
num=strlen(str); if(num<=0) { err=4; goto end;}
if(Alloc(num+1)!=0) { err=5; goto end;}
for(i=0;i<laySize;i++) GeomSymbs[i]=str[i]; GeomSymbs[laySize]='\0';

// ������ ��� ���������.
if(fscanf(fp," %lf %lf %d",&depth,&dz,&nDiv)==EOF) { err=6; goto end;}

end: SAFE_DELETE_ARR(str); return err;
}

//-----------------------------------------------------------------------------------------------------------
// ������ �� ����� ������������� �����.

BYTE strLay::ReadFieldDistr(FILE *file)
{
if(file==NULL) return 1;
if(XDistr.Read(file)!=0) return 2;
if(YDistr.Read(file)!=0) return 3;
if(ZDistr.Read(file)!=0) return 4;
return 0;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� ��������� ���������.

//-----------------------------------------------------------------------------------------------------------
// �����������.

clCrystal::clCrystal(void)
{
Zero();
}

//-----------------------------------------------------------------------------------------------------------
// ����������.

clCrystal::~clCrystal(void)
{
Free();
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ����������.

void clCrystal::Zero(void)
{
Lays=NULL; laysNum=0; Period=0.;
}

//-----------------------------------------------------------------------------------------------------------
// ������������ ������.

void clCrystal::Free(void)
{
SAFE_DELETE_ARR(Lays); laysNum=0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������ ��� �������.

BYTE clCrystal::Alloc(int laysNum_)
{
Free(); if(laysNum_<=0) return 1; laysNum=laysNum_;
Lays=new strLay[laysNum]; if(Lays==NULL) return 2; return 0;
} 

//-----------------------------------------------------------------------------------------------------------
// ��������.

BYTE clCrystal::IsOK(void) const
{
if(laysNum<=0) return 1; if(Lays==NULL) return 2; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������.

BYTE clCrystal::IsOKLay(void) const
{
int i;

if(IsOK()!=0) return 1; for(i=0;i<laysNum;i++) if(Lays[i].IsOK()!=0) return 2; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ��������� �� ������� ���� � ������� 'num'.

strLay *clCrystal::Get(int num)
{
if(IsOK()!=0) return NULL; if(num<0||num>=laysNum) return NULL; return Lays+num;
}

//-----------------------------------------------------------------------------------------------------------
// ������ ������ � ��������� �� �����.

BYTE clCrystal::Read(FILE *fp)
{
int i,laysNum_;

if(fp==NULL) return 1;

if(fscanf(fp,"%d\n",&laysNum_)==EOF) return 2;
if(Alloc(laysNum_)!=0) return 3; // ��������� ������ ��� ������� �����. 
if(fscanf(fp,"%lf",&Period)==EOF) return 4;
for(i=0;i<laysNum;i++) { if(fscanf(fp,"\n",&laysNum_)==EOF) return 5; if(Lays[i].Read(fp)!=0) return 6;}
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ������ ������������� ����.

BYTE clCrystal::ReadFieldDistr(FILE *file)
{
int i;

if(file==NULL) return 1; if(IsOK()!=0) return 2;
for(i=0;i<laysNum;i++) if(Lays[i].ReadFieldDistr(file)!=0) return 3; return 0;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� �������� ����.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// �������������� ��������.

#define idT_Main_CheckCurPos 1 // ������ �������� ��������� �������.
#define uT_Main_CheckCurPos 500 // ����� ������� �������� ��������� �������.

//-----------------------------------------------------------------------------------------------------------
// �����������.

clMain::clMain(void)
{
Zero(); Alloc();
}

//-----------------------------------------------------------------------------------------------------------
// ����������.

clMain::~clMain(void)
{
FreeDlg(); Free();
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ��������������� � ����������.

void clMain::Zero(void)
{
hwnd=hDlgCntrl=NULL; BmpDiag=BmpPalP=BmpPalPN=BmpAnglDisp=NULL; FileName=NULL; ZeroDlg(); ZeroDistr(); cur_wait=NULL;
y0=0; MashtabX=MashtabY=0.; DepthCryst=0.; cx1=cx2=cz1=cz2=-1.; DistrStep=1.;
InitAmpNorm(); flTypDraw=TypDraw_X; flAnglDisp=0; TypImage=TypScale=0; flGrid=1; flCompDistr=0; flCurMouse=0;
}

//-----------------------------------------------------------------------------------------------------------
// �������� �������� �� ������.

void clMain::Free(void)
{
FreeDistr(); FreeAnglDispDistr(); SAFE_DELETE(BmpDiag); SAFE_DELETE(BmpPalP); SAFE_DELETE(BmpPalPN);
SAFE_DELETE(BmpAnglDisp); FreeString(&FileName);
}

//-----------------------------------------------------------------------------------------------------------
// �������� ��� �������� ������� ������ �������� ����.

BYTE clMain::Alloc(void)
{
Free();
BmpDiag=new clBmpPict(); if(BmpDiag==NULL) return 1;
BmpPalP=new clBmpPict(); if(BmpPalP==NULL) return 2;
BmpPalPN=new clBmpPict(); if(BmpPalPN==NULL) return 3;
BmpAnglDisp=new clBmpPict(); if(BmpAnglDisp==NULL) return 4;
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� �������� ��� ����������� ����.

void clMain::ZeroDlg(void)
{
ZeroBrushes(); ZeroFonts();
}

//-----------------------------------------------------------------------------------------------------------
// �������� �������� ��� ����������� ����.

void clMain::FreeDlg(void)
{
FreeBrushes(); FreeFonts();
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������ ��� ������������ ����.

void clMain::ZeroBrushes(void)
{
hBrushBkg=hBrushDial=NULL;
}

//-----------------------------------------------------------------------------------------------------------
// �������� ������ ��� ������������ ����.

void clMain::FreeBrushes(void)
{
SAFE_DELETE_OBJECT(hBrushBkg);
SAFE_DELETE_OBJECT(hBrushDial);
}

//-----------------------------------------------------------------------------------------------------------
// �������� ������ ��� ������������ ����.

BYTE clMain::CreateBrushes(void)
{
FreeBrushes();
hBrushBkg=CreateSolidBrush(COL_WHITE); if(hBrushBkg==NULL) return 1;
hBrushDial=CreateSolidBrush(ColDial); if(hBrushDial==NULL) return 2;
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� �������.

void clMain::ZeroFonts(void)
{
hFontListLay=NULL;
}

//-----------------------------------------------------------------------------------------------------------
// �������� �������.

void clMain::FreeFonts(void)
{
SAFE_DELETE_OBJECT(hFontListLay);
}

//-----------------------------------------------------------------------------------------------------------
// �������� �������.

void clMain::CreateFonts(void)
{
HFONT GetFontConstWid(char *nameFont,SHRT Wid,SHRT Hei); // �������� ������.

FreeFonts(); hFontListLay=GetFontConstWid("Courier New",0,-12);
}

//-----------------------------------------------------------------------------------------------------------
// ������������� �������� ���������� � ��������� �� ��������� ����������.

void clMain::InitAmpNorm(void)
{
flTypNorm=0; pAmpNorm=AmpNormArr; // ��� ���������� � ��������� �� ��������� ����������.
AmpNormArr[typNorm_E]=AmpNormE_Stand; // ���� 'E'.
AmpNormArr[typNorm_H]=AmpNormH_Stand; // ���� 'H'.
AmpNormArr[typNorm_E2]=AmpNormE2_Stand; // ������� ���� 'E'.
AmpNormArr[typNorm_H2]=AmpNormH2_Stand; // ������� ���� 'H'.
AmpNormArr[typNorm_FvFc]=AmpNormFvFc_Stand; // ��������� ������������ 'ExE*' ��� 'HxH*'.
AmpNormArr[typNorm_Poynt]=AmpNormPoynt_Stand; // ���������� � ������ ������� ���������.
AmpNormArr[typNorm_EImE2]=AmpNormEImE2_Stand; // ������������� �������� ������ 'eps".E^2'.
AmpNormArr[typNorm_ReEps]=AmpNormReEps_Stand; // �������������� ����� 'eps'.
AmpNormArr[typNorm_ImEps]=AmpNormImEps_Stand; // ������ ����� 'eps'.
AmpNormArr[typNorm_AnglDisp]=AmpNormAnglDisp_Stand; // ������� ���������.
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ���������� �� �������������.

void clMain::ZeroDistr(void)
{
flDistr=flChSizeImg=0; flDComp=UCHAR_MAX; xSizeD=ySizeD=xSizeDM=ySizeDM=0; DistrX=DistrY=DistrZ=NULL;
DistrF=DistrFAbs=DistrSqE=DistrSqH=DistrFvFc=DistrPx=DistrPz=DistrPAbs=DistrDivP=DistrE2EpsIm=NULL;
DistrReEps=DistrImEps=NULL;
}

//-----------------------------------------------------------------------------------------------------------
// �������� �������������.

void clMain::FreeDistr(void)
{
BYTE ind; double **pD; complex **pC;

flDistr=flChSizeImg=0; flDComp=UCHAR_MAX; xSizeD=ySizeD=xSizeDM=ySizeDM=0;
for(ind=0;ind<3;ind++) {
switch(ind) { default: continue;
case 0: pC=&DistrX; break;
case 1: pC=&DistrY; break;
case 2: pC=&DistrZ; break;}
SAFE_DELETE_ARR(*pC);}

for(ind=0;ind<12;ind++) {
switch(ind) { default: continue;
case 0: pD=&DistrF; break;
case 1: pD=&DistrFAbs; break;
case 2: pD=&DistrSqE; break;
case 3: pD=&DistrSqH; break;
case 4: pD=&DistrFvFc; break;
case 5: pD=&DistrPx; break;
case 6: pD=&DistrPz; break;
case 7: pD=&DistrPAbs; break;
case 8: pD=&DistrDivP; break;
case 9: pD=&DistrE2EpsIm; break;
case 10: pD=&DistrReEps; break;
case 11: pD=&DistrImEps; break;}
SAFE_DELETE_ARR(*pD);}
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������ ��� �������������.

BYTE clMain::AllocDistr(int xSizeD_,int ySizeD_)
{
BYTE ind,ber; UINT sz; double **pD; complex **pC;

FreeDistr(); if(xSizeD_<=0||ySizeD_<=0) return 1; ber=0;
xSizeD=xSizeDM=xSizeD_; ySizeD=ySizeDM=ySizeD_; sz=(UINT)xSizeD*(UINT)ySizeD;

for(ind=0;ind<3;ind++) {
switch(ind) { default: continue;
case 0: pC=&DistrX; break;
case 1: pC=&DistrY; break;
case 2: pC=&DistrZ; break;}
*pC=new complex[sz]; if(*pC==NULL) { ber=2; goto end;}}

for(ind=0;ind<12;ind++) {
switch(ind) { default: continue;
case 0: pD=&DistrF; break;
case 1: pD=&DistrFAbs; break;
case 2: pD=&DistrSqE; break;
case 3: pD=&DistrSqH; break;
case 4: pD=&DistrFvFc; break;
case 5: pD=&DistrPx; break;
case 6: pD=&DistrPz; break;
case 7: pD=&DistrPAbs; break;
case 8: pD=&DistrDivP; break;
case 9: pD=&DistrE2EpsIm; break;
case 10: pD=&DistrReEps; break;
case 11: pD=&DistrImEps; break;}
*pD=new double[sz]; if(*pD==NULL) { ber=3; goto end;}}

end: if(ber!=0) FreeDistr(); return ber;
}

//-----------------------------------------------------------------------------------------------------------
// ������������ ������ ��� ������������� ������� ���������.

void clMain::FreeAnglDispDistr(void)
{
SAFE_DELETE_ARR(AnglDispDistr); xSizeAnglD=0; ySizeAnglD=0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������ ��� ������������� ������� ���������.

BYTE clMain::AllocAnglDispDistr(int xSizeD_,int ySizeD_)
{
UINT sz;

FreeAnglDispDistr(); if(xSizeD_<=0||ySizeD_<=0) return 1;
xSizeAnglD=xSizeD_; ySizeAnglD=ySizeD_;
sz=(UINT)xSizeAnglD*(UINT)ySizeAnglD;
AnglDispDistr=new complex[sz]; if(AnglDispDistr==NULL) return 2;
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// �������� �������� �������������.

BYTE clMain::IsOK_Distr(void)
{
if(xSizeD<=0||ySizeD<=0) return 1;
if(DistrX==NULL) return 2; if(DistrY==NULL) return 3; if(DistrZ==NULL) return 4;
if(DistrF==NULL) return 5; if(DistrFAbs==NULL) return 6;
if(DistrSqE==NULL) return 7; if(DistrSqH==NULL) return 8;
if(DistrFvFc==NULL) return 9; if(DistrPx==NULL) return 10; if(DistrPz==NULL) return 11;
if(DistrPAbs==NULL) return 12; if(DistrDivP==NULL) return 13; if(DistrE2EpsIm==NULL) return 14;
if(DistrReEps==NULL) return 15; if(DistrImEps==NULL) return 16; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// �������� ������� ���������.

BYTE clMain::IsOK_DispAngl(void)
{
if(Task.wLen_Fin<=0.) return 1; if(Task.wLen_St<=0.) return 2;
if(Task.Th_Fin<-90.||Task.Th_Fin>90.) return 3; if(Task.Th_St<-90.||Task.Th_St>90.) return 4;
if(AnglDisp.IsOK()!=0) return 5;
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ��������� �� ������ �������������.

double *clMain::GetDistr(void)
{
double *pD;

switch(flTypDraw) { default: pD=NULL; break;
case TypDraw_X: case TypDraw_Y: case TypDraw_Z: pD=DistrF; break; // ������������ ������� ��������� �����.
case TypDraw_Full: pD=DistrFAbs; break; // ������������ ���� 'E' ('p') ��� 'H' ('s').
case TypDraw_SqE: pD=DistrSqE; break; // ������� ��������� ���� 'E'.
case TypDraw_SqH: pD=DistrSqH; break; // ������� ��������� ���� 'H'.
case TypDraw_FvFc: pD=DistrFvFc; break; // ��������� ������������ 'ExE*' ��� 'HxH*'.
case TypDraw_Px: pD=DistrPx; break; // X-� ���������� ������� ���������.
case TypDraw_Pz: pD=DistrPz; break; // Z-� ���������� ������� ���������.
case TypDraw_PAbs: pD=DistrPAbs; break; // ������ ������� ���������.
case TypDraw_DivP: pD=DistrDivP; break; // ����������� ������� ���������.
case TypDraw_EImE2: pD=DistrE2EpsIm; break; // ������������� �������� ������ 'eps".E^2'.
case TypDraw_ReEps: pD=DistrReEps; break; // ������������� �������������� ����� 'eps'.
case TypDraw_ImEps: pD=DistrImEps; break; // ������������� ������ ����� 'eps'.
}
return pD;
}

//-----------------------------------------------------------------------------------------------------------
// ���������� ������� ������ ���������� ���� ��� ���������� ���� �������������.

BYTE clMain::FillDistrComp(void)
{
int i,j,jv,jSh; complex **pC;

switch(flTypDraw) { default: return 0;
case TypDraw_X: pC=&DistrX; break; // ������������ ���� 'Ex' ('p') ��� 'Hx' ('s').
case TypDraw_Y: pC=&DistrY; break; // ������������ ���� 'Hy' ('p') ��� 'Ey' ('s').
case TypDraw_Z: pC=&DistrZ; break; // ������������ ���� 'Ez' ('p') ��� 'Hz' ('s').
}
if(pC==NULL) return 1; if(*pC==NULL) return 2; if(DistrF==NULL) return 3; if(xSizeD<=0||ySizeD<=0) return 4;
for(i=0;i<ySizeD;i++) { jSh=i*xSizeD; for(j=0;j<xSizeD;j++) { jv=j+jSh; DistrF[jv]=abs((*pC)[jv]);}}
flDComp=flTypDraw; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ������������ ������ ��� �����������.

void clMain::FreeBmpAll(void)
{
if(BmpDiag!=NULL) BmpDiag->Free(); // ������������ ������ � ������ ����������� �������������.
if(BmpPalP!=NULL) BmpPalP->Free(); // ������������ ������ � ������ �������.
if(BmpPalPN!=NULL) BmpPalPN->Free(); // ������������ ������ � ������ �������.
if(BmpAnglDisp!=NULL) BmpAnglDisp->Free(); // ������������ ������ � ������ ����������� ������������� ������� ���������.
}

//-----------------------------------------------------------------------------------------------------------
// �������� � ������ ������ ���������.

BYTE clMain::OnCreate(HWND hwnd_)
{
int dx,dy;

if(hwnd_==NULL) return 1; hwnd=hwnd_;
if(CreateBrushes()!=0) return 2; // �������� ������ ��� ������������ ����.
CreateFonts(); // �������� �������.
cur_wait=LoadCursor(NULL,IDC_WAIT);
// ���������� ������ ������.
PalDistrP.FillColor(ColBaseDistrP);
PalDistrN.FillColor(ColBaseDistrN);

if(CreateDlgCntrl()!=0) return 3; // �������� ����������� ���� ����������.

// ����������� ���������� ��������� ������� ���������.
if(hDlgCntrl==NULL) return 4; if(GetClientRect(hDlgCntrl,&rcCntrl)==FALSE) return 5;
y0=rcCntrl.bottom-rcCntrl.top;
if(GetClientRect(hwnd,&rc)==FALSE) return 6;

// ������������ ������������ �������� ����.
if(GetWindowRect(GetDesktopWindow(),&rc)==FALSE) return 7;
dx=(int)(rc.right-rc.left);
dy=(int)(rc.bottom-rc.top);
if(SetWindowPos(hwnd,NULL,0,0,dx,dy,SWP_NOZORDER)==FALSE) return 8;

FillListFiles(); // ���������� ���������������� ������ ������� ������.
SetTimer(hDlgCntrl,idT_Main_CheckCurPos,uT_Main_CheckCurPos,NULL);
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// �������� ����������� ������������ ����.

BYTE clMain::CreateDlgCntrl(void)
{
LRESULT CALLBACK DlgProcCntrlMain(HWND,UINT,WPARAM,LPARAM); // ����������� ���� �������� ����.

if(hwnd==NULL) return 1; if(hInst==NULL) return 2; CloseWin_(&hDlgCntrl);
hDlgCntrl=CreateDialogParam(hInst,(LPCTSTR)IDD_CNTRL_MAIN,hwnd,(DLGPROC)DlgProcCntrlMain,(LPARAM)this);
if(hDlgCntrl==NULL) return 3;
SetDlgCntrlCombo(); SetDlgCntrl(); return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ���������� ���������������� ������ ������� ������.

BYTE clMain::FillListFiles(void)
{
BYTE num; int id;

if(hDlgCntrl==NULL) return 1; id=IDC_COMBO_OPEN_FILE; ClearCombo(hDlgCntrl,id);
if(Fill_CLB_Files(hDlgCntrl,id,0,PathToProgDir,NULL,extFileDistr,1)!=0) return 2;
if(FileName!=NULL) { if(FindTxtStringCombo(hDlgCntrl,id,FileName,&num)==0) SetSelCombo(hDlgCntrl,id,num);}
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// �������� �����.

BYTE clMain::OpenFile(void)
{
BYTE num;

if(GetSelCombo(hDlgCntrl,IDC_COMBO_OPEN_FILE,&num)!=0) return 1;
if(GetTxtStringSelCombo(hDlgCntrl,IDC_COMBO_OPEN_FILE,TxtStr,strL_Txt)!=0) return 2;
if(LoadFile(TxtStr)!=0) return 3; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// �������� ����� � ������������� ��������.

BYTE clMain::LoadFile(char *fName)
{
if(fName==NULL) return 1; CloseFile();
if(ReadFile(fName)!=0) { sprintf(TxtStr,"Error in reading of input file !"); MessageBox(NULL,TxtStr,"",MB_EX); return 2;}
if(DupString(&FileName,fName)!=0) FreeString(&FileName);
SetDlgCntrlCombo(); DialogInfo(); UpdateWindow_(hwnd); flAnglDisp=0; CreateComputeDistrAll_(); return 0;
}

//-----------------------------------------------------------------------------------------------------------
// �������� ����������.

void clMain::CloseFile(void)
{
FreeDistr(); FreeBmpAll(); Cryst.Free(); UpdateWindow_(hwnd); SetStateBtnRedraw(); FreeString(&FileName);
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������� ��������� �������� ����.

LRESULT clMain::MsgCommand(UINT msg,WPARAM wParam,LPARAM lParam,BYTE *flag)
{
HDC hdc; PAINTSTRUCT ps;

if(flag==NULL) return 0L; *flag=0; if(hwnd==NULL) return 0L; if(msg==WM_CREATE) return 0L;

switch(msg) { default: break;

// WM_ERASEBKGND ............................................................................................
case WM_ERASEBKGND: *flag=1; return 0L;

// WM_SIZE ..................................................................................................
case WM_SIZE: *flag=1; if(wParam==SIZE_MINIMIZED) break;
if(CheckSizeImg()!=0) { flChSizeImg=1; SetStateBtnRedraw();} break;

// WM_MOUSEMOVE .............................................................................................
case WM_MOUSEMOVE: *flag=1; SetFocus(hwnd); OnMouseDistr(lParam,0); break;

// WM_LBUTTONDBLCLK .........................................................................................
case WM_LBUTTONDBLCLK: *flag=1; SetFocus(hwnd); OnMouseDistr(lParam,1); break;

// WM_RBUTTONDBLCLK .........................................................................................
case WM_RBUTTONDBLCLK: *flag=1; SetFocus(hwnd); OnMouseDistr(lParam,2); break;

// WM_COMMAND ...............................................................................................
case WM_COMMAND: if(Command(wParam)==0) *flag=1; break;

// WM_PAINT .................................................................................................
case WM_PAINT: *flag=1; hdc=BeginPaint(hwnd,&ps);
if(OnPaintDistr(hdc)!=0) OnPaintDistrDef(hdc); EndPaint(hwnd,&ps); break;

// WM_CLOSE .................................................................................................
case WM_CLOSE: *flag=1; DestroyWindow(hwnd); break;
}

return 0L;
}

//-----------------------------------------------------------------------------------------------------------
// �������.

BYTE clMain::Command(WPARAM wParam)
{
INT_PTR CALLBACK DlgAbout(HWND,UINT,WPARAM,LPARAM); // ������� ����������� ���� � ���������.

BYTE flag; int wmId;

if(hwnd==NULL) return 1; flag=0; wmId=LOWORD(wParam);

switch(wmId) { default: flag=2; break;

// IDM_INFO .................................................................................................
case IDM_INFO: DialogInfo(); break;

// IDM_READANGLDISP_T .........................................................................................
case IDM_READANGLDISP_T: ReadAnglDisp(0); flAnglDisp=1; CreateComputeAnglDisp(); 
sprintf(TxtStr,"wLen_St wLen_Fin dwLen %lf %lf %lf Th_St Th_Fin dTh %lf %lf %lf",Task.wLen_St,Task.wLen_Fin,Task.dwLen,Task.Th_St,Task.Th_Fin,Task.dTh); MessageBox(NULL,TxtStr,"",MB_EX); 
DrawAnglDisp_(); UpdateWindow_(hwnd); break;

// IDM_READANGLDISP_R .........................................................................................
case IDM_READANGLDISP_R: ReadAnglDisp(1); flAnglDisp=1; CreateComputeAnglDisp();
sprintf(TxtStr,"wLen_St wLen_Fin dwLen %lf %lf %lf Th_St Th_Fin dTh %lf %lf %lf",Task.wLen_St,Task.wLen_Fin,Task.dwLen,Task.Th_St,Task.Th_Fin,Task.dTh); MessageBox(NULL,TxtStr,"",MB_EX); 
DrawAnglDisp_(); UpdateWindow_(hwnd); break; 

// IDM_READANGLDISP_A .........................................................................................
case IDM_READANGLDISP_A: ReadAnglDisp(2); flAnglDisp=1; CreateComputeAnglDisp();
sprintf(TxtStr,"wLen_St wLen_Fin dwLen %lf %lf %lf Th_St Th_Fin dTh %lf %lf %lf",Task.wLen_St,Task.wLen_Fin,Task.dwLen,Task.Th_St,Task.Th_Fin,Task.dTh); MessageBox(NULL,TxtStr,"",MB_EX); 
DrawAnglDisp_(); UpdateWindow_(hwnd); break;

// IDM_ABOUT ................................................................................................
case IDM_ABOUT: DialogBox(hInst,(LPCTSTR)IDD_ABOUTBOX,hwnd,(DLGPROC)DlgAbout); break;

// IDM_EXIT .................................................................................................
case IDM_EXIT: DestroyWindow(hwnd); break;
}
return flag;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������� ��������� ���� ����������.

LRESULT clMain::MsgCommandCntrl(UINT msg,WPARAM wParam,LPARAM lParam,BYTE *flag)
{
int id; HDC hdc;

if(flag==NULL) return 0L; *flag=0; if(hDlgCntrl==NULL) return 0L; if(msg==WM_INITDIALOG) return 0L;

switch(msg) { default: break;

// WM_CTLCOLORSTATIC ........................................................................................
case WM_CTLCOLORSTATIC: hdc=(HDC)wParam; id=GetDlgCtrlID((HWND)lParam); if(id<=0) break; *flag=1;
SetBkColor(hdc,GetSysColor(COLOR_WINDOW)); SetTextColor(hdc,GetSysColor(COLOR_BTNTEXT));
SetBkMode(hdc,TRANSPARENT);
if(id==IDC_COOR_X||id==IDC_COOR_Z||id==IDC_VAL_A||id==IDC_VAL_B) return (LRESULT)hBrushBkg;
return (LRESULT)hBrushDial;

// WM_TIMER .................................................................................................
case WM_TIMER: *flag=1;
if(wParam==idT_Main_CheckCurPos) { CheckCurPos(); break;}
break;

// WM_COMMAND ...............................................................................................
case WM_COMMAND: if(CommandCntrl(wParam)==0) *flag=1; break;
}

return 0L;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������ ���� ����������.

BYTE clMain::CommandCntrl(WPARAM wParam)
{
BYTE fl; int id; double coe,AmpNorm_;

if(hDlgCntrl==NULL) return 1; id=LOWORD(wParam);

switch(id) { default: return 2;

// IDC_UPDATE_DIR ............................................................................................
case IDC_UPDATE_DIR: FillListFiles(); break;

// IDC_COMBO_OPEN_FILE .......................................................................................
case IDC_COMBO_OPEN_FILE: if(HIWORD(wParam)!=CBN_SELCHANGE) break; OpenFile(); break;

// ��������� ��������� ���������� �������.
// IDC_AMPNORM_M IDC_AMPNORM_P ...............................................................................
case IDC_AMPNORM_M: case IDC_AMPNORM_P: if(pAmpNorm==NULL) break; coe=(double)sqrt(2.);
if(id==IDC_AMPNORM_M) *pAmpNorm*=coe; else *pAmpNorm/=coe; SetAmpNorm(); if(TypImage!=0) break;
DrawDistr_(); UpdateWindow_(hwnd); break;

// IDC_AMPNORM_OK ............................................................................................
case IDC_AMPNORM_OK: if(pAmpNorm==NULL) break; if(GetDlEdt(hDlgCntrl,IDC_AMPNORM,&AmpNorm_)!=0) break;
if(AmpNorm_<0) { SetAmpNorm(); break;} *pAmpNorm=AmpNorm_; SetAmpNorm(); if(TypImage!=0) break;
DrawDistr_(); UpdateWindow_(hwnd); break;

// IDC_IDC_TYPE_DRAW .........................................................................................
case IDC_TYPE_DRAW: if(HIWORD(wParam)!=CBN_SELCHANGE) break; OnChangeTypDraw(); if(TypImage!=0) break;
DrawDistr_(); UpdateWindow_(hwnd); break; 

// IDC_RADIO_FSCREEN IDC_RADIO_ACCORD_SCALE ..................................................................
case IDC_RADIO_ACCORD_SCALE: case IDC_RADIO_FSCREEN:
if(GetPosRadio(hDlgCntrl,IDC_RADIO_ACCORD_SCALE,IDC_RADIO_FSCREEN,&fl)!=0) break; if(fl==TypScale) break;
TypScale=fl; CreateComputeDistrAll_(); break;

// IDC_RADIO_IMG_FIELDS IDC_RADIO_IMG_CRYSTAL ................................................................
case IDC_RADIO_IMG_FIELDS: case IDC_RADIO_IMG_CRYSTAL:
if(GetPosRadio(hDlgCntrl,IDC_RADIO_IMG_FIELDS,IDC_RADIO_IMG_CRYSTAL,&fl)!=0) break; if(fl==TypImage) break;
TypImage=fl; ChooseDraw(); UpdateWindow_(hwnd); break;

// IDC_REDRAW_IMAGE ..........................................................................................
case IDC_REDRAW_IMAGE: if(flCompDistr!=0) break; CreateComputeDistrAll_(); break;

// IDC_CHECK_GRID ............................................................................................
case IDC_CHECK_GRID: if(GetChBox(hDlgCntrl,id,&flGrid)!=0) break; UpdateWindow_(hwnd); break;

// IDB_WRITE_DISTR ...........................................................................................
case IDB_WRITE_DISTR: if(OnWriteDistr()!=0)
MessageBox(NULL,"Incorrect input data or errror in computations !","Error",MB_EX);
else MessageBox(NULL,"Data is written in file","Done",MB_EX); break;
}
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// �������� � �������� ����������� ���� ���������� � ���������.

void clMain::DialogInfo(void)
{
INT_PTR CALLBACK DlgInfo(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam); // ������� ����������� ���� ���������� � ���������.

if(hInst==NULL) return; if(hwnd==NULL) return;
DialogBox(hInst,(LPCTSTR)IDD_INFO,hwnd,(DLGPROC)DlgInfo);
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ���������� � ���������� ����.

BYTE clMain::SetDlgInfo(HWND hDlg)
{
int i; char pol; struct strLay *pL; struct strMaterial *pM; HWND hWnd;

if(Matter.IsOK()!=0) return 1; if(Cryst.IsOKLay()!=0) return 2;

// ���������� ������ ����������.
hWnd=GetDlgItem(hDlg,IDC_LIST_MATTER);
for(i=0;i<Matter.N;i++) { pM=Matter.Mat+i;
sprintf(TxtStr,"%s   Eps': %lf   Eps'': %lf   Symbol: %c",pM->name,pM->eps.re,pM->eps.im,pM->chr);
SendMessage(hWnd,LB_ADDSTRING,0,(LPARAM)(LPSTR)TxtStr);}

// ���������� ������ �����.
hWnd=GetDlgItem(hDlg,IDC_LIST_LAYERS);
for(i=0;i<Cryst.laysNum;i++) { pL=Cryst.Lays+i;
sprintf(TxtStr,"%s     depth %.2lf",pL->GeomSymbs,pL->depth);
SendMessage(hWnd,LB_ADDSTRING,0,(LPARAM)(LPSTR)TxtStr);}

// ���������� ��������� ����������.
SetDlEdt(hDlg,IDC_PERIOD,Cryst.Period,"%.2lf");
SetDlEdt(hDlg,IDC_WLENGH,Task.wLength,"%.2lf");
SetDlEdt(hDlg,IDC_ANGLE,Task.Theta,"%.2lf");
if(Task.flPol==0) pol='p'; else pol='s'; sprintf(TxtStr,"%c",pol); SetDlgItemText(hDlg,IDC_POL,(LPCSTR)TxtStr);
sprintf(TxtStr,"%d %d",Task.L1,Task.M1); SetDlgItemText(hDlg,IDC_HARMS,TxtStr); 
SetDlEdt(hDlg,IDC_EPS_INC,Task.EpsInc.re,"%.2lf");
SetDlEdt(hDlg,IDC_EPS_OUT,Task.EpsOut.re,"%.2lf");
SetDlEdt(hDlg,IDC_DZ,Task.dz,"%.2lf");

return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� �������� � combobox-�.

void clMain::SetDlgCntrlCombo(void)
{
UINT *pID;

if(hDlgCntrl!=NULL) { ClearCombo(hDlgCntrl,IDC_TYPE_DRAW);
if(Task.flPol==p_wave_Pol) pID=IDSArrTypDraw_p; else pID=IDSArrTypDraw_s;
FillStrCombo(hDlgCntrl,IDC_TYPE_DRAW,pID,nTypDraw,flTypDraw);}
SetNameValues(); SetTypNorm();
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ���������� � ����������� ����.

void clMain::SetDlgCntrl(void)
{
if(hDlgCntrl==NULL) return; SetAmpNorm();
CheckRadioButton(hDlgCntrl,IDC_RADIO_IMG_FIELDS,IDC_RADIO_IMG_CRYSTAL,IDC_RADIO_IMG_FIELDS+(int)TypImage);
CheckRadioButton(hDlgCntrl,IDC_RADIO_ACCORD_SCALE,IDC_RADIO_FSCREEN,IDC_RADIO_ACCORD_SCALE+(int)TypScale);
SetChBox(hDlgCntrl,IDC_CHECK_GRID,flGrid);
SetDlEdt(hDlgCntrl,IDC_DISTR_STEP,DistrStep,"%.2lf");
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ��������� ���������� � ����.

void clMain::SetAmpNorm(void)
{
if(pAmpNorm==NULL) return; if(hDlgCntrl==NULL) return;
SetDlEdt(hDlgCntrl,IDC_AMPNORM,*pAmpNorm,"%6.3lf");
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ���� ���������.

BYTE clMain::OnChangeTypDraw(void)
{
BYTE num;

if(GetSelCombo(hDlgCntrl,IDC_TYPE_DRAW,&num)!=0) return 1; if(num>=nTypDraw) return 2;
if(flTypDraw==num) return 0; flTypDraw=num; SetNameValues(); SetTypNorm(); return 0;
}

//-----------------------------------------------------------------------------------------------------------
// �������� ��� ������� �� ������� ������ ������������� ����� ����� � ����.

BYTE clMain::OnWriteDistr(void)
{
if(cx1<0.||cz1<0) return 1; if(cx2<0.||cz2<0.) return 2;
if(cx1==cx2&&cz1==cz2) return 3;
GetDlEdt(hDlgCntrl,IDC_DISTR_STEP,&DistrStep); if(DistrStep<=0.) return 4;
if(CompDistrLine()!=0) return 5;
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ���������� � ������ � ���� ������������� ����� �����.

BYTE clMain::CompDistrLine(void)
{
BYTE flX,flZ,err; int j,xD,xDv,Nx,numL,numD,num; 
double depthSum,depthSumN,dxDistr,xPix,yPix,yPixCurLay,weiX,weiY,v,Alpha,*CoorX,*CoorZ,StepX,StepZ,MaxAbs;
complex A1,A2,AyKT,AyKB,kcoe,*Distr; struct strLay *pL; clRows *pR; clRowMatr *pRM; FILE *fp_x,*fp_z;


Distr=NULL; CoorX=CoorZ=NULL; err=0;
if(Cryst.IsOKLay()!=0) return 1; if(MashtabX<=0.||MashtabY<=0.) return 2;
Alpha=abs(atan(abs(cz2-cz1)/abs(cx2-cx1)));
if(DistrStep*cos(Alpha)>abs(cx2-cx1)) return 3; if(DistrStep*sin(Alpha)>abs(cz2-cz1)) return 4;

// ��������� ������.
num=int(sqrt((cx2-cx1)*(cx2-cx1)+(cz2-cz1)*(cz2-cz1))/DistrStep);
Distr=new complex[num]; if(Distr==NULL) { err=5; goto end;}
CoorX=new double[num]; if(CoorX==NULL) { err=6; goto end;} CoorZ=new double[num]; if(CoorX==NULL) { err=7; goto end;}

// ���������� ������������� � �������� �������������.
// ���� ��������.
depthSum=0.; numL=0; pL=Cryst.Lays; depthSumN=pL->depth;
StepX=DistrStep*cos(Alpha); StepZ=DistrStep*sin(Alpha);
if(sqrt(cz1*cz1+cx1*cx1)>sqrt(cz2*cz2+cx2*cx2)) { xPix=cx2; yPix=cz2;
if(cx2>cx1) StepX*=-1.; if(cz2>cz1) StepZ*=-1.; MaxAbs=sqrt(cz1*cz1+cx1*cx1);}
else { xPix=cx1; yPix=cz1; if(cx1>cx2) StepX*=-1.; if(cz1>cz2) StepZ*=-1.; MaxAbs=sqrt(cz2*cz2+cx2*cx2);}
j=0;

while(sqrt(yPix*yPix+xPix*xPix)<=MaxAbs) {
// ��������� � ���������� ����.
if(yPix>depthSumN&&numL<Cryst.laysNum) { numL++;
if(numL<Cryst.laysNum) { pL=Cryst.Get(numL); if(pL==NULL) { err=8; goto end;}
depthSum=depthSumN; depthSumN+=pL->depth;}}

// ���� ����� ��������� 'numD' � ������� ����, ����� �������� ����� �������.
yPixCurLay=yPix-depthSum; if(yPixCurLay<0.) yPixCurLay=0.;
if(pL->dz<=0.) { err=9; goto end;}
v=yPixCurLay/pL->dz; numD=(int)v;
//sprintf(TxtStr,"---->C"); MessageBox(NULL,TxtStr,"",MB_EX);
if(numD>pL->nDiv) { err=10; goto end;}
//sprintf(TxtStr,"---->D"); MessageBox(NULL,TxtStr,"",MB_EX);
if(numD<pL->nDiv) weiY=v-(double)numD; else weiY=1.;

// ����� ������� �������������.
switch(flTypDraw) { default: { err=11; goto end;}
case TypDraw_X: pR=&pL->XDistr; break; 
case TypDraw_Y: pR=&pL->YDistr; break;
case TypDraw_Z: pR=&pL->ZDistr; break;}
if(pR->IsOK()!=0) { err=12; goto end;}
if(numD>=pR->Ny) { err=13; goto end;} Nx=pR->Nx; dxDistr=Cryst.Period/(double)Nx;

//sprintf(TxtStr,"---->D"); MessageBox(NULL,TxtStr,"",MB_EX);

// ���������� ��������� ������� ������������ ��������� (����� ��������� �� ��� 'x', ����� �������� ����� �������).
v=xPix/dxDistr; xD=(int)v; if(xD>=Nx) { err=14; goto end;} weiX=v-(double)xD;
if(xD<Nx-1) xDv=xD+1; else xDv=0;

//sprintf(TxtStr,"---->E"); MessageBox(NULL,TxtStr,"",MB_EX);

// �������� ������������.
pRM=pR->Rows+numD; if(pRM->IsOK()!=0) { err=15; goto end;} if(pRM->N!=Nx) { err=16; goto end;}
A2=pRM->Vect[xDv]; A1=pRM->Vect[xD]; AyKT=A1*(1.-weiX)+A2*weiX; // ������������ �� 'x' � ������� ����.
if(numD==pR->Ny-1) Distr[j]=AyKT;
else { pRM=pR->Rows+numD+1; if(pRM->IsOK()!=0) { err=17; goto end;} if(pRM->N!=Nx) { err=18; goto end;}
A2=pRM->Vect[xDv]; A1=pRM->Vect[xD]; AyKB=A1*(1.-weiX)+A2*weiX; // ������������ �� 'x' � ������ ����.
Distr[j]=AyKT*(1.-weiY)+AyKB*weiY;} // ������������ �� 'z'.
CoorX[j]=xPix; CoorZ[j]=yPix;
sprintf(TxtStr,"j CoorX CoorZ Distr[j] %d %lf %lf %lf",j,CoorX[j],CoorZ[j],abs(Distr[j])); MessageBox(NULL,TxtStr,"",MB_EX);
yPix+=StepZ; xPix+=StepX; j++;
} // ����� ����� �� 'i'.

// ������ � ����.
fp_x=fp_z=NULL; flX=flZ=0; 
if(cx1!=cx2) { fp_x=fopen(FName_DistrLine_X,"w"); if(fp_x==NULL) { err=19; goto end;} flX=1;}
if(cz1!=cz2) { fp_z=fopen(FName_DistrLine_Z,"w"); if(fp_z==NULL) { err=20; goto end;} flZ=1;}

if(flX==1) for(j=0;j<num;j++) fprintf(fp_x,"%lf %lf\n",CoorX[j],abs(Distr[j]));
if(flZ==1) for(j=0;j<num;j++) fprintf(fp_z,"%lf %lf\n",CoorZ[j],abs(Distr[j]));

end: SAFE_CLOSE(fp_x); SAFE_CLOSE(fp_z); SAFE_DELETE_ARR(Distr); SAFE_DELETE_ARR(CoorX); SAFE_DELETE_ARR(CoorZ); return err;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ���� ����������.

void clMain::SetTypNorm(void)
{
BYTE typ;

switch(flTypDraw) { default: 
case TypDraw_Y: if(Task.flPol==p_wave_Pol) typ=typNorm_H; else typ=typNorm_E; break; // ������������ ���������� 'y' �����.
case TypDraw_X: case TypDraw_Z: case TypDraw_Full: // ������������ ��������� ����� 'x,z' ��� ��������� �������� �����.
if(Task.flPol==p_wave_Pol) typ=typNorm_E; else typ=typNorm_H; break;
case TypDraw_SqE: typ=typNorm_E2; break; // ������� ��������� ���� 'E'.
case TypDraw_SqH: typ=typNorm_H2; break; // ������� ��������� ���� 'H'.
case TypDraw_FvFc: typ=typNorm_FvFc; break; // ��������� ������������ 'ExE*' ��� 'HxH*'.
case TypDraw_Px: case TypDraw_Pz: case TypDraw_PAbs: typ=typNorm_Poynt; break; // ���������� � ������ ������� ���������.
case TypDraw_DivP: typ=typNorm_ReEps; break; // ����������� ������� ���������.
case TypDraw_EImE2: typ=typNorm_EImE2; break; // ������������� �������� ������ 'eps".E^2'.
case TypDraw_ReEps: typ=typNorm_ReEps; break; // ������������� �������������� ����� 'eps'.
case TypDraw_ImEps: typ=typNorm_ImEps; break; // ������������� ������ ����� 'eps'.
}
OnChTypNorm(typ);
}

//-----------------------------------------------------------------------------------------------------------
// �������� ��� ��������� ���� ����������.

void clMain::OnChTypNorm(BYTE typ)
{
if(typ==flTypNorm) return; if(typ>=nTypNorm) return; flTypNorm=typ;
pAmpNorm=AmpNormArr+flTypNorm; SetAmpNorm();
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ����� ��������� �������.

void clMain::SetNameValues(void)
{
char *cp;

if(hDlgCntrl==NULL) return;
switch(flTypDraw) { default: cp=""; break;
case TypDraw_X: case TypDraw_Y: case TypDraw_Z: cp="Amp.Phase:"; break;
case TypDraw_Full: case TypDraw_SqE: case TypDraw_SqH: case TypDraw_FvFc:
case TypDraw_DivP: case TypDraw_EImE2: cp="Ampl.:"; break;
case TypDraw_Px: case TypDraw_Pz: cp="Px,Pz:"; break;
case TypDraw_PAbs: cp="P,Px:Pz"; break;
case TypDraw_ReEps: case TypDraw_ImEps: cp="Re,Im:"; break;}
SetDlgItemText(hDlgCntrl,IDC_NAME_VALUES,cp);
}

//-----------------------------------------------------------------------------------------------------------
// ����������� ��������.

BYTE clMain::FindMashtab(int xSize,int ySize)
{
int i;

MashtabY=MashtabX=0.; if(xSize<=0||ySize<=0) return 1;
if(Cryst.IsOK()!=0) return 2; if(Cryst.Period<=0.) return 3;
DepthCryst=0.; for(i=0;i<Cryst.laysNum;i++) DepthCryst+=Cryst.Lays[i].depth; // ����������� ����� ������� ���������.
MashtabX=Cryst.Period/(double)xSize; if(MashtabX<=0.) return 4;
MashtabY=DepthCryst/(double)ySize; if(MashtabY<=0.) return 5;
if(TypScale==0) MashtabX=MashtabY=MAX(MashtabX,MashtabY); return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ����������� ��������.

BYTE clMain::FindMashtabAngl(int xSize,int ySize)
{
if(this->IsOK_DispAngl()!=0) return 1;
AnglMashtabY=AnglMashtabX=0.; if(xSize<=0||ySize<=0) return 2;
if(xSize>=ySize) { AnglMashtabY=abs(Task.wLen_Fin-Task.wLen_St)/(double)ySize; if(AnglMashtabY<=0.) return 3;
AnglMashtabX=abs(Task.Th_Fin-Task.Th_St)/(double)ySize; if(AnglMashtabX<=0.) return 4;}

else { AnglMashtabX=abs(Task.Th_Fin-Task.Th_St)/(double)xSize; if(AnglMashtabX<=0.) return 5;
AnglMashtabY=abs(Task.wLen_Fin-Task.wLen_St)/(double)xSize; if(AnglMashtabY<=0.) return 6;}
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������� �������������, ���������� ��������, ��������� ������, ������ ���� ������������� � ����������� ����.

void clMain::CreateComputeDistrAll_(void)
{
CreateComputeDistrAll(); ChooseDraw(); UpdateWindow_(hwnd);
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������� �������������, ���������� ��������, ��������� ������ � ������ ���� �������������.

void clMain::CreateComputeDistrAll(void)
{
flCompDistr=1; FreeDistr(); SetStateBtnRedraw();
if(CreateDistrAll()!=0) return; // ��������� ������� �������������, ���������� ��������, ��������� ������ ��� �������������.
flChSizeImg=0; SetStateBtnRedraw();
if(TypImage==0) ComputeDistrAll(); // ������ ���� �������������.
flCompDistr=0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������� ������������� �������� �������������, ���������� ��������, ������ � ����������� ����.

BYTE clMain::CreateComputeAnglDisp(void)
{
UpdateWindow_(hwnd);
FreeAnglDispDistr(); if(CreateAnglDisp()!=0) return 1; 
if(ComputeAnglDispDistr(AnglDispDistr)!=0) return 2; // ������ ������������� ������� ���������.
pAmpNorm=AmpNormArr+typNorm_AnglDisp; SetAmpNorm();
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������� �������������, ���������� ��������, ��������� ������ ��� �������������.

BYTE clMain::CreateDistrAll(void)
{
int xSize,ySize,xD,yD; RECT rc;

FreeDistr(); FreeBmpAll();
if(BmpDiag==NULL) return 1; if(BmpPalP==NULL) return 2; if(BmpPalPN==NULL) return 3;
if(hwnd==NULL) return 4; if(Cryst.IsOK()!=0) return 5;

// ����������� ������� ���������.
if(GetClientRect(hwnd,&rc)==FALSE) return 6;
xSize=(int)(rc.right-rc.left-PalPixSize-GapSize-TextLen); ySize=(int)(rc.bottom-rc.top)-y0; // �������� ������ ���� ����������.
if(xSize<=0||ySize<=0) return 7;

// ����������� ��������.
if(FindMashtab(xSize,ySize)!=0) { MashtabY=MashtabX=0.; return 8;}

// ����������� ������� �������������.
if(Cryst.Period<=0.) return 9; if(DepthCryst<=0.) return 10;
xD=(int)(Cryst.Period/MashtabX);
yD=(int)(DepthCryst/MashtabY);
if(xD<=0||yD<=0) return 11;

// ��������� ������.
if(BmpDiag->Init(xD,yD,NULL)!=0) return 12; // ������������� 'pvBits'.
if(BmpPalP->Init(PalPixSize,yD,NULL)!=0) return 13; // ������������� 'pvBits'.
if(BmpPalPN->Init(PalPixSize,yD,NULL)!=0) return 14; // ������������� 'pvBits'.
if(AllocDistr(xD,yD)!=0) return 15; // ��������� ������ ��� �������������.
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������� ������������� ������� ���������, ���������� ��������.

BYTE clMain::CreateAnglDisp(void)
{
int xSize,ySize,SizeD; RECT rc;

FreeBmpAll(); FreeAnglDispDistr();
if(BmpAnglDisp==NULL) return 1; if(BmpPalP==NULL) return 2; if(BmpPalPN==NULL) return 3;
if(hwnd==NULL) return 4;

// ����������� ������� ���������.
if(GetClientRect(hwnd,&rc)==FALSE) return 5;
xSize=(int)(rc.right-rc.left-PalPixSize-GapSize-2*TextLen); ySize=(int)(rc.bottom-rc.top)-y0-TextLen; // �������� ������ ���� ����������.
if(xSize<=0||ySize<=0) return 6;

// ����������� ��������.
if(FindMashtabAngl(xSize,ySize)!=0) { AnglMashtabY=AnglMashtabX=0.; return 7;}

// ����������� ������� ������� �������������.
if(xSize>=ySize) SizeD=ySize; else SizeD=xSize;

// ��������� ������.
if(BmpAnglDisp->Init(SizeD,SizeD,NULL)!=0) return 8; // ������������� 'pvBits'.
if(BmpPalP->Init(PalPixSize,SizeD,NULL)!=0) return 9; // ������������� 'pvBits'.
if(BmpPalPN->Init(PalPixSize,SizeD,NULL)!=0) return 10; // ������������� 'pvBits'.
if(AllocAnglDispDistr(SizeD,SizeD)!=0) return 11; // ��������� ������ ��� �������������.
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ������ ���� �������������.

BYTE clMain::ComputeDistrAll(void)
{
BYTE ind,k,ber; int i,j,jv,jSh,kv; double v,s,**pD,coeX,coeZ,coe; complex **pC,cX,cY,cZ; HCURSOR cur;

if(IsOK_Distr()!=0) return 1; if(MashtabX<=0.||MashtabY<=0.) return 2;
coe=Task.wLength/(2.*M_PI);

cur=NULL; ber=0;
if(cur_wait!=NULL) cur=SetCursor(cur_wait);

// ������ ����������� ��������� ����� 'Ex','Hy','Ez' ('p') ��� 'Hx','Ey','Hz' ('s').
for(ind=0;ind<3;ind++) {
switch(ind) { default: continue;
case 0: pC=&DistrX; break;
case 1: pC=&DistrY; break;
case 2: pC=&DistrZ; break;}
if(ComputeDistr(xSizeD,ySizeD,*pC,ind)!=0) { ber=3; goto end;}}

// ���������� ������������� ������ ����� ��������������� �������������.
if(ComputeDistrEps(xSizeD,ySizeD,DistrReEps,DistrImEps)!=0) { ber=4; goto end;}

// ������ ������������� ������� ����� 'E' ('p') ��� 'H' ('s') � �������� ������ ����� 'E','H'.
if(Task.flPol==p_wave_Pol) pD=&DistrSqE; else pD=&DistrSqH;
for(i=0;i<ySizeD;i++) { jSh=i*xSizeD; for(j=0;j<xSizeD;j++) { jv=j+jSh;
cX=DistrX[jv]; cZ=DistrZ[jv]; v=absSq(cX)+absSq(cZ); DistrFAbs[jv]=sqrt(v); (*pD)[jv]=v;}}
if(Task.flPol==p_wave_Pol) pD=&DistrSqH; else pD=&DistrSqE;
for(i=0;i<ySizeD;i++) { jSh=i*xSizeD; for(j=0;j<xSizeD;j++) { jv=j+jSh; (*pD)[jv]=absSq(DistrY[jv]);}}

// ������ ������������� 'Im([ExE*])' ��� 'Im([HxH*])'.
for(i=0;i<ySizeD;i++) { jSh=i*xSizeD; for(j=0;j<xSizeD;j++) { jv=j+jSh;
cX=DistrX[jv]; cZ=-DistrZ[jv]; DistrFvFc[jv]=2.*imag(conj(cX)*cZ);}}

// ������ ��������� � ������ ������� ���������.
for(i=0;i<ySizeD;i++) { jSh=i*xSizeD; for(j=0;j<xSizeD;j++) { jv=j+jSh;
cX=DistrX[jv]; cY=DistrY[jv]; cZ=-DistrZ[jv];
if(Task.flPol==p_wave_Pol) { cY*=Cmplx_I; DistrPx[jv]=-real(cZ*conj(cY)); DistrPz[jv]=real(cX*conj(cY));}
else { cX*=Cmplx_I; cZ*=Cmplx_I; DistrPx[jv]=real(cY*conj(cZ)); DistrPz[jv]=-real(cY*conj(cX));}
DistrPx[jv]*=0.5; DistrPz[jv]*=0.5;
v=DistrPx[jv]; s=v*v; v=DistrPz[jv]; s+=v*v; DistrPAbs[jv]=sqrt(s);}}

// ������ ������������� ����������� ������� ���������.
coeX=0.25/MashtabX; coeZ=0.5/MashtabY;
for(i=0;i<ySizeD;i++) { jSh=i*xSizeD; for(j=0;j<xSizeD;j++) { jv=j+jSh; s=0.;
// ����������� ���������� 'Px'.
v=0.; pD=&DistrPx;
if(j>0) kv=jv-1; else kv=xSizeD-1+jSh; v+=(*pD)[jv]-(*pD)[kv];
if(j<xSizeD-1) kv=jv+1; else kv=jSh; v+=(*pD)[kv]-(*pD)[jv];
s+=v*coeX;
// ����������� ���������� 'Pz'.
v=0.; k=0; pD=&DistrPz;
if(i>0) { kv=jv-xSizeD; v+=(*pD)[jv]-(*pD)[kv]; k++;}
if(i<ySizeD-1) { kv=jv+xSizeD; v+=(*pD)[kv]-(*pD)[jv]; k++;}
if(k>0) s+=v*coeZ/(double)k;
DistrDivP[jv]=-s*coe;}}

// ������������� �������� ������ 'eps".E^2'.
for(i=0;i<ySizeD;i++) { jSh=i*xSizeD; for(j=0;j<xSizeD;j++) { jv=j+jSh;
DistrE2EpsIm[jv]=DistrSqE[jv]*DistrImEps[jv];}}

flDistr=1; SetStateBtnRedraw();
end: if(cur!=NULL) SetCursor(cur); return ber;
}

//-----------------------------------------------------------------------------------------------------------
// ���������� ������� �������������.
// typDistr = 0,1,2 - 'XDistr','YDistr','ZDistr'.

BYTE clMain::ComputeDistr(int xSize,int ySize,complex *Distr,BYTE typDistr)
{
int i,j,k,xD,xDv,Nx,jSh,numL,numD; double depthSum,depthSumN,dxDistr,xPix,yPix,yPixCurLay,weiX,weiY,v;
complex A1,A2,AyKT,AyKB,kcoe; struct strLay *pL; clRows *pR; clRowMatr *pRM;

if(Cryst.IsOKLay()!=0) return 1; if(xSize<=0||ySize<=0) return 2; if(typDistr<0||typDistr>=3) return 3;
if(Distr==NULL) return 4; if(MashtabX<=0.||MashtabY<=0.) return 5;

// ���������� ������������� � �������� �������������.
// ���� �� �������� �� ��� 'z'.
depthSum=0.; numL=0; pL=Cryst.Lays; depthSumN=pL->depth;
for(i=0;i<ySize;i++) { jSh=i*xSize;
yPix=(double)i*MashtabY;
// ��������� � ���������� ����.
if(yPix>depthSumN&&numL<Cryst.laysNum) { numL++;
if(numL<Cryst.laysNum) { pL=Cryst.Get(numL); if(pL==NULL) return 6;
depthSum=depthSumN; depthSumN+=pL->depth;}}

// ����� �� ������� ���������.
if(numL>=Cryst.laysNum) { for(k=0;k<xSize;k++) Distr[k+jSh]=Cmplx_0; continue;}

// ���� ����� ��������� 'numD' � ������� ����, ����� �������� ����� �������.
yPixCurLay=yPix-depthSum; if(yPixCurLay<0.) yPixCurLay=0.;
if(pL->dz<=0.) return 7; v=yPixCurLay/pL->dz; numD=(int)v; if(numD>pL->nDiv) return 8;
if(numD<pL->nDiv) weiY=v-(double)numD; else weiY=1.;

// ����� ������� �������������.
switch(typDistr) { default: return 9;
case 0: pR=&pL->XDistr; break; 
case 1: pR=&pL->YDistr; break;
case 2: pR=&pL->ZDistr; break;}
if(pR->IsOK()!=0) return 10;
if(numD>=pR->Ny) return 11; Nx=pR->Nx; dxDistr=Cryst.Period/(double)Nx;

// ���� �� �� �������� �� ��� 'x'.
for(j=0;j<xSize;j++) { xPix=(double)j*MashtabX;
if(xPix>Cryst.Period) return 12; // ���� ����� �� ������� ���������.
// ���������� ��������� ������� ������������ ��������� (����� ��������� �� ��� 'x', ����� �������� ����� �������).
v=xPix/dxDistr; xD=(int)v; if(xD>=Nx) return 13; weiX=v-(double)xD;
if(xD<Nx-1) xDv=xD+1; else xDv=0;

// �������� ������������.
pRM=pR->Rows+numD; if(pRM->IsOK()!=0) return 14; if(pRM->N!=Nx) return 15;
A2=pRM->Vect[xDv]; A1=pRM->Vect[xD]; AyKT=A1*(1.-weiX)+A2*weiX; // ������������ �� 'x' � ������� ����.
if(numD==pR->Ny-1) Distr[j+jSh]=AyKT;
else { pRM=pR->Rows+numD+1; if(pRM->IsOK()!=0) return 16; if(pRM->N!=Nx) return 17;
A2=pRM->Vect[xDv]; A1=pRM->Vect[xD]; AyKB=A1*(1.-weiX)+A2*weiX; // ������������ �� 'x' � ������ ����.
Distr[j+jSh]=AyKT*(1.-weiY)+AyKB*weiY;} // ������������ �� 'z'.
} // ����� ����� �� 'j'.
} // ����� ����� �� 'i'.

return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ���������� ������������� �������������� � ������ ����� ��������������� �������������.

BYTE clMain::ComputeDistrEps(int xSize,int ySize,double *DistrRe,double *DistrIm)
{
BYTE ber; int i,j,jSh,k,num,numS,numL,symbNum,*NumSubs,yI,yF; size_t ln,sz;
double depthSum,depthSumN,MashtSymb,coe; complex eps; char *cp,chr; struct strLay *pL;
struct strMaterial *pMat;

if(Cryst.IsOKLay()!=0) return 1; if(xSize<=0||ySize<=0) return 2; if(DistrRe==NULL&&DistrIm==NULL) return 3;
if(MashtabX<=0.||MashtabY<=0.) return 4;

// �������� ������ ��� ������� ������� ������� ��� ������������� ����� ����.
sz=0; for(k=0;k<Cryst.laysNum;k++) { pL=Cryst.Get(k); if(pL==NULL) return 5;
cp=pL->GeomSymbs; if(cp==NULL) return 6; ln=strlen(cp); if(ln==0) return 7; if(ln>sz) sz=ln;}
if(sz==0) return 8;

NumSubs=NULL; ber=0;
NumSubs=new int[sz]; if(NumSubs==NULL) { ber=9; goto end;}

// ���� �� �����.
depthSum=0.;
for(numL=0;numL<Cryst.laysNum;numL++) {
pL=Cryst.Get(numL); if(pL==NULL) { ber=10; goto end;}
depthSumN=depthSum+pL->depth;
yI=GetIntTest(depthSum/MashtabY);
yF=GetIntTest(depthSumN/MashtabY);
if(yI<0||yI>=ySize) { ber=11; goto end;}
if(yF>ySize) yF=ySize; if(yF<yI) { ber=12; goto end;}
if(yF==yI&&yF<ySize) yF++;

cp=pL->GeomSymbs; if(cp==NULL) { ber=13; goto end;} ln=strlen(cp); if(ln==0||ln>sz) { ber=14; goto end;}
MashtSymb=Cryst.Period/(double)ln; if(MashtSymb<=0.) { ber=15; goto end;}
coe=MashtabX/MashtSymb;

// ��������� ������ ������� �������.
for(k=0;k<(int)ln;k++) NumSubs[k]=-1; num=0;
rep: if(NumSubs[num]>=0) goto fin; chr=cp[num]; numS=Matter.GetNum(chr); if(numS<0) { ber=16; goto end;}
for(k=num;k<(int)ln;k++) if(cp[k]==chr) NumSubs[k]=numS;
fin: num++; if(num<(int)ln) goto rep;

// ���� �� �������� �� ��� 'z'.
for(i=yI;i<yF;i++) { jSh=i*xSize;
for(j=0;j<xSize;j++) { symbNum=(int)((double)j*coe); if(symbNum>=(int)ln) { ber=17; goto end;}
pMat=Matter.Get(NumSubs[symbNum]); if(pMat==NULL) { ber=18; goto end;}
eps=pMat->eps;
if(DistrRe!=NULL) DistrRe[j+jSh]=real(eps);
if(DistrIm!=NULL) DistrIm[j+jSh]=imag(eps);
}}

depthSum=depthSumN;} // ����� ����� �� �����.

end: SAFE_DELETE_ARR(NumSubs); return ber;
}

//-----------------------------------------------------------------------------------------------------------
// ���������� ������� ������������� ������� ���������.

BYTE clMain::ComputeAnglDispDistr(complex *AnglDispDistr)
{
int i,j,k,xD,xDv,Nx,jSh,numD; double dxDistr,xPix,yPix,weiX,weiY,v,ndiv;
complex A1,A2,AyKT,AyKB,kcoe; clRows *pR; clRowMatr *pRM;

if(IsOK_DispAngl()!=0) return 1; if(xSizeAnglD<=0||ySizeAnglD<=0) return 2;
if(AnglDispDistr==NULL) return 3; if(AnglMashtabX<=0.||AnglMashtabY<=0.) return 4;

pR=&AnglDisp; if(pR->IsOK()!=0) return 5; if(Task.dwLen<=0.) return 6; Nx=pR->Nx; dxDistr=Task.dTh;

// ���������� ������������� � �������� �������������.
// ���� �� �������� �� ��� 'z'.
for(i=0;i<ySizeAnglD;i++) { jSh=i*xSizeAnglD;
yPix=(double)i*AnglMashtabY;

// ����� �� �������.
if(yPix>=ySizeAnglD) { for(k=0;k<xSizeAnglD;k++) AnglDispDistr[k+jSh]=Cmplx_0; continue;}

// ���� ����� ��������� 'numD', ����� �������� ����� �������.
v=yPix/Task.dwLen; numD=(int)v; ndiv=int(abs(Task.wLen_Fin-Task.wLen_St)/Task.dwLen+0.5); if(numD>ndiv) return 7;
if(numD<ndiv) weiY=v-(double)numD; else weiY=1.;
if(numD>=pR->Ny) return 8;

// ���� �� �� �������� �� ��� 'x'.
for(j=0;j<xSizeAnglD;j++) { xPix=(double)j*AnglMashtabX;
if(xPix>abs(Task.Th_Fin-Task.Th_St)) return 9; // ���� ����� �� �������.
// ���������� ��������� ������� ������������ ��������� (����� ��������� �� ��� 'x', ����� �������� ����� �������).
v=xPix/dxDistr; xD=(int)v; if(xD>=Nx) return 10; weiX=v-(double)xD;
if(xD<Nx-1) xDv=xD+1; else xDv=0;

// �������� ������������.
pRM=pR->Rows+numD; if(pRM->IsOK()!=0) return 11; if(pRM->N!=Nx) return 12;
A2=pRM->Vect[xDv]; A1=pRM->Vect[xD]; AyKT=A1*(1.-weiX)+A2*weiX; // ������������ �� 'x' � ������� ����.
if(numD==pR->Ny-1) AnglDispDistr[j+jSh]=AyKT;
else { pRM=pR->Rows+numD+1; if(pRM->IsOK()!=0) return 13; if(pRM->N!=Nx) return 14;
A2=pRM->Vect[xDv]; A1=pRM->Vect[xD]; AyKB=A1*(1.-weiX)+A2*weiX; // ������������ �� 'x' � ������ ����.
AnglDispDistr[j+jSh]=AyKT*(1.-weiY)+AyKB*weiY;
//sprintf(TxtStr,"B: i,j,AyKT,weiY,AyKB %d %d %lf %lf %lf",i,j,abs(AyKT),weiY,abs(AyKB)); MessageBox(NULL,TxtStr,"",MB_EX);
} // ������������ �� 'z'.
} // ����� ����� �� 'j'.
} // ����� ����� �� 'i'.

return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������������� ����� � ������.

void clMain::DrawDistr_(void)
{
if(flAnglDisp==1) { DrawAnglDisp_(); return;}
if(DrawDistr()!=0) { DrawDistrVoid(); return;} 
DrawPal(0); DrawPal(1); // ������ ������.
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������� ��������� � ������.

void clMain::DrawAnglDisp_(void)
{
if(DrawAnglDisp()!=0) { DrawAnglDispVoid(); return;} 
DrawPal(0); DrawPal(1); // ������ ������.
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������������� �����.

BYTE clMain::DrawDistr(void)
{
BYTE *pvBits,k,flSign,*bp; int i,j,jSh; UINT dx,dy,dxB,l0,l,nC; double amp,coe,v,va,*pD; struct strPal *pPal;

if(BmpDiag==NULL) return 1; if(BmpDiag->IsOKB()!=0) return 2;
dx=(UINT)BmpDiag->dx; dy=(UINT)BmpDiag->dy; dxB=BmpDiag->dxB; // ������������� ����������.
pvBits=BmpDiag->pvBits; if(pvBits==NULL) return 3;
if(xSizeD<=0||ySizeD<=0) return 4; if((UINT)xSizeD>dx||(UINT)ySizeD>dy) return 5;
if(pAmpNorm==NULL) return 6; amp=*pAmpNorm; if(amp<=0.) return 7;

if(flDistr==0) { flCompDistr=1; ComputeDistrAll(); flCompDistr=0;} // ������ ���� �������������.

// ���������� ������� ������ ���������� ���� ��� ���������� ���� �������������.
if(flTypDraw==TypDraw_X||flTypDraw==TypDraw_Y||flTypDraw==TypDraw_Z) {
if(flDComp!=flTypDraw) { if(FillDistrComp()!=0) return 8;}}

pD=GetDistr(); if(pD==NULL) return 9; // ��������� ��������� �� ������ �������������.

// ���� ������������� ������� �� ������.
if(flTypDraw==TypDraw_FvFc||flTypDraw==TypDraw_Px||flTypDraw==TypDraw_Pz||flTypDraw==TypDraw_ReEps) flSign=1; else flSign=0;
if(flSign==0) pPal=&PalDistrP; // ����� �������.

// ���������� 'pvBits'.
coe=1./amp;
for(i=0;i<ySizeD;i++) { jSh=i*xSizeD; l0=(dy-1-(UINT)i)*dxB;
for(j=0;j<xSizeD;j++) { v=pD[j+jSh]*coe; if(v>=0.) va=v; else va=-v;
if(v<=0.&&flSign==0) nC=0; else { if(va>=1.0F) nC=nColSmoothPal-1; else nC=(UINT)((float)(nColSmoothPal-1)*va);}
if(flSign!=0) { if(v<0.) pPal=&PalDistrN; else pPal=&PalDistrP;} bp=&pPal->MasRGB[nC][0];
l=l0+(UINT)j*3; for(k=0;k<3;k++) *(pvBits+l+(UINT)k)=bp[2-k];}
// ���������� ������ �������, ��� ��� �������������.
if(dx>(UINT)xSizeD) for(j=xSizeD;j<(int)dx;j++) { l=l0+(UINT)j*3; for(k=0;k<3;k++) *(pvBits+l+(UINT)k)=0;}
}

// ���������� ������ �������, ��� ��� �������������.
if(dy>(UINT)ySizeD) {
for(i=ySizeD;i<(int)dy;i++) { l0=(dy-1-(UINT)i)*dxB;
for(j=0;j<(int)dx;j++) { l=l0+(UINT)j*3; for(k=0;k<3;k++) *(pvBits+l+(UINT)k)=0;}}}

return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������������� �����.

BYTE clMain::DrawAnglDisp(void)
{
BYTE *pvBits,k,flSign,*bp; int i,j,jSh; UINT dx,dy,dxB,l0,l,nC; double amp,coe,v,va; struct strPal *pPal;

if(BmpAnglDisp==NULL) return 1; if(BmpAnglDisp->IsOKB()!=0) return 2;
dx=(UINT)BmpAnglDisp->dx; dy=(UINT)BmpAnglDisp->dy; dxB=BmpAnglDisp->dxB; // ������������� ����������.
pvBits=BmpAnglDisp->pvBits; if(pvBits==NULL) return 3;
if(xSizeAnglD<=0||ySizeAnglD<=0) return 4; if((UINT)xSizeAnglD>dx||(UINT)ySizeAnglD>dy) return 5;
if(pAmpNorm==NULL) return 6; amp=*pAmpNorm; if(amp<=0.) return 7;

// ���� ������������� ������� �� ������.
pPal=&PalDistrP; flSign=0; // ����� �������.

// ���������� 'pvBits'.
coe=1./amp;
for(i=0;i<ySizeAnglD;i++) { jSh=i*xSizeAnglD; l0=(dy-1-(UINT)i)*dxB;
for(j=0;j<xSizeAnglD;j++) { v=abs(AnglDispDistr[j+jSh])*coe; if(v>=0.) va=v; else va=-v;
if(v<=0.&&flSign==0) nC=0; else { if(va>=1.0F) nC=nColSmoothPal-1; else nC=(UINT)((float)(nColSmoothPal-1)*va);}
if(flSign!=0) { if(v<0.) pPal=&PalDistrN; else pPal=&PalDistrP;} bp=&pPal->MasRGB[nC][0];
l=l0+(UINT)j*3; for(k=0;k<3;k++) *(pvBits+l+(UINT)k)=bp[2-k];}
// ���������� ������ �������, ��� ��� �������������.
if(dx>(UINT)xSizeAnglD) for(j=xSizeAnglD;j<(int)dx;j++) { l=l0+(UINT)j*3; for(k=0;k<3;k++) *(pvBits+l+(UINT)k)=0;}
}

// ���������� ������ �������, ��� ��� �������������.
if(dy>(UINT)ySizeAnglD) {
for(i=ySizeAnglD;i<(int)dy;i++) { l0=(dy-1-(UINT)i)*dxB;
for(j=0;j<(int)dx;j++) { l=l0+(UINT)j*3; for(k=0;k<3;k++) *(pvBits+l+(UINT)k)=0;}}}

return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� �������. fl=0 --> ������������� �������, fl=1 --> ������ �������.

BYTE clMain::DrawPal(BYTE fl)
{
BYTE *pvBits,k,*bp; SCHAR sign; int i,j,dx,dy,nC; UINT dxB,l0,l; double coe,v; struct strPal *pPal;
clBmpPict *BmpPal;

if(fl<0||fl>1) return 1; if(fl==0) BmpPal=BmpPalP; else BmpPal=BmpPalPN;
if(BmpPal==NULL) return 2; if(BmpPal->IsOKB()!=0) return 3;

dx=BmpPal->dx; dy=BmpPal->dy; dxB=BmpPal->dxB; // ������������� ����������.
pvBits=BmpPal->pvBits; if(pvBits==NULL) return 3; if(dy<=1) return 4;

// ���������� 'pvBits' ��� ������� PN.
coe=(double)(nColSmoothPal-1)/(double)(dy-1);
for(i=0;i<dy;i++) { l0=(dy-1-i)*dxB; if(fl==0) v=(double)(dy-1-2*i)*coe; else v=(double)(dy-1-i)*coe;
if(v<0.) { v=-v; sign=-1;} else sign=1; nC=(int)v; nC=MIN(nC,nColSmoothPal-1);
if(sign<0) pPal=&PalDistrN; else pPal=&PalDistrP; bp=&pPal->MasRGB[nC][0];
for(j=0;j<PalPixSize;j++) { l=l0+(UINT)j*3; for(k=0;k<3;k++) *(pvBits+l+(UINT)k)=bp[2-k];}}
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� � ������ ������.

BYTE clMain::DrawDistrVoid(void)
{
BYTE *pvBits,k; UINT i,j,dx,dy,dxB,l,l0;

if(BmpDiag==NULL) return 1; if(BmpDiag->IsOKB()!=0) return 2;
dx=(UINT)BmpDiag->dx; dy=(UINT)BmpDiag->dy; dxB=BmpDiag->dxB; // ������������� ����������.
pvBits=BmpDiag->pvBits; if(pvBits==NULL) return 3;
for(i=0;i<dy;i++) { l0=(dy-1-i)*dxB;
for(j=0;j<dx;j++) { l=l0+j*3; for(k=0;k<3;k++) *(pvBits+l+(UINT)k)=0;}}
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� � ������ ������.

BYTE clMain::DrawAnglDispVoid(void)
{
BYTE *pvBits,k; UINT i,j,dx,dy,dxB,l,l0;

if(BmpAnglDisp==NULL) return 1; if(BmpAnglDisp->IsOKB()!=0) return 2;
dx=(UINT)BmpAnglDisp->dx; dy=(UINT)BmpAnglDisp->dy; dxB=BmpAnglDisp->dxB; // ������������� ����������.
pvBits=BmpAnglDisp->pvBits; if(pvBits==NULL) return 3;
for(i=0;i<dy;i++) { l0=(dy-1-i)*dxB;
for(j=0;j<dx;j++) { l=l0+j*3; for(k=0;k<3;k++) *(pvBits+l+(UINT)k)=0;}}
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ��������� ���������.

BYTE clMain::DrawCrystGeom(void)
{
BYTE *pvBits,RGB[3]; UINT i,j,jSh,dx,dy,dxB,yI,yF,l0,l; int k,xSize,ySize,numL,symbNum; size_t ln;
double depthSum,depthSumN,MashtSymb,DepthCr,coe; char *cp; struct strLay *pL;

if(BmpDiag==NULL) return 1; if(BmpDiag->IsOKB()!=0) return 2;
dx=(UINT)BmpDiag->dx; dy=(UINT)BmpDiag->dy; dxB=BmpDiag->dxB; // ������������� ����������.
pvBits=BmpDiag->pvBits; if(pvBits==NULL) return 3;
if(MashtabX<=0.||MashtabY<=0.) return 4; if(Cryst.IsOK()!=0) return 5;
DepthCr=0.; for(k=0;k<Cryst.laysNum;k++) DepthCr+=Cryst.Lays[k].depth; // ����������� ����� ������� ���������.
xSize=(int)(Cryst.Period/MashtabX); ySize=(int)(DepthCr/MashtabY);
if(xSize<=0||ySize<=0) return 6; if((UINT)xSize>dx||(UINT)ySize>dy) return 7;

depthSum=0.;

// ���� �� �����.
for(numL=0;numL<Cryst.laysNum;numL++) {
pL=Cryst.Get(numL); if(pL==NULL) return 8;
cp=pL->GeomSymbs; if(cp==NULL) return 9; ln=strlen(cp); if(ln==0) return 10;
MashtSymb=Cryst.Period/(double)ln; if(MashtSymb<=0.) return 11; coe=MashtabX/MashtSymb;
depthSumN=depthSum+pL->depth;
yI=GetUINT_Test(depthSum/MashtabY);
yF=GetUINT_Test(depthSumN/MashtabY);

// ���� �� �������� �� ��� 'z'.
for(i=yI;i<yF;i++) { jSh=i*xSize; l0=(UINT)(dy-1-i)*(UINT)dxB;
for(j=0;j<(UINT)xSize;j++) { symbNum=(int)((double)j*coe);
// ������������� ���� �� ������ �������.
if(symbNum>=0&&symbNum<(int)ln) SymbCols.Symb_to_RGB(cp[symbNum],&RGB[0],&RGB[1],&RGB[2]); else RGB[0]=RGB[1]=RGB[2]=0;
l=l0+j*3; for(k=0;k<3;k++) *(pvBits+l+(UINT)k)=RGB[2-k];
} // ����� ����� �� 'j'.
// ���������� ������ �������, ��� ��� �������������.
if(dx>(UINT)xSize) for(j=(UINT)xSize;j<dx;j++) { l=l0+j*3; for(k=0;k<3;k++) *(pvBits+l+(UINT)k)=0;}
} // ����� ����� �� 'i'.
depthSum=depthSumN;} // ����� ����� �� �����.

// ����� �� ������� ���������.
if(dy>(UINT)ySize) {
for(i=(UINT)ySize;i<dy;i++) { l0=(dy-1-i)*dxB;
for(j=0;j<dx;j++) { l=l0+j*3; for(k=0;k<3;k++) *(pvBits+l+(UINT)k)=0;}}}

return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ���� �������������, ���� ��������� ���������.

void clMain::ChooseDraw(void)
{
if(flAnglDisp==1) { DrawAnglDisp_(); return;}
if(TypImage==0) DrawDistr_(); else if(DrawCrystGeom()!=0) DrawDistrVoid();
}

//-----------------------------------------------------------------------------------------------------------
// ��������� � ������� ������������� �����. 

BYTE clMain::OnPaintDistr(HDC hdc)
{
// ��������� ����� ������������� ������� ���������. 
//flOrient=0 - �� ���������. flDir=0 - ������ ����. flDir=1 - ����� �����. flSideText=0 - ����� �����. flSideText=1 - ����� ������.
//flOrient=1 - �� �����������. flDir=0 - ����� �������. flDir=1 - ������ ������. flSideText=0 - ����� �����. flSideText=1 - ����� ������.
//flShift0 - ����� ����� � ������. 1 - ��������, 0 - �� ��������.
//flSign=0 - '+'.
BYTE DrawScale(HDC hdc,int x0,int y0,int dx,int dy,double Val_St,double Val_Fin,BYTE flOrient,BYTE flDir,
BYTE flSideText,BYTE flSign,BYTE flShift0,int TxtLen,double MajDivLen,double MinDivLen,double AvDivLen,double MajDivWid,double MinDivWid,int nScales,strParScale *Scales);

BYTE flSign,be; int xSize,ySize,xImg,yImg,Shift; double Mas; clBmpPict *BMP;

if(hdc==NULL) return 1; if(hwnd==NULL) return 2;
if(BmpPalP==NULL) return 3; if(BmpPalP->IsOKB()!=0) return 4;
if(BmpPalPN==NULL) return 5; if(BmpPalPN->IsOKB()!=0) return 6;
if(GetClientRect(hwnd,&rc)==FALSE) return 7;
if(flAnglDisp==1) BMP=BmpAnglDisp; else BMP=BmpDiag;
if(BMP==NULL) return 8; if(BMP->IsOKB()!=0) return 9;

Shift=GapSize+PalPixSize+TextLen;
xSize=(int)(rc.right-rc.left-Shift); ySize=(int)(rc.bottom-rc.top)-y0; // �������� ������ ���� ����������.
if(flAnglDisp==1) { xSize-=TextLen; ySize-=TextLen;}
if(xSize<=0||ySize<=0) return 10;

// ����������� ��� ������ �� ���� ����������.
rc.left=rcCntrl.right; if(rc.right>rc.left) {
rc.top=0; rc.bottom=rcCntrl.bottom; ImgRectC(hdc,&rc,ColBkg,ColBkg,1);}

// ���������� ������� �����������.
if(TypScale!=0&&flAnglDisp==0) { xImg=xSize; yImg=ySize;}
else { Mas=MAX((double)BMP->dx/(double)xSize,(double)BMP->dy/(double)ySize); Mas=1./Mas;
xImg=GetIntTest((double)BMP->dx*Mas);
yImg=GetIntTest((double)BMP->dy*Mas);}
if(flAnglDisp==1) BMP->Image(hdc,TextLen,y0,xImg,yImg,1); else BMP->Image(hdc,0,y0,xImg,yImg,1); // ����� �����������.

// ���� ������������� ������� �� ������.
if(flTypDraw==TypDraw_FvFc||flTypDraw==TypDraw_Px||flTypDraw==TypDraw_Pz||flTypDraw==TypDraw_ReEps) flSign=1; else flSign=0;
if(flSign==1) if(flAnglDisp==0) BmpPalP->Image(hdc,xImg+GapSize,y0,PalPixSize,yImg,1); else BmpPalP->Image(hdc,xImg+GapSize+TextLen,y0,PalPixSize,yImg,1);
else if(flAnglDisp==0) BmpPalPN->Image(hdc,xImg+GapSize,y0,PalPixSize,yImg,1); else BmpPalPN->Image(hdc,xImg+GapSize+TextLen,y0,PalPixSize,yImg,1); // ��������� �������.
if(flGrid!=0&&flAnglDisp!=1) DrawGrid(hdc,y0,Shift); // ��������� �����.

// ����������� ���, ��� ��� ��� �������������.
if(xSize>xImg) { rc.left=(long)xImg+Shift; rc.right=(long)xSize+Shift;rc.top=y0; rc.bottom=(long)(y0+ySize);
if(flAnglDisp==1) { rc.left+=TextLen; rc.right+=TextLen; rc.bottom+=TextLen;}
ImgRectC(hdc,&rc,ColBkg,ColBkg,1);}
if(ySize>yImg) { rc.left=0; rc.right=(long)xSize+Shift; rc.top=(long)(y0+yImg); rc.bottom=(long)(y0+ySize);
if(flAnglDisp==1) { rc.right+=TextLen; rc.top+=TextLen; rc.bottom+=TextLen;}
ImgRectC(hdc,&rc,ColBkg,ColBkg,1);}
// ����������� ���� ����� �������������� � ��������.
rc.left=xImg; rc.right=xImg+GapSize; rc.top=y0; rc.bottom=y0+yImg;
if(flAnglDisp==1) { rc.left+=TextLen; rc.right+=TextLen;} ImgRectC(hdc,&rc,ColGap,ColGap,1);
// ����������� ����� ��� ������ � �������.
rc.left=xImg+GapSize+PalPixSize; rc.right=xImg+Shift; rc.top=y0; rc.bottom=y0+yImg;
if(flAnglDisp==1) { rc.left+=TextLen; rc.right+=TextLen;} ImgRectC(hdc,&rc,ColTextBkg,ColTextBkg,1);
// ����������� ����� ��� ������ � �������� �������������.
if(flAnglDisp==1) { rc.left=0; rc.right=TextLen; rc.top=y0; rc.bottom=y0+yImg; ImgRectC(hdc,&rc,ColTextBkg,ColTextBkg,1);
rc.left=0; rc.right=xImg+Shift+TextLen; rc.top=y0+yImg; rc.bottom=rc.top+TextLen; ImgRectC(hdc,&rc,ColTextBkg,ColTextBkg,1);}

if(flAnglDisp==0) DrawScalePal(hdc,xImg+GapSize,y0,PalPixSize,yImg,flSign); else DrawScalePal(hdc,xImg+GapSize+TextLen,y0,PalPixSize,yImg,flSign); // ��������� ����� �� �������.
if(flAnglDisp==1) DrawScale(hdc,TextLen,y0,xImg,yImg,Task.wLen_St,Task.wLen_Fin,0,0,0,0,1,TextLen,MajDivLen_Angl,MinDivLen_Angl,AvDivLen_Angl,
MajDivWid_Angl,MinDivWid_Angl,nSclsAnglDisp_Y,ScaleAnglDisp_Y);
if(flAnglDisp==1)  be=DrawScale(hdc,TextLen,y0,xImg,yImg,Task.Th_St,Task.Th_Fin,1,0,0,0,1,TextLen,MajDivLen_Angl,MinDivLen_Angl,AvDivLen_Angl,
MajDivWid_Angl,MinDivWid_Angl,nSclsAnglDisp_X,ScaleAnglDisp_X); // ��������� ����� �� ������������� ������� ���������.
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ������������ ���� � ������� ������������� �����. 

BYTE clMain::OnPaintDistrDef(HDC hdc)
{
DWORD Col;

if(hdc==NULL) return 1; if(hwnd==NULL) return 2; if(GetClientRect(hwnd,&rc)==FALSE) return 3;
Col=ColBkgErr; ImgRectC(hdc,&rc,Col,Col,1); return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ����� �� ����� ���������. 

BYTE clMain::DrawGrid(HDC hdc,int yShift,int xShift)
{
BYTE CrSelPen_(HDC hdc,HPEN *hPen,HPEN *hPenP,int penStyle,BYTE Wid,DWORD Col); // �������� � ����� ����.
void UnSelDelPen(HDC hdc,HPEN *hPen,HPEN *hPenP); // ������������ � �������� ����.
void DrawLine_(HDC hdc,int xI,int yI,int xF,int yF); // ��������� �����.

BYTE err; int i,xSize,ySize,x,y; double MasX,MasY,depthSum; HPEN hPen,hPenP; struct strLay *pL;

if(hdc==NULL) return 1; if(hwnd==NULL) return 2; if(MashtabX<=0.||MashtabY<=0.) return 3;
if(Cryst.IsOK()!=0) return 4; if(Cryst.Period<=0.) return 5; if(DepthCryst<=0.) return 6;
if(SetBkMode(hdc,OPAQUE)==0) return 7;
if(SetBkColor(hdc,COL_BLACK)==CLR_INVALID) return 8;

// ����������� ������� ���������.
if(GetClientRect(hwnd,&rc)==FALSE) return 9;
xSize=(int)(rc.right-rc.left-xShift); ySize=(int)(rc.bottom-rc.top)-y0; // �������� ������ ���� ����������.
if(xSize<=0||ySize<=0) return 10;

// ����������� ��������.
MasX=Cryst.Period/xSize; MasY=DepthCryst/ySize; if(MasX<=0.||MasY<=0.) return 11;
if(TypScale==0) MasX=MasY=MAX(MasX,MasY); // ����� ��������.
x=(int)(Cryst.Period/MasX);

hPen=hPenP=NULL; err=0;
if(CrSelPen_(hdc,&hPen,&hPenP,PS_DOT,1,COL_WHITE)!=0) { err=12; goto end;}

y=yShift; DrawLine_(hdc,0,y,x,y);
depthSum=0.; for(i=0;i<Cryst.laysNum;i++) { pL=Cryst.Get(i); if(pL==NULL) { err=13; goto end;}
depthSum+=pL->depth; y=(int)(depthSum/MasY+0.5)+yShift; DrawLine_(hdc,0,y,x,y);}

end: UnSelDelPen(hdc,&hPen,&hPenP); return err;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ����� ������������� ������� ���������. 
//flOrient=0 - �� ���������. flDir=0 - ������ ����. flDir=1 - ����� �����. flSideText=0 - ����� �����. flSideText=1 - ����� ������.
//flOrient=1 - �� �����������. flDir=0 - ����� �������. flDir=1 - ������ ������. flSideText=0 - ����� �����. flSideText=1 - ����� ������.
//flShift0 - ����� ����� � ������. 1 - ��������, 0 - �� ��������.
//flSign=0 - '+'.

BYTE DrawScale(HDC hdc,int x0,int y0,int dx,int dy,double Val_St,double Val_Fin,BYTE flOrient,BYTE flDir,
BYTE flSideText,BYTE flSign,BYTE flShift0,int TxtLen,double MajDivLen,double MinDivLen,double AvDivLen,double MajDivWid,double MinDivWid,int nScales,strParScale *Scales)
{
BYTE CrSelPen_(HDC hdc,HPEN *hPen,HPEN *hPenP,int penStyle,BYTE Wid,DWORD Col); // �������� � ����� ����.
void UnSelDelPen(HDC hdc,HPEN *hPen,HPEN *hPenP); // ������������ � �������� ����.
void DrawLine_(HDC hdc,int xI,int yI,int xF,int yF); // ��������� �����.

BYTE i; int k,l,MajLen,MinLen,AvLen,r1_maj,r1_min,r1_Av,r2_maj,r2_min,r2_Av,dr1,dr2,r01,r02;
double PosPhys,PhysStep,Pos,PixStep,PixStepTics; HPEN hPenMaj,hPenMin; HFONT font; RECT rc;
HGDIOBJ old; struct strParScale *ParScl;

if(x0<0||y0<0||dx<0||dy<0) return 1; if(flDir<0||flDir>1) return 2; if(flOrient<0||flOrient>1) return 3; if(flSideText<0||flSideText>1) return 4; 
if(flSign<0||flSign>1) return 5; if(flShift0<0||flShift0>1) return 6; if(TxtLen<=0) return 7; if(nScales<=0) return 8;

// ���������� ������� ���� ������ �����.
ParScl=NULL;
for(i=0;i<nScales;i++) if(Val_Fin<Scales[i].ValMax&&Val_St>=Scales[i].ValMin) { ParScl=&Scales[i]; break;}
if(ParScl==NULL) return 9;

if(flOrient==0) { dr1=dy; dr2=dx; r01=y0; r02=x0;} else { dr1=dx; dr2=dy; r01=x0; r02=y0;}


if(SetBkMode(hdc,OPAQUE)==0) return 10; if(SetBkColor(hdc,COL_WHITE)==CLR_INVALID) return 11;
font=CreateFont(-16,0,0,0,0,ANSI_CHARSET,0U,0U,0U,0U,0U,0U,0U,TEXT("Arial")); // �������� �����.
old=SelectObject(hdc,font); // ����� �����.

// �������� ������ �������� ����� � ��������������� �����.
hPenMaj=hPenMin=NULL;
hPenMaj=CreatePen(PS_SOLID,(int)MajDivWid,COL_BLACK); hPenMin=CreatePen(PS_SOLID,(int)MinDivWid,COL_BLACK);
if(hPenMaj==NULL||hPenMin==NULL) return 12;

// ��������� ���� ����� � �����.
PixStep=(double)dr1/(abs(Val_Fin-Val_St)/ParScl->Step); PixStepTics=(double)PixStep/(ParScl->NumTics+1);
PosPhys=Val_St; PhysStep=ParScl->Step; if(flSign==1) PhysStep*=-1.;
MajLen=int(dr2*MajDivLen); MinLen=int(dr2*MinDivLen); AvLen=int(dr2*AvDivLen);

// ���� ��� ������.
if(flDir==0) { Pos=r01; k=0; l=0; while(Pos<=r01+dr1+1) { 
for(i=0;i<2;i++) { if(i==0) { r1_maj=r1_min=r1_Av=r02; r2_maj=r02+MajLen; r2_min=r02+MinLen; r2_Av=r02+AvLen;}
if(i==1) { r2_maj=r2_min=r2_Av=r02+dr2; r1_maj=r02+dr2-MajLen; r1_min=r02+dr2-MinLen; r1_Av=r02+dr2-AvLen;}
if(k==ParScl->NumTics+1) { Pos+=k*PixStepTics; Pos-=PixStep; k=0;}
if(k==0) { SelectObject(hdc,hPenMaj); if(flOrient==0) DrawLine_(hdc,r1_maj,int(Pos+0.5),r2_maj,int(Pos+0.5)); else DrawLine_(hdc,int(Pos+0.5),r1_maj,int(Pos+0.5),r2_maj);}
if(ParScl->NumTics%2!=0) if(k==(ParScl->NumTics+1)/2&&k!=0) {
SelectObject(hdc,hPenMaj); if(flOrient==0) DrawLine_(hdc,r1_Av,int(Pos+0.5),r2_Av,int(Pos+0.5)); else DrawLine_(hdc,int(Pos+0.5),r1_Av,int(Pos+0.5),r2_Av);} 
if(k!=0&&(k!=(ParScl->NumTics+1)/2||(ParScl->NumTics%2==0&&k==(ParScl->NumTics+1)/2))) { SelectObject(hdc,hPenMin); 
if(flOrient==0) DrawLine_(hdc,r1_min,int(Pos+0.5),r2_min,int(Pos+0.5)); else DrawLine_(hdc,int(Pos+0.5),r1_min,int(Pos+0.5),r2_min); }
} // ����� ����� �� "i".

if(l%ParScl->NumMinStep==0) { sprintf(TxtStr,ParScl->form,PosPhys); 
if(flOrient==0) { if(flSideText==1) { rc.left=r02+dr2; rc.right=r02+dr2+TxtLen;} else { rc.right=r02; rc.left=r02-TxtLen;}
rc.top=int(Pos+0.5)-8; rc.bottom=int(Pos+0.5)+8;
if(flShift0==1&&rc.top<r01) { rc.top=r01; rc.bottom=rc.top+16;}
if(rc.bottom>r01+dr1) { rc.bottom=r01+dr1; rc.top=rc.bottom-20;}} // �������� ������ �� �������.
else { if(flSideText==0) { rc.top=r02+dr2+2; rc.bottom=r02+dr2+TxtLen;} else { rc.bottom=r02-2; rc.top=r02-TxtLen;}
rc.left=int(Pos+0.5)-8; rc.right=int(Pos+0.5)+8;
if(flShift0==1&&rc.left<r01) { rc.left=r01; rc.right=rc.left+16;}
if(rc.right>r01+dr1) { rc.right=r01+dr1; rc.left=rc.right-20;}} // �������� ������ �� �������.
DrawText(hdc,TxtStr,strlen(TxtStr),&rc,DT_CENTER);}
k++; l++; Pos+=PixStepTics; PosPhys+=PhysStep/(ParScl->NumTics+1);
}}

// ����� ��� �����.
if(flDir==1) { Pos=r01+dr1; k=0; l=0; while(Pos>=y0-1) { 
for(i=0;i<2;i++) { if(i==0) { r1_maj=r1_min=r1_Av=r02; r2_maj=r02+MajLen; r2_min=r02+MinLen; r2_Av=r02+AvLen;}
if(i==1) { r2_maj=r2_min=r2_Av=r02+dr2; r1_maj=r02+dr2-MajLen; r1_min=r02+dr2-MinLen; r1_Av=r02+dr2-AvLen;}
if(k==ParScl->NumTics+1) { Pos+=k*PixStepTics; Pos-=PixStep; k=0;}
if(k==0) { SelectObject(hdc,hPenMaj); if(flOrient==0) DrawLine_(hdc,r1_maj,int(Pos+0.5),r2_maj,int(Pos+0.5)); else DrawLine_(hdc,int(Pos+0.5),r1_maj,int(Pos+0.5),r2_maj);}
if(ParScl->NumTics%2!=0) if(k==(ParScl->NumTics+1)/2&&k!=0) {
SelectObject(hdc,hPenMaj); if(flOrient==0) DrawLine_(hdc,r1_Av,int(Pos+0.5),r2_Av,int(Pos+0.5)); else DrawLine_(hdc,int(Pos+0.5),r1_Av,int(Pos+0.5),r2_Av);} 
if(k!=0&&(k!=(ParScl->NumTics+1)/2||(ParScl->NumTics%2==0&&k==(ParScl->NumTics+1)/2))) { SelectObject(hdc,hPenMin);
if(flOrient==0) DrawLine_(hdc,r1_min,int(Pos+0.5),r2_min,int(Pos+0.5)); else DrawLine_(hdc,int(Pos+0.5),r1_min,int(Pos+0.5),r2_min);}
} // ����� ����� �� "i".

if(l%ParScl->NumMinStep==0) { sprintf(TxtStr,ParScl->form,PosPhys);
if(flOrient==0) { if(flSideText==1) { rc.left=r02+dr2; rc.right=r02+dr2+TxtLen;} else { rc.right=r02; rc.left=r02-TxtLen;}
rc.top=int(Pos+0.5)-8; rc.bottom=int(Pos+0.5)+8;
if(flShift0==1&&rc.bottom>r01+dr1) { rc.bottom=r01+dr1; rc.top=rc.bottom-16;} 
if(rc.top<r01) { rc.top=r01; rc.bottom=rc.top+16;}} // �������� ������ �� �������.
else { if(flSideText==0) { rc.top=r02+dr2+2; rc.bottom=r02+dr2+TxtLen;} else { rc.bottom=r02-2; rc.top=r02-TxtLen;}
rc.left=int(Pos+0.5)-8; rc.right=int(Pos+0.5)+8;
if(flShift0==1&&rc.right>r01+dr1) { rc.right=r01+dr1; rc.left=rc.right-16;}
if(rc.left<r01) { rc.left=r01; rc.right=rc.left+16;}} // �������� ������ �� �������.
DrawText(hdc,TxtStr,strlen(TxtStr),&rc,DT_CENTER);}
k++; l++; Pos-=PixStepTics; PosPhys+=PhysStep/(ParScl->NumTics+1);
}}

DeleteObject(font); SelectObject(hdc,GetStockObject(NULL_PEN));
SAFE_DELETE_OBJECT(hPenMaj); SAFE_DELETE_OBJECT(hPenMin); // ������������ ������.
return 0; 
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ����� �� �������. 0 - ������������� �������, 1 - ������������� �������

BYTE clMain::DrawScalePal(HDC hdc,int x0,int y0,int dx,int dy,BYTE flPal)
{
// ��������� ����� ������������� ������� ���������. 
//flOrient=0 - �� ���������. flDir=0 - ������ ����. flDir=1 - ����� �����. flSideText=0 - ����� �����. flSideText=1 - ����� ������.
//flOrient=1 - �� �����������. flDir=0 - ����� �������. flDir=1 - ������ ������. flSideText=0 - ����� �����. flSideText=1 - ����� ������.
//flShift0 - ����� ����� � ������. 1 - ��������, 0 - �� ��������.
//flSign=0 - '+'.
BYTE DrawScale(HDC hdc,int x0,int y0,int dx,int dy,double Val_St,double Val_Fin,BYTE flOrient,BYTE flDir,
BYTE flSideText,BYTE flSign,BYTE flShift0,int TxtLen,double MajDivLen,double MinDivLen,double AvDivLen,double MajDivWid,double MinDivWid,int nScales,strParScale *Scales);

int yAv,dy1,dy2;

if(hdc==NULL) return 1;  if(flPal<0||flPal>1) return 2;
if(x0<0||y0<0||dx<0||dx<0) return 3;

if(flPal==0) DrawScale(hdc,x0,y0,dx,dy,0.,*pAmpNorm,0,1,1,0,1,TextLen,MajDivLen_Pal,MinDivLen_Pal,AvDivLen_Pal,MajDivWid_Pal,MinDivWid_Pal,nScls_Pal,ParScaleArr_Pal); // ������������� �������.

// ������������� �������.
else { yAv=(y0+dy)/2; if(2*yAv!=y0+dy) { dy1=dy/2; dy2=dy/2+1;} else dy1=dy2=dy/2;
DrawScale(hdc,x0,y0,dx,dy1,0.,*pAmpNorm,0,1,1,0,0,TextLen,MajDivLen_Pal,MinDivLen_Pal,AvDivLen_Pal,MajDivWid_Pal,MinDivWid_Pal,nScls_Pal,ParScaleArr_Pal);
DrawScale(hdc,x0,y0+dy1,dx,dy2,0.,*pAmpNorm,0,0,1,1,0,TextLen,MajDivLen_Pal,MinDivLen_Pal,AvDivLen_Pal,MajDivWid_Pal,MinDivWid_Pal,nScls_Pal,ParScaleArr_Pal);
}
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// �������� ��������� �������� ����, ��������� ��������� ������ ����������� �����������.

BYTE clMain::CheckSizeImg(void)
{
int xSize,ySize; double MasX,MasY;

if(hwnd==NULL) return 1; if(GetClientRect(hwnd,&rc)==FALSE) return 2;
xSize=(int)(rc.right-rc.left); ySize=(int)(rc.bottom-rc.top)-y0; // �������� ������ ���� ����������.
if(xSize<=0||ySize<=0) return 3;
if(DepthCryst<=0.) return 4; if(Cryst.Period<=0.) return 5;
MasX=Cryst.Period/(double)xSize;
MasY=DepthCryst/(double)ySize;
if(TypScale==0) MasX=MasY=MAX(MasX,MasY);
xSizeDM=(int)(Cryst.Period/MasX);
ySizeDM=(int)(DepthCryst/MasY);
if(xSizeDM==xSizeD&&ySizeDM==ySizeD) flChSizeImg=0; else flChSizeImg=1; SetStateBtnRedraw(); return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ��������� ������ ����������� �����������.

void clMain::SetStateBtnRedraw(void)
{
BYTE En;

if(flDistr==0) { if(Cryst.IsOK()==0) En=1; else En=0;} else if(flChSizeImg==0) En=0; else En=1;
EnableChWin(hDlgCntrl,IDC_REDRAW_IMAGE,En);
}

//-----------------------------------------------------------------------------------------------------------
// ������ ������ �� �����.

BYTE clMain::ReadFile(char *File_Name)
{
BYTE err; int i; FILE *fp; HCURSOR cur; struct strLay *pL;

fp=NULL; cur=NULL; err=0;
if(cur_wait!=NULL) cur=SetCursor(cur_wait);
fp=fopen(File_Name,"r"); if(fp==NULL) { err=1; goto end;}

// ������ ���������� � ���������.
if(SymbCols.Read(FName_SymbCol_Stand)!=0) { err=2; goto end;}
if(Task.Read(fp)!=0) { err=3; goto end;}
if(Matter.Read(fp)!=0) { err=4; goto end;}
if(Cryst.Read(fp)!=0) { err=5; goto end;}

// ������ ������������� �����.
if(Task.flPol==p_wave_Pol) {
for(i=0;i<Cryst.laysNum;i++) { pL=Cryst.Lays+i; if(pL->XDistr.Read(fp)!=0) { err=6; goto end;}}
for(i=0;i<Cryst.laysNum;i++) { pL=Cryst.Lays+i; if(pL->YDistr.Read(fp)!=0) { err=7; goto end;}}}
else {
for(i=0;i<Cryst.laysNum;i++) { pL=Cryst.Lays+i; if(pL->YDistr.Read(fp)!=0) { err=8; goto end;}}
for(i=0;i<Cryst.laysNum;i++) { pL=Cryst.Lays+i; if(pL->XDistr.Read(fp)!=0) { err=9; goto end;}}}

for(i=0;i<Cryst.laysNum;i++) { pL=Cryst.Lays+i; if(pL->ZDistr.Read(fp)!=0) { err=10; goto end;}}

end: SAFE_CLOSE(fp); if(cur!=NULL) SetCursor(cur); return err;
}

//-----------------------------------------------------------------------------------------------------------
// ������ ����� ������� ���������.

BYTE clMain::ReadAnglDisp(BYTE fl)
{
FILE *fp; int nRows,n,i,j;

if(fl<0||fl>2) return 1;
fp=NULL;

switch(fl) {
default: break;
case 0: fp=fopen(FName_AnglDisp_T,"r"); if(fp==NULL) return 2; break;
case 1: fp=fopen(FName_AnglDisp_R,"r"); if(fp==NULL) return 2; break;
case 2: fp=fopen(FName_AnglDisp_A,"r"); if(fp==NULL) return 2; break;
}
if(fscanf(fp,"%lf%lf%lf%lf%lf%lf%d%d",&Task.wLen_St,&Task.wLen_Fin,&Task.dwLen,&Task.Th_St,&Task.Th_Fin,&Task.dTh,&nRows,&n)==EOF) return 3;
if(AnglDisp.Alloc(n,nRows)!=0) return 4;

for(i=0;i<nRows;i++) { for(j=0;j<n;j++) if(fscanf(fp,"%lf",&AnglDisp.Rows[i].Vect[j].re)==EOF) return 5; if(fscanf(fp,"\n")==EOF) return 6;}
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// �������� ��� ����������� ������� ��� �������� ������� ������� ���� � ���� �������������.
// fl=0 - ����������� ����. fl=1 - LDOUBLECLK, fl=2 - RDOUBLECLK

void clMain::OnMouseDistr(LPARAM lParam,BYTE fl)
{
int cx,cy;

if(fl<0||fl>2) return;
if(flDistr==0) { Clear: if(fl!=0) ClearCoor2(fl);
if(fl==0) if(flCurMouse!=0) { ClearCoor1(); ClearVal(); flCurMouse=0;} return;}
cx=LOWORD(lParam); cy=HIWORD(lParam)-y0; if(cx>=xSizeDM||cy>=ySizeDM) goto Clear;
SetCoorMouse(cx,cy,fl); if(fl==0) { if(SetValMouse(cx,cy)!=0) ClearVal(); flCurMouse=1;}
}

//-----------------------------------------------------------------------------------------------------------
// �������� �������������� �������.

void clMain::CheckCurPos(void)
{
BYTE fl; POINT pt;

if(flCurMouse==0) return; if(flDistr==0) { ClearCoor1(); ClearVal(); flCurMouse=0; return;}
fl=0; if(hwnd==NULL) goto end;
if(GetCursorPos(&pt)==FALSE) goto end; if(ScreenToClient(hwnd,&pt)==FALSE) goto end;
rc.left=0; rc.right=(long)xSizeDM; rc.top=(long)y0; rc.bottom=rc.top+(long)ySizeDM;
if(PtInRect(&rc,pt)==FALSE) goto end; fl=1;
end: if(fl==0) { ClearCoor1(); ClearVal(); flCurMouse=0;}
}

//-----------------------------------------------------------------------------------------------------------
// ������� ���� ���������.

void clMain::ClearCoor1(void)
{
if(hDlgCntrl==NULL) return;
SetDlgItemText(hDlgCntrl,IDC_COOR_X,"");
SetDlgItemText(hDlgCntrl,IDC_COOR_Z,"");
}

//-----------------------------------------------------------------------------------------------------------
// ������� ���� ���������.

void clMain::ClearCoor2(BYTE fl)
{
if(fl<1||fl>2) return; if(hDlgCntrl==NULL) return;
if(fl==1) { SetDlgItemText(hDlgCntrl,IDC_COOR_X_1,""); SetDlgItemText(hDlgCntrl,IDC_COOR_Z_1,""); cx1=cz1=-1.;}
if(fl==2) { SetDlgItemText(hDlgCntrl,IDC_COOR_X_2,""); SetDlgItemText(hDlgCntrl,IDC_COOR_Z_2,""); cx2=cz2=-1.;}
}

//-----------------------------------------------------------------------------------------------------------
// ������� ���� �������.

void clMain::ClearVal(void)
{
if(hDlgCntrl==NULL) return;
SetDlgItemText(hDlgCntrl,IDC_VAL_A,"");
SetDlgItemText(hDlgCntrl,IDC_VAL_B,"");
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ��������� �� �������������� �������.
// fl=0 - ����������� ����. fl=1 - LDOUBLECLK, fl=2 - RDOUBLECLK

void clMain::SetCoorMouse(int cx,int cy,BYTE fl)
{
double v;

if(fl<0||fl>2) return;
if(hDlgCntrl==NULL) return;
if(Cryst.Period>0.&&xSizeDM>0) { v=(double)cx/(double)xSizeDM*Cryst.Period; sprintf(TxtStr,FormCoor,v);} else strcpy(TxtStr,"-");
switch(fl) {
case 0: SetDlgItemText(hDlgCntrl,IDC_COOR_X,TxtStr); break;
case 1: SetDlgItemText(hDlgCntrl,IDC_COOR_X_1,TxtStr); cx1=v; break;
case 2: SetDlgItemText(hDlgCntrl,IDC_COOR_X_2,TxtStr); cx2=v; break;
}

if(DepthCryst>0.&&ySizeDM>0) { v=(double)cy/(double)ySizeDM*DepthCryst; sprintf(TxtStr,FormCoor,v);} else strcpy(TxtStr,"-");
SetDlgItemText(hDlgCntrl,IDC_COOR_Z,TxtStr);
switch(fl) {
case 0: SetDlgItemText(hDlgCntrl,IDC_COOR_Z,TxtStr); break;
case 1: SetDlgItemText(hDlgCntrl,IDC_COOR_Z_1,TxtStr); cz1=v; break;
case 2: SetDlgItemText(hDlgCntrl,IDC_COOR_Z_2,TxtStr); cz2=v; break;
}
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������� �� �������������� �������.

BYTE clMain::SetValMouse(int cxM,int cyM)
{
BYTE ind; int cx,cy,jv,id; double v,px,pz,*pD,coeA; complex c,*pC; char *form;

if(hDlgCntrl==NULL) return 1; if(xSizeD<=0||ySizeD<=0) return 2;
if(flChSizeImg==0) { cx=cxM; cy=cyM;}
else { if(xSizeDM<=0||ySizeDM<=0) return 3;
cx=GetIntTest((double)cxM/(double)xSizeDM*(double)xSizeD);
cy=GetIntTest((double)cyM/(double)ySizeDM*(double)ySizeD);}
if(cx<0||cx>=xSizeD) return 4;
if(cy<0||cy>=ySizeD) return 5;
coeA=180./M_PI;
jv=cy*xSizeD+cx;

switch(flTypDraw) { default: return 6;
// ����������� ���������� �����.
case TypDraw_X: case TypDraw_Y: case TypDraw_Z:
switch(flTypDraw) { default: return 7;
case TypDraw_X: pC=DistrX; break;
case TypDraw_Y: pC=DistrY; break;
case TypDraw_Z: pC=DistrZ; break;}
if(pC==NULL) return 8; c=pC[jv];
sprintf(TxtStr,FormAmp,abs(c)); SetDlgItemText(hDlgCntrl,IDC_VAL_A,TxtStr);
sprintf(TxtStr,FormPhase,arg(c)*coeA); SetDlgItemText(hDlgCntrl,IDC_VAL_B,TxtStr);
break;

// ��������� ��������� ��������� �������.
case TypDraw_Full: case TypDraw_SqE: case TypDraw_SqH: case TypDraw_FvFc:
case TypDraw_DivP: case TypDraw_EImE2:
switch(flTypDraw) { default: return 9;
case TypDraw_Full: pD=DistrFAbs; form=FormAmp; break;
case TypDraw_SqE: pD=DistrSqE; form=FormSqFieldAmp; break;
case TypDraw_SqH: pD=DistrSqH; form=FormSqFieldAmp; break;
case TypDraw_FvFc: pD=DistrFvFc; form=FormSqFieldAmp; break;
case TypDraw_DivP: pD=DistrDivP; form=FormPowLoss; break;
case TypDraw_EImE2: pD=DistrE2EpsIm; form=FormPowLoss; break;}
if(pD==NULL) return 10; v=pD[jv];
sprintf(TxtStr,form,v); SetDlgItemText(hDlgCntrl,IDC_VAL_A,TxtStr);
SetDlgItemText(hDlgCntrl,IDC_VAL_B,"-"); break;

// ���������� ������� ���������.
case TypDraw_Px: case TypDraw_Pz:
for(ind=0;ind<2;ind++) {
switch(ind) { default: continue;
case 0: pD=DistrPx; id=IDC_VAL_A; break;
case 1: pD=DistrPz; id=IDC_VAL_B; break;}
if(pD==NULL) return 11; sprintf(TxtStr,FormPoynt,pD[jv]); SetDlgItemText(hDlgCntrl,id,TxtStr);}
break;

// ������ � ��������� ��������� ������� ���������.
case TypDraw_PAbs:
if(DistrPAbs!=NULL) sprintf(TxtStr,FormPoynt,DistrPAbs[jv]); else strcpy(TxtStr,"-");
SetDlgItemText(hDlgCntrl,IDC_VAL_A,TxtStr);
if(DistrPx!=NULL&&DistrPz!=NULL) { px=DistrPx[jv]; pz=DistrPz[jv];
v=MAX(fabs(px),fabs(pz)); if(v<=0.) strcpy(TxtStr,"0:0"); else { v=1./v; sprintf(TxtStr,"%4.3lf:%4.3lf",px*v,pz*v);}}
else strcpy(TxtStr,"-");
SetDlgItemText(hDlgCntrl,IDC_VAL_B,TxtStr); break;

// ��������������� �������������.
case TypDraw_ReEps: case TypDraw_ImEps:
for(ind=0;ind<2;ind++) {
switch(ind) { default: continue;
case 0: pD=DistrReEps; id=IDC_VAL_A; break;
case 1: pD=DistrImEps; id=IDC_VAL_B; break;}
if(pD==NULL) return 12; sprintf(TxtStr,FormEps,pD[jv]); SetDlgItemText(hDlgCntrl,id,TxtStr);}
break;}

return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ������� �������� ����.

LRESULT CALLBACK WndProcMain(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
BYTE InitMain(HWND hwnd); // ������������� ������ �������� ����.

BYTE flag;

if(msg!=WM_CREATE) { LRes=MW.MsgCommand(msg,wParam,lParam,&flag); if(flag!=0) return LRes;}

switch(msg) {

default: return DefWindowProc(hwnd,msg,wParam,lParam);

// WM_CREATE ................................................................................................
case WM_CREATE: if(InitMain(hwnd)!=0) { PostMessage(hwnd,WM_CLOSE,0,0L); return 0L;} break;

// WM_CLOSE .................................................................................................
case WM_CLOSE: DestroyWindow(hwnd); break;

// WM_DESTROY ...............................................................................................
case WM_DESTROY: PostQuitMessage(0); break;
}

return 0L;
}

//-----------------------------------------------------------------------------------------------------------
// ������������� ������ �������� ����.

BYTE InitMain(HWND hwnd)
{
if(hwnd==NULL) return 1; if(MW.OnCreate(hwnd)!=0) return 2; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// ����������� ���� �������� ����.

LRESULT CALLBACK DlgProcCntrlMain(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam)
{   
BYTE flag; clMain *MW_;

if(msg!=WM_INITDIALOG) { MW_=(clMain *)GetWindowLong(hDlg,DWL_USER);
if(MW_!=NULL) { LRes=MW_->MsgCommandCntrl(msg,wParam,lParam,&flag); if(flag!=0) return LRes;}}

switch(msg) { default: break;

// WM_INITDIALOG ............................................................................................
case WM_INITDIALOG: SetWindowLong(hDlg,DWL_USER,(long)lParam); return (LRESULT)TRUE;

// WM_PAINT .................................................................................................
case WM_PAINT: ImgWinC(hDlg,ColDial,ColDial); break;

// WM_CLOSE .................................................................................................
case WM_CLOSE: DestroyWindow(hDlg); break;

// WM_DESTROY ...............................................................................................
case WM_DESTROY: SetWindowLong(hDlg,DWL_USER,0L); break;
}

return FALSE;
}

//-----------------------------------------------------------------------------------------------------------
// ������� ����������� ���� ���������� � ���������.

INT_PTR CALLBACK DlgInfo(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
BYTE SetFont(HWND hwnd,HFONT hFont); // ��������� ������ � ����.

int id; HWND hwnd; HDC hdc;

switch(message) { 

// WM_INITDIALOG ............................................................................................
case WM_INITDIALOG:
hwnd=GetDlgItem(hDlg,IDC_LIST_LAYERS); if(hwnd!=NULL) SetFont(hwnd,MW.hFontListLay);
MW.SetDlgInfo(hDlg); return (LRESULT)TRUE;

// WM_CTLCOLORSTATIC ........................................................................................
case WM_CTLCOLORSTATIC: hdc=(HDC)wParam; id=GetDlgCtrlID((HWND)lParam); if(id<=0) break;
SetBkColor(hdc,GetSysColor(COLOR_WINDOW)); SetTextColor(hdc,GetSysColor(COLOR_BTNTEXT));
SetBkMode(hdc,TRANSPARENT);
if(id==IDC_PERIOD||id==IDC_WLENGH||id==IDC_ANGLE||id==IDC_POL||id==IDC_HARMS||id==IDC_EPS_INC||id==IDC_EPS_OUT||
id==IDC_DZ) return (LRESULT)MW.hBrushBkg; return (LRESULT)MW.hBrushDial;

// WM_COMMAND ...............................................................................................
case WM_COMMAND: 

switch(LOWORD(wParam)) {
case IDOK: case IDCANCEL: { EndDialog(hDlg,0); return TRUE;} break; 
}
break;

// WM_DESTROY .................................................................................................
case WM_DESTROY: break; 
}
return FALSE;
}

//-------------------------------------------------------------------------------------------------------------
// ������� ����������� ���� � ���������.

INT_PTR CALLBACK DlgAbout(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
UNREFERENCED_PARAMETER(lParam);

switch (message) {
case WM_INITDIALOG:	return (INT_PTR)TRUE;
case WM_COMMAND: if(LOWORD(wParam)==IDOK||LOWORD(wParam)==IDCANCEL) { EndDialog(hDlg,LOWORD(wParam)); return (INT_PTR)TRUE;}
break;
}
return (INT_PTR)FALSE;
}
