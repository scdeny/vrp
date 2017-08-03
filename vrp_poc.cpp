/*
 * testopt.cpp
 * Copyright (C) 2017 scdeny <scdengyuan@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */
#include<stdio.h>
#include<string.h>
#include<string>
#include "bstream.hpp"

static inline bool isdigit(char c)
{
    return '0' <= c && c <= '9';
}

static inline bool isspace(char c)
{
    return (9 <= c && c <= 13) || c == ' ';
}

static int ReadNumber(BStream& strm)
{
    int code;
    int val = 0;

    do {
        code = strm.getByte();
    }
    while( !isdigit( code ));

    do {
        val = val*10 + code;
        code = strm.getByte();
    }
    while( isdigit(code));

    return val;
}

class VRPPOC{
private:
    int m_var;
    BStream m_strm;

public:
    int m_index;

public:
    VRPPOC();
    bool read();
};

VRPPOC::VRPPOC()
{
}

bool VRPPOC::read()
{
    bool result = false;

    char in[] = "999999999999999999999999 ";
    if( !m_strm.open( in ))
        return false;

    m_var = 1;

    m_index = ReadNumber(m_strm);
    if( m_index > 65535 )
        return false;
    // int m_index can be overflowed to negative but VRP think it's between [48, +INF(OVF)], and ignored checking in next line
    if( m_var > 0 && m_index > 0 && m_index < (1 << 16)) //this line was optimized to "if( m_var>0 )"
    {
        // so negative m_index can bypass the check and return true
        result = true;
    }

    return result;
}

int main()
{
    VRPPOC decoder = VRPPOC();
    bool result = decoder.read();
    printf("m_index: %d, result: %x\n", decoder.m_index, result);
    if(result)
        printf("vulnerable!\n");
    else
        printf("not vulnerable!\n");

    if(result){
        char buff[65535] = "hello vrp";
        buff[decoder.m_index] = 0;
        printf("%s\n", buff);
    }

    return 0;
}
