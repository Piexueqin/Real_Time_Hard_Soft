#ifndef MYARITHMETIC_H
#define MYARITHMETIC_H

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#define SERVO_CIRCLE 0x800000
#define PI 3.1416
using namespace std;
/********************************T 算法**********************************************/
struct Trap
{
    double a1,a2,a3; //位移值的表达式的系数
    double b1,b2,b3;
    double c1,c2,c3;
    double t1;//加速度时间
    double t2;//匀速时间
    double t3;//停止时间
    double vel;//能达到的最大速度
    double T_All;
    double SegNum;  //多少段
    bool flag;
};
struct Position
{
    double pos; //位置
    double vel;//速度
    double acc;//加速度
};

//time：插补的时间 表示在 time 时间的轨迹
struct Position Trap_Profile_pos(struct Trap trap,double time);
// TRAP_IN[0]:运行距离  TRAP_IN[1]:最大速度  TRAP_IN[2]: 最大加速度
struct Trap Trap_Profile_KDL(double s,double maxvel,double maxacc);
//T二次规划运行
struct Trap Trap_Profile_T(double s,double maxvel,double maxacc,double T);
//T型规划
struct Trap Trap_Profile_Luigi(double s,double maxvel,double maxacc);
//判断double类型的两个数据是否相等
bool doubleEqual(double a,double b);
//角度转换为距离
int angleTransform(double angle);
//获取梯形算法结果最大时间所在下标
int getMaxT3Index(vector<struct Trap> &array);
//距离转换为角度
double getAngle(double distance);
double getAnglePro(double distance);

/********************×××××××××××水平机器人相关算法**×××××××××****************************/
struct RobotScara
{
    double DH[4][4];
    double lead;
    double zoffset;
    double hand;
};

bool scara_ikine_Siciliano1(const RobotScara robot, const double pos[], double q[]);
bool scara_ikine_Siciliano2(const RobotScara robot, const double pose[], double q[]);

//弧度转角度
double rad2angle(double rad);
double getMovlS(double *p0, double *p1);
void getMovlPi(double *pi, double *p0, double *p1, double pos);
void getMovjPose(const double *movjP, const double *movjR, const double hand, double *movjPose);

/***********************************S 规划******************************************/
struct Para
{
   double Ta;       //Ta 加速时间
   double Tv;              //Tv 匀速时间
   double Td;              //Td 减速时间
   double Tj;              //Tj 加加速时间，减加速，减加速，减减速时间
   double q_0;             //q_0 起始位置
   double q_1;             //q_1 终点位置
   double v_0;             //v_0 起始速度
   double v_1;             //v_1 终点速度
   double v_lim;           //v_lim 能够达到的最大速度
   double a_lima;          // a_lima 能够到达的加速度
   double j_max;           // j_max 命令加加速度 或者 能够到达的最大加加速度
   double T_All;           //T_All 最大加速度
   double seg_num;         // seg_num 段数

};
struct Res
{
    double q;//位移
    double qd;//速度
    double qdd;//加速度
    double qddd;//加加速度
};
/********************
函数名：S_Profile
% 输入参数：
% s 运行距离
% vmax 最大速度
% amax 最大加速度
% jmax 最大加加速度
% 输出参数：
% [Ta, Tv, Td, Tj, q_0, q_1, v_0, v_1, v_lim, a_lima, j_max, T_All, seg_num];
% Ta 加速时间
% Tv 匀速时间
% Td 减速时间
% Tj 加加速时间，减加速，减加速，减减速时间
% q_0 起始位置
% q_1 终点位置
% v_0 起始速度
% v_1 终点速度
% v_lim 能够达到的最大速度
% a_lima 能够到达的加速度
% j_max 命令加加速度 或者 能够到达的最大加加速度
% seg_num S曲线的段数
% T_All 最大加速度
% seg_num 段数
% 注意不要改动输出参数的顺序！
% S曲线规划
*/
struct Para S_Profile(double s,double vmax,double amax,double jmax);
//盛金公式
std::vector<double>  Solve3Polynomial(double a,double b,double c,double d);
/********************************
函数名：SelectVmax
%函数功能： 选取合法的速度值
% vmax：由盛金公式函数求取的速度值的开方，有三个解，已经从小到大排序
% v_：原始速度值，时间较小时的规划的速度值，已知*****************/
double SelectVmax(std::vector<double> &a,double v_);
/********************
函数： S_Profile_T
% 输入参数：
% s 运行距离
% vmax 最大速度
% amax 最大加速度
% jmax 最大加加速度

% 输出参数：
% [Ta, Tv, Td, Tj, q_0, q_1, v_0, v_1, v_lim, a_lima, j_max, T_All, seg_num];
% Ta 加速时间
% Tv 匀速时间
% Td 减速时间
% Tj 加加速时间，减加速，减加速，减减速时间
% q_0 起始位置
% q_1 终点位置
% v_0 起始速度
% v_1 终点速度
% v_lim 能够达到的最大速度
% a_lima 能够到达的加速度
% j_max 命令加加速度 或者 能够到达的最大加加速度
% seg_num S曲线的段数
% T_All 最大加速度
% seg_num 段数
% 注意不要改动输出参数的顺序！

返回值：
    para.seg_num=-4  :"SEG 4 应比原始时间长"
    para.seg_num=-5  :"SEG 5 应比原始时间长"
    para.seg_num=-6  :"SEG 6 应比原始时间长"
    para.seg_num=-7  :"SEG 7 应比原始时间长"

**********************/
struct Para S_Profile_T(double s,double vmax_,double amax,double jmax,double T);



/**********************
* 程序当前行转为运动指令行，程序中每一个指令后面都跟随着一个Delay的指令，但该指令不需要发送到B3中执行
* 另外定义了一个vector来存放这些指令，导致实际的程序行号与使用时的vector的下标不一致,所以使用该函数来转换
*********************************/
int currentLine2sportLine(int currentLine);

#endif // MYARITHMETIC_H
