#include<string.h>
#include<string>

#define uchar unsigned char
using namespace std;
class BStream
{
public:
    //methods
    BStream();
    virtual ~BStream();

    virtual bool  open( char* src );
    int     getByte();

protected:
    uchar*  m_start;
    uchar*  m_end;
    uchar*  m_current;
};

