/*...........................................................................................................

// Класс столбца матрицы.
class clRowMatr { clRowMatr,clRowMatr,clRowMatr,=,Zero,Free,Alloc,IsOK,-,+=R,-=R,+=c,-=c,*=c,/=c,*=d,/=d,
SetZero,SetRand,GetAbsMax,GetNorm,Norm},

// Операторы и функции для класса столбца.
+,-,*c,/c,c*,R+c,c+R,R-c,R*R,!,Conj,

// Класс массива столбцов...
...........................................................................................................*/


#include "stdafx.h"

#include "Const.h"
#include "cmplx.h"
#include "Matrix.h"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Класс столбца матрицы.

//-----------------------------------------------------------------------------------------------------------
// Конструктор.

clRowMatr::clRowMatr(void)
{
Zero();
}

//-----------------------------------------------------------------------------------------------------------
// Копирующий конструктор.

clRowMatr::clRowMatr(const clRowMatr &RM_)
{
int i;

Zero(); if(RM_.IsOK()!=0) return; if(Alloc(RM_.N)!=0) return; for(i=0;i<N;i++) Vect[i]=RM_.Vect[i];
}

//-----------------------------------------------------------------------------------------------------------
// Деструктор.

clRowMatr::~clRowMatr(void)
{
Free();
}

//-----------------------------------------------------------------------------------------------------------
// Оператор копирования. 

BYTE clRowMatr::operator =(const clRowMatr &RM_)
{
BYTE fl; int i;

if(RM_.IsOK()!=0) return 1; fl=0; if(IsOK()!=0) fl=1; else if(N!=RM_.N) fl=1;
if(fl!=0) { if(Alloc(RM_.N)!=0) return 2;} for(i=0;i<N;i++) Vect[i]=RM_.Vect[i]; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Обнуление переменных.

void clRowMatr::Zero(void)
{
Vect=NULL; N=0;
}

//-----------------------------------------------------------------------------------------------------------
// Освобождение памяти.

void clRowMatr::Free(void)
{
SAFE_DELETE_ARR(Vect); N=0;
}

//-----------------------------------------------------------------------------------------------------------
// Выделение памяти для массива.

BYTE clRowMatr::Alloc(int N_)
{
Free(); if(N_<=0) return 1; N=N_; Vect=new complex[N]; if(Vect==NULL) return 2; return 0;
} 

//-----------------------------------------------------------------------------------------------------------
// Проверки.

BYTE clRowMatr::IsOK(void) const
{
if(N<=0) return 1; if(Vect==NULL) return 2; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Оператор заполнения одинаковым числом.

BYTE clRowMatr::operator =(complex c)
{
int i;

if(IsOK()!=0) return 1; for(i=0;i<N;i++) Vect[i]=c; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Знак минус.

clRowMatr clRowMatr::operator -()
{
int i; clRowMatr RM;

if(IsOK()!=0) goto end; if(RM.Alloc(N)!=0) goto end; for(i=0;i<N;i++) RM.Vect[i]=-Vect[i];
end: return RM;
}

//-----------------------------------------------------------------------------------------------------------
// Прибавление столбца.

clRowMatr &clRowMatr::operator +=(clRowMatr const &RM)
{
int i;

if(IsOK()!=0) goto end; if(RM.IsOK()!=0) goto end; if(N!=RM.N) goto end;
for(i=0;i<N;i++) Vect[i]+=RM.Vect[i];
end: return *this;
}

//-----------------------------------------------------------------------------------------------------------
// Вычитание столбца.

clRowMatr &clRowMatr::operator -=(clRowMatr const &RM)
{
int i;

if(IsOK()!=0) goto end; if(RM.IsOK()!=0) goto end; if(N!=RM.N) goto end;
for(i=0;i<N;i++) Vect[i]-=RM.Vect[i];
end: return *this;
}

//-----------------------------------------------------------------------------------------------------------
// Прибавление единичной матрицы с множителем 'c'.

clRowMatr &clRowMatr::operator +=(complex c)
{
int i;

if(IsOK()!=0) return *this; for(i=0;i<N;i++) Vect[i]+=c; return *this;
}

//-----------------------------------------------------------------------------------------------------------
// Вычитание единичной матрицы с множителем 'c'.

clRowMatr &clRowMatr::operator -=(complex c)
{
int i;

if(IsOK()!=0) return *this; for(i=0;i<N;i++) Vect[i]-=c; return *this;
}

//-----------------------------------------------------------------------------------------------------------
// Умножение на комплексное число.

clRowMatr &clRowMatr::operator *=(complex c)
{
int i;

if(IsOK()!=0) return *this; for(i=0;i<N;i++) Vect[i]*=c; return *this;
}

//-----------------------------------------------------------------------------------------------------------
// Деление на комплексное число.

clRowMatr &clRowMatr::operator /=(complex c)
{
int i; complex cInv;

if(IsOK()!=0) return *this; cInv=Inv(c); for(i=0;i<N;i++) Vect[i]*=cInv; return *this;
}

//-----------------------------------------------------------------------------------------------------------
// Умножение на действительное число.

clRowMatr &clRowMatr::operator *=(double d)
{
int i;

if(IsOK()!=0) return *this; for(i=0;i<N;i++) Vect[i]*=d; return *this;
}

//-----------------------------------------------------------------------------------------------------------
// Деление на действительное число.

clRowMatr &clRowMatr::operator /=(double d)
{
int i; double v;

if(IsOK()!=0) return *this; if(d==0.) return *this; v=1./d; for(i=0;i<N;i++) Vect[i]*=v; return *this;
}

//-----------------------------------------------------------------------------------------------------------
// Обнуление вектора.

BYTE clRowMatr::SetZero(void)
{
int i;

if(IsOK()!=0) return 1; for(i=0;i<N;i++) Vect[i]=Cmplx_0; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Заполнение случайными числами в пределах Re,Im от -Lim до +Lim.

BYTE clRowMatr::SetRand(double Lim)
{
int i; double coe,Re,Im;

if(IsOK()!=0) return 1; coe=2./(double)RAND_MAX;
for(i=0;i<N;i++) { Re=((double)rand()*coe-1.)*Lim; Im=((double)rand()*coe-1.)*Lim; Vect[i]=complex(Re,Im);}
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Получение максимального значения.

double clRowMatr::GetAbsMax(void)
{
int i; double v,vM;

if(IsOK()!=0) return 0.; vM=0.; for(i=0;i<N;i++) { v=abs(Vect[i]); if(v>vM) vM=v;} return vM;
}

//-----------------------------------------------------------------------------------------------------------
// Получение нормы вектора.

double clRowMatr::GetNorm(void)
{
int i; double s; complex c;

if(IsOK()!=0) return 0.; s=0.; for(i=0;i<N;i++) { c=Vect[i]; s+=real(c*conj(c));} if(s<=0.) return 0.;
return sqrt(s);
}

//-----------------------------------------------------------------------------------------------------------
// Нормировка вектора столбца.

BYTE clRowMatr::Norm(void)
{
int i; double s; complex c;

if(IsOK()!=0) return 1; s=0.; for(i=0;i<N;i++) { c=Vect[i]; s+=real(c*conj(c));} if(s<=0.) return 2;
s=1./sqrt(s); for(i=0;i<N;i++) Vect[i]*=s; return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Запись столбца в файл.

BYTE clRowMatr::Write(FILE *fp)
{
int i;

if(fp==NULL) return 1;

for(i=0;i<N;i++) fprintf(fp,"%lf %lf ",Vect[i].re,Vect[i].im);
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Чтение столбца из файла.

BYTE clRowMatr::Read(FILE *fp)
{
int i;

if(fp==NULL) return 1;

for(i=0;i<N;i++) fscanf(fp,"%lf %lf ",&Vect[i].re,&Vect[i].im);

return 0;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Операторы и функции для класса столбца.

//-----------------------------------------------------------------------------------------------------------
// Сложение.

clRowMatr operator +(const clRowMatr &RM1,const clRowMatr &RM2)
{
int i; clRowMatr RM;

if(RM1.IsOK()!=0||RM2.IsOK()!=0) goto end; if(RM1.N!=RM2.N) goto end; if(RM.Alloc(RM1.N)!=0) goto end;
for(i=0;i<RM.N;i++) RM.Vect[i]=RM1.Vect[i]+RM2.Vect[i]; end: return RM;
}

//-----------------------------------------------------------------------------------------------------------
// Вычитание.

clRowMatr operator -(const clRowMatr &RM1,const clRowMatr &RM2)
{
int i; clRowMatr RM;

if(RM1.IsOK()!=0||RM2.IsOK()!=0) goto end; if(RM1.N!=RM2.N) goto end; if(RM.Alloc(RM1.N)!=0) goto end;
for(i=0;i<RM.N;i++) RM.Vect[i]=RM1.Vect[i]-RM2.Vect[i]; end: return RM;
}

//-----------------------------------------------------------------------------------------------------------
// Умножение на число.

clRowMatr operator *(const clRowMatr &RM_,complex c)
{
int i; clRowMatr RM;

if(RM_.IsOK()!=0) goto end; if(RM.Alloc(RM_.N)!=0) goto end;
for(i=0;i<RM.N;i++) RM.Vect[i]=RM_.Vect[i]*c; end: return RM;
}

//-----------------------------------------------------------------------------------------------------------
// Деление на число.

clRowMatr operator /(const clRowMatr &RM_,complex c)
{
int i; complex cInv; clRowMatr RM;

if(RM_.IsOK()!=0) goto end; if(RM.Alloc(RM_.N)!=0) goto end; cInv=Inv(c);
for(i=0;i<RM.N;i++) RM.Vect[i]=RM_.Vect[i]*cInv; end: return RM;
}

//-----------------------------------------------------------------------------------------------------------
// Умножение на число.

clRowMatr operator *(complex c,const clRowMatr &RM_)
{
int i; clRowMatr RM;

if(RM_.IsOK()!=0) goto end; if(RM.Alloc(RM_.N)!=0) goto end;
for(i=0;i<RM.N;i++) RM.Vect[i]=RM_.Vect[i]*c; end: return RM;
}

//-----------------------------------------------------------------------------------------------------------
// Прибавление единичной матрицы с множителем 'c'.

clRowMatr operator +(const clRowMatr &RM_,complex c)
{
int i; clRowMatr RM;

if(RM_.IsOK()!=0) goto end; if(RM.Alloc(RM_.N)!=0) goto end;
for(i=0;i<RM.N;i++) RM.Vect[i]=RM_.Vect[i]+c; end: return RM;
}

//-----------------------------------------------------------------------------------------------------------
// Прибавление единичной матрицы с множителем 'c'.

clRowMatr operator +(complex c,const clRowMatr &RM_)
{
int i; clRowMatr RM;

if(RM_.IsOK()!=0) goto end; if(RM.Alloc(RM_.N)!=0) goto end;
for(i=0;i<RM.N;i++) RM.Vect[i]=RM_.Vect[i]+c; end: return RM;
}

//-----------------------------------------------------------------------------------------------------------
// Вычитание единичной матрицы с множителем 'c'.

clRowMatr operator -(const clRowMatr &RM_,complex c)
{
int i; clRowMatr RM;

if(RM_.IsOK()!=0) goto end; if(RM.Alloc(RM_.N)!=0) goto end;
for(i=0;i<RM.N;i++) RM.Vect[i]=RM_.Vect[i]-c; end: return RM;
}

//-----------------------------------------------------------------------------------------------------------
// Умножение диагональных матриц.

clRowMatr operator *(const clRowMatr &RM1,const clRowMatr &RM2)
{
int i,N; clRowMatr RM;

if(RM1.IsOK()!=0) goto end; if(RM2.IsOK()!=0) goto end; N=RM1.N; if(RM2.N!=N) goto end;
if(RM.Alloc(N)!=0) goto end; for(i=0;i<N;i++) RM.Vect[i]=RM1.Vect[i]*RM2.Vect[i];
end: return RM;
}

//-----------------------------------------------------------------------------------------------------------
// Обратная диагональная матрица.

clRowMatr operator !(const clRowMatr &RM_)
{
int i; clRowMatr RM;

if(RM_.IsOK()!=0) goto end; if(RM.Alloc(RM_.N)!=0) goto end;
for(i=0;i<RM.N;i++) RM.Vect[i]=Inv(RM_.Vect[i]); end: return RM;
}

//-----------------------------------------------------------------------------------------------------------
// Комплексное сопряжение.

clRowMatr Conj(clRowMatr const &RM_)
{
int i; clRowMatr RM;

if(RM_.IsOK()!=0) goto end; if(RM.Alloc(RM_.N)!=0) goto end;
for(i=0;i<RM.N;i++) RM.Vect[i]=conj(RM_.Vect[i]); end: return RM;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Класс массива столбцов clRowMatr.

//-----------------------------------------------------------------------------------------------------------
// Конструктор.

clRows::clRows(void)
{
Zero();
}

//-----------------------------------------------------------------------------------------------------------
// Копирующий конструктор.

clRows::clRows(const clRows &R_)
{
int i;

Zero(); if(R_.IsOK()!=0) return; if(Alloc(R_.Nx,R_.Ny)!=0) return;
for(i=0;i<Ny;i++) Rows[i]=R_.Rows[i];
}

//-----------------------------------------------------------------------------------------------------------
// Деструктор.

clRows::~clRows(void)
{
Free();
}

//-----------------------------------------------------------------------------------------------------------
// Оператор копирования. 

BYTE clRows::operator =(const clRows &R_)
{
BYTE fl; int i;

if(R_.IsOK()!=0) return 1; fl=0; if(IsOK()!=0) fl=1; else if(Nx!=R_.Nx||Ny!=R_.Ny) fl=1;
if(fl!=0) { if(Alloc(R_.Nx,R_.Ny)!=0) return 2;}
for(i=0;i<Nx;i++) Rows[i]=R_.Rows[i];
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Обнуление переменных.

void clRows::Zero(void)
{
Rows=NULL; Nx=Ny=0;
}

//-----------------------------------------------------------------------------------------------------------
// Освобождение памяти.

void clRows::Free(void)
{
int i;

for(i=0;i<Ny;i++) Rows[i].Free(); SAFE_DELETE_ARR(Rows); Nx=Ny=0;
}

//-----------------------------------------------------------------------------------------------------------
// Выделение памяти для массива.

BYTE clRows::Alloc(int Nx_,int Ny_)
{
int i;

Free(); if(Nx_<=0||Ny_<=0) return 1; if(INT_MAX/Ny_<Nx_) return 2; Nx=Nx_; Ny=Ny_;
Rows=new clRowMatr[Ny]; if(Rows==NULL) return 3;
for(i=0;i<Ny;i++) if(Rows[i].Alloc(Nx)!=0) return 4; return 0;
} 

//-----------------------------------------------------------------------------------------------------------
// Проверки.

BYTE clRows::IsOK(void) const
{
int i;

if(Nx<=0||Ny<=0) return 1; if(Rows==NULL) return 2;
for(i=0;i<Ny;i++) if(Rows[i].IsOK()!=0) return 3;
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Получение указателя на столбец с номером 'num'.

clRowMatr *clRows::Get(int num)
{
if(IsOK()!=0) return NULL; if(num<0||num>=Ny) return NULL; return Rows+num;
}

//-----------------------------------------------------------------------------------------------------------
// Запись матрицы в файл.

BYTE clRows::Write(FILE *fp)
{
int i;

if(fp==NULL) return 1;

fprintf(fp,"%d %d\n",Nx,Ny);
for(i=0;i<Ny;i++) { if(Rows[i].Write(fp)!=0) return 2; fprintf(fp,"\n");}
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// Чтение матрицы из файла.

BYTE clRows::Read(FILE *fp)
{
int i,Nx_,Ny_;

if(fp==NULL) return 1;

Free();
if(fscanf(fp,"%d %d\n",&Nx_,&Ny_)==EOF) return 2; if(Nx_<=0||Ny_<=0) return 3;
if(Alloc(Nx_,Ny_)!=0) return 4;
for(i=0;i<Ny;i++) { if(Rows[i].Read(fp)!=0) return 5; fscanf(fp,"\n");}
return 0;
}
