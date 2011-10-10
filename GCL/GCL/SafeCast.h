#pragma once


namespace GCL
{

  template<class T, class S>
  inline T safe_cast(S s)
  {
    T t = dynamic_cast<T>(s);
    GCLAssertMsg(t, "you are trying to up cast in the wrong type. this is very dangerous");
    return t;
  }

}
