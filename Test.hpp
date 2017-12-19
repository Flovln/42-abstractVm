#ifndef TEST_HPP
# define TEST_HPP

#include <sstream>
#include <iostream>

class Test {
  
  public:
    Test(void);
    Test(std::string name);
    Test(Test const & rhs);
    ~Test(void);

    std::string getName() const;
    std::string const & toString(void) const;

  private:
    std::string _name;
};

std::ostream & operator<<(std::ostream & o, Test const & obj);

#endif