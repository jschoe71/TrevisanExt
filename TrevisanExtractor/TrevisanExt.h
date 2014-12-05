#include <stdlib.h>
#include <math.h>
#include "CONFIG.h"
#include "ArrayClass.h"
#include "MakeSi.h"

#ifndef _TREVISANEXT_H
#define _TREVISANEXT_H

inline bool get_bit(ArrayClass *, unsigned int);	
//���� ���� �Է� T���� i(0~T_LEN-1)��° ��ġ�� ��Ʈ�� ���
inline void extract(ArrayClass *, unsigned int*, int ,ArrayClass *);
//���� ���� �Է� T���� Si�� ���ҵ鿡 �ش��ϴ� ��ġ�� ��Ʈ L_LEN���� Y�� ���
//Y�� start ��Ʈ���� ����
inline GFClass Cal_poly(ArrayClass *, ArrayClass * );
//����ü GF(2^(GF))���� ���, ���� �ҽ� X�� �Է����� �� POLY_DEGREE ������ ���׽Ŀ� Y�� �Է��Ͽ� ���
inline GFClass MultioverGF(GFClass , GFClass );
//Cal_poly���� ���
//����ü GF(2^GF) �󿡼� GF ��Ʈ ������ �� �� X,Y�� ���� ���
inline bool wHmod2(GFClass , ArrayClass );
//ECC
inline bool onebit_ext(ArrayClass *, ArrayClass *);
//onebit_extractor
inline void trevisan_extract(ArrayClass *, ArrayClass *, ArrayClass *);
//��ü Trevisan Extractor ����
#endif