//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ����� ����������� �����.

class complex {

public:

double re,im;

complex(); // �����������.
complex(double re_,double im_); // �����������.
complex operator +(); // ���� ����.
complex operator -(); // ���� �����.
complex operator +=(complex &); // ����������� ������������ �����.
complex operator -=(complex &); // ��������� ������������ �����.
complex operator *=(complex &); // ��������� �� ����������� �����.
complex operator /=(complex &); // ������� �� ����������� �����.
complex operator =(double); // ������������ ��������������� �����.
complex operator *=(double); // ��������� �� �����.
complex operator /=(double); // ������� �� �����.
};

complex operator +(complex &,complex &); // ��������.
complex operator -(complex &,complex &); // ���������.
complex operator *(complex &,complex &); // ���������.
complex operator /(complex &,complex &); // �������.
complex operator *(complex &,double); // ��������� �� �����.
complex operator *(double,complex &); // ��������� �� �����.
complex operator /(complex &,double); // ������� �� �����.
complex operator /(double,complex &); // ������� �� �����.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ������� ��� ����������� �����.

complex polar(double Abs,double Phase); // �������� ������������ ����� �� ��������� � ����.
complex conj(complex c); // ����������� ����������.
double real(complex c); // �������������� �����.
double imag(complex c); // ������ �����.
double absSq(complex c); // ������� ������ ������������ �����.
double abs(complex c); // ������ ������������ �����.
double arg(complex c); // �������� ������������ �����.
complex sqrt(complex c); // ���������� ������.
complex pow(complex c,double p); // ���������� � �������.
complex exp(complex c); // ����������.
complex log(complex c); // ��������.
complex Inv(complex c); // �������� �����.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ���������.

#define Cmplx_0 complex(0.,0.)
#define Cmplx_1 complex(1.,0.)
#define Cmplx_I complex(0.,1.)
