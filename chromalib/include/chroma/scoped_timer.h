#pragma once

#include "chroma.h"


namespace chroma {
  class scoped_timer {
  public:
    scoped_timer() : m_name("Timer") {}
    scoped_timer(std::string _name) : m_name(_name) {
      init();
    }

    ~scoped_timer() {
      auto t1 = std::chrono::high_resolution_clock::now(); 
      std::chrono::duration<float, std::milli> time_span = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(t1 - m_t0);
      std::cout << m_name << " took " <<time_span.count() << " ms."<< std::endl;
    }

    void init() {
      m_t0 = std::chrono::high_resolution_clock::now();
    }

  private:
    std::string m_name;
    std::chrono::high_resolution_clock::time_point m_t0;
  };
} // namespace chroma
