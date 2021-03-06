/*...........................................................................................................

// ������� ��� ����������� �����.
polar,conj,real,imag,absSq,abs,arg,sqrt,pow,exp,log,Inv,

// ����� ����������� �����.
class complex { complex,complex,'+c','-c','+=c','-=c','*=c','/=c','=d','*=d','/=d'},

// ��������� ��� ������ ����������� �����.
'c+c','c-c','c*c','c/c','c*d','d*c','c/d','d/c'

...........................................................................................................*/

#include "stdafx.h"

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Const.h"
#include "cmplx.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ������� � �����������.

#define SmCnst32_d 1.e-32

#define SQRT(v) (v<SmCnst32_d?0.:sqrt(v)) // ���������� ����������� �����.

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ������� ��� ����������� �����.

//-----------------------------------------------------------------------------------------------------------
// �������� ������������ ����� �� ��������� � ����.

complex polar(double Abs,double Phase)
{
complex c;

c.re=Abs*cos(Phase); c.im=Abs*sin(Phase); return c;
}

//-----------------------------------------------------------------------------------------------------------
// ����������� ����������.

complex conj(complex c)
{
return complex(c.re,-c.im);
}

//-----------------------------------------------------------------------------------------------------------
// �������������� �����.

double real(complex c)
{
return c.re;
}

//-----------------------------------------------------------------------------------------------------------
// ������ �����.

double imag(complex c)
{
return c.im;
}

//-----------------------------------------------------------------------------------------------------------
// ������� ������ ������������ �����.

double absSq(complex c)
{
return c.re*c.re+c.im*c.im;
}

//-----------------------------------------------------------------------------------------------------------
// ������ ������������ �����.

double abs(complex c)
{
double v;

v=pow(c.re,2.)+pow(c.im,2.); return SQRT(v);
}

//-----------------------------------------------------------------------------------------------------------
// �������� ������������ �����.

double arg(complex c)
{
return atan2(c.im,c.re);
}

//-----------------------------------------------------------------------------------------------------------
// ���������� ������.

complex sqrt(complex c)
{
double Abs,Arg;

Abs=abs(c); Arg=arg(c); return polar(SQRT(Abs),Arg*0.5);
}

//-----------------------------------------------------------------------------------------------------------
// ���������� � �������.

complex pow(complex c,double p)
{
double Abs,Arg;

Abs=abs(c); Arg=arg(c); return polar(pow(Abs,p),Arg*p);
}

//-----------------------------------------------------------------------------------------------------------
// ����������.

complex exp(complex c)
{
return polar(exp(c.re),c.im);
}

//-----------------------------------------------------------------------------------------------------------
// ��������.

complex log(complex c)
{
return polar(log(abs(c)),arg(c));
}

//-----------------------------------------------------------------------------------------------------------
// �������� �����.

complex Inv(complex c)
{
double x,y,v;

x=c.re; y=c.im; v=1./(x*x+y*y); return complex(x*v,-y*v);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� ����������� �����.

//-----------------------------------------------------------------------------------------------------------
// �����������.

complex::complex()
{
re=0.; im=0.;
}

//-----------------------------------------------------------------------------------------------------------
// �����������.

complex::complex(double re_,double im_)
{
re=re_; im=im_;
}

//-----------------------------------------------------------------------------------------------------------
// ���� ����.

complex complex::operator +()
{
return *this;
}

//-----------------------------------------------------------------------------------------------------------
// ���� �����.

complex complex::operator -()
{
return complex(-re,-im);
}

//-----------------------------------------------------------------------------------------------------------
// ����������� ������������ �����.

complex complex::operator +=(complex &a)
{
re+=a.re; im+=a.im; return *this;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� ������������ �����.

complex complex::operator -=(complex &a)
{
re-=a.re; im-=a.im; return *this;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� �� ����������� �����.

complex complex::operator *=(complex &a)
{
complex c;

c.re=re; c.im=im; c=c*a; re=c.re; im=c.im; return *this;
}

//-----------------------------------------------------------------------------------------------------------
// ������� �� ����������� �����.

complex complex::operator /=(complex &a)
{
double v,R,I;

v=1./(a.re*a.re+a.im*a.im); R=re*v; I=im*v; re=R*a.re+I*a.im; im=I*a.re-R*a.im; return *this;
}

//-----------------------------------------------------------------------------------------------------------
// ������������ ��������������� �����.

complex complex::operator =(double d)
{
re=d; im=0.; return *this;
}

//-----------------------------------------------------------------------------------------------------------
// ��������� �� �����.

complex complex::operator *=(double d)
{
re*=d; im*=d; return *this;
}

//-----------------------------------------------------------------------------------------------------------
// ������� �� �����.

complex complex::operator /=(double d)
{
re/=d; im/=d; return *this;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ��������� ��� ������ ����������� �����.

//-----------------------------------------------------------------------------------------------------------
// ��������.

complex operator +(complex &a,complex &b)
{
return complex(a.re+b.re,a.im+b.im);
}

//-----------------------------------------------------------------------------------------------------------
// ���������.

complex operator -(complex &a,complex &b)
{
return complex(a.re-b.re,a.im-b.im);
}

//-----------------------------------------------------------------------------------------------------------
// ���������.

complex operator *(complex &a,complex &b)
{
return complex(a.re*b.re-a.im*b.im,a.re*b.im+a.im*b.re);
}

//-----------------------------------------------------------------------------------------------------------
// �������.

complex operator /(complex &a,complex &b)
{
double v,R,I;

v=1./(b.re*b.re+b.im*b.im); R=a.re*v; I=a.im*v; return complex(R*b.re+I*b.im,I*b.re-R*b.im);
}

//---------------------------------------------------------------------------------------------------------------------------
// ��������� �� �����.

complex operator *(complex &a,double d)
{
complex c;

c.re=a.re*d; c.im=a.im*d; return c;
}

//---------------------------------------------------------------------------------------------------------------------------
// ��������� �� �����.

complex operator *(double d,complex &a)
{
complex c;

c.re=a.re*d; c.im=a.im*d; return c;
}

//---------------------------------------------------------------------------------------------------------------------------
// ������� �� �����.

complex operator /(complex &a,double d)
{
complex c;

c.re=a.re/d; c.im=a.im/d; return c;
}

//---------------------------------------------------------------------------------------------------------------------------
// ������� �� �����.

complex operator /(double d,complex &a)
{
double R;

R=d/(a.re*a.re+a.im*a.im); return complex(R*a.re,-R*a.im);
}
