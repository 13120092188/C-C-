//
//定义了各种类型
//
//


#ifndef __TYPE_H__
#define __TYPE_H__

const int BNLEN  =      1024;
const int DBNLEN = 2 * BNLEN;

#ifdef __cplusplus
	extern "C"
	{
#endif

	typedef unsigned char     U8;
	typedef          char     S8;
	typedef unsigned short    U16;
	typedef          short    S16;
	typedef unsigned int      U32;
	typedef          int      S32;
	typedef unsigned __int64  U64;
	typedef          __int64  S64;

#ifdef __cplusplus
	}
#endif




#endif