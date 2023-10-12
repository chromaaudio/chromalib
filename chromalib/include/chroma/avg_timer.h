#pragma once

#include <iostream>
#include <chrono>

namespace chroma {
  class avg_timer {
  public:
    avg_timer(std::string _name) : m_name(_name), m_count(0) {}
    
    void start() {
      m_t0 = std::chrono::high_resolution_clock::now();
    }

    void stop() {
      auto t1 = std::chrono::high_resolution_clock::now(); 
      std::chrono::duration<float, std::milli> time_span = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(t1 - m_t0);
      m_time_sum += time_span;
      ++m_count;
    }

    std::chrono::duration<float, std::milli> get_current() {
      if (m_count == 0)
        return m_time_sum; 
    
      auto current_avg = m_time_sum / m_count;
      return current_avg;
    }

    std::size_t count() {
      return m_count;
    }

    void reset() {
      m_count = 0;
      m_time_sum = std::chrono::duration<float, std::milli>(0);
    }

    void print_current() {
      std::cout << m_name << " average time: "  << get_current().count() << "ms." << std::endl;
    }
  
  private:
    std::string m_name;
    std::chrono::high_resolution_clock::time_point m_t0;
    std::chrono::duration<float, std::milli> m_time_sum;
    std::size_t m_count;
  };
} // namespace chroma