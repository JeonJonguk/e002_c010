#ifndef __CJ_RESOURCE_PATH_DIRECTOR_H__
#define __CJ_RESOURCE_PATH_DIRECTOR_H__



#include "CJFlashStdC.h"
#include "CJFlashUtil.h"


namespace CJFlash
{

	/*************************************************************************
	@
	@	name: CResourcePathDirector
	@
	@	author: [2013.1.28 CJFlash. YHM]
	@
	@	brief: 리소스 경로 관리자
	@		   CJAnimationLibrary 는 이 리소스 경로 관리자를 이용하여 로드 / 언로드를 함
	@
	**************************************************************************/
	class CResourcePathDirector : public CSingleton<CResourcePathDirector>
	{
	private:
		typedef std::map<std::string, std::string>				STL_MAP_ResourcePath;	
		typedef std::map<std::string, std::string>::iterator	STL_MAP_ITER_ResourcePath;


	private:
		std::string				m_strRootResourcePath;

		STL_MAP_ResourcePath	m_stl_map_ResourcePaths;


	public:
		CResourcePathDirector();
		~CResourcePathDirector();


	public:
		/**  [2013.1.28 CJFlash. YHM]
		  desc: 루트 리소스 디렉터리 설정
		  param: 
				- strOriginResPath : 루트 리소스 경로
		**/
		void setRootResourcePath(std::string strOriginResPath);

		/**  [2013.1.28 CJFlash. YHM]
		  desc: 리소스 경로를 추가
		  param: 
				- strKey : 키값
				- strPath : 리소스 경로
		**/
		void addResourcePath(std::string strKey, std::string strPath);


	public:
		std::string getRealPath(std::string strFileName);
		std::string getRealPath(std::string strKey, std::string strFileName);
        
        
        //common path
    private:
		std::string	m_strCommonResourcePath;
	public:
		void setCommonResourcePath(std::string strOriginResPath);
	public:
		std::string getCommonPath(std::string strFileName);
	};

}	// end of namespace 


#define CJ_ROOT_PATH( file )		CJFlash::CResourcePathDirector::sharedInstance()->getRealPath( file )
#define CJ_KEY_PATH( key, file )	CJFlash::CResourcePathDirector::sharedInstance()->getRealPath( key, file )

#define CJ_ROOT_PATH_C( file )		CJFlash::CResourcePathDirector::sharedInstance()->getRealPath( file ).c_str()
#define CJ_KEY_PATH_C( key, file )	CJFlash::CResourcePathDirector::sharedInstance()->getRealPath( key, file ).c_str()


#endif // !__CJ_RESOURCE_PATH_DIRECTOR_H__
