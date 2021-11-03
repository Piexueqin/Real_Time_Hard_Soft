#include "./include/myarithmetic.h"



// 输入参数：
// trap ： 由 velocityprofile_trap 函数计算出的结果
// trap 参数结构体
// a1 ~ c3 位移值的表达式的系数
// t1 加速时间
// t2 匀速段截止时的时间，有时 = t1
// t3 停止时间
// time：插补的时间 表示在 time 时间的轨迹
//
// 输出参数：
// pos ： 数据结构体
// pos：位置
// vel：速度
// acc：加速度

//time：插补的时间 表示在 time 时间的轨迹
struct Position Trap_Profile_pos(struct Trap trap, double time)
{
    struct Position pos;
    if(time<0)
    {
        pos.pos=0;
        pos.vel=0;
        pos.acc=0;
    }
    else if(time<trap.t1)
    {
        pos.pos=trap.a1+trap.a2*time+trap.a3*time*time;
        pos.vel=trap.a2+2*trap.a3*time;
        pos.acc=2*trap.a3;
    }
    else if(time<trap.t2)// 若 t1=t2 则此步被省略 直接跳到 下一条件 < t3
    {
        pos.pos=trap.b1+trap.b2*time+trap.b3*time*time;
           pos.vel=trap.b2+2*trap.b3*time;
           pos.acc=2*trap.b3;
    }
    else if(time<=trap.t3)
    {
        pos.pos=trap.c1+trap.c2*time+trap.c3*time*time;
        pos.vel=trap.c2+2*trap.c3*time;
        pos.acc=2*trap.c3;
    }
    return pos;
}

/*
% KDL中的梯形轨迹
% 输入参数：
% s:运行距离
% maxvel 最大速度 eg.[5]
% maxacc 最大加速度 eg.[10]
% T 消耗的总时间
% 输出参数：
% trap 参数结构体
% a1 ~ c3 位移值的表达式的系数
% t1 加速时间
% t2 匀速段截止时的时间，有时 = t1
% t3 停止时间
% vel 能够到达的最大速度

% 梯形速度规划
% 结果 被Trap_Profile_pos调用
*/

struct Trap Trap_Profile_KDL(double s,double maxvel,double maxacc)
{
    struct Trap trap;
    double t1,t2,t3, a1,a2,a3, b1,b2,b3 ,c1,c2,c3;
    bool flag;
   // double s=TRAP_IN[0];                             // 运行距离
    //double maxvel=TRAP_IN[1];                        //最大速度
   // double maxacc=TRAP_IN[2];                        //最大加速度
    t1=maxvel/maxacc;                         //初算加速时间
    double delta=s-(maxvel*maxvel)/maxacc;           //判断是否到达最大速度
    double SegNum;
    if(delta<0)
    {
        flag=false;
        t1=sqrt(s/maxacc);                          //没有到达最大速度，确定加速时间
        SegNum=2;
    }
    else
    {
        flag=true;
        SegNum=3;                                   //到达最大速度
    }
   double deltaT=(s-t1*maxvel)/maxvel;              //匀速段时间
   if(deltaT>0)                                     //如果有匀速段时间
   {
       t3=2*t1+deltaT;
       t2=t3-t1;                                    //匀速段的截止时间
   }
   else                                             //如果没有匀速段
   {
       t3=2*t1;
       t2=t1;                                       //匀速段的截止时间t2和t1一样
   }

   a3=maxacc/2;
   a2=0;
   a1=0;
   b3=0;
   b2=a2+2*a3*t1 - 2*b3*t1;
   b1 = a1+t1*(a2+a3*t1) - t1*(b2+t1*b3);
   c3=-maxacc/2;
   c2=b2+2*b3*t2 - 2.0*c3*t2;
   c1 = b1+t2*(b2+b3*t2) - t2*(c2+t2*c3);

   trap.a3=a3;trap.a2=a2;trap.a1=a1;
   trap.b3=b3;trap.b2=b2;trap.b1=b1;
   trap.c1=c1;trap.c2=c2;trap.c3=c3;

   trap.t1=t1;trap.t2=t2;trap.t3=t3;
   trap.vel=t1*maxacc;
   trap.flag=flag;
   trap.SegNum=SegNum;
   return trap;
}

struct Trap Trap_Profile_T(double s,double maxvel,double maxacc,double T)  //T二次规划运行
{
    struct Trap trap;
   // double s=TRAP_IN[0];
   // double maxvel=TRAP_IN[1];
  //  double maxacc=TRAP_IN[2];
    double v_lim, Ta, a_lim,deltaT;
    double t1,t2,t3, a1,a2,a3, b1,b2,b3 ,c1,c2,c3;

    struct Trap trap1=Trap_Profile_KDL(s,maxvel,maxacc);//求段数

    if (trap1.SegNum==2)
    {
        v_lim=2*s/T;        // 实际能到达的速度
        Ta=T/2;           // 实际的加速时间和减速时间
        a_lim=v_lim/Ta;   // 实际的加速度
        t1=Ta;            // 加（减）速时间
        t3=2*t1;          //总时间
        t2=t1;            //匀速段的截止时间（同加速段一样）
    }
    else                    //三段
    {
        a_lim=maxacc;
        //    Ta=(a_lim*T-sqrt(a_lim^2*T^2-4*a_lim*s))/2/a_lim;%Luigi书中方法P65,
        //     v_lim=a_lim*Ta;
        v_lim=(T*a_lim-sqrt(((T*a_lim)*(T*a_lim))-4*s*a_lim))/2;//必须是减号，否则不成立，同上述的Luigi方法是等价的
        Ta=v_lim/a_lim;
        t1=Ta;
        deltaT=(s-t1*v_lim)/v_lim;      //匀速段时间
        t3=2*t1+deltaT;                 //总时间
        t2=t3-t1;                       //匀速段的截止时间
    }
    a1=0;
    a2=0;
    a3=v_lim/2/Ta;
    b3=0;
    b2=v_lim;
    b1=0-v_lim*Ta/2;
    c1=s-v_lim*T*T/2/Ta;
    c2=v_lim*T/Ta;
    c3=-v_lim/2/Ta;

    trap.a3=a3;trap.a2=a2;trap.a1=a1;
    trap.b3=b3;trap.b2=b2;trap.b1=b1;
    trap.c1=c1;trap.c2=c2;trap.c3=c3;

    trap.t1=t1;trap.t2=t2;trap.t3=t3;
    trap.vel=t1*a_lim;
    //trap.flag=flag;
    return trap;
}

//Luigi中的梯形轨迹 P62
// 输入参数：
// s:运行距离
// maxvel 最大速度 eg.[5]
// maxacc 最大加速度 eg.[10]
// T 消耗的总时间
// 输出参数：
// trap 参数结构体
// a1 ~ c3 位移值的表达式的系数
// t1 加速时间
// t2 匀速段截止时的时间，有时 = t1
// t3 停止时间
// vel 能够到达的最大速度
//
// 梯形速度规划
// 结果 被S_Profile_pos调用
struct Trap Trap_Profile_Luigi(double s,double maxvel,double maxacc)
{
    double t1,t2,t3,v_lim,Ta,T;
    double a1,a2,a3,b1,b2,b3,c1,c2,c3;
    t1=maxvel/maxacc; // 初算加速时间
    double delta=s-(maxvel*maxvel)/maxacc;//判断是否到达最大速度
    bool flag;
    double deltaT;
    double SegNum;
    struct Trap trap;
    if (delta<0)
    {
        flag=false;
        t1=sqrt(s/maxacc); //没有到达最大速度，确定加速时间
        SegNum=2;
    }
    else
    {
        flag=true;//到达最大速度
        SegNum=3;
    }
    deltaT=(s-t1*maxvel)/maxvel; //匀速段时间

    if (deltaT>0)// %如果有匀速段时间
    {
        t3=2*t1+deltaT;
        t2=t3-t1; //匀速段的截止时间
    }
    else //如果没有匀速段
    {
        t3=2*t1;
        t2=t1; //匀速段的截止时间t2和t1一样
    }
    v_lim=t1*maxacc;
    Ta=t1;
    T=t3;
    a1=0;
    a2=0;
    a3=v_lim/2/Ta;
    b3=0;
    b2=v_lim;
    b1=0-v_lim*Ta/2;
    c1=s-v_lim*T*T/2/Ta;
    // c1=s-maxvel*T*T/2/Ta;
    c2=v_lim*T/Ta;
    c3=-v_lim/2/Ta;
    trap.a3=a3;trap.a2=a2;trap.a1=a1;
    trap.b3=b3;trap.b2=b2;trap.b1=b1;
    trap.c1=c1;trap.c2=c2;trap.c3=c3;
    trap.t1=t1;trap.t2=t2;trap.t3=t3;
    trap.vel=t1*maxacc;
    trap.flag=flag;
    trap.SegNum=SegNum;
    return trap;
}


bool doubleEqual(double a,double b)
{
    if(fabs(a-b)<0.000001)
        return true;
    else
        return false;
}

int angleTransform(double angle)
{
    int aCircle=SERVO_CIRCLE;
    return (aCircle*angle/360);
}

int getMaxT3Index(vector<struct Trap> &array)
{
    int index=0;
    double max=array[0].t3;
    for(int i=0;i<array.size();i++)
    {
        if(max<array[i].t3)
        {
            max=array[i].t3;
            index=i;
        }
    }
    return index;
}

double getAnglePro(double distance)
{
    if(fabs(distance)<SERVO_CIRCLE)
        return (distance/SERVO_CIRCLE)*360;
    else {
        return (double)((int)distance%SERVO_CIRCLE)/SERVO_CIRCLE*360;
    }
}

double getAngle(double distance)
{
    if(fabs(distance)<SERVO_CIRCLE)
        return (distance/SERVO_CIRCLE)*360;
}

/**************************水平机器人相关算法*************************************/
bool scara_ikine_Siciliano1(const RobotScara robot, const double pos[], double q[])
{
    double a1 = robot.DH[1][0];
    double a2 = robot.DH[2][0];
    double x = pos[0];
    double y = pos[1];
    double z = pos[2];
    double fai = pos[3];
    double pi = 3.1416;

    double alpha = atan2(y,x);
    double beta = acos((x*x + y*y + a1*a1 - a2*a2)/2/a1/sqrt(x*x + y*y));

    if (robot.hand == 0)
    {
        q[1] = -acos((x*x + y*y - a1*a1 - a2*a2)/2/a1/a2);
        q[0] = alpha + beta;
    }
    else if (robot.hand == 1)
    {
        q[1] = acos((x*x + y*y - a1*a1 - a2*a2)/2/a1/a2);
        q[0] = alpha - beta;
    }
    else
    {
       return false;
    }
    q[3] = fai - q[0] - q[1];
    q[2] = 2*PI*(z+robot.zoffset)/robot.lead;

    return true;
}

bool scara_ikine_Siciliano2(const RobotScara robot, const double pose[], double q[])
{
    double a1 = robot.DH[1][0];
    double a2 = robot.DH[2][0];
    double x = pose[0];
    double y = pose[1];
    double z = pose[2];
    double fai = pose[5];

    double alpha = atan2(y,x);
    double beta = acos((x*x + y*y + a1*a1 - a2*a2)/2.0/a1/sqrt(x*x + y*y));
    double hand = pose[6];

    if (hand == 0)
    {
        q[1] = -acos((x*x + y*y - a1*a1 - a2*a2)/2/a1/a2);
        q[0] = alpha + beta;
    }
    else if (hand == 1)
    {
        q[1] = acos((x*x + y*y - a1*a1 - a2*a2)/2/a1/a2);
        q[0] = alpha - beta;
    }
    else
    {
       return false;
    }
    q[3] = fai - q[0] - q[1];
    q[2] = 2*PI*(z+robot.zoffset)/robot.lead;

    return true;
}

double rad2angle(double rad)
{
    return rad*(180/PI);
}

double getMovlS(double *p0, double *p1)
{
    double max = 0;
    for (int i = 0; i < 3; i++)
    {
        if (fabs(p1[i]-p0[i])>max)
        {
            max=fabs(p1[i]-p0[i]);
        }
    }
    return max;
}

void getMovlPi(double *pi, double *p0, double *p1, double pos)
{
    double vec[3]={0};
    for (int i = 0; i < 3; i++)
    {
        vec[i] = (p1[i] - p0[i]) / getMovlS(p0, p1);
        pi[i] = p0[i] + pos * vec[i];
    }
}

/***********S 规划*******************/
struct Para S_Profile(double s,double vmax,double amax,double jmax)
{
    double q_0 = 0;
    double q_1 = s;
    double v_0 = 0;
    double v_1 = 0;
    double v_max = vmax;
    double a_max = amax;
    double j_max = jmax;
    double Tj,Ta,Td,T_All,a_lima,Tv,seg_num,a_lim,v_lim;

    if ((v_max)*j_max < (a_max*a_max))
    {
        Tj = sqrt((v_max - v_0) / j_max);  // 达不到a_max
        Ta = 2*Tj;
        a_lima = j_max * Tj;
    }
    else
    {
        Tj = a_max / j_max; //能够达到a_max
        Ta = Tj + (v_max) / a_max;
        a_lima = a_max;
    }
    Tv = (q_1 - q_0)/v_max - Ta;
    // 对Tv进行讨论
    if (Tv > 0)
    {
        //达到最大速度v_max，即存在匀速阶段
        if (v_max*j_max>=(a_max*a_max))
        {
            Tj=a_max/j_max;
            Ta=Tj+v_max/a_max;
            seg_num=7;
        }
        else
        {
        Tj=sqrt(v_max/j_max);
        Ta=2*Tj;
        seg_num=5;
        }
        Tv=(q_1-q_0)/v_max-Ta;
    }
    else
    {
        //没有达到最大速度v_max，不存在匀速阶段
        if ((q_1-q_0)>=(2*a_max*a_max*a_max)/(j_max*j_max))
        {
            Tj=a_max/j_max;
            Ta=Tj/2+sqrt(pow(Tj/2,2)+(q_1-q_0)/a_max);
            seg_num=6;
        }
        else
        {
            Tj=pow((q_1-q_0)/2.0/j_max,1.0/3);
            Ta=2*Tj;
            seg_num=4;
        }
        Tv=0;
    }
    a_lim=j_max*Tj;
    v_lim=(Ta-Tj)*a_lim;
    Td=Ta;
    T_All=Ta+Tv+Td;
    struct Para pa= {Ta, Tv, Td, Tj, q_0, q_1, v_0, v_1, v_lim, a_lima, j_max, T_All, seg_num};
    return pa;
}

std::vector<double>  Solve3Polynomial(double a,double b,double c,double d)
{
    std::vector<double> X123;
    /************************************************************************/
    /* 盛金公式求解三次方程的解
       德尔塔f=B^2-4AC
           这里只要了实根，虚根需要自己再整理下拿出来
    */
    /************************************************************************/
    double A=b*b-3*a*c;
    double B=b*c-9*a*d;
    double C=c*c-3*b*d;
    double f=B*B-4*A*C;
    double i_value;
    double Y1,Y2;
    if (fabs(A)<1e-6 && fabs(B)<1e-6)//公式1
    {
        X123.push_back(-b/(3*a));
        X123.push_back(-b/(3*a));
        X123.push_back(-b/(3*a));
    }
    else if (fabs(f)<1e-6)   //公式3
    {
        double K=B/A;
        X123.push_back(-b/a+K);
        X123.push_back(-K/2);
        X123.push_back(-K/2);
    }
    else if (f>1e-6)      //公式2
    {
        Y1=A*b+3*a*(-B+sqrt(f))/2;
        Y2=A*b+3*a*(-B-sqrt(f))/2;
        double Y1_value=(Y1/fabs(Y1))*pow((double)fabs(Y1),1.0/3);
        double Y2_value=(Y2/fabs(Y2))*pow((double)fabs(Y2),1.0/3);
        X123.push_back((-b-Y1_value-Y2_value)/(3*a));//虚根我不要
        //虚根还是看看吧，如果虚根的i小于0.1，则判定为方程的一根吧。。。
        i_value=sqrt(3.0)/2*(Y1_value-Y2_value)/(3*a);
        if (fabs(i_value)<1e-1)
        {
            X123.push_back((-b+0.5*(Y1_value+Y2_value))/(3*a));
        }
    }
    else if (f<-1e-6)   //公式4
    {
        double T=(2*A*b-3*a*B)/(2*A*sqrt(A));
        double S=acos(T);
        X123.push_back((-b-2*sqrt(A)*cos(S/3))/(3*a));
        X123.push_back((-b+sqrt(A)*(cos(S/3)+sqrt(3.0)*sin(S/3)))/(3*a));
        X123.push_back((-b+sqrt(A)*(cos(S/3)-sqrt(3.0)*sin(S/3)))/(3*a));
    }

   sort(X123.begin(),X123.end());  //从小到大排序

   return X123;
}

double SelectVmax(std::vector<double> &a,double v_)
{
    std::vector <double> b=a;
    double v;

    for(int i=0;i<b.size();i++)
    {
        if((b.at(i)>=0)&&(b.at(i)*b.at(i)<v_))
        {
            v=b.at(i);
            return v;
        }
    }
    return -1;
}

struct Para S_Profile_T(double s,double vmax_,double amax,double jmax,double T)
{
   struct Para para_= S_Profile(s,vmax_,amax,jmax);
   double SegNum=para_.seg_num;
   double T1=para_.Ta+para_.Tv+para_.Td;
   double A,B,C,D,vmax,Tj,Ty,Ta,Tv;
   double seg_num;
   switch ((int)SegNum) {
   case 7:
       if(T1<T)
       {
           A=jmax;
           B=pow(amax,2)-(amax*jmax*T);
           C=jmax*amax*s;
           vmax=(-B-sqrt(pow(B,2)-4*A*C))/2/A;
           Tj=amax/jmax;
           Ty=vmax/amax-Tj;
           Ta=2*Tj+Ty;
           Tv=s/vmax-Ta;
           seg_num=7;
       }
       else {
           seg_num=-7;
           //perror("SEG 7 应比原始时间长");
       }
       break;
   case 5:
       if(T1<T)
       {
           A=2/sqrt(jmax);
           B=-T;
           C=0;
           D=s;

           std::vector <double>  vmax_temp=Solve3Polynomial(A,B,C,D);
           vmax=SelectVmax(vmax_temp,vmax_);

           vmax=vmax*vmax;

            Tj=sqrt(vmax/jmax);
            Ta=2*Tj;
            Tv=s/vmax-Ta;
             seg_num=5;
           //vmax=(-B-sqrt(pow(B,2)-4*A*C))/2/A;
           //Tj=amax/jmax;
           //Ty=vmax/amax-Tj;
           //Ta=2*Tj+Ty;
           //Tv=s/vmax-Ta;
           //seg_num=7;
       }
       else {
            seg_num=-5;
           //perror("SEG 5 应比原始时间长");
       }
       break;
    case 6:
       if(T1 < T)
       {
           A=2.0*T;
           B=-T*T*jmax;
           C=4.0*s*jmax;
           amax=(-B-sqrt(B*B-4.0*A*C))/2.0/A;//一元二次方程的根，需证明唯一性

           // 求各个时间段
           Tj=amax/jmax;
           Ta=Tj/2.0+sqrt((Tj/2.0)*(Tj/2.0)+s/amax);
           Tv=0;
           // 段数
           seg_num=6;
       }
       else
            seg_num=-6;
            //perror("SEG 6 应比原始时间长");
       break;

   case 4:
          if (T1 < T)
          {
              // 由于时间拉长，需要求能够到达的最大加加速度，即重置最大速度值 jmax == j_max
              jmax=64*s/2/(T*T*T);
              // 求各个时间段
              Tj=pow((s/2/jmax),1/3.0);
             // Tj=(s/2/jmax)^(1/3);
              Ta=2*Tj;
              Tv=0;
              seg_num=4;
          }
          else
               seg_num=-4;
              //perror("SEG 4 应比原始时间长");
         break;

   }
   double a_lima,v_lim,j_max;
   a_lima=jmax*Tj;   // 实际能够到达的最大的正向加速度
   v_lim=(Ta-Tj)*a_lima; // 实际能够到达的最大的速度
   j_max = jmax; // 命令值 正向加加速度 或者 重置的加加速度

   double q_0 = 0,q_1,v_0,v_1;
   q_0 = 0;
   q_1 = s;
   v_0 = 0;
   v_1 = 0;

   double Td=Ta;
   double T_All=Ta+Tv+Td;

   struct Para pa = {Ta, Tv, Td, Tj, q_0, q_1, v_0, v_1, v_lim, a_lima, j_max, T_All, seg_num};
   return pa;
}


int currentLine2sportLine(int currentLine)
{
    return (currentLine-1)/2;
}

void getMovjPose(const double *movjP, const double *movjR, const double hand,double *movjPose)
{
    movjPose[0] = movjP[0];
    movjPose[1] = movjP[1];
    movjPose[2] = movjP[2];
    movjPose[3] = movjR[0];
    movjPose[4] = movjP[1];
    movjPose[5] = movjP[2];
    movjPose[6] = movjP[0];
    movjPose[6] = hand;
}
