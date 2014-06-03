#ifndef __CJ_FLASH_UTIL_H__
#define __CJ_FLASH_UTIL_H__


#include "CJFlashMacro.h"


namespace CJFlash
{

// 	struct foSingleObjectDeleteFunctor
// 	{
// 		template <__type>
// 		void operator() (__type* t_pObject){ delete t_pObject; }
// 	};
// 	struct foArrayObjectDeleteFunctor
// 	{
// 		template <__type>
// 		void operator() (__type* t_pObject){ delete[] t_pObject; }
// 	};

	/*************************************************************************
	@
	@	name: 스마트포인터 클래스
	@
	@	author: [2012.11.27 CJFlash. YHM]
	@
	@	brief: 
	@
	**************************************************************************/
	template <class __type>
	class CSmartPointer
	{
	private:
		struct __Impl
		{
			__type*					__pObject;			// 힙에 생성된 실제 객체
			unsigned int			__nRef;				// 래퍼런스 카운트

			__Impl( __type* pObject ) : 
				__pObject( pObject ), 
				__nRef( 1 ) 
			{}
			~__Impl() { delete __pObject; }
		};

		__Impl*		__impl;


	public:
		CSmartPointer(__type* t_pObject) :
			__impl( new __Impl( t_pObject ) )
		{

		}
		CSmartPointer(const CSmartPointer<__type>& spDst) :
			__impl( spDst.__impl )
		{
			addRef();
		}
		~CSmartPointer()
		{
			release();
		}


	public:
		inline void addRef(void)
		{
			++(__impl->__nRef);
		}

		inline void release(void)
		{
			if( --(__impl->__nRef) == 0 )
				delete __impl;
		}
		inline bool isPtr(void)
		{
			return __impl->__pObject != NULL ? true : false;
		}

	public:
		inline __type& operator*()
		{
			return *(__impl->__pObject);
		}
		inline __type* operator->()
		{
			return __impl->__pObject;
		}
		inline CSmartPointer<__type>& operator=(CSmartPointer<__type>& spDst)
		{
			if( __impl != spDst.__impl )
			{
				release();
				__impl = spDst.__impl;
				addRef();
			}

			return *this;
		}
	};

	//
	//

	/*************************************************************************
	@
	@	name: 싱글톤 클래스
	@
	@	author: [2012.11.27 CJFlash. YHM]
	@
	@	brief: 
	@
	**************************************************************************/
	template <class type>
	class CSingleton
	{
	private:
		static type*		m_pInstance;

		
	protected:
		CSingleton(void)
		{
			if( m_pInstance != NULL )
			{
				delete this;
			}

			m_pInstance = (type*)this;
		}
		virtual ~CSingleton(void)
		{
			m_pInstance = NULL;
		}

	public:
		/**  [2012.11.22 CJFlash. YHM]
		  desc: 인스턴스 객체를 가져옴
		  param: 
		**/
		static type* sharedInstance(void)
		{
			if( m_pInstance == NULL )
			{
				createInstance();
			}

			return m_pInstance;
		}

		/**  [2012.11.23 CJFlash. YHM]
		  desc: 인스턴스 객체 생성
		  param: 
		**/
		static type* createInstance(void)
		{
			if( m_pInstance == NULL )
			{
				m_pInstance = new type;
			}

			return m_pInstance;
		}

		/**  [2013.1.28 CJFlash. YHM]
		  desc: 인스턴스 객체 제거
		  param: 
		**/
		static void destroyInstance(void)
		{
			if( m_pInstance != NULL )
				CJ_SAFE_DELETE( m_pInstance );
		}
	};

	template <class type>
	type* CSingleton<type>::m_pInstance = NULL;	


}	// end of namespace CJFlash




#endif // !__CJ_FLASH_UTIL_H__

