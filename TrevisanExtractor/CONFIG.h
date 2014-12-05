#ifndef _CONFIG_H
#define _CONFIG_H

//���� �Ʒ��� ���ð��� ���� �� ��, Si �κе� �����ؾ� ��
#define X_LEN 134400		//���� �ҽ� X�� ��Ʈ ����
#define POLY_DEGREE 1400	//���� �ҽ� X�� GF�� ���� ����, ���׽��� ����� ���
#define T_LEN 24649			//���� ���� �Է� T�� ��Ʈ ����, L_LEN�� ����
#define L_LEN 157			//T���� �����ϴ� ��Ʈ�� ��, Si�� ������ ��
#define OUT_LEN 32768		//��� ��Ʈ ����
#define GF 96				//���� �ҽ� X�� ������ ���׽��� ���ǵ� ����ü GF(2^n)���� n
#define GF_32 3				//n�� �����ϴ��� �ʿ��� ���� ����
#define Concatenate_LOG 62	//�� TrevisanExtractor�� �����ϴµ� ���Ǵ� ECC�� �����ϴµ� ���̴� ��� Y_GF�� ���� 2^m���� �� m
#define GF_MASK 0x80000000	//GF(2^n)������ ��꿡 ���
const unsigned int IRR_POLY[GF_32] = {0x00000000, 0x00028000, 0x00000005};
//GF(2^n)������ ��꿡 ���(x^96 + x^49 + x^47 + x^2 + 1 = 0)

//Si ����
#define MOD 157				//Si ������ ���Ǵ� ���׽Ŀ��� ���Ǵ� modular ��
#define DEGREE 2			//Si ������ ���Ǵ� ���׽��� ����


#define POOL_LEN (X_LEN+31)/32
//���� üũ ����
//#define EXPENSIVE_SANITY_CHECKS


#endif