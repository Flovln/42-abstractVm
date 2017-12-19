#ifndef TEST_HPP
# define TEST_HPP

#include <sstream>
#include <iostream>

class Test {
  
  public:
    enum eOperandType
    {
      Int8,
      Int16,
      Int32,
      Float,
      Double
    };

    Test(void);
    Test(std::string name);
    Test(Test const & rhs);
    ~Test(void);

    std::string getName() const;
    std::string const & toString(void) const;

    void createOperand( eOperandType type, std::string const & value ); //const;
    void createInt8( std::string const & value );// const;
    void createInt16( std::string const & value );// const;
    void createInt32( std::string const & value );// const;
    void createFloat( std::string const & value );// const;
    void createDouble( std::string const & value );// const;

  private:
    std::string _name;
};

std::ostream & operator<<(std::ostream & o, Test const & obj);

#endif