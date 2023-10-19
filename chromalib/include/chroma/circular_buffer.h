#pragma once

#include "chroma.h"


namespace chroma {
  template <typename T>
  class circular_buffer {
  public:
    circular_buffer(std::size_t _size) : m_size(_size) {
      m_buffer = std::make_unique<T[]>(_size); 
    }

    void push(T* _data, std::size_t _n) {
      while (_n--) {
        m_buffer[m_head] = *(_data++);
        m_head = (++m_head) % m_size;
        m_count = m_count + (static_cast<std::size_t>(!m_full));
        if (m_head == m_tail) m_full = true;
        if (m_full) m_tail = m_head;
      }
    }

    void pop(T* _data, std::size_t _n) {
      if (m_count < _n)
        throw std::out_of_range("Too many items were requested.");

      while (_n--) {
        *(_data++) = m_buffer[m_tail];
        m_tail = (++m_tail) % m_size;
        --m_count;
      }

      m_full = false;
    }

    std::size_t size()            { return m_size; }
    std::size_t count()           { return m_count; }
    bool full()                   { return m_full; }
    bool empty()                  { return !m_full; }

  private: 
    std::size_t m_size;
    std::size_t m_count = 0;
    bool m_full = false;
    std::size_t m_head = 0;
    std::size_t m_tail = 0;
    std::unique_ptr<T[]> m_buffer;
  };
} //namespace chroma
