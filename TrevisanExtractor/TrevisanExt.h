#include <stdlib.h>
#include <math.h>
#include "CONFIG.h"
#include "ArrayClass.h"
#include "MakeSi.h"

#ifndef _TREVISANEXT_H
#define _TREVISANEXT_H

inline bool get_bit(ArrayClass *, unsigned int);	
//균일 분포 입력 T에서 i(0~T_LEN-1)번째 위치의 비트를 출력
inline void extract(ArrayClass *, unsigned int*, int ,ArrayClass *);
//균일 분포 입력 T에서 Si의 원소들에 해당하는 위치의 비트 L_LEN개를 Y에 출력
//Y의 start 비트부터 복사
inline GFClass Cal_poly(ArrayClass *, ArrayClass * );
//유한체 GF(2^(GF))상의 계산, 랜덤 소스 X를 입력으로 한 POLY_DEGREE 차수의 다항식에 Y를 입력하여 계산
inline GFClass MultioverGF(GFClass , GFClass );
//Cal_poly에서 사용
//유한체 GF(2^GF) 상에서 GF 비트 길이의 두 수 X,Y의 곱을 계산
inline bool wHmod2(GFClass , ArrayClass );
//ECC
inline bool onebit_ext(ArrayClass *, ArrayClass *);
//onebit_extractor
inline void trevisan_extract(ArrayClass *, ArrayClass *, ArrayClass *);
//전체 Trevisan Extractor 과정
#endif