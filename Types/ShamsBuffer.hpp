#pragma once

#include <cstdint>
#include <vector>
#include <stdexcept>

namespace SHAMS
{
    template <typename T>
    class Buffer
    {
    public:
        Buffer() = default;

        /**
         * @brief Inserts an item into the buffer
         *
         * @param item - The item to insert
         * @return bool - True if the item was inserted, false otherwise
         */
        bool insert(const T &item)
        {
            m_buffer.push_back(item);
            return true;
        }

        /**
         * @brief Returns the current size of the buffer
         *
         * @return uint32_t - The size of the buffer, in number of elements.
         */
        uint32_t size() const
        {
            return static_cast<uint32_t>(m_buffer.size());
        }

        /**
         * @brief Overloaded subscript operator to access elements in the buffer
         *
         * @param index - The index of the element to access
         * @throws std::out_of_range - If the index is out of range
         * @return T& - The reference to the element at the index
         */
        T &operator[](uint32_t index)
        {
            if (index < m_buffer.size())
                return m_buffer[index];
            else
                throw std::out_of_range("Index out of range");
        }

        /**
         * @brief Searches the buffer to see if the item is present
         *
         * @param item - The item to search for
         * @return bool - True if the item is present, false otherwise
         */
        bool contains(const T &item)
        {
            for (const auto &element : m_buffer)
            {
                if (element == item)
                {
                    return true;
                }
            }
            return false;
        }

        // Iterator access
        auto begin() { return m_buffer.begin(); }
        auto end() { return m_buffer.end(); }
        auto begin() const { return m_buffer.begin(); }
        auto end() const { return m_buffer.end(); }
        auto cbegin() const { return m_buffer.cbegin(); }
        auto cend() const { return m_buffer.cend(); }

    private:
        std::vector<T> m_buffer;
    };

} // namespace SHAMS
