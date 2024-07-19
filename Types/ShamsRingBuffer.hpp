#pragma once

#include <cstdint>
#include <mutex>
#include <memory>
#include <stdexcept>

namespace SHAMS
{
    template <typename T>
    class RingBuffer
    {

    public:
        RingBuffer(uint32_t capacity)
            : m_buffer(std::make_unique<T[]>(capacity)),
              m_capacity(capacity)
        {
        }

        bool push(const T &item)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_size == m_capacity)
            {
                return false;
            }
            m_buffer[m_tail] = item;
            m_tail = (m_tail + 1) % m_capacity;
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
            m_head = (m_head + 1) % m_capacity;
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
            return m_capacity;
        }

        // bool operator bool() const
        // {
        //     return this->size() > 0;
        // }

    private:
        std::unique_ptr<T[]> m_buffer;
        std::mutex m_mutex;
        uint32_t m_head = 0;
        uint32_t m_tail = 0;
        uint32_t m_size = 0;
        const uint32_t m_capacity;
    };

} // namespace SHAMS
