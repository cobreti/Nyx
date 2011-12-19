#ifndef _NYXRANGE_HPP_
#define _NYXRANGE_HPP_


#include <NyxTypes.hpp>
#include <vector>

namespace Nyx
{
    /**
     *
     */
    class CRange
    {
    public:
        CRange() :
            m_Start(-1),
            m_Length(-1)
        {
        }
        
        CRange(const CRange& range) :
            m_Start(range.m_Start),
            m_Length(range.m_Length)
        {
        }
        
        CRange(const size_t& start, const size_t& length) :
            m_Start(start),
            m_Length(length)
        {
        }
        
        const CRange& operator = (const CRange& range)
        {
            m_Start = range.m_Start;
            m_Length = range.m_Length;
            return *this;
        }
        
        const size_t&  Start() const               { return m_Start; }
        size_t&        Start()                     { return m_Start; }
        
        const size_t&  Length() const              { return m_Length; }
        size_t&        Length()                    { return m_Length; }
        
    protected:
        size_t     m_Start;
        size_t     m_Length;
    };
    
    
    /**
     *
     */
    typedef     std::vector<CRange>         CRangesArray;
}


#endif // _NYXRANGE_HPP_
