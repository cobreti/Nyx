#ifndef _NYXNETCONNECTION_HPP_
#define _NYXNETCONNECTION_HPP_

namespace NyxNet
{
	class IConnection
	{
	public:

		virtual void Close() = 0;
	};
}

#endif // _NYXNETCONNECTION_HPP_
