#pragma once

#include <cstdint>
#include <array>
#include <stdexcept>
#include <algorithm>

namespace SHAMS
{
template <size_t t_maxLength = 16 >
class StaticString
{
    public:
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
        for (size_t i = 0; i < m_length; ++i) {
            m_buffer[i] = str[i];
        }
        m_buffer[m_length] = '\0';
    }

    template <size_t t_otherLength>
    constexpr StaticString& operator=(const char (&str)[t_otherLength])
    {
        static_assert(t_otherLength > t_maxLength, "String is too long");
        m_length = t_maxLength - 1;
        for (size_t i = 0; i < m_length; ++i) {
            m_buffer[i] = str[i];
        }
        m_buffer[m_length] = '\0';
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
    



    
    private:
        size_t m_length = 0;
        std::array<char, t_maxLength> m_buffer;
};

} // namespace SHAMS
