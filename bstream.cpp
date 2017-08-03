#include<stdio.h>
#include "bstream.hpp"

BStream::BStream()
{
}

BStream::~BStream()
{
    delete m_start;
}

bool BStream::open( char* src )
{
    m_start = new uchar[256];
    int len = strlen(src);
    strcpy((char*)m_start, src);
    m_end = m_start + len;
    m_current = m_start;
    return true;
}

int  BStream::getByte()
{
    uchar *current = m_current;
    int   val = *((uchar*)current);
    m_current = current + 1;
    return val;
}


