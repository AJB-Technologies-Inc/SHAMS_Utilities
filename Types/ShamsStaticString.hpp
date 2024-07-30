#pragma once

#include <cstdint>
#include <array>
#include <stdexcept>
#include <algorithm>
#include <ranges>

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
