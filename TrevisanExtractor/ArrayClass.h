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
	//���Ϸκ��� �Է� �޴� �Լ�
	//n�� ��Ʈ ����, ������ ���� 16����(Not binary)
	{
		int i;
		Len = n;
		Block = (Len+31)/32;
		for(i=0;i<Block;i++)
		{
			fscanf(fp,"%08X",&Data[i]);
		}
	//16���� �������� �� ����
	Data[Block-1] = Data[Block-1]<<(32-4*(((Len%32)+3)/4));
	}
	void InitZero(int n)
	//ArrayClass�� n��Ʈ ������ zero string���� �ʱ�ȭ 
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
	//ArrayClass�� RowData���� n��Ʈ�� �޾� ����
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
	//GF_42���� ������ zero string�� GFClass ����
	{
		int i;
		for(i=0;i<GF_32;i++)
		{
			Data[i] = 0;
		}
	}
	void InitZero()
	//GFClass�� zero string���� �ʱ�ȭ 
	{
		int i;
		for(i=0;i<GF_32;i++)
		{
			Data[i] = 0;
		}
	}
	void CopyGFBit(ArrayClass *In, int num)
	//GFClass�� num��Ʈ ���̸� ArrayClass�κ��� ����
	{
		int i;
		for(i=0;i<num;i++)
		{
			Data[GF_32-num+i] = In->Data[i];
		}
	}
	void CopyGFBit(ArrayClass *In, int start, int num)
	//GFClass�� ArrayClass�� start ��Ʈ ��ġ���� num��Ʈ ���̸� ����
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