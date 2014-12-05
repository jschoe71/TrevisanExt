#ifndef _CONFIG_H
#define _CONFIG_H

//만약 아래의 세팅값을 변경 할 시, Si 부분도 수정해야 함
#define X_LEN 134400		//랜덤 소스 X의 비트 길이
#define POLY_DEGREE 1400	//랜덤 소스 X를 GF로 나눈 길이, 다항식의 계수로 사용
#define T_LEN 24649			//균일 분포 입력 T의 비트 길이, L_LEN의 제곱
#define L_LEN 157			//T에서 추출하는 비트의 수, Si의 원소의 수
#define OUT_LEN 32768		//출력 비트 길이
#define GF 96				//랜덤 소스 X로 생성된 다항식이 정의된 유한체 GF(2^n)에서 n
#define GF_32 3				//n을 정의하느데 필요한 워드 길이
#define Concatenate_LOG 62	//본 TrevisanExtractor를 구성하는데 사용되는 ECC를 구성하는데 쓰이는 행렬 Y_GF의 수가 2^m개일 때 m
#define GF_MASK 0x80000000	//GF(2^n)에서의 계산에 사용
const unsigned int IRR_POLY[GF_32] = {0x00000000, 0x00028000, 0x00000005};
//GF(2^n)에서의 계산에 사용(x^96 + x^49 + x^47 + x^2 + 1 = 0)

//Si 관련
#define MOD 157				//Si 생성에 사용되는 다항식에서 사용되는 modular 값
#define DEGREE 2			//Si 생성에 사용되는 다항식의 차수


#define POOL_LEN (X_LEN+31)/32
//길이 체크 여부
//#define EXPENSIVE_SANITY_CHECKS


#endif