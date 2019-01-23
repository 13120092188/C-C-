//
//

#include "stdafx.h"
#include "type.h"
#include "mon.h"

/*
===========================================================================================================
函数描述： 计算得到了   pwx*pwy*r^-1      其中r为b^ipwmwordlen    ，  也就是说  r的取值取决于pwm的字长
这里 pwx 与 pwy 都小于 1024 个字节
     pwm 小于 1024 字节
	
	 这里用到了 CIOS中的一部分    因为把pwx*pwy单独出来了一个函数
     
===========================================================================================================
*/
void MonPro(U32 *pwX, U32 *pwY, U32 *pwM, U32 *pwR, U32 inverse_n0)
{
	/************************************************************************/
	U32 Temp[DBNLEN] = {0};
	S32 j = 0;
	S32 i = 0;
	S32 iWordLen = BN_GetWordLen(pwM);
	U32 t0 = 0;
	U64 carry = 0;
	S32 k = 0;
	/************************************************************************/

	if (inverse_n0 == 0)
		inverse_n0 = 0 - MonInverse(pwM[0]);     
 	/* pwM[0] 模 2^32 的  负逆  */

	memset(Temp, 0, sizeof(Temp));            //给temp赋值为  pwx*pwy

	i = BN_GetWordLen(pwX);
	j = BN_GetWordLen(pwY);

	if (pwX == pwY)
	{
 		BN_Mul_Sqr(pwX, Temp, i);  
	}
	else
	{
		k = i > j ? i : j;
		BN_Mul(pwX, pwY, Temp, k);
	}

	k = i + j;
	k = k > iWordLen ? (k + 1) : (iWordLen + 2);

	for (i = 0; i <iWordLen; i++)
	{
		t0 = inverse_n0 * Temp[0];
		carry = 0;
		for (j = 0; j < iWordLen; j++)
		{
			carry  += (U64)t0 * pwM[j] + Temp[j];
			Temp[j] = (U32)carry;
			carry >>= 32;
		}
		while (carry != 0)
		{
			carry += (U64)Temp[j];
			Temp[j] = (U32)carry;
			carry >>= 32;
			j++;
		}

		BN_ShiftRightOneWord(Temp, k);

	}

	if (BN_JE(Temp, pwM, k) == 1 || BN_JE(Temp, pwM, k) == 0)
	{
		BN_Sub(Temp, pwM, Temp, k);
	}

//这里慎用， 表示可以 把结果赋值给 pwx；
	memset(pwX, 0, 4 * BNLEN);

	memcpy(pwR, Temp, k * 4);

}
/*
===========================================================================================================

===========================================================================================================
*/
void BN_Div(U32 *pwDividend, U32 *pwDivisor, U32 *pwQuotient, U32 *pwRemainder)
{
	/************************************************************************/
	S32 i = 0;
	S32 j = 0;
	S32 w = 0;
	U64 q = 0;
	U32 pwY[DBNLEN] = {0};
	U32 pwX[DBNLEN] = {0};    
	U32 pwQ[DBNLEN] = {0};
	U32 pwR[DBNLEN] = {0};
	S32 iWordLen_Y = BN_GetWordLen(pwDivisor);
	S32 iWordLen_X = BN_GetWordLen(pwDividend, DBNLEN);
	S32 iWordLen_Q = 0;
	/************************************************************************/
	
	BN_Assign(pwX, pwDividend, iWordLen_X);

	BN_Assign(pwY, pwDivisor, iWordLen_Y);

	//让除数的最高位为1， 达到 第一个子 大于等于 [b/2]	
	while ((pwY[iWordLen_Y - 1]&0x80000000) != 0x80000000)
	{
		BN_ShiftLeftOneBit(pwY, iWordLen_Y);
		BN_ShiftLeftOneBit(pwX, iWordLen_X);
		w++;
	}
	if (pwX[iWordLen_X] != 0)
	{
		iWordLen_X++;
	}

	if (iWordLen_X < iWordLen_Y)
	{
		BN_Assign(pwRemainder, pwDividend, iWordLen_X);
		pwQuotient[0]  = 0;
	}
	else if (iWordLen_X == iWordLen_Y && BN_JE(pwX, pwY, iWordLen_X) == 1)
	{
		pwRemainder[0] = 0;
		pwQuotient[0]  = 1;
	}
	else
	{	

		BN_ShiftLeftOneWord(pwY, iWordLen_X - iWordLen_Y, iWordLen_Y);             //左移pwy  是的与pwx 高位平齐

		if (BN_JE(pwX, pwY, iWordLen_X) == 1 || BN_JE(pwX, pwY, iWordLen_X) == 0)
		{
			BN_Sub(pwX, pwY, pwX, iWordLen_X);
			pwQ[iWordLen_Q] = 1;
			iWordLen_Q++;
		}
		
		j = iWordLen_X - iWordLen_Y;
		for (i = 1; i <= j; i++)
		{
			BN_ShiftRightOneWord(pwY, iWordLen_X - i + 1);

			//试商
			if (pwX[iWordLen_X - i] == pwY[iWordLen_X - i - 1])
			{
				q = 0xffffffff;

			}
			else
			{
				q = (((U64)pwX[iWordLen_X - i] << 32) | (U64)pwX[iWordLen_X - i - 1]) / ((U64)pwY[iWordLen_X - i - 1]);
				if (q&0xffffffff00000000)
				{
					q = 0xffffffff;
				}
			}

			//精确商  并且计算出来  pwx - q*pwy
			memset(pwR, 0, sizeof(pwR));
			BN_WordMul(pwY, (U32)q, pwR, iWordLen_X - i);
			while (BN_JE(pwR, pwX, iWordLen_X) == 1)
			{
				q--;
				memset(pwR, 0, 4 * iWordLen_X);
				BN_WordMul(pwY, (U32)q, pwR, iWordLen_X - i);
			}
			
			BN_Sub(pwX, pwR, pwX, iWordLen_X);
			
			pwQ[iWordLen_Q] = (U32)q;           //把结果赋值到 商里面去
			iWordLen_Q++;                  //存放商的长度加1
		}
		
		//得到余数  并且赋值给 pwRemainder
		
		BN_Assign(pwRemainder, pwX, iWordLen_Y);

		BN_ShiftRightOneBit(pwRemainder, iWordLen_Y, w);      //w<32
		
		//得到商，  并且赋值给 pwQuotient
		for (i = 0; i < iWordLen_Q; i++)
		{
			pwQuotient[i] = pwQ[iWordLen_Q - i - 1];
		}
	}
	
}

/*
===========================================================================================================
算法描述： 对于U32数字的模2^32的逆
===========================================================================================================
*/
U32 MonInverse(const U32 x)
{
	/************************************************************************/
	U32 inverse_x = 1;
	U32 y = 1;
	U64 temp = 0;
	S32 j = 1;                                                              
	/************************************************************************/

	if ((x&0x00000001) == 0)             //判断x的奇偶性   偶数没有逆
	{
		return 0;
	}
	else
	{
		y <<= 1;

		for (j = 1; j < 32; j++)
		{
			temp = (U64)inverse_x * x;
			temp <<= 63 - j;
			temp >>= 63 - j;              //把temp的高位置零， 相当于对 2^j+1取模

			if ((U32)temp > y)
			{
				inverse_x += y;
			}

			y <<= 1;

		}

		return inverse_x;
	}

}

/*
===========================================================================================================
函数描述： 大整数减法
===========================================================================================================
*/
void BN_Sub(U32 *pwX, U32 *pwY, U32 *pwR, S32 iWordLen)
{
	/************************************************************************/
	S32 i = 0;
	U64 borrow = 0;
	/************************************************************************/

	for (i = 0; i < iWordLen; i++)
	{

		borrow += (U64)pwX[i] - pwY[i];
		pwR[i] = (U32)borrow;
		borrow = (U64)((S64)borrow >> 32);
	
	}
}

/*
===========================================================================================================
函数描述： 大整数求字数， 大整数低位存在数组前面的字节里面
===========================================================================================================
*/
S32  BN_GetWordLen(U32 *pwX, S32 iWordLen)
{
	/************************************************************************/
	S32 i = 0;                                                                   
	/************************************************************************/
	
	for (i = iWordLen - 1; i >= 0; i--)
	{
		if (pwX[i] != 0)
		{
			break;
		}
	}

	return i + 1;	

}

/*
===========================================================================================================
函数描述： 大整数乘法
===========================================================================================================
*/
void BN_Mul(U32 *pwX, U32 *pwY, U32 *pwR, S32 iWordLen)
{
	/************************************************************************/
	U64 carry = 0;
	S32 i = 0;
	S32 j = 0;
	/************************************************************************/

	if (pwX == pwY)
	{
		BN_Mul_Sqr(pwX, pwR, iWordLen);
	}
	else
	{
		for (i = 0; i < iWordLen; i++)
		{
			carry = 0;
			for (j = 0; j < iWordLen; j++)
			{
				carry += (U64)pwX[i] * pwY[j] + (U64)pwR[i + j];
				pwR[i + j] = (U32)carry;
				carry >>= 32;
			}
			pwR[i + j] = (U32)carry;
		}

	}

}

/*
===========================================================================================================
函数描述：  大整数的平方   用到了两个64位的作为进位存储  经过转换 相当于三个字存放进位
===========================================================================================================
*/
void BN_Mul_Sqr(U32 *pwX, U32 *pwR, S32 iWordLen)
{
	/************************************************************************/
	S32 i     = 0;
	S32 j     = 0;
	S32 k     = 0;
	U64 carry = 0;
	/************************************************************************/

	for (i = 0; i < iWordLen; i++)
	{
		carry = (U64)pwR[2 * i] + (U64)pwX[i] * pwX[i];
		pwR[2 * i] = (U32)carry;
		carry >>= 32;

		for (j = i + 1; j < iWordLen; j++)
		{
			k = i + j;
			carry += (U64)pwX[i] * pwX[j] + (U64)pwR[k];
			pwR[k] = (U32)carry;
			carry >>= 32;
			while (carry != 0)
			{
				k++;
				carry += (U64)pwR[k];
				pwR[k] = (U32)carry;
				carry >>= 32;
			}

			carry = (U64)pwX[i] * pwX[j] + (U64)pwR[i + j];
			pwR[i + j] = (U32)carry;
			carry >>= 32;
		}

		k = i + j;
		while (carry != 0)
		{
			carry += (U64)pwR[k];
			pwR[k] = (U32)carry;
			carry >>= 32;
			k++;
		}
	}
	
}

/*
===========================================================================================================
函数描述： 大整数复制  
===========================================================================================================
*/
void BN_Assign(U32 *pwDest, U32 *pwSource, S32 iWordLen)
{

	memcpy(pwDest, pwSource, 4 * iWordLen);
}

/*
===========================================================================================================
函数描述： 比较大小
返回值  ： 1     pwx > pwy
           0     pwx = pwy
		   -1    pwx < pwy
===========================================================================================================
*/
S32 BN_JE(U32 *pwX, U32 *pwY, S32 iWordLen)
{
	/************************************************************************/
	S32 i = 0;                                                                     
	/************************************************************************/
	
	for (i = iWordLen - 1; i >= 0; i--)
	{
		if (pwX[i] > pwY[i])
		{
			return 1;
		}
		else if (pwX[i] < pwY[i])
		{
			return -1;
		}
	}

	return 0;
}
/*
===========================================================================================================
函数描述： 大整数右移一个字节   相当于把低位的字节去掉
===========================================================================================================
*/
void BN_ShiftRightOneWord(U32 *pwX, S32 iWordLen)
{
	/************************************************************************/
	S32 i = 0;                                                                  
	/************************************************************************/

	for (i = 0; i < iWordLen - 1; i++)
	{
		pwX[i] = pwX[i + 1];
	}
	pwX[i] = 0;
}


/*
===========================================================================================================
函数描述： 大整数左移一个位  （ 不是完整的算法）
===========================================================================================================
*/
void BN_ShiftLeftOneBit(U32 *pwX, S32 iWordLen)
{
	/************************************************************************/
	S32 i = 0;                                                                  
	/************************************************************************/
	
	for (i = iWordLen; i > 0; i--)
	{
		pwX[i] = (pwX[i] << 1) | (pwX[i - 1] >> 31); 
	}

	pwX[0] <<= 1;

}
/*
===========================================================================================================
函数描述： 大整数左移 iwordtoshift 个字节  
===========================================================================================================
*/
void BN_ShiftLeftOneWord(U32 *pwX, S32 iWordToShift, S32 iWordLen)
{
	/************************************************************************/
	S32 i = 0;                                                                 
	/************************************************************************/

	for (i = iWordLen - 1; i >= 0; i--)
	{
		pwX[i + iWordToShift] = pwX[i];
	}

	for (i = 0; i < iWordToShift; i++)
	{
		pwX[i]   = 0;
	}
}
/*
===========================================================================================================

===========================================================================================================
*/
void BN_WordMul(U32 *pwX, U32 iY, U32 *pwR, S32 iWordLen)
{
	/************************************************************************/
	S32 i     = 0;
	U64 carry = 0;
	/************************************************************************/
	
	for (i = 0; i < iWordLen; i++)
	{
		carry += (U64)pwX[i] * iY;
		pwR[i] = (U32)carry;
		carry >>= 32;
	}
	pwR[iWordLen] = (U32)carry;

}
/*
===========================================================================================================
函数描述： 大整数右移ibittoshift （默认一个）比特
===========================================================================================================
*/
void BN_ShiftRightOneBit(U32 *pwX, S32 iWordLen, S32 iBitToShift)
{
	/************************************************************************/
	S32 i = 0;                                                                  
	/************************************************************************/

	for (i = 0; i < iWordLen - 1; i++)
	{
		pwX[i] = (U32)(((U64)pwX[i] >> iBitToShift) | ((U64)pwX[i + 1] << (32 - iBitToShift)));
	}

	pwX[i] = (U32)((U64)pwX[i] >> iBitToShift);

}
/*
===========================================================================================================

===========================================================================================================
*/
S32 BN_Add(U32 *pwX, U32 *pwY, U32 *pwR, S32 nWordLen)
{
	/************************************************************************/
	S32 i = 0; 
	U64 carry = 0;
	/************************************************************************/
	
	for (i = 0; i < nWordLen; i++)
	{
		carry += (U64)pwX[i] + (U64)pwY[i];
		pwR[i] = (U32)carry;
		carry >>= 32;
	}
	pwR[i] = (U32)carry;

	if (carry != 0)
	{
		return nWordLen + 1;
	}
	else
	{
		return nWordLen;
	}

}


void MonExp_odd(U32 *pwA, U32 *pwB, U32 *pwM, U32 *pwR)
{
	/************************************************************************/
	U32 pwQ[BNLEN]     = {0};
	
	U32 T[2 * BNLEN]   = {0};
	U32 A0R[BNLEN]     = {0};
	U32 A1R[BNLEN]     = {0};
	U32 A2R[BNLEN]     = {0};
	U32 A3R[BNLEN]     = {0};

	U32 flag[16] = {0xc0000000, 0x30000000, 0x0c000000, 0x03000000, 0x00c00000, 0x00300000, 0x000c0000, 0x00030000, \
					0x0000c000, 0x00003000, 0x00000c00, 0x00000300, 0x000000c0, 0x00000030, 0x0000000c, 0x00000003};

	S32 i = 0;
	S32 wordlen = 0;
	S32 nwordlen_m   = 0;
	U32 inverse_n0 = 0;
	/************************************************************************/


	nwordlen_m = BN_GetWordLen(pwM);
	wordlen = BN_GetWordLen(pwA);
	T[nwordlen_m] = 1;
	BN_Div(T, pwM, pwQ, A0R);			
				
	T[nwordlen_m] = 0;
	BN_Assign(T, pwA, wordlen);			
	BN_ShiftLeftOneWord(T, nwordlen_m, wordlen);
	BN_Div(T, pwM, pwQ, A1R);
	
	memset(T, 0, sizeof(T));
	BN_Mul_Sqr(pwA, T, wordlen);
	BN_Div(T, pwM, pwQ, pwR);
	memset(T, 0, sizeof(T));
	wordlen = BN_GetWordLen(pwR);
	BN_Assign(T, pwR, wordlen);
	BN_ShiftLeftOneWord(T, nwordlen_m, wordlen);
	BN_Div(T, pwM, pwQ, A2R);			
	
	memset(T, 0, sizeof(T));
	BN_Mul(pwR, pwA, T);
	memset(pwR, 0, 4 * BNLEN);
	BN_Div(T, pwM, pwQ, pwR);
	wordlen = BN_GetWordLen(pwR);
	memset(T, 0, sizeof(T));
	BN_Assign(T, pwR, wordlen);
	BN_ShiftLeftOneWord(T, nwordlen_m, wordlen);
	BN_Div(T, pwM, pwQ, A3R);
	
	memset(pwQ, 0, sizeof(pwQ));
	memset(pwR, 0, 4 * BNLEN);
	BN_Assign(pwR, A0R);
	
	wordlen = BN_GetWordLen(pwB);
	inverse_n0 = 0 - MonInverse(pwM[0]);  
	for (i = 0; i < 16 * wordlen - 1; i++)
	{
		
		switch ((pwB[wordlen - 1 - (i / 16)] & flag[i % 16]) >> (30 - 2 * i))
		{
		case 0:
			break;
		case 1:
			MonPro(pwR, A1R, pwM, pwR, inverse_n0);
			break;
		case 2:
			MonPro(pwR, A2R, pwM, pwR, inverse_n0);
			break;
		case 3:
			MonPro(pwR, A3R, pwM, pwR, inverse_n0);
			break;
		default :
			break;
		}
		
		MonPro(pwR, pwR, pwM, pwR, inverse_n0);
		MonPro(pwR, pwR, pwM, pwR, inverse_n0);
		
	}
	
	switch ((pwB[wordlen - 1 - (i / 16)] & flag[i % 16]) >> (30 - 2 * i))
	{
	case 0:
		break;
	case 1:
		MonPro(pwR, A1R, pwM, pwR, inverse_n0);
		break;
	case 2:
		MonPro(pwR, A2R, pwM, pwR, inverse_n0);
		break;
	case 3:
		MonPro(pwR, A3R, pwM, pwR, inverse_n0);
		break;
	default :
		break;
	}
	
	pwQ[0] = 1;
	MonPro(pwR, pwQ, pwM, pwR, inverse_n0);			

}