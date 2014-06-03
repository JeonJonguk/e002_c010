#ifndef __CJ_H_MACRO_H__
#define __CJ_H_MACRO_H__
	

#ifndef NULL
#define			NULL							0
#endif // !NULL

#define			CJ_NONE						0x00000000


#define			CJ_SAFE_DELETE( pObj )		if( pObj ){ delete pObj; } pObj = NULL	



#endif // !__CJ_H_MACRO_H__
