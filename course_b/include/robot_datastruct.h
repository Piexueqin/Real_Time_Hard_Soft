/*
 * DataDefine.h
 *
 *  Created on: Jun 25, 2021
 *      Author: BRT192
 */

#ifndef SRC_DATADEFINE_H_
#define SRC_DATADEFINE_H_

#include <iostream>
using namespace std;


typedef int8_t I8;
typedef int16_t I16;
typedef int32_t I32;
typedef int64_t I64;
typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef float F32;
typedef double F64;

/* 名称：姿态参数
*  说明：存储坐标系或机器人末端的姿态信息
*  单位：度
*/
typedef struct orient{
    double A;
    double B;
    double C;
}Orient;

/* 名称：位置参数
*  说明：存储机器人末端的位置，使用直角坐标来表示机器人的位置
*/
typedef struct pos{
    double X;
    double Y;
    double Z;
}Pos;

/* 名称：末端负载参数
*  说明：存储机器人关节角度值
*/
typedef struct loaddata{
    double mass;    //质量
    Pos cog;        //质心位置
    Orient aom;     //记录负载惯量主轴的方向
    double ix;      //惯量x
    double iy;      //惯量y
    double iz;      //惯量z
}LoadData;

/*
*  说明：表示外部轴位置
*/
typedef struct extax{
    double e1;
    double e2;
    double e3;
    double e4;
    double e5;
    double e6;
}Extax;

/*
*  说明：表示机器人关节角度
*/
typedef struct robax{
    double J1;
    double J2;
    double J3;
    double J4;
    double J5;
    double J6;
}Robax;

/* 名称：位姿参数
*  说明：存储机器人末端的位置和姿态
*/
typedef struct pose{
   Pos thans;   //位置
   Orient rot;  //姿态
}Pose;

/* 名称：工件参数
*  说明：wobj是工件Work Object的缩写，工件是指被机器人加工、处理、搬运的物体。
*    robhold：记录工具安装状态，数据类型为bool型，True表示工具安装在机器人上，False表示工件没有安装在机器人上，当前正在使用普通工具。
*    ufprog：用户坐标系是否移动（User Frame Programmed），bool类型。True表示用户坐标系是固定的，False表示用户坐标系是移动的，例如定义在外部变位机或者其它机器人上。
*    oframe：记录工件坐标系的原点和姿态，数据类型为pose。
*    uframe_id：用户坐标系（user frame）id，数据类型int。存储用户坐标系的id。可通过id找到对应的用户坐标系。
*/
typedef struct wobjdata{
    bool robhald;   //工件坐标系状态
    bool ufprog;    //用户坐标系的状态
    Pose oframe;    //
    int ufram_id;   //
}WobjData;

/* 名称：工具参数
*  说明：存储机器人工具参数，包括机器人所用工具的TCP，姿态及动力学参数。
*    robhold：记录工具安装状态，数据类型为bool型，True表示工具安装在机器人上，False表示工件没有安装在机器人上，当前正在使用普通工具。
*    tframe：记录工件坐标系的原点和姿态，数据类型为pose。
*    tload：记录工具的动力学参数，数据类型为loaddata。
*/
typedef struct tooldata{
    bool robhold;
    Pose tframe;
    LoadData tload;
}ToolData;

/* 名称：机器人构型参数
*  说明：用于特殊定义机器人到达某个目标点时的位姿种类。对于串联6轴机器人，同一个工作空间的目标点最多可定义8组不同的逆解，此时需要用confdata来明确指定是那一组解。
*/
typedef struct confdata{
    int cf1;
    int cf4;
    int cf6;
    int cfx;
}ConfData;

/*目标位姿参数*/
/* 名称：目标位姿参数
*  说明：存储机器人末端需要到达的位置和姿态参数，用于MOVJ，MOVL，MOVC等指令，同时包括外部轴的位置。
*/
typedef struct robtarget{
    Pos trans;      //位置
    Orient rot;     //姿态
    ConfData conf;  //机器人的构型
    Extax extax;    //外部轴信息，数据结构为[e1,e2,e3]
}RobTarget;

/* 名称：关节角度位置
*  说明：存储机器人关节角度值
*/
typedef struct jointtarget{
    Robax robax;    //机器人关节角度
    Extax extax;    //外部轴位置
}JointTarget;

/* 名称：速度参数
*  说明：存储机器人运行过程中关节角速度，末端工具线速度，空间旋转速度，外部轴线速度，外部轴角速度。
*/
typedef struct speeddata{
    double j_per;       //关节速度百分比
    double tcp_per;     //末端工具的线速度的百分比
    double tcp_rot;     //末端工具的空间旋转速度的百分比
    double exj_line;    //外部轴的线速度
    double exj_rot;     //外部轴的角速度
}SpeedData;

/* 名称：转弯区参数
*  说明：用于定义某一个运动如何结束或者说两条运动轨迹之间转弯区的大小。
*/
typedef struct zonedata
{
    double distance;    //工作空间转弯区大小
}ZoneData;

struct InnerData{
    uint8_t type;
    union
    {
        bool *value_b;  //0
        char *value_c;  //1
        int  *value_i;  //2
        double *value_d; //3
        std::string *value_s;  //4
        JointTarget *value_jointt;  //5
        SpeedData *value_speed; //6
        ZoneData *value_zone;//7
        ToolData *value_tool;//8
        WobjData *value_wobj;//9
        RobTarget *value_rob;//10
       // axispos_t *value_ap;inner
       // cartpos_t *value_cp;
       // tool_t   *value_tool;
       // coord_t *value_coord;
    }v;
};

//点动
struct jogInfo{
    int joint;//几轴
    int angle;//角度
    bool isForeward;//正转 or 反转
    bool isLongPress;//长安 or 短按
    bool isRelease;//按键释放 or 按键按下
};


//手动模式下试运行的结构体
struct Program_PointData
{
    double joints[6];       //关节数据
};


/*************************************************
 *                config.XML文件定义                    *
 *************************************************/

/***********************************************/
/* 连杆参数结构体 */
struct link_param
{
    string  name;              //连杆名称
    char    id;                //连杆序号
    char    joint_type;        //连杆关节类型
    double  dh[5];             //连杆DH参数
    double  pos_limit[2];      //连杆角度极限  [0]:min [1]:max
    double  vel_limit[2];      //连杆角速度极限
    double  acc_limit[2];      //连杆角加速度极限
    double  jerk_limit[2];     //连杆角加加速度极限
    double  mass;              //连杆质量
    double  cog[3];            //连杆质心向量  [0]:x  [1]:y [2]:z
    double  inertia[6];        //连杆质心向量  [0]:ixx [1]:ixy [2]:ixz [3]:iyy [4]:iyz [5]:izz
};

/* 工具参数结构体 */
struct tool_param
{
    string  name;                 //末端工具名称
    char    id;                   //末端工具序号
    bool    robhold;              //安装状态
    double  pos[3];               //位置
    double  orient[3];            //位姿
    double  mass;                 //末端工具质量
    double  cog[3];               //末端工具质心向量
    double  inertia[3];           //末端工具惯量矩阵
};

/*工件坐标系参数结构体*/
struct wobj_param
{
    string  name;                   //工件坐标系信息：名称
    char    id;                     //用户坐标系信息：id
    double  pos[3];                 //用户坐标系信息：位置
    double  orient[3];              //用户坐标系信息：姿态
};

/* 用户坐标系参数结构体 */
struct user_param
{
    string  name;           //工件坐标系信息：名称
    char    id;             //用户坐标系信息：id
    double  pos[3];         //用户坐标系信息：位置
    double  orient[3];      //用户坐标系信息：姿态
};


/* 轨迹规划参数结构体 */
struct traj_param
{
    char    type;           //工作空间轨迹规划信息：规划方式
    double  vel_max;        //工作空间轨迹规划信息：速度极大值
    double  acc_max;        //工作空间轨迹规划信息：加速度极大值
    double  jerk_max;       //工作空间轨迹规划信息：加加速度极大值
    double  Ta;             //工作空间轨迹规划信息：加速时间
    double  Tj;             //工作空间轨迹规划信息：加加速度百分比
};

#define _link_num            6
#define _tool_param_num      6
#define _wobj_param_num      6
#define _user_param_num      6
#define _traj_param_num      6
/* 机器人配置结构体 */
struct robot_config
{
    string              configuration;                   //机器人构型
    string              name_of_robot;                   //机器人名称
    char                num_of_links;                    //连杆个数
    char                dh_type;                         //DH参数类型
    struct link_param   link_param[_link_num];           //连杆0~n-1参数
    char                num_of_tools;                    //工具坐标
    struct tool_param   tool_param[_tool_param_num];     //工具坐标系参数
    char                num_of_wobjs;                    //工件坐标数量
    struct wobj_param   wobj_param[_wobj_param_num];     //工件坐标结构体
    char                num_of_users;                    //用户坐标系数量
    struct user_param   user_param[_user_param_num];     //用户坐标系数量1
    char                num_of_trajs;                    //轨迹规划方式数量
    struct traj_param   traj_param[_traj_param_num];     //工作空间轨迹规划参数设置
    //struct traj_param                                  //关节空间轨迹规划参数设置
};











/***********************************************/
/* 伺服设备结构体 */
/***********************************************/
struct servo_param
{
    string  name;       //伺服设备的名称
    char    dev_id;         //伺服设备的序号
    char    link_id;        //伺服设备所控制连杆的序号
    char    run_mode;       //伺服设备的运行模式
    double  pos_limit[2];      //伺服设备的位置极值 //[0] min   [1] max
    double  ratio;    //伺服设备的减速比
    char    encoder_bits;   //伺服设备的编码器位数
};
/* 伺服配置结构体 */
#define _servo_param_num 6
struct servo_config
{
    char    bus_type;                                   //总线类型
    char    num_of_servos;                              //伺服驱动数量
    float   period;                                     //总线刷新周期
    struct servo_param servo_param[_servo_param_num];   //伺服设备1~6
};




/***********************************************/
/* 附加轴结构体 */
struct aux_param
{
    string        name;          //附加轴名称
    char        type;          //附加轴类型
    double      ratio;         //附加轴减速比
    char        bus_id;             //附加轴对应的总线编号
    double      pos_limit[2];       //附加轴位置极值
    double      vel_limit[2];       //附加轴速度极值
    double      acc_limit[2];       //附加轴加速度极值
    double      jerk_limit[2];      //附加轴加加速度极值
};
/* 附加轴配置结构体 */
struct aux_config
{
    char num_of_auxs;                   //附加轴个数
    struct aux_param aux_param[2];//附加轴1~2
};






/***********************************************/
/* 连杆补偿值信息结构体 */
struct link_compensate_message
{
    string  link_name;      //连杆名称
    char      link_id;        //连杆序号
    char    joint_type;     //连杆关节类型
    double    theta_zero;     //连杆关节角度零位
    double  a_zero;         //连杆连杆长度偏差
    double  d_zero;         //连杆连杆偏置偏差
    double  ratio_zero;     //连杆减速比偏差
};

/* 工具坐标系标定信息结构体 */
struct tool_csys_message
{
    string  csys_name;      //工具坐标系名称
    char    csys_id;        //工具坐标系序号
    double  csysmatrix[12]; //工具坐标系位姿矩阵
};

/* 机器人标定结构体 */
struct Calibration_Config
{
    char                            robot_configuration;    //机器人构型
    string                          robot_name;             //机器人名称
    int                              link_num;               //连杆个数
    char                            DH_type;                //DH参数类型

    struct link_compensate_message link[7];//  连杆1~6补偿值信息
   // struct link_compensate_message  link1;                  //连杆1补偿值信息
   // struct link_compensate_message  link2;                  //连杆2补偿值信息
   // struct link_compensate_message  link3;                  //连杆3补偿值信息
   // struct link_compensate_message  link4;                  //连杆4补偿值信息
  //  struct link_compensate_message  link5;                  //连杆5补偿值信息
  //  struct link_compensate_message  link6;                  //连杆6补偿值信息
    int tcp_calibration_num;
    struct tool_csys_message        tool_csys;              //工具坐标系

    int user_coordinate_calibration_num;
    struct tool_csys_message       user_coordinate;
};








//关键结构体v1.1
/*************************************************
 *              监控线程结构体                   *
 *************************************************/
struct rc_cur_state
{
    char    mode;                   //机器人运行模式
    char    start;                  //启动位
    char    move_mode;              //运动模式
   // string  cur_project;          //当前工程名
   // string  cur_program;          //当前程序名
    char    cur_project[64];        //当前工程名
    char    cur_program[64];        //当前程序名
    int      pc;                    //当前程序指针
    int      cur_linenum;           //当前程序行号
    char    exec_status;            //程序（解释器）执行状态 停止：0；执行：1；
    char    ready;                  //程序就绪标志
    char    interp_status;          //插补器运行状态
    char    coord;                  //坐标系选择
    double  speed;                  //速度百分比
    char    tool;                   //当前参考工具坐标系
    char    usr_coord;              //作业坐标系
};

/*绝对插补：MOVABSJParam	*/
struct MOVABSJParam
{
    jointtarget ToJointPoint;       //目标关节角度值
    speeddata Speed;                //速度参数
    zonedata Zone;                  //转弯区参数
    tooldata Tool;                  //工具参数
    wobjdata Wobj;                  //工件坐标系
};

/*关节插补：MOVJParam*/
struct MOVJParam
{
    robtarget ToPoint;              //目标位姿值
    speeddata Speed;                //速度参数
    zonedata Zone;                  //转弯区参数
    tooldata Tool;                  //工具参数
    wobjdata Wobj;                  //工件坐标系
};

/*直线插补：MOVLParam  */
/*struct MOVLParam
{
    robtarget ToPoint;              //目标位姿值
    speeddata Speed;                //速度参数
    zonedata Zone;                  //转弯区参数
    tooldata Tool;                  //工具参数
    wobjdata Wobj;                  //工件坐标系
};*/
typedef MOVJParam MOVLParam;

/*圆弧插补：MOVCParam*/
struct MOVCParam{
    robtarget MidPoint;             //中间点位姿值
    robtarget ToPoint;              //目标位姿值
    speeddata Speed;                //速度参数
    zonedata Zone;                  //转弯区参数
    tooldata Tool;                  //工具参数
    wobjdata Wobj;                  //工件坐标系
};

/*JointJogParam*/
struct JointJogParam{
    char     goalJointVec;          //速度方向
    double   JointVel;              //设定关节速度百分比
    char 	 JointNum;              //运动轴号
};


/*CartJogParam*/
struct CartJogParam{
    char    velVec;                 //速度方向
    double LineVel;                 //速度百分比
    tooldata   Tool;                //工具参数
    wobjdata   Wobj;                //工件坐标系
};

/*RotJogParam*/
struct RotJogParam{
    char         rotVec;            //旋转轴方向
    double       CirVel;            //速度百分比
    tooldata     Tool;              //工具参数
    wobjdata     Wobj;              //工件坐标系
};

/*param（共用体）*/
union param
{
    JointJogParam   *JointJog;      //关节空间点动
    CartJogParam    *CartJog;       //工作空间位置点动
    RotJogParam     *RotJog;   //工作空间旋转点动
    MOVJParam       *MOVJ;          //关节插补运动
    MOVLParam       *MOVL;          //直线插补运动
    MOVCParam       *MOVC;          //圆弧插补运动
    MOVABSJParam    *MOVABSJ;       //绝对关节运动
};

/*内部指令结构体：in_rbt_inst*/
struct In_rbt_inst
{
    char instType;                  //指令类型
    param movParam;                 //运动参数

};

/*内部指令缓冲区：in_rbt_inst_buff*/
struct In_rbt_inst_buff
{
    bool instFlag;                  //指令类型
    In_rbt_inst in_rbt_inst;        //运动参数
};

/*	计算一个周期插补点（工作空间的值）：Cart_interp		*/
struct Cart_interp
{
    double cart_Pos[4][4];          //工作空间位姿
    double cart_vel[6];             //工作空间旋量
    double cart_acc[6];             //工作空间加速度
};

/*     计算一个周期插补点（连杆的值）:Joint_interp         */
struct Joint_interp
{
    double ang_pos[6];              //连杆角度
    double ang_vel[6];              //连杆角速度
    double ang_acc[6];              //连杆角加速度
    double ang_tor[6];              //连杆力矩计算值
};

/*	计算一个周期插补点（经减速比和校准补偿后转化成伺服驱动的指令值）:Servo_interp*/
struct Servo_interp
{
    /*之后写*/
};











/*************************************************
 *            共享内存结构体定义                 *
 *************************************************/
/* 伺服从站信息结构体 */
struct salve_servo
{
    char            servo_id;           //伺服从站序号
    char            servo_err;          //伺服从站出错码
    short           servo_status;       //伺服从站状态
    char            run_mode;           //伺服从站运行模式
    char            enable_flag;        //伺服从站伺服使能标志
    int             cur_site;           //伺服从站当前位置值
    int             cur_speed;          //伺服从站当前速度值
    short           cur_moment;         //伺服从站当前力矩值
    short           cur_electric;       //伺服从站当前电流值
    int             goal_site;          //伺服从站目标位置值
    int             goal_speed;         //伺服从站目标速度值
    short           goal_moment;        //伺服从站目标力矩值
    unsigned int    goal_feedforward;   //伺服从站目标加速度前馈增益
};

/* PLC/RC共享内存区 */
struct plc_rc_shm
{
    uint8_t   status;                   //状态标志字
    struct salve_servo servo1;          //伺服从站
    unsigned int io_input;              //IO数字输入映像区
    unsigned int io_output;             //IO数字输出映像区
};

/***********************************************/
/* 总线及任务状态结构体 */
struct bus_task_status_shm
{
    char bus_type;              //总线类型
    char slave_servo_status;    //从站设备运行状态
    char task_status;           //总线接口任务运行状态
};

/**********************************************/
/* 伺服状态及控制结构体 */
struct servo_status_shm
{
    char servo_num;
    struct salve_servo  servo;
};

/* IO设备结构体 */
struct io_dev_shm
{
    unsigned long long io_input;    //IO数字输入映像区
    unsigned long long io_output;   //IO数字输出映像区
};


/**********************************************/
/* 任务信息结构体 */
struct task_info
{
    string          task_name;  //任务名称
    unsigned long   task_id;    //任务id
    int             rss;        //虚拟内存
    int             vss;        //物理内存
    double          cpu;        //cpu使用率
};

/* 系统运行状态结构体 */
struct system_run_status_shm
{
    char                run_mode;           //系统运行模式
    int                 sys_err;            //系统故障信息
    short               dev_status;         //设备1状态字
        //
        //
        //
    char                running_task_num;   //运行任务个数
    struct task_info    task;               //任务1信息
        //
        //
        //

};






/*PLC/RC共享内存区*/
typedef union status
{
   struct{
        uint8_t bit0 : 2;//RC模式位。0：示教模式；1：再现模式；2：停止模式
        uint8_t bit2 : 1;//RC启动完成标志位。0：未启动完成；1：启动完成
        uint8_t bit3 : 1;//插补就绪标志位。0：未就绪；1：就绪
        uint8_t bit4 : 1;//软PLC启动完成标志位。0：初始化未完成；1：初始化完成；
        uint8_t bit5 : 1;//RC允许位。0：RC禁止启动；1：RC允许启
        uint8_t bit6 : 2;//保留位
    }status_w;
    uint8_t value;
}RC_PLC_STAT_WORD;

typedef struct
{
    I32 present_p;  //当前位置值
    I32 present_v;  //当前速度值
    I16 present_t;  //当前力矩值
    I32 present_i;  //当前电流值
}Present_Servos_Stat;

typedef struct
{
I32 target_p;//目标位置
I32 target_v;  //目标速度
I16 target_t;//目标力矩
U32 target_feedbook_v; //速度前馈
U32 target_feedbook_a;//加速度前馈增益
}Target_Servos_ctrl;

/*PLC/RC共享内存结构体*/
typedef struct
{
    RC_PLC_STAT_WORD stat;//内存状态区
    Present_Servos_Stat servos_stat[6];
    Target_Servos_ctrl servos_ctrl[6];
    U32 IO_i;//IO数字输入映像区
    U32 IO_o;//IO数字输出映像区
}RC_PLC_SHARE_BUFF;



#endif /* SRC_DATADEFINE_H_ */
