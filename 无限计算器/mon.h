//
//

#ifndef __MON_H__
#define __MON_H__

#include "type.h"

#ifdef __cplusplus
extern "C"
	{
#endif

		void BN_ShiftLeftOneWord(U32 *pwX, S32 iWordToShift, S32 iWordLen = BNLEN);
		void BN_Div(U32 *pwDividend, U32 *pwDivisor, U32 *pwQuotient, U32 *pwRemainder);
		void MonPro(U32 *pwX, U32 *pwY, U32 *pwM, U32 *pwR, U32 inverse_n0 = 0);
		void BN_Assign(U32 *pwDest, U32 *pwSource, S32 iWordLen = BNLEN);
		void BN_Mul(U32 *pwX, U32 *pwY, U32 *pwR, S32 iWordLen = BNLEN);
		void BN_Mul_Sqr(U32 *pwX, U32 *pwR, S32 iWordLen = BNLEN);
		void BN_ShiftRightOneWord(U32 *pwX, S32 iWordLen = BNLEN);
		void BN_Sub(U32 *pwX, U32 *pwY, U32 *pwR, S32 iWordLen = BNLEN);
		void BN_ShiftLeftOneBit(U32 *pwX, S32 iWordLen = BNLEN);
		void BN_ShiftRightOneBit(U32 *pwX, S32 iWordLen = BNLEN, S32 iBitToShift = 1);
		void BN_WordMul(U32 *pwX, U32 iY, U32 *pwR, S32 iWordLen = BNLEN);
		S32  BN_JE(U32 *pwX, U32 *pwY, S32 iWordLen = BNLEN);
		S32  BN_GetWordLen(U32 *pwX, S32 iWordLen = BNLEN);
		U32  MonInverse(const U32 x);
		S32  BN_Add(U32 *pwX, U32 *pwY, U32 *pwR, S32 nWordLen);
		void MonExp_odd(U32 *pwA, U32 *pwB, U32 *pwM, U32 *pwR);

#ifdef __cplusplus
	}
#endif
#endif