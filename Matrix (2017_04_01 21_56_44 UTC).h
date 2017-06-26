/*...........................................................................................................

clRowMatr,clRows

...........................................................................................................*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ����� ������� �������.

class clRowMatr {

public:
int N; complex *Vect;

clRowMatr(void); // �����������.
clRowMatr(const clRowMatr &); // ���������� �����������.
~clRowMatr(void); // ����������.
BYTE operator =(const clRowMatr &); // �������� �����������.
void Zero(void); // ��������� ����������.
void Free(void); // ������������ ������.
BYTE Alloc(int N_); // ��������� ������ ��� �������.
BYTE IsOK(void) const; // ��������.
BYTE operator =(complex); // �������� ���������� ���������� ������.
clRowMatr operator -(); // ���� �����.
clRowMatr &operator +=(clRowMatr const &); // ����������� �������.
clRowMatr &operator -=(clRowMatr const &); // ��������� �������.
clRowMatr &operator +=(complex); // ����������� ��������� ������� � ���������� 'c'.
clRowMatr &operator -=(complex); // ��������� ��������� ������� � ���������� 'c'.
clRowMatr &operator *=(complex); // ��������� �� ����������� �����.
clRowMatr &operator /=(complex); // ������� �� ����������� �����.
clRowMatr &operator *=(double); // ��������� �� �������������� �����.
clRowMatr &operator /=(double); // ������� �� �������������� �����.
BYTE SetZero(void); // ��������� �������.
BYTE SetRand(double Lim); // ���������� ���������� ������� � �������� Re,Im �� -Lim �� +Lim.
double GetAbsMax(void); // ��������� ������������� ��������.
double GetNorm(void); // ��������� ����� �������.
BYTE Norm(void); // ���������� ������� �������.
BYTE Write(FILE *fp); // ������ ������� � ����.
BYTE Read(FILE *fp); // ������ ������� �� �����.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ��������� � ������� ��� ������ �������.

clRowMatr operator +(const clRowMatr &,const clRowMatr &); // ��������.
clRowMatr operator -(const clRowMatr &,const clRowMatr &); // ���������.
clRowMatr operator *(const clRowMatr &,complex); // ��������� �� �����.
clRowMatr operator /(const clRowMatr &,complex); // ������� �� �����.
clRowMatr operator *(complex,const clRowMatr &); // ��������� �� �����.
clRowMatr operator +(const clRowMatr &RM_,complex c); // ����������� ��������� ������� � ���������� 'c'.
clRowMatr operator +(complex c,const clRowMatr &RM_); // ����������� ��������� ������� � ���������� 'c'.
clRowMatr operator -(const clRowMatr &RM_,complex c); // ��������� ��������� ������� � ���������� 'c'.
clRowMatr operator *(const clRowMatr &,const clRowMatr &); // ��������� ������������ ������.
clRowMatr operator !(const clRowMatr &); // �������� ������������ �������.
clRowMatr conj(clRowMatr const &); // ����������� ����������.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ����� ������� �������� clRowMatr.

class clRows
{
public:

int Nx,Ny; clRowMatr *Rows;

clRows(void); // �����������.
clRows(const clRows &); // ���������� �����������.
~clRows(void); // ����������.
BYTE operator =(const clRows &); // �������� �����������. 
void Zero(void); // ��������� ����������.
void Free(void); // ������������ ������.
BYTE Alloc(int Nx_,int Ny_); // ��������� ������ ��� �������.
BYTE IsOK(void) const; // ��������.
clRowMatr *Get(int num); // ��������� ��������� �� ������� � ������� 'num'.
BYTE Write(FILE *fp); // ������ ������� � ����.
BYTE Read(FILE *fp); // ������ ������� �� �����.
};