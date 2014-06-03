#include "CJFlashResourcePathDirector.h"


namespace CJFlash
{

	CResourcePathDirector::CResourcePathDirector()
	{
		m_strRootResourcePath = "";
        m_strCommonResourcePath = "";
	}

	CResourcePathDirector::~CResourcePathDirector()
	{

	}

	void CResourcePathDirector::setRootResourcePath( std::string strOriginResPath )
	{
		STL_MAP_ITER_ResourcePath iter = m_stl_map_ResourcePaths.begin();

		while( iter != m_stl_map_ResourcePaths.end() )
		{
			std::string& realPath = iter->second;

			realPath.erase( 0, m_strRootResourcePath.size() );

//			realPath.insert( 0, strOriginResPath.append("/") );

			iter++;
		}
		
		//
		//

		m_strRootResourcePath = strOriginResPath.append("/");
	}

	void CResourcePathDirector::addResourcePath( std::string strKey, std::string strPath )
	{
		std::string realPath = "";

		realPath = getRealPath( strPath );

		m_stl_map_ResourcePaths.insert( std::pair<std::string, std::string>( strKey, realPath ) );
	}

	std::string CResourcePathDirector::getRealPath( std::string strFileName )
	{
		std::string realPath = m_strRootResourcePath;

		//realPath.append( "/" );
		realPath.append( strFileName );

		return realPath;
	}

	std::string CResourcePathDirector::getRealPath( std::string strKey, std::string strFileName )
	{
		STL_MAP_ITER_ResourcePath iter = m_stl_map_ResourcePaths.find( strKey );

		std::string realPath = "";

		if( iter != m_stl_map_ResourcePaths.end() )
			realPath = iter->second;

		//realPath.append( "/" );
		realPath.append( strFileName );

		return realPath;
	}


#pragma mark - common path
    
    void CResourcePathDirector::setCommonResourcePath(std::string strOriginResPath)
    {
        m_strCommonResourcePath = strOriginResPath.append("/");
    }
    
    std::string CResourcePathDirector::getCommonPath(std::string strFileName)
    {
        std::string realPath = m_strCommonResourcePath;
		realPath.append( strFileName );
		return realPath;
    }
    
    
    
}	// end of namespace