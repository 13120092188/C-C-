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
	U8  pByteBuf[4 * 2 * BNLEN]     = {0};                     //���ڳ˷�������2 * bnlen ���ȵĽ��
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
	����:��S8��������ת����U8��������
	����:
		pCharBuf:S8�������飬Ϊ'0'-'9'��'a'-'f'��'A'-'F',��������򷵻�0
		charlen:S8�������鳤��
	���:
		pByteBuf:U8��������,���charlenΪ����,pByteBuf��������Ϊcharlen/2+1,��������Ϊcharlen/2
		bytelen:U8�������鳤��,
	����ֵ:
		0:ת�����̴���
		1:ת���ɹ�
=======================================================================================================================
*/
