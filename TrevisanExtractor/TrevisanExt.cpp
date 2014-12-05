#include "TrevisanExt.h"
#ifndef _TREVISANEXT_CPP
#define _TREVISANEXT_CPP

inline bool get_bit(ArrayClass *T, unsigned int i)
{
	int idx = (i>>5);
	unsigned int chunk =T->Data[idx];
	
	bool bit = chunk & (1<<(31-(i&0x1F)));
	return bit;
}

inline void extract(ArrayClass *T, unsigned int* Si, int start, ArrayClass *Y)
{
	int i;
	for(i=0;i<L_LEN;i++)
	{
		if(get_bit(T,Si[i]))
		{
			Y->Data[(i+start)>>5] |=1<<(31-((i+start)&0x1F));
		}
	}
}

inline GFClass Cal_poly(ArrayClass *X, ArrayClass *Y )
{
	int i,j;
	GFClass A;
	GFClass R;
	GFClass x;

	x.CopyGFBit(Y,(Concatenate_LOG+31)>>5);
	R.CopyGFBit(X,0,GF_32);
	for(i=1;i<POLY_DEGREE;i++)
	{	
		R = MultioverGF(R,x);
		A.CopyGFBit(X,GF_32*i,GF_32);
		for(j=0;j<GF_32;j++)
		{
			R.Data[j] ^= A.Data[j];
		}
	}
	return R;
}

inline GFClass MultioverGF(GFClass X, GFClass Y)
{
	GFClass Temp;
	int i,j,k;
	int count;
	for(i=GF_32 - 1;i>=0;i--)
	{
		count = 0;
		while(Y.Data[i])
		{
			if(Y.Data[i] & 1)
			{
				for(j=0;j<GF_32;j++)
				{
					Temp.Data[j] ^= X.Data[j];
				}
			}
			Y.Data[i] >>= 1;
			if(X.Data[0]& GF_MASK)
			{
				for(j=0;j<GF_32 -1;j++)
				{
					X.Data[j] = ((X.Data[j]<<1) ^ (X.Data[j+1]>>31)) ^ IRR_POLY[j];
				}
				X.Data[j] = (X.Data[j]<<1) ^ IRR_POLY[j];
			}
			else
			{
				for(j=0;j<GF_32 -1;j++)
				{
					X.Data[j] = ((X.Data[j]<<1) ^ (X.Data[j+1]>>31));
				}
				X.Data[j] = (X.Data[j]<<1);
			}
			count++;
		}
		for(k=count;k<32;k++)
		{
			if(X.Data[0]& GF_MASK)
			{
				for(j=0;j<GF_32 -1;j++)
				{
					X.Data[j] = ((X.Data[j]<<1) ^ (X.Data[j+1]>>31)) ^ IRR_POLY[j];
				}
				X.Data[j] = (X.Data[j]<<1) ^ IRR_POLY[j];
			}
			else
			{
				for(j=0;j<GF_32 -1;j++)
				{
					X.Data[j] = ((X.Data[j]<<1) ^ (X.Data[j+1]>>31));
				}
				X.Data[j] = (X.Data[j]<<1);
			}
		}
	}
	return Temp;
}

inline bool wHmod2(GFClass *R, ArrayClass *Y)
{
	int mask[5]={0x1, 0x3, 0xF, 0xFF, 0xFFFF};
	int i,j;
	unsigned int temp=0;
	
	for(i=0,j=(Concatenate_LOG+31)>>5;i<GF_32;i++)
	{
		temp^=(R->Data[i]&Y->Data[j+i]);
	}
	for(i=4,j=16;i>=0;i--)
	{
		temp=(temp>>j)^(temp&mask[i]);
		j>>=1;
	}
	return temp;
}

inline bool onebit_ext(ArrayClass *X, ArrayClass *Y)
{
	static GFClass PX;
	Y->Data[Y->Block-1] |=1;//Y의 마지막 비트에 1 연접
	PX = Cal_poly(X, Y);
	return wHmod2(&PX,Y);
}

inline void trevisan_extract(ArrayClass *X, ArrayClass *T, ArrayClass *RND)
{
	int i;
	int start;
	unsigned int Si[L_LEN]={0};
	RND->InitZero(OUT_LEN);
	ArrayClass Y;
	start=32-Concatenate_LOG&0x1F;
	for(i=0;i<OUT_LEN;i++)
	{
		ComputeSi(i,Si);
		Y.InitZero(L_LEN+1);
		extract(T,Si,start,&Y);
		if(onebit_ext(X, &Y))
		{
			RND->Data[i/32] |=1<<(31-(i&0x1F));
		}
	}
}

#endif