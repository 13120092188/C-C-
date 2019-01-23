#ifndef __HEADER_COMMON_H__
#define __HEADER_COMMON_H__

#include "type.h"

#ifdef  __cplusplus
extern "C" {
#endif
	S32 conver(S8 chTemp, U8 *byTemp);
	S32 CharToByte(S8 *pCharBuf, U8 *pByteBuf, S32 nCharLen);
	S32 input(CString &m_strTemp, U32 *pwT);
	void reconver(U8 bytebuf, S8 *charBuf);
	void output(CString &m_strT, U32 *pwR, S32 nWordLen);

#ifdef  __cplusplus
}
#endif

#endif
