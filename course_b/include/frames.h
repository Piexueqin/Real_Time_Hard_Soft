// 作者：夏雪琴 003241
//文件描述：构建机器人模型所需要的基本几何类的定义
// Vector:3D向量，描述点和平移向量
// Rotation：3D旋转矩阵，描述点的旋转、点和坐标系的表达
// Frame：3D齐次变换矩阵，描述空间向量变换与齐次变换
// Wrench：6D力空间向量，一般指力和力矩组合，线动量与角动量组
// Twist：6D运动空间向量，一般指线速度和角速度组合，线加速度与角加速度组合
// Vector2：2D向量
// Rotation2：2D旋转矩阵
// Frame2：2D齐次变换矩阵

#ifndef RTHS_FRAMES_H
#define RTHS_FRAMES_H

#include"fths-config.h"
#include"utility.h"

namespace RTHS {
class Vector;
class Rotation;
class Frame;
class Wrench;
class Twist;
class Vector2;
class Rotation2;
class Frame2;

inline bool Equal(const Vector& a,const Vector& b,double eps=epsilon);
inline bool Equal(const Frame& a,const Frame& b,double eps=epsilon);
inline bool Equal(const Twist& a,const Twist& b,double eps=epsilon);
inline bool Equal(const Wrench& a,const Wrench& b,double eps=epsilon);
inline bool Equal(const Vector2& a,const Vector2& b,double eps=epsilon);
inline bool Equal(const Rotation2& a,const Rotation2& b,double eps=epsilon);
inline bool Equal(const Frame2& a,const Frame2& b,double eps=epsilon);

// 三维空间中的向量类
class Vector
{
public:
    double data[3];    
    // 创建向量和初始化
    inline Vector() {data[0]=data[1]=data[2] = 0.0;}
    inline Vector(double x,double y, double z);
    inline Vector(const Vector& arg);
    inline Vector& operator = ( const Vector& arg);

    // 访问元素：数字索引访问
    // 当没有设置NDEBUG时，对索引进行范围检测
    inline double operator()(int index) const;
    inline double& operator() (int index);

    // 获取向量的元素值
    inline double x() const;
    inline double y() const;
    inline double z() const;
    inline void x(double);
    inline void y(double);
    inline void z(double);

    // 四则运算
    inline void ReverseSign();//对data[3]进行取反操作
    inline Vector& operator-=(const Vector& arg);//运算符重载：-=
    inline Vector& operator +=(const Vector& arg);//运算符重载：＋=

    inline friend Vector operator*(const Vector& lhs,double rhs);
    inline friend Vector operator*(double lhs,const Vector& rhs);
    inline friend Vector operator/(const Vector& lhs,double rhs);
    inline friend Vector operator+(const Vector& lhs,const Vector& rhs);
    inline friend Vector operator-(const Vector& lhs,const Vector& rhs);
    inline friend Vector operator*(const Vector& lhs,const Vector& rhs);
    inline friend Vector operator-(const Vector& arg);
    inline friend double dot(const Vector& lhs,const Vector& rhs);

    // 归零化与归一化，逻辑判断
    // 归零化：Zero（）和SetToZero（）
    inline friend void SetToZero(Vector& v) ;
    inline static Vector Zero();

    // 归一化：Normalize
    double Normalize(double eps=epsilon);
    
    // 求模运算
    double Norm(double eps=epsilon) const;

    inline void Set2DXY(const Vector2& v);
    inline void Set2DYZ(const Vector2& v);
    inline void Set2DZX(const Vector2& v);
    inline void Set2DPlane(const Frame& F_someframe_XY,const Vector2& v_XY);

    //Equal，==，!=：阈值等于、完全等于、不等于
    inline friend bool Equal(const Vector& a,const Vector& b,double eps);
    inline friend bool operator==(const Vector& a,const Vector& b);
    inline friend bool operator!=(const Vector& a,const Vector& b);

    friend class Rotation;
    friend class Frame;
};

// 三维空间中的旋转矩阵
class Rotation
{
public:
    double data[9];   
    /*****旋转矩阵创建与初始化*****/
    inline Rotation() {
		*this = Rotation::Identity();
	}
    inline Rotation(double Xx,double Yx,double Zx,
                double Xy,double Yy,double Zy,
                double Xz,double Yz,double Zz);
    inline Rotation(const Vector& x,const Vector& y,const Vector& z);
    inline Rotation(const Rotation& arg);
    inline Rotation& operator=(const Rotation& arg);

    /*****矩阵运算*****/
    inline Vector operator*(const Vector& v) const;//R*V
    inline Twist operator * (const Twist& arg) const;
    inline Wrench operator * (const Wrench& arg) const;

    // 访问元素：数字索引
    inline double& operator()(int i,int j);
    inline double operator() (int i,int j) const;

    friend Rotation operator *(const Rotation& lhs,const Rotation& rhs);//R*R
    // 矩阵转置
    inline void SetInverse();
    inline Rotation Inverse() const;
    // 矩阵的转置*参数
    inline Vector Inverse(const Vector& v) const;
    inline Wrench Inverse(const Wrench& arg) const;
    inline Twist Inverse(const Twist& arg) const;
    
    inline static Rotation Identity();//单位旋转矩阵
 
    /*****旋转矩阵和单轴旋转*****/
    // 分别绕X、Y、Z轴旋转angle度
    // 旋转的方向：旋转轴指向自己，顺时针旋转
    inline static Rotation RotX(double angle);
    inline static Rotation RotY(double angle);
    inline static Rotation RotZ(double angle);

    // 旋转矩阵和轴角之间的关系
    static Rotation Rot(const Vector& rotvec,double angle);
    static Rotation Rot2(const Vector& rotvec,double angle);
    Vector GetRot() const;
	double GetRotAngle(Vector& axis,double eps=epsilon) const;

    // 旋转矩阵和欧拉角ZYZ之间的关系
    static Rotation EulerZYZ(double Alfa,double Beta,double Gamma);
    void GetEulerZYZ(double& alpha,double& beta,double& gamma) const;

    // 旋转矩阵和四元数之间的关系
    static Rotation Quaternion(double x,double y,double z, double w);
    void GetQuaternion(double& x,double& y,double& z, double& w) const;

    // 旋转矩阵与RPY角之间的关系
    static Rotation RPY(double roll,double pitch,double yaw);
    void GetRPY(double& roll,double& pitch,double& yaw) const;

    // ZYX与RPY等效
    inline static Rotation EulerZYX(double Alfa,double Beta,double Gamma) {
        return RPY(Gamma,Beta,Alfa);
    }
    inline void GetEulerZYX(double& Alfa,double& Beta,double& Gamma) const {
        GetRPY(Gamma,Beta,Alfa);
    }

    /*****Get/Set函数*****/
    // 返回值：旋转矩阵的0，3，6项，即X
     inline Vector UnitX() const {
         return Vector(data[0],data[3],data[6]);
     }

     inline void UnitX(const Vector& X) {
        data[0] = X(0);
        data[3] = X(1);
        data[6] = X(2);
     }
    // 返回值：旋转矩阵的1，4，7项，即Y
     inline Vector UnitY() const {
         return Vector(data[1],data[4],data[7]);
     }

     inline void UnitY(const Vector& X) {
        data[1] = X(0);
        data[4] = X(1);
        data[7] = X(2);
     }

    // 旋转矩阵的2，5，8项，即Z
     inline Vector UnitZ() const {
         return Vector(data[2],data[5],data[8]);
     }

     inline void UnitZ(const Vector& X) {
        data[2] = X(0);
        data[5] = X(1);
        data[8] = X(2);
     }

    /*****逻辑判断*****/
     friend bool Equal(const Rotation& a,const Rotation& b,double eps);
     friend bool operator==(const Rotation& a,const Rotation& b);
     friend bool operator!=(const Rotation& a,const Rotation& b);

     friend class Frame;     
};

bool operator==(const Rotation& a,const Rotation& b);
bool Equal(const Rotation& a,const Rotation& b,double eps=epsilon);

// 三维空间中的旋转+平移
class Frame 
{
public:
    Vector p;       
    Rotation M;

public:
    /*****Frame创建和初始化*****/
    inline Frame(const Rotation& R,const Vector& V);
    explicit inline Frame(const Vector& V);
    explicit inline Frame(const Rotation& R);
    inline Frame() {}
    inline Frame(const Frame& arg);
    void Make4x4(double* d);

    // 访问元素值
    inline double operator()(int i,int j);
    inline double operator() (int i,int j) const;

    /*****矩阵运算*****/
    inline Frame Inverse() const;
    inline Vector Inverse(const Vector& arg) const;
    inline Wrench Inverse(const Wrench& arg) const;
    inline Twist  Inverse(const Twist& arg) const;

    inline Frame& operator = (const Frame& arg);
    inline Vector operator * (const Vector& arg) const;
    inline Wrench operator * (const Wrench& arg) const;
    inline Twist operator * (const Twist& arg) const;

    inline friend Frame operator *(const Frame& lhs,const Frame& rhs);//F*F
    inline static Frame Identity();//Frame单位化

    // 改进的DH参数法建系
    static Frame DH_Craig1989(double a,double alpha,double d,double theta);
    // 标准的DH参数法建系
    static Frame DH(double a,double alpha,double d,double theta);

    /*****逻辑判断*****/
    inline friend bool Equal(const Frame& a,const Frame& b,double eps);
    inline friend bool operator==(const Frame& a,const Frame& b);
    inline friend bool operator!=(const Frame& a,const Frame& b);
};

// 某一点上线速度和角速度的组合
class Twist 
{
public:
    Vector vel; //该点线速度
    Vector rot; //该点角速度
public:

    /*****运动旋量创建和初始化*****/
    Twist():vel(),rot() {};
    Twist(const Vector& _vel,const Vector& _rot):vel(_vel),rot(_rot) {};

    inline Twist& operator-=(const Twist& arg);
    inline Twist& operator+=(const Twist& arg);

    //Get/Set 函数
    inline double& operator()(int i);

    //! For use with a const Twist
    inline double operator()(int i) const;

     double operator[] ( int index ) const
       {
	 return this->operator() ( index );
       }

     double& operator[] ( int index )
       {
	 return this->operator() ( index );
       }

    inline friend Twist operator*(const Twist& lhs,double rhs);
    inline friend Twist operator*(double lhs,const Twist& rhs);
    inline friend Twist operator/(const Twist& lhs,double rhs);
    inline friend Twist operator+(const Twist& lhs,const Twist& rhs);
    inline friend Twist operator-(const Twist& lhs,const Twist& rhs);
    inline friend Twist operator-(const Twist& arg);
    inline friend double dot(const Twist& lhs,const Wrench& rhs);
    inline friend double dot(const Wrench& rhs,const Twist& lhs);
    inline friend void SetToZero(Twist& v);
    inline friend Twist operator*(const Twist& lhs,const Twist& rhs);
    inline friend Wrench operator*(const Twist& lhs,const Wrench& rhs);

     //! @return a zero Twist : Twist(Vector::Zero(),Vector::Zero())
    static inline Twist Zero();

     //! Reverses the sign of the twist
    inline void ReverseSign();
    inline Twist RefPoint(const Vector& v_base_AB) const;

    inline friend bool Equal(const Twist& a,const Twist& b,double eps);

    inline friend bool operator==(const Twist& a,const Twist& b);
    inline friend bool operator!=(const Twist& a,const Twist& b);

    friend class Rotation;
    friend class Frame;
};

// Wrench类
class Wrench
{
public:
    Vector force;       //!< Force that is applied at the origin of the current ref frame
    Vector torque;      //!< Torque that is applied at the origin of the current ref frame
public:
    Wrench():force(),torque() {};
    Wrench(const Vector& _force,const Vector& _torque):force(_force),torque(_torque) {};

    inline Wrench& operator-=(const Wrench& arg);
    inline Wrench& operator+=(const Wrench& arg);

     //! index-based access to components, first force(0..2), then torque(3..5)
    inline double& operator()(int i);

     //! index-based access to components, first force(0..2), then torque(3..5)
     //! for use with a const Wrench
    inline double operator()(int i) const;

    double operator[] ( int index ) const
       {
	return this->operator() ( index );
       }

    double& operator[] ( int index )
       {
	return this->operator() ( index );
       }

     //! Scalar multiplication
    inline friend Wrench operator*(const Wrench& lhs,double rhs);
     //! Scalar multiplication
    inline friend Wrench operator*(double lhs,const Wrench& rhs);
     //! Scalar division
    inline friend Wrench operator/(const Wrench& lhs,double rhs);

    inline friend Wrench operator+(const Wrench& lhs,const Wrench& rhs);
    inline friend Wrench operator-(const Wrench& lhs,const Wrench& rhs);

     //! An unary - operator
    inline friend Wrench operator-(const Wrench& arg);
    inline friend void SetToZero(Wrench& v);

     //! @return a zero Wrench
    static inline Wrench Zero();

     //! Reverses the sign of the current Wrench
    inline void ReverseSign();

    inline Wrench RefPoint(const Vector& v_base_AB) const;

    inline friend bool Equal(const Wrench& a,const Wrench& b,double eps);
	 //! The literal equality operator==(), also identical.
    inline friend bool operator==(const Wrench& a,const Wrench& b);
	 //! The literal inequality operator!=().
    inline friend bool operator!=(const Wrench& a,const Wrench& b);

    friend class Rotation;
    friend class Frame;
};

// Vector2类
class Vector2
{
    double data[2];
public:
     //! Does not initialise to Zero().
     Vector2() {data[0]=data[1] = 0.0;}
     inline Vector2(double x,double y);
     inline Vector2(const Vector2& arg);

     inline Vector2& operator = ( const Vector2& arg);

     //! Access to elements, range checked when NDEBUG is not set, from 0..1
     inline double operator()(int index) const;

     //! Access to elements, range checked when NDEBUG is not set, from 0..1
     inline double& operator() (int index);

    //! Equivalent to double operator()(int index) const
	double operator[] ( int index ) const
	{
		return this->operator() ( index );
	}

	//! Equivalent to double& operator()(int index)
	double& operator[] ( int index )
	{
		return this->operator() ( index );
	}

	inline double x() const;
	inline double y() const;
	inline void x(double);
	inline void y(double);

    inline void ReverseSign();
    inline Vector2& operator-=(const Vector2& arg);
    inline Vector2& operator +=(const Vector2& arg);

    inline friend Vector2 operator*(const Vector2& lhs,double rhs);
    inline friend Vector2 operator*(double lhs,const Vector2& rhs);
    inline friend Vector2 operator/(const Vector2& lhs,double rhs);
    inline friend Vector2 operator+(const Vector2& lhs,const Vector2& rhs);
    inline friend Vector2 operator-(const Vector2& lhs,const Vector2& rhs);
    inline friend Vector2 operator*(const Vector2& lhs,const Vector2& rhs);
    inline friend Vector2 operator-(const Vector2& arg);
    inline friend void SetToZero(Vector2& v);

     //! @return a zero 2D vector.
    inline static Vector2 Zero();

    double Normalize(double eps=epsilon);

     //!  @return the norm of the vector
    double Norm(double eps=epsilon) const;

     //! projects v in its XY plane, and sets *this to these values
    inline void Set3DXY(const Vector& v);

     //! projects v in its YZ plane, and sets *this to these values
    inline void Set3DYZ(const Vector& v);

     //! projects v in its ZX plane, and sets *this to these values
    inline void Set3DZX(const Vector& v);
    inline void Set3DPlane(const Frame& F_someframe_XY,const Vector& v_someframe);
    inline friend bool Equal(const Vector2& a,const Vector2& b,double eps);
	inline friend bool operator==(const Vector2& a,const Vector2& b);
	inline friend bool operator!=(const Vector2& a,const Vector2& b);
    friend class Rotation2;
};

// Rotation2类
class Rotation2
{
    double s,c;
    //! c,s represent  cos(angle), sin(angle), this also represents first col. of rot matrix
    //! from outside, this class behaves as if it would store the complete 2x2 matrix.
public:
    //! Default constructor does NOT initialise to Zero().
    Rotation2() {c=1.0;s=0.0;}

    explicit Rotation2(double angle_rad):s(sin(angle_rad)),c(cos(angle_rad)) {}

    Rotation2(double ca,double sa):s(sa),c(ca){}

    Rotation2(const Rotation2& arg);

     inline Rotation2& operator=(const Rotation2& arg);
     inline Vector2 operator*(const Vector2& v) const;
     //!    Access to elements 0..1,0..1, bounds are checked when NDEBUG is not set
     inline double operator() (int i,int j) const;

     inline friend Rotation2 operator *(const Rotation2& lhs,const Rotation2& rhs);

     inline void SetInverse();
     inline Rotation2 Inverse() const;
     inline Vector2 Inverse(const Vector2& v) const;

     inline void SetIdentity();
     inline static Rotation2 Identity();


     //! The SetRot.. functions set the value of *this to the appropriate rotation matrix.
     inline void SetRot(double angle);

     //! The Rot... static functions give the value of the appropriate rotation matrix bac
     inline static Rotation2 Rot(double angle);

     //! Gets the angle (in radians)
     inline double GetRot() const;

     //! do not use operator == because the definition of Equal(.,.) is slightly
     //! different.  It compares whether the 2 arguments are equal in an eps-interval
     inline friend bool Equal(const Rotation2& a,const Rotation2& b,double eps);
};

// Frame2类
class Frame2
 {
public:
    Vector2 p;          //!< origine of the Frame
    Rotation2 M;        //!< Orientation of the Frame

public:

    inline Frame2(const Rotation2& R,const Vector2& V);
    explicit inline Frame2(const Vector2& V);
    explicit inline Frame2(const Rotation2& R);
    inline Frame2(void);
    inline Frame2(const Frame2& arg);
    inline void Make4x4(double* d);

    inline double operator()(int i,int j);
    inline double operator() (int i,int j) const;

    inline void SetInverse();
    inline Frame2 Inverse() const;
    inline Vector2 Inverse(const Vector2& arg) const;
    inline Frame2& operator = (const Frame2& arg);
    inline Vector2 operator * (const Vector2& arg) const;
    inline friend Frame2 operator *(const Frame2& lhs,const Frame2& rhs);
    inline void Integrate(const Twist& t_this,double frequency);
    inline void SetIdentity();
    inline static Frame2 Identity() {
        Frame2 tmp;
        tmp.SetIdentity();
        return tmp;
    }
    inline friend bool Equal(const Frame2& a,const Frame2& b,double eps);
};


IMETHOD Vector diff(const Vector& p_w_a,const Vector& p_w_b,double dt=1);

IMETHOD Vector diff(const Rotation& R_a_b1,const Rotation& R_a_b2,double dt=1);

IMETHOD Twist diff(const Frame& F_a_b1,const Frame& F_a_b2,double dt=1);

IMETHOD Twist diff(const Twist& a,const Twist& b,double dt=1);

IMETHOD Wrench diff(const Wrench& W_a_p1,const Wrench& W_a_p2,double dt=1);

IMETHOD Vector addDelta(const Vector& p_w_a,const Vector& p_w_da,double dt=1);

IMETHOD Rotation addDelta(const Rotation& R_w_a,const Vector& da_w,double dt=1);

IMETHOD Frame addDelta(const Frame& F_w_a,const Twist& da_w,double dt=1);

IMETHOD Twist addDelta(const Twist& a,const Twist&da,double dt=1);

IMETHOD Wrench addDelta(const Wrench& a,const Wrench&da,double dt=1);

#ifdef RTHS_INLINE
#include "frames.inl"
#endif
}
#endif