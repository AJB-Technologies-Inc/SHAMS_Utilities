#pragma once

#include <cstdint>
#include <array>

namespace SHAMS
{
    template <typename T, uint32_t capacity>
    class StaticBuffer
    {
    public:
        StaticBuffer() = default;

        /**
         * @brief Inserts an item into the buffer
         *
         * @param item - The item to insert
         * @return bool - True if the item was inserted, false otherwise
         */
        bool insert(const T &item)
        {
            if (m_size >= capacity)
                return false;

            m_buffer[m_size++] = item;
            return true;
        }

        bool insert(T &&item)
        {
            if (m_size >= capacity)
                return false;

            m_buffer[m_size++] = std::move(item);
            return true;
        }

        /**
         * @brief Removes an item from the buffer
         *
         * @param item - The item to remove
         * @return bool - True if the item was removed, false otherwise
         */
        bool remove(const T &item)
        {
            for (uint32_t i = 0; i < m_size; i++)
            {
                if (m_buffer[i] == item)
                {

                    if constexpr (std::is_default_constructible<T>::value)
                    {
                        m_buffer[i] = T{};
                    }

                    for (uint32_t j = i; j < m_size - 1; j++)
                    {
                        m_buffer[j] = m_buffer[j + 1];
                    }
                    m_size--;
                    return true;
                }
            }
            return false;
        }

        /**
         * @brief Removes an item from the buffer by index
         *
         * @param index - The index of the item to remove
         * @return bool - True if the item was removed, false otherwise
         */
        bool removeByIndex(uint32_t index)
        {
            if (index >= m_size)
                return false;

            for (uint32_t i = index; i < m_size - 1; i++)
            {
                m_buffer[i] = m_buffer[i + 1];
            }
            m_size--;
            return true;
        }

        /**
         * @brief Returns the current size of the buffer
         *
         * @return uint32_t - The size of the buffer, in number of elements.
         */
        uint32_t size() const
        {
            return m_size;
        }

        /**
         * @brief Overloaded subscript operator to access elements in the buffer
         *
         * @param index - The index of the element to access
         * @throws std::out_of_range - If the index is out of range
         * @return T& - The reference to the element at the index
         */
        T &operator[](uint32_t index) const
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
        bool contains(const T &item) const
        {
            for (uint32_t i = 0; i < m_size; i++)
            {
                if (m_buffer[i] == item)
                {
                    return true;
                }
            }
            return false;
        }

        /**
         * @brief Clears the buffer
         */
        void clear()
        {
            if constexpr (std::is_default_constructible<T>::value)
            {
                for (uint32_t i = 0; i < m_size; i++)
                {
                    m_buffer[i] = T{};
                }
            }
            m_size = 0;
        }

    private:
        std::array<T, capacity> m_buffer;
        uint32_t m_size = 0;
    };

} // namespace SHAMS
