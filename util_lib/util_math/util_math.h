#ifndef UTIL_MATH__H 
#define UTIL_MATH__H
 

/******************************************************************************
** 宏定义函数
******************************************************************************/

//使用加减乘除替代取余运算 //当m整除n时，商为n/m; 当m不整除n时, 商为n/m+1;
#define MATH_MOD_SIMPLE(m,n)    ( 1 + ( ((n) - 1) / (m) ) ) //等价于 n % m == 0 ? (n/m) :(n/m + 1)
//n必须以m对齐,向上对齐
#define MATH_MOD_SIMPLE_ALIGN_UP_M(m,n)    ( ( 1 + ( ( (n) - 1) / (m) ) ) * (m) ) //等价于 n % m == 0 ? (n) :(n + m - n % m)
//n必须以m对齐,向下对齐
#define MATH_MOD_SIMPLE_ALIGN_DOWN_M(m,n)  ( ( (n) / (m) ) * (m) ) //等价于 n % m == 0 ? (n) :(n - n%m)

//数值交换, 宏定义方式，可避免各种数据类型数值交换时涉及指针强转换出现的问题
//通过位计算，交换数值方式1
#define MATH_SWAP(x, y)   do{\
			     x = x ^ y; \
			     y = y ^ x; \
			     x = x ^ y; \
			  }while(0)
//通过数学方法，交换数值方式2
#define MATH_SWAP2(x, y)  do{\
			     x = x + y; \
			     y = x - y; \
			     x = x - y; \
			  }while(0)

//求数值的平方
#define MATH_POW2(x)	    ( (x) * (x) )
		    


/******************************************************************************
** ABS(x)                 absolute value of x
** SIGN(x)                sign of x
** CMP(x,y)               0 if x==y; 1 if x>y; -1 if x<y
******************************************************************************/
#define MATH_ABS(x)          ( (x) >= 0 ? (x) : (-(x)) )
#define MATH_SIGN(x)         ( (x) >= 0 ? 1 : -1 )
#define MATH_CMP(x,y)        (((x) == (y)) ? 0 : (((x) > (y)) ? 1 : -1))

/******************************************************************************
** MAX2(x,y)              maximum of x and y
** MIN2(x,y)              minimum of x and y
** MAX3(x,y,z)            maximum of x, y and z
** MIN3(x,y,z)            minimun of x, y and z
** MEDIAN(x,y,z)          median of x,y,z
** MEAN2(x,y)             mean of x,y
******************************************************************************/
#define MATH_MAX2(x,y)       ( (x)>(y) ? (x):(y) )
#define MATH_MIN2(x,y)       ( (x)<(y) ? (x):(y) )
#define MATH_MAX3(x,y,z)     ( (x)>(y) ? MATH_MAX2(x,z) : MATH_MAX2(y,z) )
#define MATH_MIN3(x,y,z)     ( (x)<(y) ? MATH_MIN2(x,z) : MATH_MIN2(y,z) )
#define MATH_MEDIAN(x,y,z)   (((x)+(y)+(z) - MATH_MAX3(x,y,z)) - MATH_MIN3(x,y,z) )
#define MATH_MEAN2(x,y)      (((x)+(y)) >> 1 )

/******************************************************************************
** CLIP3(x,min,max)       clip x within [min,max]
** WRAP_MAX(x,max,min)    wrap to min if x equal max
** WRAP_MIN(x,min,max)    wrap to max if x equal min
** VALUE_BETWEEN(x,min.max)   True if x is between [min,max] inclusively.
******************************************************************************/
#define MATH_CLIP3(x,min,max)         ( (x)< (min) ? (min) : ((x)>(max)?(max):(x)) )
#define MATH_WRAP_MAX(x,max,min)      ( (x)>=(max) ? (min) : (x) )
#define MATH_WRAP_MIN(x,min,max)      ( (x)<=(min) ? (max) : (x) )
#define MATH_VALUE_BETWEEN(x,min,max) (((x)>=(min)) && ((x) <= (max)))

/******************************************************************************
** MULTI_OF_2_POWER(x,a)  whether x is multiple of a(a must be power of 2)
** CEILING_2_POWER(x,a)   ceiling x to multiple of a(a must be power of 2)
** FLOOR_2_POWER(x,a)     floor x to multiple of a(a must be power of 2)
** HIALIGN(x, a)            align x to multiple of a
**
** Example:
** CEILING_2_POWER(5,4) = 8
** FLOOR_2_POWER(5,4)   = 4
******************************************************************************/
#define MATH_MULTI_OF_2_POWER(x,a)    (!((x) & ((a) - 1) ) )
#define MATH_CEILING_2_POWER(x,a)     ( ((x) + ((a) - 1) ) & ( ~((a) - 1) ) )
#define MATH_FLOOR_2_POWER(x,a)       (  (x) & (~((a) - 1) ) )
#define MATH_HIALIGN(x, a)              ((a) * (((x) + (a) - 1) / (a)))
#define MATH_HICEILING(x, a)           (((x)+(a)-1)/(a))

/******************************************************************************
** Get the span between two unsinged number, such as
** SPAN(HI_U32, 100, 200) is 200 - 100 = 100
** SPAN(HI_U32, 200, 100) is 0xFFFFFFFF - 200 + 100
** SPAN(HI_U64, 200, 100) is 0xFFFFFFFFFFFFFFFF - 200 + 100
******************************************************************************/
#define MATH_SPAN(type, begin, end)\
({                            \
   type b = (begin);          \
   type e = (end);            \
   (type)((b >= e) ? (b - e) : (b + ((~((type)0))-e))); \
})

/******************************************************************************
** FRACTION32(de,nu)          fraction: nu(minator) / de(nominator).
** NUMERATOR32(x)              of x(x is fraction)
** DENOMINATOR32(x)           Denominator of x(x is fraction)

** represent fraction in 32 bit. LSB 16 is numerator, MSB 16 is denominator
** It is integer if denominator is 0.
******************************************************************************/
#define MATH_FRACTION32(de,nu)       ( ((de) << 16) | (nu) ) 
#define MATH_NUMERATOR32(x)          ( (x) & 0xffff)
#define MATH_DENOMINATOR32(x)        ( (x) >> 16 )  

#endif

