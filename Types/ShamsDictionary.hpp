#pragma once

#include <cstdint>
#include <memory>
#include <mutex>

namespace SHAMS
{

    template <typename key_type, typename value_type>
    class Dictionary
    {
    public:
        Dictionary(uint32_t maxCapacity)
            : m_maxCapacity{maxCapacity},
              m_keys{std::make_unique<key_type[]>(maxCapacity)},
              m_values{std::make_unique<value_type[]>(maxCapacity)},
              m_states{std::make_unique<bool[]>(maxCapacity)}
        {
            std::fill(m_states.get(), m_states.get() + maxCapacity, false);
        }

        bool insert(const key_type &key, const value_type &value)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return this->addItem(key, value);
        }

        bool remove(const key_type &key)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return this->removeItem(key);
        }

        bool contains(const key_type &key) const
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return this->hasKey(key);
        }

        value_type &operator[](const key_type &key)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return this->getValue(key);
        }

        uint32_t size() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_size;
        }

    private:
        uint32_t findNextFreeIndex()
        {
            if (m_size == m_maxCapacity)
            {
                return m_maxCapacity;
            }

            for (uint32_t i = 0; i < m_maxCapacity; i++)
            {
                if (m_states[i] == false)
                {
                    return i;
                }
            }
            return m_maxCapacity;
        }

        bool hasKey(const key_type &key) const
        {
            for (uint32_t i = 0; i < m_maxCapacity; i++)
            {
                if (m_states[i] and m_keys[i] == key)
                {
                    return true;
                }
            }
            return false;
        }

        bool addItem(const key_type &key, const value_type &value)
        {

            uint32_t index = findNextFreeIndex();
            // Check if the dictionary is full
            if (index == m_maxCapacity)
            {
                return false;
            }

            // Check if the key already exists, no duplicate keys allowed
            if (this->hasKey(key))
            {
                return false;
            }

            // Insert the key and value into the free index
            m_keys[index] = key;
            m_values[index] = value;
            m_states[index] = true;
            m_size++;
            return true;
        }

        bool removeItem(const key_type &key)
        {
            for (uint32_t i = 0; i < m_maxCapacity; i++)
            {
                if (m_states[i] and m_keys[i] == key)
                {
                    m_states[i] = false;
                    m_size--;
                    return true;
                }
            }
            return false;
        }

        value_type &getValue(const key_type &key)
        {
            for (uint32_t i = 0; i < m_maxCapacity; i++)
            {
                if (m_keys[i] == key)
                {
                    return m_values[i];
                }
            }
            throw std::out_of_range("Key not found");
        }

    private:
        const uint32_t m_maxCapacity;
        mutable std::mutex m_mutex;
        uint32_t m_size = 0;
        std::unique_ptr<key_type[]> m_keys;
        std::unique_ptr<value_type[]> m_values;
        std::unique_ptr<bool[]> m_states;
    };

} // namespace SHAMS
