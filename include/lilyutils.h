/**
 * @file lilyutils.h
 * @author bipsydev
 * @brief Common C++ utility functions.
 * @version 0.1
 * @date Oct. 16th, 2023
 */

#pragma once
#ifndef LCODE_LILYUTILS_H
#define LCODE_LILYUTILS_H

#include <iostream> // std::cout
#include <string>   // std::string
#include <vector>   // std::vector
#include <cstddef>  // size_t

namespace LCode
{

/**
 * @brief Prints `length` amount of `bar` characters, and if `newline` is
 *        true, also a newline at the end. @n
 *        Default prints 80 underscores with newline. (should be the
 *        length of the terminal winddow)
 * 
 * @param length  Number of characters to print.
 * @param bar     The character to print.
 * @param newline Whether or not to print a newline character at the end.
 */
inline void print_bar(size_t length = 80, char bar = '_', bool newline = true)
{
    std::cout << std::string(length, bar) << (newline? "\n" : "");
}


/**
 * @brief Represents the platform this program is compiled with.
 */
enum Platforms
{
    LINUX, WINDOWS, MACOS
};

/**
 * @brief Get which platform this program is compiled with.
 * 
 * @return either  `LINUX`, `WINDOWS`, or `MACOS`.
 */
inline Platforms get_platform()
{
    #ifdef __linux__ || __unix__
        return LINUX;
    #elif _WIN32 || __MINGW32__
        return WINDOWS;
    #elif __APPLE__
        return MACOS;
    #endif
}

/**
 * @return true if compiled on Windows (MSVC or MinGW), false otherwise.
 */
inline bool on_windows()
{
    #ifdef _WIN32 || __MINGW32__
        return true;
    #else
        return false;
    #endif
}

/**
 * @return true if compiled on Linux/Unix, false otherwise.
 */
inline bool on_linux()
{
    #ifdef __linux__ || __unix__
        return true;
    #else
        return false;
    #endif
}

/**
 * @return true if compiled on MacOS, false otherwise.
 */
inline bool on_macos()
{
    #ifdef __APPLE__
        return true;
    #else
        return false;
    #endif
}


/**
 * @brief Returns a lowercase version of the string using `std::tolower`.
 * 
 * @param str a `std::string`.
 * @return  `std::string` that is all lowercase.
 */
inline std::string str_tolower(const std::string & str)
{
    std::string ret;
    for (char c : str)
    {
        ret += static_cast<char>(std::tolower(c));
    }
    return ret;
}


/**
 * @brief Splits a string based on delimeter (default space) into a vector
 *        of strings.
 * 
 * @param str The string to split.
 * @param delim The character to use as a delimeter.
 * @return `std::vector<std::string> `
 */
inline std::vector<std::string> str_split(std::string str, char delim = ' ')
{
    using std::string;

    std::vector<std::string> words;
    while(str.length() > 0)
    {
        // trim beginning delims
        size_t first_not_delim = str.find_first_not_of(delim);
        if (first_not_delim == string::npos)
        {
            first_not_delim = 0;
        }
        str = str.substr(first_not_delim);
        // get to next delim
        size_t next_delim = str.find(delim);
        if (next_delim == string::npos)
        {
            next_delim = str.length();
        }
        string sub = str.substr(0, next_delim);
        words.push_back(sub);
        // remove taken word
        str = str.substr(next_delim);
        size_t next_word_begin = str.find_first_not_of(delim);
        if (next_word_begin == string::npos)
        {
            str = "";
        }
        else
        {
            str = str.substr(next_word_begin);
        }
    }
    return words;
}


/**
 * @brief Returns a string representation of the vector. This template
 *        function uses `+=` to append the element to the string.
 * 
 * @tparam ElemT The element within the vector to append to the string.
 * @param list The input vector.
 * @return `std::string` that shows the vector like so: `{1, 2, 3}` 
 */
template <typename ElemT>
inline std::string vector_str(std::vector<ElemT> list)
{
    std::string ret{"{"};
    for (size_t i = 0; i < list.size(); ++i)
    {
        ret += list[i];
        if (i < list.size() - 1)
        {
            ret += ", ";
        }
    }
    ret += "}";
    return ret;
}


/**
 * @brief Template function that tests if a given variable is of
 *        a given type using dynamic_cast!
 * 
 * @tparam TestType The type you are testing against.
 * @tparam VarType  Inferred based on argument given.
 * @param var       The variable to test its type.
 * 
 * @return dynamic_cast<TestType>(var) != nullptr;
 */
template <typename TestType, typename VarType>
inline bool is_type(VarType var)
{
    return dynamic_cast<TestType>(var) != nullptr;
}

} // namespace LCode

#endif // LCODE_LILYUTILS_H