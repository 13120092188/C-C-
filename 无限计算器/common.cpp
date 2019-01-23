//
//
//

#include "stdafx.h"
#include "common.h"

S32 input(CString &m_strTemp, U32 *pwT)
{
	/************************************************************************/
	S32 i = 0;
	U8  ByteBuf[4 *     BNLEN] = {0};
	S8  CharBuf[4 * 2 * BNLEN] = {0};
	/************************************************************************/

	i = m_strTemp.GetLength();
	m_strTemp.MakeReverse();

	if ( i >= 4 * 2 * (BNLEN - 1) || i == 0)
	{
		return 0;
	}
	else
	{
		strncpy(CharBuf, m_strTemp.GetBuffer(0), i);

		if (CharToByte(CharBuf, ByteBuf, i) == 1)
		{
			memcpy(pwT, ByteBuf, i / 2 + 1);
			m_strTemp.MakeReverse();
			return 1;
		}
		else
		{
			m_strTemp.MakeReverse();
			return 0;
		}
		
	}
		
	


}




S32 CharToByte(S8 *pCharBuf, U8 *pByteBuf, S32 nCharLen)
{
	/************************************************************************/
	S32 i = 0;
	S32 j = 0;
	U8  hdata = 0;
	U8  ldata = 0;
	/************************************************************************/

	i = (nCharLen % 2) ? (nCharLen / 2 + 1) : (nCharLen / 2);
	for (j = 0; j < i; j++)
	{
		if (conver(pCharBuf[2 * j] , &ldata) == 1 && conver(pCharBuf[2 * j + 1], &hdata) == 1)
		{
			pByteBuf[j] = ldata | (hdata << 4);
		}
		else
		{
			return 0;
		}
	}

	return 1;

}



S32 conver(S8 chTemp, U8 *byTemp)
{
	if (chTemp >= '0' && chTemp <= '9')
	{
		*byTemp = (U8)chTemp - 48;
		return 1;
	}
	else if (chTemp >= 'a' && chTemp <= 'f')
	{
		*byTemp = (U8)chTemp - 87;
		return 1;
	}
	else if (chTemp >= 'A' && chTemp <= 'F')
	{
		*byTemp = (U8)chTemp - 55;
		return 1;
	}
	else if (chTemp == 0)
	{
		*byTemp = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}

void output(CString &m_strT, U32 *pwR, S32 nWordLen)
{
	/************************************************************************/
	U8  pByteBuf[4 * 2 * BNLEN]     = {0};                     //对于乘法可能有2 * bnlen 长度的结果
	S8  pCharBuf[4 * 2 * 2 * BNLEN] = {0};
	S32 i = 0;
	S32 j = 0;
	S8  hdata = 0;
	S8  ldata = 0;
	/************************************************************************/

	i = 4 * nWordLen;
	memcpy(pByteBuf, pwR, i);

	for (j = 0; j < i; j++)
	{
		reconver(pByteBuf[j] & 0x0F, &ldata);
		reconver(pByteBuf[j] >> 4, &hdata);
		pCharBuf[2 * j]     = ldata;
		pCharBuf[2 * j + 1] = hdata;
	}

	j = 2 * i;
	do 
	{
		j--;
	} while (pCharBuf[j] == '0' && j > 0);

	if (j < 0)
	{
		m_strT = "0";
	}
	for (i = j; i >=0; i--)
	{
		m_strT += pCharBuf[i];
	}

}

void reconver(U8 bytebuf, S8 *charBuf)
{

	*charBuf = (bytebuf >= 0 && bytebuf <= 9) ? ((S8)bytebuf +48) : ((S8)bytebuf + 55);
}







/*
=======================================================================================================================
	描述:把S8类型数组转换成U8类型数组
	输入:
		pCharBuf:S8类型数组，为'0'-'9'或'a'-'f'或'A'-'F',如果不是则返回0
		charlen:S8类型数组长度
	输出:
		pByteBuf:U8类型数组,如果charlen为奇数,pByteBuf长度至少为charlen/2+1,否则至少为charlen/2
		bytelen:U8类型数组长度,
	返回值:
		0:转换过程错误
		1:转换成功
=======================================================================================================================
*/
