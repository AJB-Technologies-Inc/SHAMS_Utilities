#pragma once

#include <cstdint>
#include <cstring>
#include <array>
#include <stdexcept>
#include <algorithm>
#include <ranges>
#include <string>

namespace SHAMS
{
template <size_t t_maxLength = 16 >
class StaticString
{
    public:

    constexpr ~StaticString() = default;

    /**
     * @brief Default constructor
     * Initializes the buffer with null terminators
     */
    constexpr StaticString()
    {
        m_buffer.fill('\0');
    }

    /**
     * @brief Constructor that initializes the buffer with the provided string
     * 
     * @note The input string must be null-terminated.
     *
     * @param str - The string to initialize the buffer with
     */
    constexpr StaticString(const char (&str)[t_maxLength])
            : m_length(t_maxLength - 1) // Exclude null terminator
    {
        std::copy(str, str + m_length, m_buffer.begin());
        m_buffer[m_length] = '\0';
    }

    /**
     * @brief Constructor that initializes the buffer with the provided string
     *
     * @param str - The string to initialize the buffer with
     */
    constexpr StaticString(std::string_view str)
            : m_length(str.length())
    {
        std::copy(str.begin(), str.end(), m_buffer.begin());
        m_buffer[m_length] = '\0';
    }

        /**
     * @brief Constructor that initializes the buffer with the provided string
     * 
     * @note The input string must be null-terminated.
     *
     * @param str - The string to initialize the buffer with
     */
    template<size_t t_otherLength>
    constexpr StaticString(const char (&str)[t_otherLength])
            : m_length(t_otherLength - 1) // Exclude null terminator
    {
        std::copy(str, str + m_length, m_buffer.begin());
        m_buffer[m_length] = '\0';
    }

    /**
     * @brief Copy constructor
     * 
     * @param other - The other StaticString object to copy from
     */
    constexpr StaticString(const StaticString &other)
        : m_length(other.m_length)
    {
        std::copy(other.m_buffer.begin(), other.m_buffer.end(), m_buffer.begin());
    }

    /**
     * @brief Move constructor
     * 
     * @param other - The other StaticString object to move from
     */
    constexpr StaticString(StaticString &&other)
        : m_length(other.m_length),
          m_buffer(std::move(other.m_buffer))
    {
        other.m_length = 0;
        other.m_buffer.fill('\0');
    }

    /**
     * @brief Copy assignment operator
     *
     * @param other - The other StaticString object to copy from
     * @return StaticString& - The reference to the assigned object
     */
    constexpr StaticString& operator=(const StaticString &other)
    {
        if (this != &other)
        {
            m_length = other.m_length;
            m_buffer = other.m_buffer;
        }
        return *this;
    }

    /**
     * @brief Copy assignment constructor
     * 
     * @param other - The other StaticString object to copy from
     */
    template <size_t t_otherLength>
    constexpr StaticString& operator=(const StaticString<t_otherLength> &other)
    {
        if constexpr(t_otherLength > t_maxLength)
        {
            throw std::runtime_error("New string will not fit inside existing container");
        }

        m_length = other.length() - 1;
        std::copy(other.c_str(), other.c_str() + m_length, m_buffer.begin());
        m_buffer[m_length] = '\0';
        return *this;
    }

    /**
     * @brief Copy assignment constructor from C string
     * 
     * @param other - The other StaticString object to copy from
     */
    template <size_t t_otherLength>
    constexpr StaticString& operator=(const char (&str)[t_otherLength])
    {
        if constexpr(t_otherLength > t_maxLength)
        {
            throw std::runtime_error("New string will not fit inside existing container");
        }
        m_length = t_maxLength - 1;
        std::copy(str, str + m_length, m_buffer.begin());
        m_buffer[m_length] = '\0';
        return *this;
    }

    /**
     * @brief move assignment constructor
     * 
     * @param other - The other StaticString object to move from
     */
    constexpr StaticString& operator=(StaticString&& other)
    {
        m_length = other.m_length;
        m_buffer = std::move(other.m_buffer);
        return *this;
    }



    /**
     * @brief Returns the length of the string, excluding the null terminator
     *
     * @return size_t - The length of the string
     */
    constexpr size_t length() const
    {
        return m_length;
    }

    /**
     * @brief Returns the maximum allowable length of the string container, excluding the null terminator
     *
     * @return size_t - The maximum length of the string
     */
    constexpr size_t maxLength() const
    {
        return t_maxLength;
    }

    /**
     * @brief Returns the string as a C-style string
     *
     * @return const char* - The C-style string
     */
    constexpr const char *c_str() const
    {
        return m_buffer.data();
    }

    /**
     * @brief Overloaded subscript operator to access elements in the buffer
     *
     * @param index - The index of the element to access
     * @throws std::out_of_range - If the index is out of range
     * @return char& - The reference to the element at the index
     */
    constexpr char &operator[](size_t index)
    {
        if (index < m_length)
        {
            return m_buffer[index];
        }
        else
        {
            throw std::out_of_range("String index out of range");
        }
    }


    /**
     * @brief Overloaded subscript operator to access elements in the buffer (const version)
     *
     * @param index - The index of the element to access
     * @throws std::out_of_range - If the index is out of range
     * @return const char& - The reference to the element at the index
     */
    constexpr const char &operator[](size_t index) const
    {
        if (index < m_length)
        {
            return m_buffer[index];
        }
        else
        {
            throw std::out_of_range("String index out of range");
        }
    }

    /**
     * @brief Clear the string buffer
     */
    constexpr void clear()
    {
        m_length = 0;
        m_buffer.fill('\0');
    }

    /**
     * @brief Convert the entire string to uppercase
     */
    constexpr void toUpper()
    {
        std::ranges::transform(m_buffer, m_buffer.begin(), [](char c) { return std::toupper(c); });   
    }

    /**
     * @brief Convert the entire string to lowercase
     */
    constexpr void toLower()
    {
        std::ranges::transform(m_buffer, m_buffer.begin(), [](char c) { return std::tolower(c); });  
    }

    /**
     * @brief Reverse the string
     */
    constexpr void reverse()
    {
        std::ranges::reverse(this->begin(), this->end());
    }

    /**
     * @brief Remove all instances of a character from the string
     *
     * @param c - The character to remove
     */
    constexpr void remove(char c)
    {
        m_buffer.erase(std::remove(this->begin(), this->end(), c), this->end());
        m_length = strnlen(this->c_str(), t_maxLength);
    }

    /**
     * @brief Remove all instances of a string from the string
     * 
     * @param str - The string to remove
     */
    constexpr void remove(const char *str)
    {
        m_buffer.erase(std::remove(this->begin(), this->end(), str), this->end());
        m_length = strnlen(this->c_str(), t_maxLength);
    }

    /**
     * @brief Count the number of instances of a character in the string
     *
     * @param c - The character to count
     * @return size_t - The number of instances of the character
     */
    constexpr size_t count(char c)
    {
        return std::ranges::count(this->begin(), this->end(), c);
    }

    /**
     * @brief Count the number of instances of a string in the string
     *
     * @param str - The string to count
     * @return size_t - The number of instances of the string
     */
    constexpr size_t count(std::string_view str) const
    {
        size_t count = 0;
        auto it = m_buffer.begin();
        auto str_len = str.length();

        while ((it = std::search(it, m_buffer.end(), str.begin(), str.end())) != m_buffer.end())
        {
            ++count;
            it += str_len; // Move past the last found substring
        }

        return count;
    }

    /**
     * @brief Count the number of instances of a string in the string
     *
     * @param str - The string to count
     * @return size_t - The number of instances of the string
     */
    constexpr size_t count(const StaticString &str)
    {
        return count(str.c_str());
    }


    /**
     * @brief Count the number of instances of a string in the string
     *
     * @param str - The string to count
     * @return size_t - The number of instances of the string
     */
    constexpr size_t count(const char *str, size_t length)
    {
        return std::ranges::count(this->begin(), this->end(), str, str + length);
    }

    /**
     * @brief Count the number of instances of a string in the string
     *
     * @tparam t_otherLength - The length of the other string
     * @param str - The string to count
     * @return size_t - The number of instances of the string
     */
    template<size_t t_otherLength>
    constexpr size_t count(const StaticString<t_otherLength> &str)
    {
        return std::ranges::count(this->begin(), this->end(), str.begin(), str.end());
    }

    /**
     * @brief Count the number of instances of a string in the string
     *
     * @tparam t_otherLength - The length of the other string
     * @param str - The string to count
     * @return size_t - The number of instances of the string
     */
    template<size_t t_otherLength>
    constexpr size_t count(const char (&str)[t_otherLength])
    {
        return std::ranges::count(this->begin(), this->end(), str, str + t_otherLength);
    }


    /**
     * @brief Check if the string starts with a given string
     *
     * @param str - The string to check
     * @return bool - True if the string starts with the given string, false otherwise
     */
    constexpr bool startsWith(std::string_view str)
    {
        return std::ranges::equal(str.begin(), str.end(), this->begin());
    }

    /**
     * @brief Check if the string ends with a given string
     *
     * @param str - The string to check
     * @return bool - True if the string ends with the given string, false otherwise
     */
    constexpr bool endsWith(std::string_view str)
    {
        size_t strLength = str.length();
        return std::ranges::equal(str.begin(), str.end(), this->end() - strLength);
    }

    /**
     * @brief Check if the string contains a given string
     *
     * @param str - The string to check
     * @return bool - True if the string contains the given string, false otherwise
     */
    constexpr bool contains(std::string_view str)
    {
        return (this->count(str) > 0);
    }


    /**
     * @brief Check if the string contains a given character
     *
     * @param character - The character to check
     * @return bool - True if the string contains the given character, false otherwise
     */
    constexpr bool contains(const char character)
    {
        return this->count(character) > 0;
    }

    /**
     * @brief Compare the string with a given string
     *
     * @param str - The string to compare
     * @return bool - True if the strings are equal, false otherwise
     */
    constexpr bool compare(const char *str)
    {
        return strncmp(str, this->c_str(), t_maxLength) == 0;
    }

    /**
     * @brief Compare the string with a given string
     *
     * @param str - The string to compare
     * @return bool - True if the strings are equal, false otherwise
     */
    constexpr bool compare(const StaticString &str)
    {
        return strncmp(this->c_str(), str.c_str(), t_maxLength) == 0;
    }

    /**
     * @brief Compare the string with a given string
     *
     * @param str - The string to compare
     * @return bool - True if the strings are equal, false otherwise
     */
    constexpr bool compare(const std::string &str)
    {
        return str == this->c_str();
    }

    /**
     * @brief Compare the string with a given string
     *
     * @param str - The string to compare
     * @return bool - True if the strings are equal, false otherwise
     */
    constexpr bool compare(const char *str, size_t length)
    {
        return strncmp(str, this->c_str(), length) == 0;
    }

    /**
     * @brief Compare the string with a given string
     *
     * @param str - The string to compare
     * @return bool - True if the strings are equal, false otherwise
     */
    template<size_t t_otherLength>
    constexpr bool compare(const StaticString<t_otherLength> &str)
    {
        auto max_length = std::min(t_maxLength, t_otherLength);
        return strncmp(this->c_str(), str.c_str(), max_length) == 0;
    }

    /**
     * @brief Compare the string with a given string
     *
     * @param str - The string to compare
     * @return bool - True if the strings are equal, false otherwise
     */
    template<size_t t_otherLength>
    constexpr bool compare(const char (&str)[t_otherLength])
    {
        auto max_length = std::min(t_maxLength, t_otherLength);
        return strncmp(str, this->c_str(), max_length) == 0;
    }

    /**
     * @brief Compare the string with a given string
     *
     * @param str - The string to compare
     * @return bool - True if the strings are equal, false otherwise
     */
    constexpr bool operator==(const auto &str)
    {
        return this->compare(str);
    }

    /**
     * @brief Compare the string with a given string
     *
     * @param str - The string to compare
     * @return bool - True if the strings are equal, false otherwise
     */
    constexpr bool operator==(const auto *str)
    {
        return this->compare(str);
    }


    /**
     * @brief Append a character to the end of the string
     *
     * @param c - The character to append
     */
    constexpr void append(char c)
    {
        if ((m_length < (t_maxLength - 1)) and (c != '\0'))
        {

            m_buffer[m_length++] = c;
            m_buffer[m_length] = '\0';
        }
    }

    /**
     * @brief Append a string to the end of the string
     *
     * @param str - C-style string to append
     */
    template<size_t t_otherLength>
    constexpr void append(const char (&str)[t_otherLength])
    {
        if (m_length + t_otherLength - 1 < t_maxLength)
        {
            std::copy(str, str + t_otherLength - 1, m_buffer.begin() + m_length);
            m_length += t_otherLength - 1;
            m_buffer[m_length] = '\0';
        }
    }

    /**
     * @brief Append a string to the end of the string
     *
     * @param str - static string to append
     */
    template<size_t t_otherLength>
    constexpr void append(const StaticString<t_otherLength> &str)
    {
        if (m_length + str.length() < t_maxLength)
        {
            std::ranges::copy(str, m_buffer.begin() + m_length);
            m_length += str.length();
            m_buffer[m_length] = '\0';
        }
    }

    /**
     * @brief Append a string to the end of the string
     *
     * @param str - Standard C++ string to append
     */
    constexpr void append(const std::string &str)
    {
        if (m_length + str.length() < t_maxLength)
        {
            std::ranges::copy(str, m_buffer.begin() + m_length);
            m_length += str.length();
            m_buffer[m_length] = '\0';
        }
    }

    /**
     * @brief Append a string to the end of the string
     *
     * @param str - Null-terminated C-style string to append
     */
    constexpr void append(const char *str)
    {
        size_t strLength = strnlen(str, t_maxLength);
        if (m_length + strLength < t_maxLength)
        {
            std::copy(str, str + strLength, m_buffer.begin() + m_length);
            m_length += strLength;
            m_buffer[m_length] = '\0';
        }
    }
    

    // Iterator functions to enable range-based loops
    constexpr auto begin() { return m_buffer.begin(); }
    constexpr auto end() { return m_buffer.begin() + m_length; }
    constexpr auto begin() const { return m_buffer.begin(); }
    constexpr auto end() const { return m_buffer.begin() + m_length; }


    
    private:
        size_t m_length = 0;
        std::array<char, t_maxLength> m_buffer;
};

} // namespace SHAMS
