#pragma once

#include <cstdint>
#include <array>
#include <mutex>
#include <stdexcept>

namespace SHAMS
{
    template <typename T, uint32_t capacity>
    class RingBuffer
    {

    public:
        RingBuffer() = default;

        bool push(const T &item)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_size == capacity)
            {
                return false;
            }
            m_buffer[m_tail] = item;
            m_tail = (m_tail + 1) % capacity;
            m_size++;
            return true;
        }

        bool pop(T &item)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_size == 0)
            {
                return false;
            }
            item = m_buffer[m_head];
            m_head = (m_head + 1) % capacity;
            m_size--;
            return true;
        }

        uint32_t size()
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_size;
        }

        uint32_t capacity() const
        {
            return capacity;
        }

    private:
        std::array<T, capacity> m_buffer;
        std::mutex m_mutex;
        uint32_t m_head = 0;
        uint32_t m_tail = 0;
        uint32_t m_size = 0;
    };

} // namespace SHAMS
