
#define NULL 0


template < typename T >
class FastList
{
	struct data
	{
		data( T iData ):
			m_Data( iData ),
			m_pNext( NULL )
		{}

		T 				m_Data;
		struct data*	m_pNext;
	};

public:
	class iterator
	{
	public:
		iterator() {}

		iterator( data* iData ):
			m_pData( iData )
		{
		}

		iterator& operator=( const data* iData )
		{
			this->m_pData = iData;
		}

		void Next()
		{
			this->m_pData = this->m_pData->m_pNext;
		}

		T Data()
		{
			return this->m_pData->m_Data;
		}

		bool End()
		{
			return NULL == this->m_pData->m_pNext;
		}

	private:
		data*	m_pData;
	};

public:
	FastList():
		m_pFirst( NULL ),
		m_pLast( NULL ),
		m_Size( 0 )
	{
	}

	~FastList()
	{
		while ( this->m_pFirst )
		{
			data* save = this->m_pFirst->m_pNext;
			delete this->m_pFirst;
			this->m_pFirst = save;
		}
	}

	unsigned int 	Size()
	{
		return this->m_Size;
	}

	bool			Empty()
	{
		return NULL == this->m_pFirst;
	}

	/* Perform a push back */
	void			Push( T iData )
	{
		data* newElem = new data( iData );
		if ( NULL != this->m_pLast )
			this->m_pLast->m_pNext = newElem;

		this->m_pLast = newElem;

		if ( NULL == this->m_pFirst )
			this->m_pFirst = newElem;

		this->m_Size++;
	}

	/* Perform a pop front */
	T 				Pop()
	{
		// TODO There is an issue here due to the copy of the element
		//      I think that the element is destroyed at the end of the scope...
		if ( NULL == this->m_pFirst )
			throw "";
		T ret = this->m_pFirst->m_Data;
		data* save = this->m_pFirst;
		this->m_pFirst = this->m_pFirst->m_pNext;
		delete save;
		this->m_Size--;
		return ret;
	}

	T 				Front() const
	{
		if ( NULL == this->m_pFirst )
			throw "";
		return this->m_pFirst->m_Data;
	}

	T 				Back() const
	{
		if ( NULL == this->m_pLast )
			throw "";
		return this->m_pLast->m_Data;
	}

	data*			Begin() const
	{
		return this->m_pFirst;
	}

private:
	data*		m_pFirst;
	data*		m_pLast;

	unsigned int m_Size;
};
