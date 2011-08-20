/*
 * Copyright (C) 2011 by Jeffrey Lim
 * Copyright (C) 2011 by Francois Coulombe
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
//============================================================================

#pragma once
#include "GCL/Macro.h"
#include <float.h>

//============================================================================

namespace GCL
{
//============================================================================

	// Generic interface
	template<typename T> class TypeData
	{
	public:
		static T Minimum()			{ return 0;	}
		static T Maximum();

		// Allows other TypeDatas to override what "Zero" means (eg. for intervals)
		static T Zero()				{ return 0; }

		static T Identity()			{ return 1;	}

		enum { IS_INTEGRAL			= false };
		enum { IS_FLOAT				= false };
		enum { IS_POD				= false };
		enum { IS_BITWISE_COPY_SAFE	= false };
		enum { IS_POINTER			= false };

		// ParameterUpcast is the type that the C compiler will use when passing parameters through "..."
		typedef T ParameterUpcast;

		// MathematicalUpcast is the type that the C compiler will use when performing basic operations
		typedef T MathematicalUpcast;

		// MathematicalFloatUpcast is the type that the C compiler will need/use when performing <cmath> functions
		typedef float MathematicalFloatUpcast;

		// ParameterType is the type most appropriate for passing this data around
		typedef const T& ParameterType;
	};

//============================================================================

	template<typename T> class TypeData<T*>
	{
	public:
		static T* Zero()				{ return 0; }

		enum { IS_FLOAT				= false };
		enum { IS_POD				= true  };
		enum { IS_BITWISE_COPY_SAFE	= true  };
		enum { IS_POINTER			= true  };

		typedef T* ParameterUpcast;
		typedef T* ParameterType;
	};

//============================================================================

	template<> class TypeData<bool>
	{
	public:
		static bool Minimum()			{ return false;	}
		static bool Maximum()			{ return true;	}
		static bool Zero()				{ return false;	}
		static bool Identity()			{ return true;	}

		enum { IS_INTEGRAL			= true };
		enum { IS_FLOAT				= false };
		enum { IS_POD				= true };
		enum { IS_BITWISE_COPY_SAFE	= true };
		enum { IS_POINTER			= false };

		typedef int ParameterUpcast;
		typedef int MathematicalUpcast;
		typedef float MathematicalFloatUpcast;
		typedef bool ParameterType;
	};

//---------------------------------------------------------------------------

	template<> class TypeData<signed char>
	{
	public:
		static signed char Minimum()	{ return -128;	}
		static signed char Maximum()	{ return  127;	}
		static signed char Zero()		{ return	0;	}
		static signed char Identity()	{ return	1;	}

		enum { IS_INTEGRAL			= true };
		enum { IS_FLOAT				= false };
		enum { IS_POD				= true };
		enum { IS_BITWISE_COPY_SAFE	= true };
		enum { IS_POINTER			= false };

		typedef int ParameterUpcast;
		typedef int MathematicalUpcast;
		typedef float MathematicalFloatUpcast;
		typedef signed char ParameterType;
	};

	template<> class TypeData<unsigned char>
	{
	public:
		static unsigned char Minimum()	{ return	0;	}
		static unsigned char Maximum()	{ return  255;	}
		static unsigned char Zero()		{ return	0;	}
		static unsigned char Identity()	{ return	1;	}

		enum { IS_INTEGRAL			= true };
		enum { IS_FLOAT				= false };
		enum { IS_POD				= true };
		enum { IS_BITWISE_COPY_SAFE	= true };
		enum { IS_POINTER			= false };

		typedef unsigned int ParameterUpcast;
		typedef unsigned int MathematicalUpcast;
		typedef float MathematicalFloatUpcast;
		typedef unsigned char ParameterType;
	};

//---------------------------------------------------------------------------

	template<> class TypeData<wchar_t>
	{
	public:
		enum { IS_INTEGRAL			= true };
		enum { IS_FLOAT				= false };
		enum { IS_POD				= true };
		enum { IS_BITWISE_COPY_SAFE	= true };
		enum { IS_POINTER			= false };

		typedef wchar_t ParameterUpcast;
		typedef wchar_t ParameterType;
		typedef int		MathematicalUpcast;
	};

	template<> class TypeData<signed short>
	{
	public:
		static signed short Minimum()	{ return -32768; }
		static signed short Maximum()	{ return  32767; }
		static signed short Zero()		{ return	  0; }
		static signed short Identity()	{ return	  1; }

		enum { IS_INTEGRAL			= true };
		enum { IS_FLOAT				= false };
		enum { IS_POD				= true };
		enum { IS_BITWISE_COPY_SAFE	= true };
		enum { IS_POINTER			= false };

		typedef int ParameterUpcast;
		typedef int MathematicalUpcast;
		typedef float MathematicalFloatUpcast;
		typedef signed short ParameterType;
	};

	template<> class TypeData<unsigned short>
	{
	public:
		static unsigned short Minimum()		{ return 0;		}
		static unsigned short Maximum()		{ return 65535;	}
		static unsigned short Zero()		{ return 0;		}
		static unsigned short Identity()	{ return 1;		}

		enum { IS_INTEGRAL			= true };
		enum { IS_FLOAT				= false };
		enum { IS_POD				= true };
		enum { IS_BITWISE_COPY_SAFE	= true };
		enum { IS_POINTER			= false };

		typedef unsigned int ParameterUpcast;
		typedef unsigned int MathematicalUpcast;
		typedef float MathematicalFloatUpcast;
		typedef unsigned short ParameterType;
	};

//---------------------------------------------------------------------------

	template<> class TypeData<signed int>
	{
	public:
		static signed int Minimum()		{ return 0x80000000;	}
		static signed int Maximum()		{ return 0x7FFFFFFF;	}
		static signed int Zero()		{ return 0;				}
		static signed int Identity()	{ return 1;				}

		enum { IS_INTEGRAL			= true };
		enum { IS_FLOAT				= false };
		enum { IS_POD				= true };
		enum { IS_BITWISE_COPY_SAFE	= true };
		enum { IS_POINTER			= false };

		typedef int ParameterUpcast;
		typedef int MathematicalUpcast;
		typedef float MathematicalFloatUpcast;
		typedef signed int ParameterType;
	};

	template<> class TypeData<unsigned int>
	{
	public:
		static unsigned int Minimum()	{ return 0;				}
		static unsigned int Maximum()	{ return 0xFFFFFFFF;	}
		static unsigned int Zero()		{ return 0;				}
		static unsigned int Identity()	{ return 1;				}

		enum { IS_INTEGRAL			= true };
		enum { IS_FLOAT				= false };
		enum { IS_POD				= true };
		enum { IS_BITWISE_COPY_SAFE	= true };
		enum { IS_POINTER			= false };

		typedef unsigned int ParameterUpcast;
		typedef unsigned int MathematicalUpcast;
		typedef float MathematicalFloatUpcast;
		typedef unsigned int ParameterType;
	};

//---------------------------------------------------------------------------

	template<> class TypeData<signed long>
	{
	public:
		static signed long Minimum()	{ return 0x80000000;	}
		static signed long Maximum()	{ return 0x7FFFFFFF;	}
		static signed long Zero()		{ return 0;				}
		static signed long Identity()	{ return 1;				}

		enum { IS_INTEGRAL			= true };
		enum { IS_FLOAT				= false };
		enum { IS_POD				= true };
		enum { IS_BITWISE_COPY_SAFE	= true };
		enum { IS_POINTER			= false };

		typedef long ParameterUpcast;
		typedef long MathematicalUpcast;
		typedef float MathematicalFloatUpcast;
		typedef signed long ParameterType;
	};

	template<> class TypeData<unsigned long>
	{
	public:
		static unsigned long Minimum()	{ return 0;				}
		static unsigned long Maximum()	{ return 0xFFFFFFFF;	}
		static unsigned long Zero()		{ return 0;				}
		static unsigned long Identity()	{ return 1;				}

		enum { IS_INTEGRAL			= true };
		enum { IS_FLOAT				= false };
		enum { IS_POD				= true };
		enum { IS_BITWISE_COPY_SAFE	= true };
		enum { IS_POINTER			= false };

		typedef unsigned long ParameterUpcast;
		typedef unsigned long MathematicalUpcast;
		typedef float MathematicalFloatUpcast;
		typedef unsigned long ParameterType;
	};

//---------------------------------------------------------------------------

	template<> class TypeData<signed long long>
	{
	public:
		static signed long long Minimum()	{ return 0x8000000000000000LL;	}
		static signed long long Maximum()	{ return 0x7FFFFFFFFFFFFFFFLL;	}
		static signed long long Zero()		{ return 0;						}
		static signed long long Identity()	{ return 1;						}

		enum { IS_INTEGRAL			= true };
		enum { IS_FLOAT				= false };
		enum { IS_POD				= true };
		enum { IS_BITWISE_COPY_SAFE	= true };
		enum { IS_POINTER			= false };

		typedef long long ParameterUpcast;
		typedef long long MathematicalUpcast;
		typedef double MathematicalFloatUpcast;
		typedef signed long long ParameterType;
	};

	template<> class TypeData<unsigned long long>
	{
	public:
		static unsigned long long Minimum()		{ return 0;						}
		static unsigned long long Maximum()		{ return 0xFFFFFFFFFFFFFFFFLL;	}
		static unsigned long long Zero()		{ return 0;						}
		static unsigned long long Identity()	{ return 1;						}

		enum { IS_INTEGRAL			= true };
		enum { IS_FLOAT				= false };
		enum { IS_POD				= true };
		enum { IS_BITWISE_COPY_SAFE	= true };
		enum { IS_POINTER			= false };

		typedef unsigned long long ParameterUpcast;
		typedef unsigned long long MathematicalUpcast;
		typedef double MathematicalFloatUpcast;
		typedef unsigned long long ParameterType;
	};

//---------------------------------------------------------------------------

	template<> class TypeData<float>
	{
	public:
		static float Minimum()		{ return -FLT_MAX;	}
		static float Maximum()		{ return FLT_MAX;	}
		static float Zero()			{ return 0.0f;		}
		static float Identity()		{ return 1.0f;		}

		enum { IS_INTEGRAL			= false };
		enum { IS_FLOAT				= true };
		enum { IS_POD				= true };
		enum { IS_BITWISE_COPY_SAFE	= true };
		enum { IS_POINTER			= false };

		typedef double	ParameterUpcast;
		typedef float	MathematicalUpcast;
		typedef float	MathematicalFloatUpcast;
		typedef float	ParameterType;
	};

//---------------------------------------------------------------------------

	template<> class TypeData<double>
	{
	public:
		static double Minimum()			{ return -DBL_MAX;	}
		static double Maximum()			{ return DBL_MAX;	}
		static double Zero()			{ return 0.0;		}
		static double Identity()		{ return 1.0;		}

		enum { IS_INTEGRAL			= false };
		enum { IS_FLOAT				= true };
		enum { IS_POD				= true };
		enum { IS_BITWISE_COPY_SAFE	= true };
		enum { IS_POINTER			= false };

		typedef double	ParameterUpcast;
		typedef double	MathematicalUpcast;
		typedef double	MathematicalFloatUpcast;
		typedef double	ParameterType;
	};

//============================================================================
} // namespace GCL
//============================================================================
