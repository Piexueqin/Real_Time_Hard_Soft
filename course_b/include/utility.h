#ifndef RTHS_UTILITY_H
#define RTHS_UTILITY_H

#include "fths-config.h"
#include <cstdlib>
#include <cassert>
#include <cmath>


// configurable options for the frames library.
#ifdef RTHS_INLINE
    #ifdef _MSC_VER
        // Microsoft Visual C
        #define IMETHOD __forceinline
    #else
        // Some other compiler, e.g. gcc
        #define IMETHOD inline
    #endif
#else
    #define IMETHOD
#endif

// 打开或关闭边界检查。若打开，assert()仍可用-DNDEBUG关闭
#ifdef RTHS_INDEX_CHECK
    #define FRAMES_CHECKI(a) assert(a)
#else
    #define FRAMES_CHECKI(a)
#endif

namespace RTHS {

#ifdef __GNUC__
    // so that sin,cos can be overloaded and complete 
    // resolution of overloaded functions work.
    using ::sin;
    using ::cos;
    using ::exp;
    using ::log;
    using ::sin;
    using ::cos;
    using ::tan;
    using ::sinh;
    using ::cosh;
    using ::pow;
    using ::sqrt;
    using ::atan;
    using ::hypot;
    using ::asin;
    using ::acos;
    using ::tanh;
    using ::atan2;
#endif

#ifndef __GNUC__
    //only real solution : get Rall1d and varia out of namespaces.
    #pragma warning (disable:4786)

    inline double sin(double a) {
        return ::sin(a);
    }
    
    inline double cos(double a) {
        return ::cos(a);
    }
    inline double exp(double a) {
        return ::exp(a);
    }
    inline double log(double a) {
        return ::log(a);
    }
    inline double tan(double a) {
        return ::tan(a);
    }
    inline double cosh(double a) {
        return ::cosh(a);
    }
    inline double sinh(double a) {
        return ::sinh(a);
    }
    inline double sqrt(double a) {
        return ::sqrt(a);
    }
    inline double atan(double a) {
        return ::atan(a);
    }
    inline double acos(double a) {
        return ::acos(a);
    }
    inline double asin(double a) {
        return ::asin(a);
    }
    inline double tanh(double a) {
        return ::tanh(a);
    }
    inline double pow(double a,double b) {
        return ::pow(a,b);
    }
    inline double atan2(double a,double b) {
        return ::atan2(a,b);
    }
#endif  

#if (__cplusplus > 199711L)
using std::isnan;
#endif

template <class T>
class TI
{
    public:
        typedef const T& Arg; //!< Arg is used for passing the element to a function.
};

template <>
class TI<double> {
public:
    typedef double Arg;
};

template <>
class TI<int> {
public:
    typedef int Arg;
};

extern int          STREAMBUFFERSIZE;
extern int          MAXLENFILENAME;// 最长文件名
extern const double PI;
extern const double PI_2;
extern const double PI_4;
extern const double deg2rad;// PI/180的值
extern const double rad2deg;// 180/PI的值，即一弧度的值
extern double     epsilon;
extern int          VSIZE;

#ifndef _MFC_VER
#undef max
inline double max(double a,double b) {
    if (b<a) 
        return a;
    else
        return b;
}

#undef min
inline double min(double a,double b) {
    if (b<a) 
        return b;
    else
        return a;
}
#endif


#ifdef _MSC_VER
    //#pragma inline_depth( 255 )
    //#pragma inline_recursion( on )
    #define INLINE __forceinline
#else
    #define INLINE inline
#endif


inline double LinComb(double alfa,double a,
        double beta,double b ) {
            return alfa*a+beta*b;
}

inline void LinCombR(double alfa,double a,
        double beta,double b,double& result ) {
            result=alfa*a+beta*b;
         }

//! to uniformly set double, RNDouble,Vector,... objects to zero in template-classes
inline void SetToZero(double& arg) {
    arg=0;
}

//! to uniformly set double, RNDouble,Vector,... objects to the identity element in template-classes
inline void SetToIdentity(double& arg) {
    arg=1;
}

inline double sign(double arg) {
    return (arg<0)?(-1):(1);
}

inline double sqr(double arg) { return arg*arg;}
inline double Norm(double arg) {
    return fabs(  (double)arg );
}

#if defined __WIN32__ && !defined __GNUC__
inline double hypot(double y,double x) { return ::_hypot(y,x);}
inline double abs(double x) { return ::fabs(x);}
#endif

// 比较两个数是否相等，相等返回true
inline bool Equal(double a,double b,double eps=epsilon)
{
    double tmp=(a-b);
    return ((eps>tmp)&& (tmp>-eps) );
}

inline void random(double& a) {
	a = 1.98*rand()/(double)RAND_MAX -0.99;
}

inline void posrandom(double& a) {
	a = 0.001+0.99*rand()/(double)RAND_MAX;
}

inline double diff(double a,double b,double dt) {
	return (b-a)/dt;
}

inline double addDelta(double a,double da,double dt) {
	return a+da*dt;
}
}
#endif
