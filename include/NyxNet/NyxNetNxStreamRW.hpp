#ifndef _NYXNETNXSTREAMRW_HPP_
#define _NYXNETNXSTREAMRW_HPP_

#include "NyxNetNxDataHeader.hpp"


namespace NyxNet
{
	class INxStreamable;

	/**
	 *	\brief		Interface describing methods to read/write section data to/from an Nx Stream
	 */
	class INxSectionStreamRW
	{
		friend class CNxSectionStreamWriter;
		friend class CNxSectionStreamReader;

	protected:

		virtual bool RequiresBytesSwap() const = 0;

		virtual Nyx::NyxResult BeginReadSection( NyxNet::NxDataSize& size ) = 0;
		virtual Nyx::NyxResult Read( void* pBuffer, const NyxNet::NxDataSize& size ) = 0;
		virtual void EndReadSection() = 0;

		virtual Nyx::NyxResult BeginWriteSection( const NyxNet::NxDataSize& size ) = 0;
		virtual Nyx::NyxResult Write( void* pBuffer, const NyxNet::NxDataSize& DataSize ) = 0;
		virtual void EndWriteSection() = 0;
	};


	/**
	 *	\brief		Interface describing methods to read/write data to/from an Nx Stream
	 */
	class INxStreamRW : public INxSectionStreamRW
	{
		friend class CNxStreamWriter;
		friend class CNxStreamReader;

	protected:

		virtual Nyx::NyxResult BeginRead( NyxNet::NxDataType& datatype ) = 0;
		virtual void EndRead() = 0;

		virtual Nyx::NyxResult BeginWrite( const NyxNet::NxDataType& datatype ) = 0;
		virtual void EndWrite() = 0;
	};


	/**
	 *	\brief		Object allowing access to data writing to an Nx Stream
	 */
	class CNxStreamWriter
	{
		friend class CNxSectionStreamWriter;

	public:
		CNxStreamWriter( INxStreamRW& rStream, const NyxNet::NxDataType& datatype ) : m_rStream(rStream)
		{
			Nyx::NyxResult		res;
			
			res = m_rStream.BeginWrite(datatype);
			m_bValid = Nyx::Succeeded(res);
		}

		CNxStreamWriter( INxStreamRW* pStream, const NyxNet::NxDataType& datatype ) : m_rStream(*pStream)
		{
			Nyx::NyxResult		res;
			
			res = m_rStream.BeginWrite(datatype);
			m_bValid = Nyx::Succeeded(res);
		}

		~CNxStreamWriter()
		{
			if ( m_bValid )
				m_rStream.EndWrite();
		}

		bool Valid() const		{ return m_bValid; }

	protected:
		INxStreamRW&		m_rStream;
		bool				m_bValid;
	};


	/**
	 *	\brief		Object used to write section data to an Nx Stream
	 */
	class CNxSectionStreamWriter
	{
	public:
		CNxSectionStreamWriter( CNxStreamWriter& rWriter, const NyxNet::NxDataSize& size ) : m_rStream(rWriter.m_rStream)
		{
			Nyx::NyxResult		res = Nyx::kNyxRes_Failure;

			if ( rWriter.Valid() )
				res = m_rStream.BeginWriteSection(size);

			m_bValid = Nyx::Succeeded(res);
		}

		~CNxSectionStreamWriter()
		{
			if ( m_bValid )
				m_rStream.EndWriteSection();
		}

		Nyx::NyxResult Write( void* pBuffer, const NyxNet::NxDataSize& size )
		{
			if ( !m_bValid )
				return Nyx::kNyxRes_Failure;

			return m_rStream.Write(pBuffer, size);
		}

		bool Valid() const			{ return m_bValid; }

	protected:
		INxSectionStreamRW&		m_rStream;
		bool					m_bValid;
	};


	/**
	 *	\brief		Object used to allow reading data from an Nx Stream
	 */
	class CNxStreamReader
	{
		friend class CNxSectionStreamReader;

	public:
		CNxStreamReader( INxStreamRW& rStream ) : m_rStream(rStream), m_DataType(eNxDT_Unknown)
		{
			Nyx::NyxResult		res;

			res = m_rStream.BeginRead(m_DataType);
			m_bValid = Nyx::Succeeded(res);
		}

		CNxStreamReader( INxStreamRW* pStream ) : m_rStream(*pStream)
		{
			Nyx::NyxResult		res;

			res = m_rStream.BeginRead(m_DataType);
			m_bValid = Nyx::Succeeded(res);
		}

		~CNxStreamReader()
		{
			if ( m_bValid )
				m_rStream.EndRead();
		}

		bool RequiresBytesSwap() const					{ return m_rStream.RequiresBytesSwap(); }

		bool Valid() const									{ return m_bValid; }

		const NyxNet::NxDataType& DataType() const			{ return m_DataType; }

	protected:
		INxStreamRW&			m_rStream;
		bool					m_bValid;
		NyxNet::NxDataType		m_DataType;
	};


	/**
	 *	\brief		Object used to read section data from an Nx Stream
	 */
	class CNxSectionStreamReader
	{
	public:
		CNxSectionStreamReader( CNxStreamReader& rReader ) : m_rStream(rReader.m_rStream), m_Size(0)
		{
			Nyx::NyxResult		res = Nyx::kNyxRes_Failure;

			if ( rReader.Valid() )
				res = m_rStream.BeginReadSection(m_Size);

			m_bValid = Nyx::Succeeded(res);
		}

		~CNxSectionStreamReader()
		{
			if (m_bValid)
				m_rStream.EndReadSection();
		}

		Nyx::NyxResult Read( void* pBuffer, const NyxNet::NxDataSize& size )
		{
			if ( !m_bValid )
				return Nyx::kNyxRes_Failure;

			return m_rStream.Read(pBuffer, size);
		}

		bool RequiresBytesSwap() const					{ return m_rStream.RequiresBytesSwap(); }

		bool Valid() const								{ return m_bValid; }

		const NyxNet::NxDataSize& Size() const			{ return m_Size; }

	protected:

		INxSectionStreamRW&				m_rStream;
		bool							m_bValid;
		NyxNet::NxDataSize				m_Size;
	};
}

#endif // _NYXNETNXSTREAMRW_HPP_

