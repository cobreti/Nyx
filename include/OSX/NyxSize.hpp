#ifndef _NYXSIZE_HPP_
#define _NYXSIZE_HPP_

namespace Nyx
{
	/**
	 *
	 */
	class NyxSize
	{
	public:
		NyxSize() : m_Value(0) {}
		NyxSize(const NyxSize& s) : m_Value(s.m_Value) {}
		NyxSize(size_t s) : m_Value(s) {}

		const NyxSize& operator = (const NyxSize& s)
		{
			m_Value = s.m_Value;
			return *this;
		}

		const NyxSize& operator = (size_t s)
		{
			m_Value = s;
			return *this;
		}

		operator size_t () const { return m_Value; }

		const NyxSize& operator ++ ()
		{
			++ m_Value;
			return *this;
		}

		const NyxSize& operator -- ()
		{
			-- m_Value;
			return *this;
		}

		const NyxSize operator ++ (int)
		{
			NyxSize s(*this);
			++ m_Value;
			return s;
		}

		const NyxSize operator -- (int)
		{
			NyxSize s(*this);
			-- m_Value;
			return s;
		}

		const NyxSize& operator += (const NyxSize& s)
		{
			m_Value += s.m_Value;
			return *this;
		}

		const NyxSize& operator += (size_t s)
		{
			m_Value += s;
			return *this;
		}

		const NyxSize& operator -= (const NyxSize& s)
		{
			m_Value -= s.m_Value;
			return *this;
		}

		const NyxSize& operator -= (size_t s)
		{
			m_Value -= s;
			return *this;
		}

	private:

		size_t		m_Value;
	};
}

#endif // _NYXSIZE_HPP_
