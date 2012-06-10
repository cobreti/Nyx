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
        
        CRange(const long& start, const long& length) :
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
        
        const long&     Start() const               { return m_Start; }
        long&           Start()                     { return m_Start; }
        
        const long&     Length() const              { return m_Length; }
        long&           Length()                    { return m_Length; }

        bool            IsEmpty() const             { return m_Length < 1; }
        
    protected:
        long     m_Start;
        long     m_Length;
    };
    
    
    /**
     *
     */
    typedef     std::vector<CRange>         CRangesArray;
}


#endif // _NYXRANGE_HPP_
