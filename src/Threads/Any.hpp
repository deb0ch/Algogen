#ifndef ANY_HPP_
# define ANY_HPP_

# include <iostream>

class Any
{
private:

  class IContainer
  {
    public:
    virtual ~IContainer()
    {}

    virtual IContainer *clone() const = 0;
  };

  template <typename T>
  class Container : public IContainer
  {
  public:
    Container(T *value)
    {
      this->_value = value;
    }

    virtual ~Container()
    {}

    virtual IContainer *clone() const
    {
      return new Container<T>(this->_value);
    }

    T *_value;
  };

public:
  Any()
  {
    this->_container = NULL;
  }

  virtual ~Any()
  {
    if (this->_container)
      delete this->_container;
  }

  template <typename T>
  Any(T *value)
  {
    this->_container = new Container<T>(value);
  }

  template <typename T>
  const T *getValue() const
  {
    const Container<T>	*tmp;

    if (this->_container)
      {
	if (!(tmp = dynamic_cast<const Container<T> * >(this->_container)))
	  {
	    return (NULL);
	  }
	return (tmp->_value);
      }
    return (NULL);
  }

  template <typename T>
  T *getValue()
  {
    Container<T>	*tmp;

    if (this->_container)
      {
	if (!(tmp = dynamic_cast< Container<T> * >(this->_container)))
	  {
	    return (NULL);
	  }
	return (tmp->_value);
      }
    return (NULL);
  }

  template <typename T>
  Any &operator=(T *value)
  {
    if (this->_container)
      delete this->_container;
    this->_container = new Container<T>(value);
    return (*this);
  }

  Any(const Any &other)
  {
    if (other._container)
      this->_container = other._container->clone();
    else
      this->_container = NULL;
  }

  Any &operator=(const Any &other)
  {
    if (this->_container)
      delete this->_container;
    if (other._container)
      this->_container = other._container->clone();
    else
      this->_container = NULL;
    return (*this);
  }

protected:
  IContainer *_container;
};

#endif /* !ANY_HPP_ */
