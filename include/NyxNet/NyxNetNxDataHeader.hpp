#ifndef _NYXNETNXDATAHEADER_HPP_
#define _NYXNETNXDATAHEADER_HPP_

#include "NyxNetTypes.hpp"

namespace NyxNet
{
	class CNxDataHeader
	{
	public:
		CNxDataHeader() : m_DataType(0), m_DataSize(0) {}
		~CNxDataHeader() {}

		const NxDataType& DataType() const { return m_DataType; }
		NxDataType& DataType() { return m_DataType; }

		const NxDataSize& DataSize() const { return m_DataSize; }
		NxDataSize& DataSize() { return m_DataSize; }

		const CNxDataHeader& operator = (const CNxDataHeader& DataHeader)
		{
			m_DataType = DataHeader.m_DataType;
			m_DataSize = DataHeader.m_DataSize;
			return *this;
		}

	protected:

		NxDataType		m_DataType;
		NxDataSize		m_DataSize;
	};
}

#endif // _NYXNETNXDATAHEADER_HPP_
