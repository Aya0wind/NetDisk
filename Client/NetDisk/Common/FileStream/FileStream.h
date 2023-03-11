#pragma once
//
// Created by li on 2020/3/26.
//
#include <fstream>
#include <array>
class FileStream
{
    size_t currentPos;
public:
    FileStream(const std::string& path,size_t startPos=0);
    template <size_t N>
    size_t read(std::array<char,N>& array);

    size_t write(std::string& buffer,size_t max);

    std::string readToEnd();
    template <size_t N>
    size_t write(const std::array<char,N>& array);
    size_t write(const std::string& buffer);

    size_t size();
    bool end();
};

template <size_t N>
size_t FileStream::write(const std::array<char, N>& array)
{
    return 0;
}
template <size_t N>
size_t FileStream::read(std::array<char, N>& array)
{
    return 0;
}

