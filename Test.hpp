#ifndef TEST_HPP
# define TEST_HPP

#include <iostream>

class Test {
  
  public:
    Test(void);
    Test(std::string name);
    Test(Test const & rhs);
    ~Test(void);

    std::string getName() const;

  private:
    std::string _name;
};

std::ostream & operator<<(std::ostream & o, Test const & fixed);

#endif