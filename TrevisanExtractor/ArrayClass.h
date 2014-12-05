#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>


#ifndef _ARRAYCLASS_H
#define _ARRAHCLASS_H

class ArrayClass
{
public:
	ArrayClass()
	{
		Len = 0;
		Block = 0;
	}
	ArrayClass(FILE *fp,int n)
	//파일로부터 입력 받는 함수
	//n은 비트 길이, 파일의 값은 16진수(Not binary)
	{
		int i;
		Len = n;
		Block = (Len+31)/32;
		for(i=0;i<Block;i++)
		{
			fscanf(fp,"%08X",&Data[i]);
		}
	//16진수 기준으로 값 설정
	Data[Block-1] = Data[Block-1]<<(32-4*(((Len%32)+3)/4));
	}
	void InitZero(int n)
	//ArrayClass를 n비트 길이의 zero string으로 초기화 
	{
		int i;
		Len = n;
		Block = (Len+31)/32;
		for(i=0;i<Block;i++)
		{
			Data[i]=0;
		}
	}
	void Init(int n, unsigned int *RowData)
	//ArrayClass를 RowData에서 n비트를 받아 복사
	{
		int i;
		Len=n;
		Block = (Len+31)/32;
		for(i=0;i<Block;i++)
		{
			Data[i] = RowData[i];
		}
	}
	void print(char *Name)
	{
		int i;
		printf("%s : ", Name);
		for(i=0;i<Block;i++)
		{
			printf("%08X",Data[i]);
		}
		printf("\n");
	}
	void fprint(FILE *fp)
	{
		int i;
		for(i=0;i<Block;i++)
		{
			fprintf(fp,"%08X",Data[i]);
		}
		fprintf(fp,"\n");
	}
	void fprint(FILE *fp, char* Name)
	{
		int i;
		fprintf(fp,"%s : ",Name);
		for(i=0;i<Block;i++)
		{
			fprintf(fp,"%08X",Data[i]);
		}
		fprintf(fp,"\n");
	}

	unsigned int Data[POOL_LEN];
	int Len;
	int Block;
};

class GFClass{
public:
	GFClass()
	//GF_42워드 길이의 zero string인 GFClass 생성
	{
		int i;
		for(i=0;i<GF_32;i++)
		{
			Data[i] = 0;
		}
	}
	void InitZero()
	//GFClass를 zero string으로 초기화 
	{
		int i;
		for(i=0;i<GF_32;i++)
		{
			Data[i] = 0;
		}
	}
	void CopyGFBit(ArrayClass *In, int num)
	//GFClass에 num비트 길이를 ArrayClass로부터 복사
	{
		int i;
		for(i=0;i<num;i++)
		{
			Data[GF_32-num+i] = In->Data[i];
		}
	}
	void CopyGFBit(ArrayClass *In, int start, int num)
	//GFClass에 ArrayClass의 start 비트 위치부터 num비트 길이를 복사
	{
		int i;
		for(i=0;i<num;i++)
		{
			Data[GF_32-num+i] = In->Data[start+i];
		}
	}

	unsigned int Data[GF_32];
};
#endif 