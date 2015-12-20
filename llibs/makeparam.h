/*
** file:makeparam.h
** Like linux magic number,this file is used to create a param number
** that is unique at all module .
**
** QianFan
*/

#include <stdint.h>

#ifndef makeparam_h
#define makeparam_h

#define MAKE_P(type,num,data) \
				( ((((uint32_t)type)&0xff)<<24) | \
				  ((((uint32_t)num)&0xff)<<16)  | \
				  (((uint32_t)data)&0xffff) )

#define P_TYPE(p) (((p)>>24)&0xff)
#define P_NUM(p)	(((p)>>16)&0xff)
#define P_DATA(p) ((p)&0xffff)

#endif
