//mmm xxx aaa
sprintf(TxtStr,"be: %d",be); MessageBox(NULL,TxtStr,"",MB_EX);


/*
//xxx mmm aaa
#define M_PI 3.141592653
//-----------------------------------------------------------------------------------------------------------
// ������ ������� �� �����.

BYTE clRows::Read(FILE *fp)
{
int i,j; int Nx_,Ny_; double x,y,coeX,coeY;

if(fp==NULL) return 1;

Free();
if(fscanf(fp,"%d %d\n",&Nx_,&Ny_)==EOF) return 2; if(Nx_<=0||Ny_<=0) return 3;
if(Alloc(Nx_,Ny_)!=0) return 4;
for(i=0;i<Ny;i++) { if(Rows[i].Read(fp)!=0) return 5; fscanf(fp,"\n");}

coeX=2.*M_PI/(double)(Nx-1)*3.;
coeY=2.*M_PI/(double)(Ny-1);
for(j=0;j<Ny;j++) { y=sin((double)j*coeY);
for(i=0;i<Nx;i++) { x=sin((double)i*coeX);
Rows[j].Vect[i]=x*y;
}}

return 0;
}
*/
/*
//------------------------------------------------------------------------------------------------------
// ��������� ��� ����� ��� ���������� ������������ �� ����� ��������� ����� � ������.


for(i=0;i<ySize;i++) { yPix=i*Mashtab; depthSum=depthSumN=0.; z=0.;

//---------------- ���������� ��������� ������� ������������ ��������� (����� ���� � ���������, ����� ������� ����� �������).
for(k=0;k<Cryst.laysNum;k++) { pL=Cryst.Lays+k; depthSum=depthSumN; depthSumN+=pL->depth;
if(int(depthSumN/yPix)>=1) { yPixCurLay=yPix-depthSum; break;} // ����� ����� ����, � ������� ��������� �������.
} // ����� ����� �� 'k'.
if(yPix>depthSumN) { for(k=0;k<xSize;k++) DistrAmp[i][k]=0.; continue;} // ���� ����� �� ������� ���������.
for(k=0;k<pL->nDiv-1;k++) { z+=pL->dz; if(int(z/yPixCurLay)>=1) break; // ����� ����� ��������� � ����, ����� ����� �������� ��������� ��� ������� (�� ��� 'z').
} // ����� ����� �� 'k'. 'k' ������ ����� ���������, ����� ����� �������� ����� ������� �� ��� 'x'.
//---------------- // ����� ��������� ���������.
if(flTypDraw==TypDraw_E) { A2=abs(pL->EDistr.Rows[k].Vect[0]); A1=abs(pL->EDistr.Rows[k+1].Vect[0]);}
else { A2=abs(pL->EDistr.Rows[k].Vect[0]); A1=abs(pL->EDistr.Rows[k+1].Vect[0]);} // ������������ ��� ������������.
kcoe=(A2-A1/pL->dz); DistrAmp[i][0]=kcoe*yPix+A1-kcoe*xDistr; //������������� �� ��� z � ������� �����, ��� ��������� �������.
}

for(j=0;j<xSize;j++) { xPix=j*Mashtab;
if(xPix>Cryst.Period) { DistrAmp[0][j]=0.; continue;} // ���� ����� �� ������� ���������.
xDistr=int(xPix/dxDistr); //���������� ��������� ������� ������������ ��������� (����� ��������� �� ��� 'x', ����� �������� ����� �������).
if(flTypDraw==TypDraw_E) { A2=abs(pL->EDistr.Rows[0].Vect[xDistr]); A1=abs(pL->EDistr.Rows[0].Vect[xDistr]);}
else { A2=abs(pL->EDistr.Rows[0].Vect[xDistr]); A1=abs(pL->EDistr.Rows[0].Vect[xDistr]);} // ������������ ��� ������������.
}
*/

//xxx kcoe=(A2-A1/dxDistr); AyK=kcoe*xPix+A1-kcoe*xDistr; // ������������� �� ��� 'x' � ������� �����.
//xxx ����������.

//xxx kcoe=(A2-A1/dxDistr); AyKN=kcoe*xPix+A1-kcoe*xDistr; // ������������� �� ��� 'x' � ������ �����.

//xxx kcoe=(A2-A1/pL->dz); DistrAmp[i][j]=kcoe*yPix+A1-kcoe*(pL->dz*k); //������������� �� ��� z � ������� �����, ��� ��������� �������.
//xxx ����������.

if(flTypDraw==TypDraw_E) { A2=abs(pL->EDistr.Rows[k].Vect[xDistr+1]); A1=abs(pL->EDistr.Rows[k].Vect[xDistr]);}
else { A2=abs(pL->HDistr.Rows[k].Vect[xDistr+1]); A1=abs(pL->HDistr.Rows[k].Vect[xDistr]);} // ������������ ��� ������������.
AyK=A1*(1.-weiX)+A2*weiX; // ������������ �� 'x'.
if(flTypDraw==TypDraw_E) { A2=abs(pL->EDistr.Rows[k+1].Vect[xDistr+1]); A1=abs(pL->EDistr.Rows[k+1].Vect[xDistr]);}
else { A2=abs(pL->HDistr.Rows[k+1].Vect[xDistr+1]); A1=abs(pL->HDistr.Rows[k+1].Vect[xDistr]);} // ������������ ��� ������������.
AyKN=A1*(1.-weiX)+A2*weiX; // ������������ �� 'x'.

//mmm
sprintf(TxtStr,"k: %d xDistr,Nx: %d %d weiX: %lf",k,xDistr,Nx,weiX); MessageBox(NULL,TxtStr,"",MB_EX);

//mmm
sprintf(TxtStr,"k: %d pR->Ny: %d",k,pR->Ny); MessageBox(NULL,TxtStr,"",MB_EX);

//mmm
sprintf(TxtStr,"pRM->N,Nx %d %d",pRM->N,Nx); MessageBox(NULL,TxtStr,"",MB_EX);
//mmm
sprintf(TxtStr,"k+1: %d pR->Ny: %d pL->nDiv: %d weiY: %lf",k+1,pR->Ny,pL->nDiv,weiY); MessageBox(NULL,TxtStr,"",MB_EX);
if(depthSum>Cryst.Period) Mashtab=depthSum/ySize; else Mashtab=Cryst.Period/xSize;
Mashtab=MIN(depthSum/ySize,Cryst.Period/xSize); if(Mashtab<=0.) return 3;
dxDistr=Cryst.Period/Cryst.Lays[0].EDistr.Nx; // ������� �� ��� x.

//-----------------------------------------------------------------------------------------------------------
// �������� �����������. 

BYTE clCrystal::operator =(clCrystal &Lays_)
{
int i;

if(Lays_.IsOK()!=0) return 1; if(Alloc(Lays_.laysNum)!=0) return 2;
for(i=0;i<laysNum;i++) Lays[i]=Lays_.Lays[i]; return 0;
}

BYTE operator =(clCrystal &); // �������� �����������.
SetSelCombo(hDlg,IDC_TYPE_DRAWUINT id,BYTE num); // ��������� ������ ������ � ��������������� ������.

SendMessage(hwnd,CB_SETCURSEL,(WPARAM)flTypDraw,0L);


//xxx mmm aaa
#define M_PI 3.141592653
//-----------------------------------------------------------------------------------------------------------
// ������ ������� �� �����.

BYTE clRows::Read(FILE *fp)
{
int i,j; int Nx_,Ny_; double x,y,coeX,coeY;

if(fp==NULL) return 1;

Free();
if(fscanf(fp,"%d %d\n",&Nx_,&Ny_)==EOF) return 2; if(Nx_<=0||Ny_<=0) return 3;
if(Alloc(Nx_,Ny_)!=0) return 4;
for(i=0;i<Ny;i++) { if(Rows[i].Read(fp)!=0) return 5; fscanf(fp,"\n");}

/*
coeX=2.*M_PI/(double)(Nx-1)*3.;
coeY=2.*M_PI/(double)(Ny-1);
for(j=0;j<Ny;j++) { y=sin((double)j*coeY);
for(i=0;i<Nx;i++) { x=sin((double)i*coeX);
Rows[j].Vect[i]=x*y;
}}
*/
return 0;
}

//-----------------------------------------------------------------------------------------------------------
// �������� �����������. 

BYTE clMaterialAll::operator =(const clMaterialAll &M_)
{
int i;

if(M_.IsOK()!=0) return 1; if(Alloc(M_.N)!=0) return 2;
for(i=0;i<N;i++) Mat[i]=M_.Mat[i]; return 0;
}



//---------------------------------------------------------------------------------
#define szXMax 2000 // ������������ ������ ������� ������������� �� ��� x (� ��������).
#define szYMax 1000 // ������������ ������ ������� ��������� �� ��� z (� ��������).
double DistrAmp[szXMax][szYMax];



/*xxx mmm aaa
//-----------------------------------------------------------------------------------------------------------
// ������ ������ �� �����.

BYTE clMain::Read(char *File_Name)
{
BYTE err; FILE *fp;

err=0; fp=NULL;
fp=fopen(File_Name,"r"); if(fp==NULL) { err=1; goto end;}
// ������ ���������� � ���������.
if(Task.Read(fp)!=0) { err=2; goto end;}
if(Matter.Read(fp)!=0) { err=3; goto end;}
if(Cryst.Read(fp)!=0) { err=4; goto end;}
// ������ ������������� �����.
if(Cryst.ReadFieldDistr(fp)!=0) { err=5; goto end;}
end: SAFE_CLOSE(fp); return err;
}
*/

//-----------------------------------------------------------------------------------------------------------
// ��������� ������������� �����.

BYTE clMain::DrawDistr(void)
{
BYTE *pvBits,nC,err; UINT dxB,l0,l; int i,j,jv,jSh,k,xSize,ySize,dy;
double amp,coe,v,a1,a2,*DistrAmp,*DistrAmp_1,*DistrAmp_2; struct strPal *pPal;

if(hwnd==NULL) return 1; if(hDlgCntrl==NULL) return 2; 
if(Cryst.IsOKLay()!=0) return 3; if(BmpDiag==NULL) return 4;
BmpDiag->Free(); // ������������ ������.
if(pAmpNorm==NULL) return 5; amp=*pAmpNorm; if(amp<=0.) return 6;

// ����������� ������� ���������.
if(GetClientRect(hwnd,&rc)==FALSE) return 7;
xSize=rc.right-rc.left; ySize=rc.bottom-rc.top-y0; // �������� ������ ���� ����������.
if(xSize<=0||ySize<=0) return 8;

DistrAmp=DistrAmp_1=DistrAmp_2=NULL; err=0;

// ��������� ������.
DistrAmp=new double[xSize*ySize]; if(DistrAmp==NULL) { err=9; goto end;}
DistrAmp_1=new double[xSize*ySize]; if(DistrAmp_1==NULL) { err=10; goto end;}
if(flTypDraw==TypDraw_Full||flTypDraw==TypDraw_SqE||flTypDraw==TypDraw_SqH) {
//xxx aaa
DistrAmp_2=new double[xSize*ySize]; if(DistrAmp_2==NULL) { err=11; goto end;}}

// ����� ������� ���������.
switch(flTypDraw) {
default: err=12; goto end;

// ������������ ����� 'Ex','Hy','Ez' ('p') ��� 'Hx','Ey','Hz' ('s').
case TypDraw_X: case TypDraw_Y: case TypDraw_Z:
if(ComputeDistr(xSize,ySize,DistrAmp_1,flTypDraw)!=0) { err=13; goto end;} // ������������ ������� �������������.
for(i=0;i<ySize;i++) { jSh=i*xSize; for(j=0;j<xSize;j++) { jv=j+jSh; DistrAmp[jv]=DistrAmp_1[jv];}}
break;

// ������������ ���� 'E' ('p') ��� 'H' ('s').
case TypDraw_Full: if(DistrAmp_2==NULL) { err=14; goto end;}
if(ComputeDistr(xSize,ySize,DistrAmp_1,TypDraw_X)!=0) { err=15; goto end;} // ������������ ������� �������������.
if(ComputeDistr(xSize,ySize,DistrAmp_2,TypDraw_Z)!=0) { err=16; goto end;} // ������������ ������� ������������� � ��������.
for(i=0;i<ySize;i++) { jSh=i*xSize; for(j=0;j<xSize;j++) { jv=j+jSh;
a1=DistrAmp_1[jv]; a2=DistrAmp_2[jv]; DistrAmp[jv]=(double)sqrt(a1*a1+a2*a2);}}
break;

// ������� ��������� ���� 'E'.
case TypDraw_SqE:
if(Task.flPol==p_wave_Pol) {
if(ComputeDistr(xSize,ySize,DistrAmp_1,TypDraw_X)!=0) { err=17; goto end;} // ������������ ������� �������������.
if(ComputeDistr(xSize,ySize,DistrAmp_2,TypDraw_Z)!=0) { err=18; goto end;} // ������������ ������� ������������� � ��������.
for(i=0;i<ySize;i++) { jSh=i*xSize; for(j=0;j<xSize;j++) { jv=j+jSh;
a1=DistrAmp_1[jv]; a2=DistrAmp_2[jv]; DistrAmp[jv]=(a1*a1+a2*a2);}}
}
else { if(ComputeDistr(xSize,ySize,DistrAmp_1,TypDraw_Y)!=0) { err=19; goto end;} // ������������ ������� �������������.
for(i=0;i<ySize;i++) { jSh=i*xSize; for(j=0;j<xSize;j++) DistrAmp[j+jSh]=DistrAmp_1[j+jSh]*DistrAmp_1[j+jSh];}}
break;

// ������� ��������� ���� 'H'.
case TypDraw_SqH: 
if(Task.flPol==s_wave_Pol) {
if(ComputeDistr(xSize,ySize,DistrAmp_1,TypDraw_X)!=0) { err=20; goto end;} // ������������ ������� �������������.
if(ComputeDistr(xSize,ySize,DistrAmp_2,TypDraw_Z)!=0) { err=21; goto end;} // ������������ ������� ������������� � ��������.
for(i=0;i<ySize;i++) { jSh=i*xSize; for(j=0;j<xSize;j++) { jv=j+jSh;
a1=DistrAmp_1[jv]; a2=DistrAmp_2[jv]; DistrAmp[jv]=(a1*a1+a2*a2);}}
}
else { if(ComputeDistr(xSize,ySize,DistrAmp_1,TypDraw_Y)!=0) { err=22; goto end;} // ������������ ������� �������������.
for(i=0;i<ySize;i++) { jSh=i*xSize; for(j=0;j<xSize;j++) DistrAmp[j+jSh]=DistrAmp_1[j+jSh]*DistrAmp_1[j+jSh];}}
break;

// ��������� ������������ 'ExE*' ��� 'HxH*'.
//xxx aaa
case TypDraw_FvFc: break;

//xxx mmm aaa
// ����������� ������� ���������.
case TypDraw_DivP: err=102; goto end; // break;
}

// ������������� 'pvBits'.
if(BmpDiag->Init(xSize,ySize,NULL)!=0) { err=23; goto end;}
if(BmpDiag->IsOKB()!=0) { err=18; goto end;}
pvBits=BmpDiag->pvBits; if(pvBits==NULL) { err=24; goto end;}

dy=BmpDiag->dy; dxB=BmpDiag->dxB; // ������������� ��������� ��������.
pPal=&PalDistr; // ����� �������.

// ���������� 'pvBits'.
coe=1./amp;
for(i=0;i<ySize;i++) { jSh=i*xSize; l0=(UINT)(dy-1-(int)i)*(UINT)dxB;
for(j=0;j<xSize;j++) { v=DistrAmp[j+jSh]*coe;
if(v>=1.0F) nC=nColSmoothPal-1; else if(v<=0.0F) nC=0; else nC=(BYTE)((float)(nColSmoothPal-1)*v);
l=l0+(UINT)j*3; for(k=0;k<3;k++) *(pvBits+l+(UINT)k)=pPal->MasRGB[nC][2-k];}
}

end: SAFE_DELETE_ARR(DistrAmp); SAFE_DELETE_ARR(DistrAmp_1); SAFE_DELETE_ARR(DistrAmp_2); return err;
}

//xxx mmm aaa
/*
// ����������� ��������.
depthSum=0.; for(i=0;i<Cryst.laysNum;i++) depthSum+=Cryst.Lays[i].depth; // ����������� ����� ������� ���������.
MashtabX=Cryst.Period/xSize; MashtabY=depthSum/ySize; if(MashtabX<=0.||MashtabY<=0.) return 4;
if(TypScale==0) MashtabX=MashtabY=MAX(MashtabX,MashtabY); // ����� ��������.
*/

//-----------------------------------------------------------------------------------------------------------
// ��������� ������������� �����.

BYTE clMain::DrawDistr(void)
{
BYTE *pvBits,nC,err; UINT dxB,l0,l; int i,j,jv,jSh,k,xSize,ySize,dy;
double amp,coe,v,a1,a2,*DistrAmp,*DistrAmp_1,*DistrAmp_2; struct strPal *pPal;

if(hwnd==NULL) return 1; if(hDlgCntrl==NULL) return 2; 
if(Cryst.IsOKLay()!=0) return 3; if(BmpDiag==NULL) return 4;
BmpDiag->Free(); // ������������ ������.
if(pAmpNorm==NULL) return 5; amp=*pAmpNorm; if(amp<=0.) return 6;

// ����������� ������� ���������.
if(GetClientRect(hwnd,&rc)==FALSE) return 7;
xSize=rc.right-rc.left; ySize=rc.bottom-rc.top-y0; // �������� ������ ���� ����������.
if(xSize<=0||ySize<=0) return 8;

DistrAmp=DistrAmp_1=DistrAmp_2=NULL; err=0;

// ��������� ������.
DistrAmp=new double[xSize*ySize]; if(DistrAmp==NULL) { err=9; goto end;}
DistrAmp_1=new double[xSize*ySize]; if(DistrAmp_1==NULL) { err=10; goto end;}
if(flTypDraw==TypDraw_Full||flTypDraw==TypDraw_SqE||flTypDraw==TypDraw_SqH) {
//xxx aaa
DistrAmp_2=new double[xSize*ySize]; if(DistrAmp_2==NULL) { err=11; goto end;}}

// ����� ������� ���������.
switch(flTypDraw) {
default: err=12; goto end;

// ������������ ����� 'Ex','Hy','Ez' ('p') ��� 'Hx','Ey','Hz' ('s').
case TypDraw_X: case TypDraw_Y: case TypDraw_Z:
if(ComputeDistr(xSize,ySize,DistrAmp_1,flTypDraw)!=0) { err=13; goto end;} // ������������ ������� �������������.
for(i=0;i<ySize;i++) { jSh=i*xSize; for(j=0;j<xSize;j++) { jv=j+jSh; DistrAmp[jv]=DistrAmp_1[jv];}}
break;

// ������������ ���� 'E' ('p') ��� 'H' ('s').
case TypDraw_Full: if(DistrAmp_2==NULL) { err=14; goto end;}
if(ComputeDistr(xSize,ySize,DistrAmp_1,TypDraw_X)!=0) { err=15; goto end;} // ������������ ������� �������������.
if(ComputeDistr(xSize,ySize,DistrAmp_2,TypDraw_Z)!=0) { err=16; goto end;} // ������������ ������� ������������� � ��������.
for(i=0;i<ySize;i++) { jSh=i*xSize; for(j=0;j<xSize;j++) { jv=j+jSh;
a1=DistrAmp_1[jv]; a2=DistrAmp_2[jv]; DistrAmp[jv]=(double)sqrt(a1*a1+a2*a2);}}
break;

// ������� ��������� ���� 'E'.
case TypDraw_SqE:
if(Task.flPol==p_wave_Pol) {
if(ComputeDistr(xSize,ySize,DistrAmp_1,TypDraw_X)!=0) { err=17; goto end;} // ������������ ������� �������������.
if(ComputeDistr(xSize,ySize,DistrAmp_2,TypDraw_Z)!=0) { err=18; goto end;} // ������������ ������� ������������� � ��������.
for(i=0;i<ySize;i++) { jSh=i*xSize; for(j=0;j<xSize;j++) { jv=j+jSh;
a1=DistrAmp_1[jv]; a2=DistrAmp_2[jv]; DistrAmp[jv]=(a1*a1+a2*a2);}}
}
else { if(ComputeDistr(xSize,ySize,DistrAmp_1,TypDraw_Y)!=0) { err=19; goto end;} // ������������ ������� �������������.
for(i=0;i<ySize;i++) { jSh=i*xSize; for(j=0;j<xSize;j++) DistrAmp[j+jSh]=DistrAmp_1[j+jSh]*DistrAmp_1[j+jSh];}}
break;

// ������� ��������� ���� 'H'.
case TypDraw_SqH: 
if(Task.flPol==s_wave_Pol) {
if(ComputeDistr(xSize,ySize,DistrAmp_1,TypDraw_X)!=0) { err=20; goto end;} // ������������ ������� �������������.
if(ComputeDistr(xSize,ySize,DistrAmp_2,TypDraw_Z)!=0) { err=21; goto end;} // ������������ ������� ������������� � ��������.
for(i=0;i<ySize;i++) { jSh=i*xSize; for(j=0;j<xSize;j++) { jv=j+jSh;
a1=DistrAmp_1[jv]; a2=DistrAmp_2[jv]; DistrAmp[jv]=(a1*a1+a2*a2);}}
}
else { if(ComputeDistr(xSize,ySize,DistrAmp_1,TypDraw_Y)!=0) { err=22; goto end;} // ������������ ������� �������������.
for(i=0;i<ySize;i++) { jSh=i*xSize; for(j=0;j<xSize;j++) DistrAmp[j+jSh]=DistrAmp_1[j+jSh]*DistrAmp_1[j+jSh];}}
break;

// ��������� ������������ 'ExE*' ��� 'HxH*'.
//xxx aaa
case TypDraw_FvFc: break;

//xxx mmm aaa
// ����������� ������� ���������.
case TypDraw_DivP: err=102; goto end; // break;
}

// ������������� 'pvBits'.
if(BmpDiag->Init(xSize,ySize,NULL)!=0) { err=23; goto end;}
if(BmpDiag->IsOKB()!=0) { err=18; goto end;}
pvBits=BmpDiag->pvBits; if(pvBits==NULL) { err=24; goto end;}

dy=BmpDiag->dy; dxB=BmpDiag->dxB; // ������������� ��������� ��������.
pPal=&PalDistr; // ����� �������.

// ���������� 'pvBits'.
coe=1./amp;
for(i=0;i<ySize;i++) { jSh=i*xSize; l0=(UINT)(dy-1-(int)i)*(UINT)dxB;
for(j=0;j<xSize;j++) { v=DistrAmp[j+jSh]*coe;
if(v>=1.0F) nC=nColSmoothPal-1; else if(v<=0.0F) nC=0; else nC=(BYTE)((float)(nColSmoothPal-1)*v);
l=l0+(UINT)j*3; for(k=0;k<3;k++) *(pvBits+l+(UINT)k)=pPal->MasRGB[nC][2-k];}
}

end: SAFE_DELETE_ARR(DistrAmp); SAFE_DELETE_ARR(DistrAmp_1); SAFE_DELETE_ARR(DistrAmp_2); return err;
}

{ Distr[j+jSh]=Cmplx_0; continue;}
if(*pD==NULL) return 4; if(DistrX==NULL||DistrZ==NULL) return 5; if(DistrFAbs==NULL) return 6;
 if(*pD==NULL) return 7;
if(DistrFvFc==NULL) return 8;

// �������� ������������.
pRM=pR->Rows+numD; if(pRM->IsOK()!=0) return 14; if(pRM->N!=Nx) return 15;
if(xDistr==Nx-1) AyKT=pRM->Vect[xDistr];
else { A2=pRM->Vect[xDistr+1]; A1=pRM->Vect[xDistr]; AyKT=A1*(1.-weiX)+A2*weiX;} // ������������ �� 'x'.

#define InpFile_Stand "PC_res_Distr.txt" // ����������� �������� �������� �����.

// IDM_FILE_OPEN ............................................................................................
case IDM_FILE_OPEN:
//xxx mmm aaa
LoadFile(InpFile_Stand); break;

#define AmpNormDVP_Stand 0.5F // ��������� ���������� ������������� ����������� ������� ��������� �� ���������.
AmpNormArr[typNorm_DVP]=AmpNormDVP_Stand; // ����������� ������� ���������.
#define typNorm_DVP   6 // ����������� ������� ���������.

#define strlength_Max 100 // ������������ ������ ��������������� ������ � �������� �����������.

if(GetNumStrCombo(hDlgCntrl,id,&num)!=0) num=numStrFileMin; SetSizeCombo(hDlgCntrl,id,num);

// ����������� ������� ���������.
if(GetClientRect(hwnd,&rc)==FALSE) return 9;
xSize=(int)(rc.right-rc.left); ySize=(int)(rc.bottom-rc.top)-y0; // �������� ������ ���� ����������.
if(xSize<=0||ySize<=0) return 10;

if(Cryst.Period<=0.) return 5; if(DepthCryst<=0.) return 6;
// ����������� ��������.
MasX=Cryst.Period/xSize; MasY=DepthCryst/ySize; if(MasX<=0.||MasY<=0.) return 11;
if(TypScale==0) MasX=MasY=MAX(MasX,MasY); // ����� ��������.
x=(int)(Cryst.Period/MasX);

#define AmpNormPal 10.F // ����������� �������.
// ����������� ������� ������.
if(ComputePalDistr(PalPixSize,ySizeD,PalDistr)!=0) { ber=5; goto end;}

//-----------------------------------------------------------------------------------------------------------
// ���������� ������������� ��� ����������� ������� ������.

BYTE clMain::ComputePalDistr(int xSize,int ySize,double *PalDistr)
{
int i,j,k,jSh,kSh,rCol,drCol; double AmpCol,dAmpCol,Wei,shift,cnt;

if(PalDistr==NULL) return 1; if(xSize<=0) return 2;

drCol=int(ySize/(nColB*2)); if(drCol<1) { for(i=0;i<(xSize*ySize);i++) PalDistr[i]=0.; return 0;}
rCol=0; AmpCol=AmpNormPal; dAmpCol=AmpNormPal/nColB; Wei=-dAmpCol/drCol;

// ��������� �������� ������ � ������.
for(i=0;i<2*nColB+1;i++) { jSh=(i*drCol)*xSize; cnt=AmpNormPal-i*dAmpCol;
for(j=0;j<xSize;j++) PalDistr[j+jSh]=cnt;
}
if(drCol==1) return 0;

// �������� ������������.
// ���� �� �������� ������.
for(i=0;i<2*nColB;i++) { shift=AmpCol-Wei*rCol;
// ���� �� ��������.
for(j=rCol+1;j<rCol+drCol;j++) { cnt=Wei*j+shift; kSh=j*xSize;
for(k=0;k<xSize;k++) PalDistr[k+kSh]=cnt;
}
AmpCol-=dAmpCol; rCol+=drCol;
}

// ��������� ����������� ����� ��� �������������.
if(rCol<=ySize) { for(i=rCol;i<ySize;i++) { jSh=i*xSize; for(j=0;j<xSize;j++) PalDistr[j+jSh]=-AmpNormPal;}}
return 0;
}


// ����������� �������.
sz=(UINT)PalPixSize*(UINT)ySizeD;
PalDistr=new double[sz]; if(PalDistr==NULL) { ber=4; goto end;} 
