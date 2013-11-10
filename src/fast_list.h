#ifndef CPPLIB_SRC_FAST_LIST_H
# define CPPLIB_SRC_FAST_LIST_H

#define NULL 0


template < typename T >
class FastList
{
	struct data
	{
		data( T iData )
			: m_Data( iData )
			, m_pNext( NULL )
		{}

		T            m_Data;
		struct data* m_pNext;
	};

public:
	class iterator
	{
	public:
		iterator() {}

		iterator( data* iData )
			: m_pData( iData )
		{}

		iterator& operator=( const data* iData )
		{
			m_pData = iData;
		}

		void Next()
		{
			m_pData = m_pData->m_pNext;
		}

		T Data()
		{
			return m_pData->m_Data;
		}

		bool End()
		{
			return NULL == m_pData->m_pNext;
		}

	private:
		data* m_pData;
	};

public:
	FastList()
		: m_pFirst( NULL )
		, m_pLast( NULL )
		, m_Size( 0 )
	{}

	~FastList()
	{
		while ( m_pFirst )
		{
			data* save = m_pFirst->m_pNext;
			delete m_pFirst;
			m_pFirst = save;
		}
	}

	unsigned int Size()
	{
		return m_Size;
	}

	bool Empty()
	{
		return NULL == m_pFirst;
	}

	/* Perform a push back */
	void Push( T iData )
	{
		data* newElem = new data( iData );

		if ( NULL != m_pLast )
			m_pLast->m_pNext = newElem;

		m_pLast = newElem;

		if ( NULL == m_pFirst )
			m_pFirst = newElem;

		m_Size++;
	}

	/* Perform a pop front */
	T Pop()
	{
		// TODO There is an issue here due to the copy of the element
		//      I think that the element is destroyed at the end of the scope...
		if ( NULL == m_pFirst )
			throw "";

		T ret = m_pFirst->m_Data;
		data* save = m_pFirst;
		m_pFirst = m_pFirst->m_pNext;
		delete save;

		m_Size--;

		return ret;
	}

	T Front() const
	{
		if ( NULL == m_pFirst )
			throw "";

		return m_pFirst->m_Data;
	}

	T Back() const
	{
		if ( NULL == m_pLast )
			throw "";

		return m_pLast->m_Data;
	}

	data* Begin() const
	{
		return m_pFirst;
	}

private:
	data*        m_pFirst;
	data*        m_pLast;

	unsigned int m_Size;
};

#endif // !CPPLIB_SRC_FAST_LIST_H
