#include <iostream>
#include <vector>

#include "./include/robot_datastruct.h"
#include "../course_c/xenomaitask.h"
#include "../course_d/include/sem_shm.h"
#include "../course_d/include/print_debug_information.h"
#include "./include/read_xml_function.h"
#include "./include/network.h"
#include "./include/myarithmetic.h"

#include "./include/mycommand.h"
#include "./include/myvisitor.h"

#include "./include/frames.h"

#include <alchemy/sem.h>
RT_SEM  g_rt_sem;  //xenomai 信号量
RT_SEM  g_rt_sem_B2;  //xenomai 信号量
RT_SEM  g_rt_sem_B3_to_B2;  //xenomai 信号量
RT_SEM  g_rt_sem_StartRun;  //xenomai 信号量

#define SINGLE_ANGLE 360
#define XMLMAXV_INCREASE 100000
#define SINGLE_CIRCLE 0.001

//内部指令结构体   Add by mushroom 2021/9/4
vector<struct In_rbt_inst> _G_instList;

static robot_config g_robot_config;  //机器人配置结构体
static servo_config g_servo_config; //伺服配置结构体
static aux_config g_add_ax_config; //附加轴配置结构体
static Calibration_Config g_calibration_config;//标定配s置

static Semaphore g_semaphore; //与c2同步信号量
static Semaphore g_sendthreadsem;//唤醒信息反馈给示教器线程信号量
static SharedMemory g_share_memory;//共享内存大类
static struct rc_cur_state  g_rc_state;//监控线程结构体
static RC_PLC_SHARE_BUFF *g_rc_plc_share_memory = nullptr;//rc_plc共享内存
static MyServerTCP g_server_tcp;//服务器类
struct In_rbt_inst_buff g_irib;//内部指令缓冲区

//Add by mushroom 2021/9/24
char g_wakeup_b3;//判断唤醒b3的类型 长按:0x1 movabsj:0x2 回到原点:0x3 MOVL:0x4 试运行:0x5
struct jogInfo g_jog_info;//长按数据，轴、正反转、速度
double g_jog_speed_percent = 0.1;//电机速度
Present_Servos_Stat g_servo_current_data[6];//记录电机的当前位置等参数
struct Program_PointData g_program_try_pointData;//试运行数据
int g_run_current_lineno;

CodeModel g_codeModel;							//    Add by mushroom 2021/8/27
MyDataVisitor g_dataVisitor(&g_codeModel);			//    Add by mushroom 2021/8/27
MyProgramVisitor g_programVisitor(&g_codeModel);	//    Add by mushroom 2021/8/27

void task_function_third(void *arg)
{
    printf("task_function\n") ;
    vector<struct Trap> trapList;//梯形轨迹规划    Add by mushroom 2021/9/4
    struct Position posList[6];//梯形轨迹规划结果    Add by mushroom 2021/9/4
    double t = 0;//插补运行时间
    double distance[6];
    double maxV = 0;
    double maxAcc = 0;
    double curPosition[6];//电机当前位置，从d2中获取
    double xmlMaxV = 0;
    double xmlMaxAcc = 0;//最大速度、最大加速度，从机型xml文件中获取
    bool trapFlag = false;//判断插补是否完成
    bool trapIsEnd = false;//判断梯形规划算法是否计算
    int runCount = 0;//统计控制电机次数
    int maxT3Index = 0;//获取梯形规划时间同步中的最大时间
    bool aixForeward[6];//记录各个轴正反转状态

    /**********long press****************/
    struct Trap jogTrap;//单个轴的梯形规划
    struct Position jogPos;//单个轴的梯形规划结果
    double posGap;//记录相邻两次梯形规划结果位置的差
    double prevPos;//记录梯形规划结果位置
    bool jogDecelerateFlag;//用于判断按键释放后，电机继续运行一个减速运动的标志位
    bool jogTimeFlag;//用于判断是加速阶段还是匀速阶段转换到的减速阶段

    /***********scara robot need params****************/
    struct RobotScara robot0603;//水平机器人机型
    robot0603.DH[0][0] = 0;
    robot0603.DH[0][1] = 0;
    robot0603.DH[0][2] = 0;
    robot0603.DH[0][3] = 0;

    robot0603.DH[1][0] = 0.325;
    robot0603.DH[1][1] = 0;
    robot0603.DH[1][2] = 0.063;
    robot0603.DH[1][3] = 0;

    robot0603.DH[2][0] = 0.275;
    robot0603.DH[2][1] = 0;
    robot0603.DH[2][2] = -0.124;
    robot0603.DH[2][3] = 0;

    robot0603.DH[3][0] = 0;
    robot0603.DH[3][1] = 0;
    robot0603.DH[3][2] = 0;
    robot0603.DH[3][3] = 0;

    robot0603.lead = 0.016;
    robot0603.zoffset = 0.061;
    robot0603.hand = 0;

    struct Trap trapMovl;
    struct Position posMovl;
    bool isMovlOrigin = false;
    double movlS;//movl所运行距离
    double movlP0[3];//空间起点
    double movlP1[3];//空间终点
    double movlPi[4] = {0};
    double radQ[4];//空间位姿矩阵

    /****Movj****/
    struct Trap trapMovj;
    struct Position posMovj;
    double movjP0[3]={0};
    double movjP1[3]={0};
    double movjR0[3]={0};
    double movjR1[3]={0};
    double movjPose0[7]={0};
    double movjPose1[7]={0};
    double hand;
    double movjQ0[4]={0};
    double movjQ1[4]={0};

    while(1)
    {
#if 1
        if(g_irib.instFlag)
        {
            cout << "no command" << endl;
            printf("g_rc_plc_share_memory->stat.status_w.bit3=%d\n", g_rc_plc_share_memory->stat.status_w.bit3);
            //堵塞等待内部指令缓冲区写入指令和接收指令
            cout << "wait b2 signal" << endl;
            rt_sem_p(&g_rt_sem, TM_INFINITE);
        }
        else
        {
            if(g_rc_plc_share_memory->stat.status_w.bit3 == 1)
            {
                g_semaphore.Semaphore_op(0, -1, 1);  //信号量  减一 等待C2进程数据处理
                //获取电机当前值
                for (int i = 0; i < 6; i++)
                {
                    g_servo_current_data[i].present_p = g_rc_plc_share_memory->servos_stat[i].present_p;//电机当前位置
//                    cout << "g_servo_current_data[" << i << "].present_p" << g_servo_current_data[i].present_p << endl;
                }
                if (g_wakeup_b3 == 0x2)//判断是b2唤醒的b3
                {
                    if (!trapIsEnd)//未规划
                    {
                        xmlMaxV = g_robot_config.link_param[0].vel_limit[1] * XMLMAXV_INCREASE;
                        xmlMaxAcc = g_robot_config.link_param[0].acc_limit[1] * XMLMAXV_INCREASE;
                        cout << "xmlMaxV=" << xmlMaxV << endl;
                        cout << "xmlMaxAcc=" << xmlMaxAcc << endl;
                        distance[0] = angleTransform(g_irib.in_rbt_inst.movParam.MOVABSJ->ToJointPoint.robax.J1 - getAnglePro(g_servo_current_data[0].present_p));//1轴要移动的距离
                        distance[1] = angleTransform(g_irib.in_rbt_inst.movParam.MOVABSJ->ToJointPoint.robax.J2 - getAnglePro(g_servo_current_data[1].present_p));//2轴要移动的距离
                        distance[2] = angleTransform(g_irib.in_rbt_inst.movParam.MOVABSJ->ToJointPoint.robax.J3 - getAnglePro(g_servo_current_data[2].present_p));//3轴要移动的距离
                        distance[3] = angleTransform(g_irib.in_rbt_inst.movParam.MOVABSJ->ToJointPoint.robax.J4 - getAnglePro(g_servo_current_data[3].present_p));//4轴要移动的距离
                        distance[4] = angleTransform(g_irib.in_rbt_inst.movParam.MOVABSJ->ToJointPoint.robax.J5 - getAnglePro(g_servo_current_data[4].present_p));//5轴要移动的距离
                        distance[5] = angleTransform(g_irib.in_rbt_inst.movParam.MOVABSJ->ToJointPoint.robax.J6 - getAnglePro(g_servo_current_data[5].present_p));//6轴要移动的距离
                        cout << "distance[0]=" << g_irib.in_rbt_inst.movParam.MOVABSJ->ToJointPoint.robax.J1 << "  distance[1]=" << g_irib.in_rbt_inst.movParam.MOVABSJ->ToJointPoint.robax.J2 << endl;
                        maxV = xmlMaxV * g_irib.in_rbt_inst.movParam.MOVABSJ->Speed.j_per/100;//转动最大速度=机型最大速度*速度%
                        maxV = xmlMaxV * g_jog_speed_percent;
                        maxAcc = xmlMaxAcc * g_jog_speed_percent;//最大加速度=机型最大加速度
//                        cout << "梯形算法规划中.........." << endl;
                        //第一次计算
                        for (int i = 0; i < 6; i++)
                        {
                            if (distance[i] < 0)
                            {
                                aixForeward[i] = false;
                            }
                            else
                            {
                                aixForeward[i] = true;
                            }
                            struct Trap trap = Trap_Profile_KDL(fabs(distance[i]), maxV, maxAcc);
                            trapList.push_back(trap);
                        }
                        maxT3Index = getMaxT3Index(trapList);//找到最大运行时间的下标
                        //第二次计算，让所有轴运行时间相等
                        for (int i = 0; i < 6; i++)
                        {
                            if(i == maxT3Index)
                                continue;
                            struct Trap trap = Trap_Profile_T(fabs(distance[i]), maxV, maxAcc, trapList[maxT3Index].t3);
                            trapList[i] = trap;
//                            cout << "trapList[" << i << "].t3=" << trapList[i].t3 <<endl;
                        }
                        t = 0;
                        trapFlag = false;//插补未完成
                        trapIsEnd = true;//规划完成
                        for (int i = 0; i < 6; i++)
                        {
                            curPosition[i] = g_servo_current_data[i].present_p;
                            g_rc_plc_share_memory->servos_ctrl[i].target_p = g_servo_current_data[i].present_p;//目标位置
                            g_rc_plc_share_memory->servos_ctrl[i].target_v = 0;//目标速度
                        }
                    }
                    else
                    {
                        //插补中
                        if (t <= trapList[maxT3Index].t3)
                        {
                            for (int i = 0; i < 6; i++)
                            {
                                posList[i] = Trap_Profile_pos(trapList[i], t);
//                            		cout << "posList[" << i << "].pos=" << posList[i].pos <<endl;
                            }
                            runCount += 1;
                            t += SINGLE_CIRCLE;
                            for (int i = 0; i < 6; i++)
                            {
                                if (aixForeward[i])
                                {
                                    g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[i] + posList[i].pos;//目标位置 正转
                                    g_rc_plc_share_memory->servos_ctrl[i].target_v = posList[i].vel;//目标速度
                                }
                                else
                                {
                                    g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[i] - posList[i].pos;//目标位置 反转
                                    g_rc_plc_share_memory->servos_ctrl[i].target_v = posList[i].vel;//目标速度
                                }

                            }
                        }
                        else
                        {
//                            cout << "trapList[" << maxT3Index << "].t3=" << trapList[maxT3Index].t3 <<endl;
//                            for (int i = 0; i < 6; i++)
//                            {
//                                cout << "posList[" << i << "].pos=" <<posList[i].pos <<endl;
//                                if (posList[i].pos < fabs(distance[i])+10||posList[i].pos>fabs(distance[i])-10)
//                                {
                                    trapFlag = true;//插补结束
                                    g_irib.instFlag = true;//变为无指令
//                                }
//                            }
                        }
                    }
                    if(trapFlag && g_irib.instFlag)
                    {
                        trapList.clear();//清空
                        cout << "runCount=" << runCount <<endl;
                        runCount = 0;
                        trapIsEnd = false;
                        g_rc_plc_share_memory->stat.status_w.bit3 = 0;
                        g_wakeup_b3 = 0x0;
//                        cout << "完成插补，向c2发送就绪位变为bit3=0" << endl;
//                			usleep(40);//为了b2能够运行阻塞等待的语句
                        rt_sem_broadcast(&g_rt_sem_B3_to_B2);
                    }
                }
                else if (g_wakeup_b3 == 0x1)//长按
                {
                    if(!trapIsEnd)//未规划
                    {
                        xmlMaxV = g_robot_config.link_param[0].vel_limit[1] * XMLMAXV_INCREASE;
                        xmlMaxAcc = g_robot_config.link_param[0].acc_limit[1] * XMLMAXV_INCREASE * 10;
                        cout << "xmlMaxV=" << xmlMaxV <<endl;
                        cout << "xmlMaxAcc=" << xmlMaxAcc <<endl;
                        jogDecelerateFlag = false;
                        distance[g_jog_info.joint] = angleTransform(g_jog_info.angle);
                        cout << "distance[0]" << g_jog_info.joint<< "=" <<distance[g_jog_info.joint] << endl;
                        maxV = xmlMaxV * g_jog_speed_percent;//转动最大速度=机型最大速度*速度% 1000000
                        maxAcc = xmlMaxAcc;//最大加速度=机型最大加速度  1000000
                        posGap = 0;
                        cout << "maxV=" << maxV <<endl;
                        cout << "maxAcc=" << maxAcc <<endl;
                        jogTrap = Trap_Profile_KDL(fabs(distance[g_jog_info.joint]), maxV, maxAcc);
                        cout << "jogTrap.t1=" << jogTrap.t1 << "jogTrap.t2=" << jogTrap.t2 << "jogTrap.t3=" << jogTrap.t3 << endl;
                        t = 0;
                        trapFlag = false;//插补未完成
                        trapIsEnd = true;//规划完成
                        for (int i = 0; i < 6; i++)
                        {
                            curPosition[i] = g_servo_current_data[i].present_p;
                            g_rc_plc_share_memory->servos_ctrl[i].target_p = g_servo_current_data[i].present_p;//目标位置
                            g_rc_plc_share_memory->servos_ctrl[i].target_v = 0;//目标速度
                        }
                    }
                    else
                    {
//                        t += SINGLE_CIRCLE;
                        if(g_jog_info.isRelease)//按键未释放
                        {
                            if(t < jogTrap.t2)//未达到减速时间段
                            {
                                jogPos = Trap_Profile_pos(jogTrap, t);
                            }
                            posGap += jogPos.vel * SINGLE_CIRCLE;
                            runCount += 1;
                            t += SINGLE_CIRCLE;
                            //改变电机位置
                            for (int i = 0; i < 6; i++)
                            {
                                if (i == g_jog_info.joint)
                                {
                                    if (g_jog_info.isForeward)
                                    {
//                                        PRINTF_INFO_MESSAGE("正转");
                                        g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[g_jog_info.joint] + posGap;//转动轴的目标位置 正转
                                    }
                                    else
                                    {
//                                        PRINTF_INFO_MESSAGE("反转");
                                        g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[g_jog_info.joint] - posGap;//转动轴的目标位置 反转
                                    }
                                    continue;
                                }
                                g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[i];//其他轴目标位置不变
                            }
                        }
                        else//按键释放
                        {
                            if(!jogDecelerateFlag)
                            {
                                jogDecelerateFlag = true;
                                if (t <= jogTrap.t1)
                                {
                                    cout << "jogTrap.t1=" << jogTrap.t1 << endl;
                                    cout << "未达到匀速阶段就就进行减速阶段" << endl;
                                    t -= SINGLE_CIRCLE;
                                    jogTimeFlag = true;
                                    jogPos = Trap_Profile_pos(jogTrap, t);
                                    posGap += jogPos.vel * SINGLE_CIRCLE;
                                }
                                else
                                {
                                    cout << "jogTrap.t2=" << jogTrap.t2 << endl;
                                    cout << "达到匀速阶段就就进行减速阶段" << endl;
                                    jogTimeFlag = false;
                                    t = jogTrap.t2;
                                    t += SINGLE_CIRCLE;
                                    jogPos = Trap_Profile_pos(jogTrap, t);
                                    posGap += jogPos.vel * SINGLE_CIRCLE;
                                }

                                for (int i = 0; i < 6; i++)//减速前运行的最后一次匀速阶段的距离
                                {
                                    if (i == g_jog_info.joint)
                                    {
                                        if (g_jog_info.isForeward)
                                        {
                                            g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[g_jog_info.joint] + posGap;//转动轴的目标位置 正转
                                        }
                                        else
                                        {
                                            g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[g_jog_info.joint] - posGap;//转动轴的目标位置 反转
                                        }
                                        continue;
                                    }
                                    g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[i];//其他轴目标位置不变
                                }
                                runCount += 1;
                            }
                            else//点动结束阶段的减速运动
                            {
//                                t += SINGLE_CIRCLE;
                                if(t <= jogTrap.t3 && !jogTimeFlag)
                                {
                                    t += SINGLE_CIRCLE;
                                    jogPos = Trap_Profile_pos(jogTrap, t);
                                    posGap += jogPos.vel * SINGLE_CIRCLE;
                                    runCount += 1;
                                    //改变电机位置
                                    for (int i = 0; i < 6; i++)
                                    {
                                        if (i == g_jog_info.joint)
                                        {
                                            if(g_jog_info.isForeward)
                                            {
                                                g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[g_jog_info.joint] + posGap;//转动轴的目标位置 正转
//                                                cout << "alex[" << g_jog_info.joint << "]=" << getAnglePro(g_servo_current_data[g_jog_info.joint].present_p + posGap) <<endl;
                                            }
                                            else
                                            {
                                                g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[g_jog_info.joint] - posGap;//转动轴的目标位置 反转
//                                                cout << "alex[" << g_jog_info.joint << "]=" << getAnglePro(g_servo_current_data[g_jog_info.joint].present_p - posGap) <<endl;
                                            }
                                            continue;
                                        }
                                        g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[i];//其他轴目标位置不变
                                    }
                                }
                                else if (t <= jogTrap.t1 && t >= 0)
                                {
                                    t -= SINGLE_CIRCLE;
                                    jogPos = Trap_Profile_pos(jogTrap, t);
                                    posGap += jogPos.vel * SINGLE_CIRCLE;
                                    runCount += 1;
                                    //改变电机位置
                                    for (int i = 0; i < 6; i++)
                                    {
                                        if (i == g_jog_info.joint)
                                        {
                                            if(g_jog_info.isForeward)
                                            {
                                                g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[g_jog_info.joint] + posGap;//转动轴的目标位置 正转
//                                                cout << "alex[" << g_jog_info.joint << "]=" << getAnglePro(g_servo_current_data[g_jog_info.joint].present_p + posGap) <<endl;
                                            }
                                            else
                                            {
                                                g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[g_jog_info.joint] - posGap;//转动轴的目标位置 反转
//                                                cout << "alex[" << g_jog_info.joint << "]=" << getAnglePro(g_servo_current_data[g_jog_info.joint].present_p - posGap) <<endl;
                                            }
                                            continue;
                                        }
                                        g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[i];//其他轴目标位置不变
                                    }
                                }
                                else
                                {
                                    trapFlag = true;//插补结束
                                    g_irib.instFlag = true;//变为无指令
                                }
                            }
                        }
                    }
                    if(trapFlag && g_irib.instFlag)
                    {
                        cout << "runCount=" << runCount <<endl;
//                        if(g_jog_info.isForeward)  printf("[%d]axle:%lf\n",g_jog_info.joint,getAnglePro(g_servo_current_data[g_jog_info.joint].present_p+posGap));
//                        else printf("[%d]axle:%lf\n",g_jog_info.joint,getAnglePro(g_servo_current_data[g_jog_info.joint].present_p-posGap));
                        runCount = 0;
                        trapIsEnd = false;
                        g_rc_plc_share_memory->stat.status_w.bit3 = 0;
                        cout << "完成插补，向c2发送就绪位变为bit3=0(b1wakeupb3)" << endl;
                        g_wakeup_b3 = 0;
                    }
                }
                //复位模块
                else if (g_wakeup_b3 == 0x3)//判断是b2唤醒的b3
                {
                    if(!trapIsEnd)//未规划
                    {
                        xmlMaxV = g_robot_config.link_param[0].vel_limit[1] * XMLMAXV_INCREASE;
                        xmlMaxAcc = g_robot_config.link_param[0].acc_limit[1] * XMLMAXV_INCREASE;
                        cout << "xmlMaxV=" << xmlMaxV <<endl;
                        cout << "xmlMaxAcc=" << xmlMaxAcc <<endl;
                        distance[0] = g_servo_current_data[0].present_p - 0;//1轴要移动的距离
                        distance[1] = g_servo_current_data[1].present_p - 0;//2轴要移动的距离
                        distance[2] = g_servo_current_data[2].present_p - 0;//3轴要移动的距离
                        distance[3] = g_servo_current_data[3].present_p - 0;//4轴要移动的距离
                        distance[4] = g_servo_current_data[4].present_p - 0;//5轴要移动的距离
                        distance[5] = g_servo_current_data[5].present_p - 0;//6轴要移动的距离
                        cout << "distance[0]=" << distance[0] << "  distance[1]=" <<distance[1] <<endl;
                        maxV = 1000000;//转动最大速度=机型最大速度*速度%
                        maxAcc = 1000000;//最大加速度=机型最大加速度
                        cout << "梯形算法规划中.........." << endl;
                        //第一次计算
                        for (int i = 0; i < 6; i++)
                        {
                            if (distance[i] < 0)
                            {
                                aixForeward[i] = false;
                            }
                            else
                            {
                                aixForeward[i] = true;
                            }
                            struct Trap trap = Trap_Profile_KDL(fabs(distance[i]), maxV, maxAcc);
                            trapList.push_back(trap);
                        }
                        maxT3Index = getMaxT3Index(trapList);//找到最大运行时间的下标
                        //第二次计算，让所有轴运行时间相等
                        for (int i = 0; i < 6; i++)
                        {
                            if (i == maxT3Index)
                                continue;
                            struct Trap trap = Trap_Profile_T(fabs(distance[i]), maxV, maxAcc, trapList[maxT3Index].t3);
                            trapList[i] = trap;
                            cout << "trapList[" << i << "].t3=" << trapList[i].t3 <<endl;
                        }
                        t = 0;
                        trapFlag = false;//插补未完成
                        trapIsEnd = true;//规划完成
                        for (int i = 0; i < 6; i++)
                        {
                            curPosition[i] = g_servo_current_data[i].present_p;
                            g_rc_plc_share_memory->servos_ctrl[i].target_p = g_servo_current_data[i].present_p;//目标位置
                            g_rc_plc_share_memory->servos_ctrl[i].target_v = 0;//目标速度
                        }
                    }
                    else
                    {
                        if (g_jog_info.isRelease)//按键未释放
                        {
                            //插补中
//                            t += SINGLE_CIRCLE;
                            if (t <= trapList[maxT3Index].t3)//插补时间未结束
                            {
                                for (int i = 0; i < 6; i++)
                                {
                                    posList[i] = Trap_Profile_pos(trapList[i], t);
    //                            		cout << "posList[" <<i <<"].pos=" << posList[i].pos <<endl;
                                }
                                runCount += 1;
                                t += SINGLE_CIRCLE;
                                for (int i = 0; i < 6; i++)
                                {
                                    if (aixForeward[i] == false)
                                    {
                                        g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[i] + posList[i].pos;//目标位置 正转
                                        g_rc_plc_share_memory->servos_ctrl[i].target_v = posList[i].vel;//目标速度
                                    }
                                    else
                                    {
                                        g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[i] - posList[i].pos;//目标位置 反转
                                        g_rc_plc_share_memory->servos_ctrl[i].target_v = posList[i].vel;//目标速度
                                    }
                                }
                            }
                            else
                            {
                                cout << "已经回到原点了" << endl;
                            }
                        }
                        else //按键释放
                        {
                            trapFlag = true;//插补结束
                            g_irib.instFlag = true;//变为无指令
                        }
                    }
                    if(trapFlag && g_irib.instFlag)
                    {
                        trapList.clear();//清空
                        cout << "runCount=" << runCount <<endl;
                        runCount = 0;
                        trapIsEnd = false;
                        g_rc_plc_share_memory->stat.status_w.bit3 = 0;
                        g_wakeup_b3 = 0;
                        cout << "完成插补，向c2发送就绪位变为bit3=0" << endl;
//                			usleep(40);//为了b2能够运行阻塞等待的语句
                        rt_sem_broadcast(&g_rt_sem_B3_to_B2);
                    }
                }
                else if (g_wakeup_b3 == 0x4)
                {
                    if (!isMovlOrigin)//未移动到movl命令的起点
                    {
                        if (!trapIsEnd)//使用movabsj方式移动到movl起点
                        {
//                            cout << "111111111111111" <<endl;
                            //movl起点
                            movlP0[0] = 0.4;
                            movlP0[1] = 0.15;
                            movlP0[2] = 0.06;
                            //movl终点
                            movlP1[0] = 0.4;
                            movlP1[1] = -0.15;
                            movlP1[2] = 0.06;
                            movlS = getMovlS(movlP0, movlP1);//计算移动距离
                            t = 0;
                            runCount = 0;

                            maxV = 0.5;
                            maxAcc = 0.5 / 0.2;
                            cout << "movlS=" << movlS << endl;
                            //获得movl起点的角度值 插补位置
                            trapMovl = Trap_Profile_KDL(movlS, maxV, maxAcc);
                            posMovl = Trap_Profile_pos(trapMovl, t);
                            getMovlPi(movlPi, movlP0, movlP1, posMovl.pos);
                            scara_ikine_Siciliano1(robot0603, movlPi, radQ);//逆解求得空间起点
//                            cout << "trapMovl.t3=" << trapMovl.t3 << endl;
//                            for(int i = 0; i < 4; i++)
//                            {
//                                cout << "movlPi[" << i << "]=" << movlPi[i] << endl;
//                                cout << "radQ[" << i << "]=" << radQ[i] << endl;
//                                cout << "rad2angle(radQ["<< i << "])=" << rad2angle(radQ[i]) <<endl;
//                                cout << "getAnglePro(g_servo_current_data[" << i <<"].present_p)=" << getAnglePro(g_servo_current_data[i].present_p) << endl;
//                            }
                            //
                            distance[0] = angleTransform(rad2angle(radQ[0]) - getAnglePro(g_servo_current_data[0].present_p));//需要转动的角度=起点角度-当前电机角度
                            distance[1] = angleTransform(rad2angle(radQ[1]) - getAnglePro(g_servo_current_data[1].present_p));
                            distance[2] = 0;
                            distance[3] = angleTransform(rad2angle(radQ[3]) - getAnglePro(g_servo_current_data[3].present_p));
                            distance[4] = 0;
                            distance[5] = 0;
                            xmlMaxV = 1.2 * XMLMAXV_INCREASE;
                            xmlMaxAcc = 1.2 * XMLMAXV_INCREASE;
                            for (int i = 0; i < 6; i++)
                            {
//                                cout << "g_servo_current_data[" << i <<"].present_p=" << g_servo_current_data[i].present_p << endl;
//                                cout << "distance[" << i << "]= " << distance[i] << endl;
                                if (distance[i] < 0)
                                {
                                    aixForeward[i] = false;
                                }
                                else
                                {
                                    aixForeward[i] = true;
                                }
                                struct Trap trap = Trap_Profile_KDL(fabs(distance[i]), xmlMaxV, xmlMaxAcc);
                                trapList.push_back(trap);
                            }
                            maxT3Index = getMaxT3Index(trapList);//找到最大运行时间的下标
//                            cout << "maxT3Index=" << maxT3Index << endl;
//                            cout << "trapList[maxT3Index].t3=" << trapList[maxT3Index].t3 << endl;
                            //第二次计算，让所有轴运行时间相等
                            for (int i = 0; i < 6; i++)
                            {
                                if(i == maxT3Index)
                                    continue;
                                struct Trap trap = Trap_Profile_T(fabs(distance[i]), xmlMaxV, xmlMaxAcc, trapList[maxT3Index].t3);
                                trapList[i] = trap;
                                cout << "trapList["<< i <<"].t3=" << trapList[i].t3 << endl;
                            }
                            trapFlag = false;//插补未完成
                            trapIsEnd = true;//规划完成
                            for (int i = 0; i < 6; i++)
                            {
                                curPosition[i] = g_servo_current_data[i].present_p;
//                                cout << "curPosition[" << i << "]=" << curPosition[i] << endl;
                                g_rc_plc_share_memory->servos_ctrl[i].target_p = g_servo_current_data[i].present_p;//目标位置
                                g_rc_plc_share_memory->servos_ctrl[i].target_v = 0;//目标速度
                            }
                        }
                        else //运动到movl起点中
                        {
                            //插补中
//                            t += SINGLE_CIRCLE;
                            if (t < trapList[maxT3Index].t3)
                            {
                                for (int i = 0; i < 6;  i++)
                                {
                                    posList[i] = Trap_Profile_pos(trapList[i], t);
//                                    cout << "posList[" <<i <<"].pos=" << posList[i].pos <<endl;
                                }
                                runCount += 1;
                                t += SINGLE_CIRCLE;
                                for (int i = 0; i < 6; i++)
                                {
                                    if(aixForeward[i])
                                    {
                                        g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[i] + posList[i].pos;//目标位置 正转
                                        g_rc_plc_share_memory->servos_ctrl[i].target_v = posList[i].vel;//目标速度
                                    }
                                    else
                                    {
                                        g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[i] - posList[i].pos;//目标位置 反转
                                        g_rc_plc_share_memory->servos_ctrl[i].target_v = posList[i].vel;//目标速度
                                    }
                                }
                            }
                            else
                            {
                                cout << "22222222222222" << endl;
                                cout << "runCount=" << runCount << endl;
                                runCount = 0;
                                t = 0;
                                isMovlOrigin = true;
                                trapIsEnd = false;
                                for (int i = 0; i < 6; i++)
                                {
//                                    cout << "----------------------curPosition[" << i << "]=" << curPosition[i] << endl;
                                    curPosition[i] = g_servo_current_data[i].present_p;
                                    cout << "======================curPosition[" << i << "]=" << curPosition[i] << endl;
                                    cout << "origin point======curPosition[" << i << "].......=" << getAnglePro(curPosition[i]) << endl;
                                    g_rc_plc_share_memory->servos_ctrl[i].target_p = g_servo_current_data[i].present_p;//目标位置
                                }
                            }
                        }
                    }
                    else //movl命令的运动过程
                    {
//                        t += SINGLE_CIRCLE;
                        if (t < trapMovl.t3)
                        {
                            posMovl = Trap_Profile_pos(trapMovl, t);
                            getMovlPi(movlPi, movlP0, movlP1, posMovl.pos);
                            scara_ikine_Siciliano1(robot0603, movlPi, radQ);//逆解
                            runCount += 1;
                            t += SINGLE_CIRCLE;
//                            cout << "**********************[" << 0<< "]=" << angleTransform(rad2angle(radQ[0])) << endl;
                            for (int i = 0; i < 6; i++)
                            {
                                if(i == 2)
                                {
                                    continue;
                                }
                                g_rc_plc_share_memory->servos_ctrl[i].target_p = angleTransform(rad2angle(radQ[i]));//目标位置
//                                cout << "rad2angle(radQ["<< i << "])=" << rad2angle(radQ[i]) <<endl;
                            }
                        }
                        else
                        {
                            cout << "333333333333" << endl;
                            cout << "runCount=" << runCount << endl;
//                            for (int i = 0; i < 6; i++)
//                            {
////                                cout << "!!!!!!!!!!!!!!!!!!!!!!curPosition[" << i << "]=" << curPosition[i] << endl;
//                                curPosition[i] = g_servo_current_data[i].present_p;
////                                cout << "@@@@@@@@@@@@@@@@@@@@@@curPosition[" << i << "]=" << curPosition[i] << endl;
////                                cout << "@@@@@@@@@@@@@@@@@@@@@@curPosition[" << i << "]------=" << getAnglePro(curPosition[i]) << endl;
//                            }
                            t = 0;
                            isMovlOrigin = false;
                            g_irib.instFlag = true;
                            trapList.clear();//清空
                            g_rc_plc_share_memory->stat.status_w.bit3 = 0;
                            g_wakeup_b3 = 0;
                            rt_sem_broadcast(&g_rt_sem_B3_to_B2);
                        }
                    }
                }
                else if (g_wakeup_b3 == 0x5) //试运行
                {
                    if(!trapIsEnd)//未规划
                    {
                        xmlMaxV = g_robot_config.link_param[0].vel_limit[1] * XMLMAXV_INCREASE;
                        xmlMaxAcc = g_robot_config.link_param[0].acc_limit[1] * XMLMAXV_INCREASE;
                        cout << "xmlMaxV=" << xmlMaxV <<endl;
                        cout << "xmlMaxAcc=" << xmlMaxAcc <<endl;
                        distance[0] = angleTransform(g_program_try_pointData.joints[0] - getAnglePro(g_servo_current_data[0].present_p));//1轴要移动的距离
                        distance[1] = angleTransform(g_program_try_pointData.joints[1] - getAnglePro(g_servo_current_data[1].present_p));//2轴要移动的距离
                        distance[2] = angleTransform(g_program_try_pointData.joints[2] - getAnglePro(g_servo_current_data[2].present_p));//3轴要移动的距离
                        distance[3] = angleTransform(g_program_try_pointData.joints[3] - getAnglePro(g_servo_current_data[3].present_p));//4轴要移动的距离
                        distance[4] = angleTransform(g_program_try_pointData.joints[4] - getAnglePro(g_servo_current_data[4].present_p));//5轴要移动的距离
                        distance[5] = angleTransform(g_program_try_pointData.joints[5] - getAnglePro(g_servo_current_data[5].present_p));//6轴要移动的距离
                        cout << "distance[0]=" << distance[0] << "  distance[1]=" <<distance[1] <<endl;
                        maxV = 1000000;//转动最大速度=机型最大速度*速度%
                        maxAcc = 1000000;//最大加速度=机型最大加速度
                        cout << "梯形算法规划中.........." << endl;
                        //第一次计算
                        for (int i = 0; i < 6; i++)
                        {
                            if(distance[i] < 0)
                            {
                                aixForeward[i] = false;
                            }
                            else
                            {
                                aixForeward[i] = true;
                            }
                            struct Trap trap = Trap_Profile_KDL(fabs(distance[i]), maxV, maxAcc);
                            trapList.push_back(trap);
                        }
                        maxT3Index = getMaxT3Index(trapList);//找到最大运行时间的下标
                        cout << "trapList[" << maxT3Index << "].t3=" << trapList[maxT3Index].t3 << endl;
                        //第二次计算，让所有轴运行时间相等
                        for (int i = 0; i < 6; i++)
                        {
                            if (i == maxT3Index)
                                continue;
                            struct Trap trap = Trap_Profile_T(fabs(distance[i]), maxV, maxAcc, trapList[maxT3Index].t3);
                            trapList[i] = trap;
                        }
                        t = 0;
                        trapFlag = false;//插补未完成
                        trapIsEnd = true;//规划完成
                        for (int i = 0; i < 6; i++)
                        {
                            curPosition[i] = g_servo_current_data[i].present_p;
                            g_rc_plc_share_memory->servos_ctrl[i].target_p = g_servo_current_data[i].present_p;//目标位置
                            g_rc_plc_share_memory->servos_ctrl[i].target_v = 0;//目标速度
                        }
                    }
                    else
                    {
                        if(g_jog_info.isRelease)//按键未释放
                        {
                            //插补中
//                            t += SINGLE_CIRCLE;
                            if (t < trapList[maxT3Index].t3)//插补时间未结束
                            {
                                for (int i = 0; i < 6; i++)
                                {
                                    posList[i] = Trap_Profile_pos(trapList[i], t);
    //                            		cout << "posList[" <<i <<"].pos=" << posList[i].pos <<endl;
                                }
                                runCount += 1;
                                t += SINGLE_CIRCLE;
                                for (int i = 0; i < 6; i++)
                                {
                                    if(aixForeward[i])
                                    {
                                        g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[i] + posList[i].pos;//目标位置 正转
                                        g_rc_plc_share_memory->servos_ctrl[i].target_v = posList[i].vel;//目标速度
                                    }
                                    else
                                    {
                                        g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[i] - posList[i].pos;//目标位置 反转
                                        g_rc_plc_share_memory->servos_ctrl[i].target_v = posList[i].vel;//目标速度
                                    }
                                }
                            }
//                            else {
//                                cout << "达到角度了" << endl;
//                            }
                        }
                        else //按键释放
                        {
                            cout << "按键释放------g_jog_info.isRelease" << g_jog_info.isRelease << endl;
                            trapFlag = true;//插补结束
                            g_irib.instFlag = true;//变为无指令
                        }
                    }
                    if(trapFlag && g_irib.instFlag)
                    {
                        trapList.clear();//清空
                        cout << "runCount=" <<runCount <<endl;
                        runCount = 0;
                        trapIsEnd = false;
                        g_rc_plc_share_memory->stat.status_w.bit3 = 0;
                        g_wakeup_b3 = 0;
                        cout << "完成插补，向c2发送就绪位变为bit3=0" << endl;
//                			usleep(40);//为了b2能够运行阻塞等待的语句
                        rt_sem_broadcast(&g_rt_sem_B3_to_B2);
                    }
                }
                else if (g_wakeup_b3 == 0x6) //movj命令
                {
                    if (!isMovlOrigin)//未移动到movj命令的起点
                    {
                        if (!trapIsEnd)//使用movabsj方式移动到movj起点
                        {

                            //movl起点
                            movjP0[0] = 0.4;
                            movjP0[1] = 0.15;
                            movjP0[2] = 0.06;
                            //movl终点
                            movjP1[0] = 0.4;
                            movjP1[1] = -0.15;
                            movjP1[2] = 0.06;

                            movjR0[0] = 0;
                            movjR0[1] = 0;
                            movjR0[2] = 0;

                            movjR1[0] = 0;
                            movjR1[1] = 0;
                            movjR1[2] = 0;

                            hand = robot0603.hand;
                            getMovjPose(movjP0, movjR0, hand, movjPose0);
                            scara_ikine_Siciliano2(robot0603, movjPose0, movjQ0);//逆解求得空间起点

                            t = 0;
                            runCount = 0;

                            //获得movj起点的角度值 插补位置



                            distance[0] = angleTransform(rad2angle(movjQ0[0]) - getAnglePro(g_servo_current_data[0].present_p));//需要转动的角度=起点角度-当前电机角度
                            distance[1] = angleTransform(rad2angle(movjQ0[1]) - getAnglePro(g_servo_current_data[1].present_p));
                            distance[2] = 0;
                            distance[3] = angleTransform(rad2angle(movjQ0[3]) - getAnglePro(g_servo_current_data[3].present_p));
                            distance[4] = 0;
                            distance[5] = 0;
                            xmlMaxV = 1.2 * XMLMAXV_INCREASE;
                            xmlMaxAcc = 1.2 * XMLMAXV_INCREASE;
                            for (int i = 0; i < 6; i++)
                            {
                                if (distance[i] < 0)
                                {
                                    aixForeward[i] = false;
                                }
                                else
                                {
                                    aixForeward[i] = true;
                                }
                                struct Trap trap = Trap_Profile_KDL(fabs(distance[i]), xmlMaxV, xmlMaxAcc);
                                trapList.push_back(trap);
                            }
                            maxT3Index = getMaxT3Index(trapList);//找到最大运行时间的下标
                            //第二次计算，让所有轴运行时间相等
                            for (int i = 0; i < 6; i++)
                            {
                                if(i == maxT3Index)
                                    continue;
                                struct Trap trap = Trap_Profile_T(fabs(distance[i]), xmlMaxV, xmlMaxAcc, trapList[maxT3Index].t3);
                                trapList[i] = trap;
                                cout << "trapList["<< i <<"].t3=" << trapList[i].t3 << endl;
                            }
                            trapFlag = false;//插补未完成
                            trapIsEnd = true;//规划完成
                            for (int i = 0; i < 6; i++)
                            {
                                curPosition[i] = g_servo_current_data[i].present_p;
//                                cout << "curPosition[" << i << "]=" << curPosition[i] << endl;
                                g_rc_plc_share_memory->servos_ctrl[i].target_p = g_servo_current_data[i].present_p;//目标位置
                                g_rc_plc_share_memory->servos_ctrl[i].target_v = 0;//目标速度
                            }
                        }
                        else //运动到movj起点中
                        {
                            //插补中
//                            t += SINGLE_CIRCLE;
                            if (t < trapList[maxT3Index].t3)
                            {
                                for (int i = 0; i < 6;  i++)
                                {
                                    posList[i] = Trap_Profile_pos(trapList[i], t);
//                                    cout << "posList[" <<i <<"].pos=" << posList[i].pos <<endl;
                                }
                                runCount += 1;
                                t += SINGLE_CIRCLE;
                                for (int i = 0; i < 6; i++)
                                {
                                    if(aixForeward[i])
                                    {
                                        g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[i] + posList[i].pos;//目标位置 正转
                                        g_rc_plc_share_memory->servos_ctrl[i].target_v = posList[i].vel;//目标速度
                                    }
                                    else
                                    {
                                        g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[i] - posList[i].pos;//目标位置 反转
                                        g_rc_plc_share_memory->servos_ctrl[i].target_v = posList[i].vel;//目标速度
                                    }
                                }
                            }
                            else
                            {

                                trapList.clear();
                                getMovjPose(movjP1, movjR1, hand, movjPose1);
                                scara_ikine_Siciliano2(robot0603, movjPose1, movjQ1);//逆解求得空间终点
                                distance[0] = angleTransform(rad2angle(movjQ1[0]) - getAnglePro(g_servo_current_data[0].present_p));//需要转动的角度=起点角度-当前电机角度
                                distance[1] = angleTransform(rad2angle(movjQ1[1]) - getAnglePro(g_servo_current_data[1].present_p));
                                distance[2] = 0;
                                distance[3] = angleTransform(rad2angle(movjQ1[3]) - getAnglePro(g_servo_current_data[3].present_p));
                                distance[4] = 0;
                                distance[5] = 0;

                                xmlMaxV = 1.2 * XMLMAXV_INCREASE;
                                xmlMaxAcc = 1.2 * XMLMAXV_INCREASE;
                                for (int i = 0; i < 6; i++)
                                {
                                    if (distance[i] < 0)
                                    {
                                        aixForeward[i] = false;
                                    }
                                    else
                                    {
                                        aixForeward[i] = true;
                                    }
                                    struct Trap trap = Trap_Profile_KDL(fabs(distance[i]), xmlMaxV, xmlMaxAcc);
                                    trapList.push_back(trap);
                                }
                                maxT3Index = getMaxT3Index(trapList);//找到最大运行时间的下标
                                //第二次计算，让所有轴运行时间相等
                                for (int i = 0; i < 6; i++)
                                {
                                    if(i == maxT3Index)
                                        continue;
                                    struct Trap trap = Trap_Profile_T(fabs(distance[i]), xmlMaxV, xmlMaxAcc, trapList[maxT3Index].t3);
                                    trapList[i] = trap;
                                    cout << "trapList["<< i <<"].t3=" << trapList[i].t3 << endl;
                                }

                                cout << "22222222222222" << endl;
                                cout << "runCount=" << runCount << endl;
                                runCount = 0;
                                t = 0;
                                isMovlOrigin = true;
                                trapIsEnd = false;
                                for (int i = 0; i < 6; i++)
                                {
                                    curPosition[i] = g_servo_current_data[i].present_p;
                                    g_rc_plc_share_memory->servos_ctrl[i].target_p = g_servo_current_data[i].present_p;//目标位置
                                }
                            }
                        }
                    }
                    else //movj过程
                    {
                        if (t < trapList[maxT3Index].t3)
                        {
                            for (int i = 0; i < 6;  i++)
                            {
                                posList[i] = Trap_Profile_pos(trapList[i], t);
//                                    cout << "posList[" <<i <<"].pos=" << posList[i].pos <<endl;
                            }
                            runCount += 1;
                            t += SINGLE_CIRCLE;
                            for (int i = 0; i < 6; i++)
                            {
                                if(aixForeward[i])
                                {
                                    g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[i] + posList[i].pos;//目标位置 正转
                                    g_rc_plc_share_memory->servos_ctrl[i].target_v = posList[i].vel;//目标速度
                                }
                                else
                                {
                                    g_rc_plc_share_memory->servos_ctrl[i].target_p = curPosition[i] - posList[i].pos;//目标位置 反转
                                    g_rc_plc_share_memory->servos_ctrl[i].target_v = posList[i].vel;//目标速度
                                }
                            }
                        }
                        else
                        {
                            cout << "333333333333" << endl;
                            cout << "runCount=" << runCount << endl;
//                            for (int i = 0; i < 6; i++)
//                            {
////                                cout << "!!!!!!!!!!!!!!!!!!!!!!curPosition[" << i << "]=" << curPosition[i] << endl;
//                                curPosition[i] = g_servo_current_data[i].present_p;
////                                cout << "@@@@@@@@@@@@@@@@@@@@@@curPosition[" << i << "]=" << curPosition[i] << endl;
////                                cout << "@@@@@@@@@@@@@@@@@@@@@@curPosition[" << i << "]------=" << getAnglePro(curPosition[i]) << endl;
//                            }
                            t = 0;
                            isMovlOrigin = false;
                            g_irib.instFlag = true;
                            trapList.clear();//清空
                            g_rc_plc_share_memory->stat.status_w.bit3 = 0;
                            g_wakeup_b3 = 0;
                            rt_sem_broadcast(&g_rt_sem_B3_to_B2);
                        }
                    }
                }
                g_semaphore.Semaphore_op(1,1,1);//向c2发送插补信号
            }
        }
#endif
    }
}



void task_function_second(void *arg)
{
    printf(" B2线程\n");
//    CodeModel g_codeModel;							//    Add by mushroom 2021/8/27
//    MyDataVisitor g_dataVisitor(&g_codeModel);			//    Add by mushroom 2021/8/27
//    MyProgramVisitor g_programVisitor(&g_codeModel);	//    Add by mushroom 2021/8/27
    int curLine;									//    Add by mushroom 2021/8/27
    char curDataFile[128];                          //    Add by mushroom 2021/8/27
    char curProgramFile[128];                       //    Add by mushroom 2021/8/27
    struct stat curDataFileStat;					//    Add by mushroom 2021/8/27
    struct stat curProgramFileStat;                 //    Add by mushroom 2021/8/27
    char lineBuf[512] = {0};
    int writeLen;
    int sportInstructionLine;
    while (1)
    {
        //阻塞等待B1线程消息命令
        while (g_rc_state.start == 0)
        {
            cout<<"阻塞等待B1线程消息命令"<<endl;
            rt_sem_p(&g_rt_sem_B2, TM_INFINITE);
        }
        /*
        Add by mushroom 2021/8/27
        根据rc_cur_state.cur_project和rc_cur_state.cur_program加载程序文件
        将数据存储在g_codeModel中的成员变量中
        判断文件名是否一致，不一致清空g_codeModel中的数据，再从文件中获取
        如果文件名一致就判断文件是否修改过，修改过就清空g_codeModel中的数据，再从文件中获取
        先对数据文件分析
        */

//        if (g_rc_state.ready == 0)//判断程序文件是否已经编译
//        {
//            cout << "-----------------" << g_rc_state.cur_project << endl;
//            cout << "-----------------" << g_rc_state.cur_program << endl;
//            //清空上个程序
//            cout << "---------loading-----------" << endl;
//            g_codeModel.clear();
//            g_programVisitor.lineno = 0;
//            clearinList();
////            curLine = 0;
////            sportInstructionLine = 0;
//            //加载编译数据文件
//            memset(curDataFile, 0, sizeof (curDataFile));
//            strcpy(curDataFile, g_rc_state.cur_project);
//            loadDataFile(curDataFile, &g_dataVisitor);
//            //加载编译程序文件
//            memset(curProgramFile, 0, sizeof (curProgramFile));
//            strcpy(curProgramFile, g_rc_state.cur_program);
//            loadProgramFile(curProgramFile, &g_programVisitor);
//            g_codeModel.executor();
//        }
        cout << "g_codeModel.StatementSpace.size()=" << g_codeModel.StatementSpace.size() << endl;
        cout << "g_codeModel.DataSpace.size()=" << g_codeModel.DataSpace.size() << endl;
        printf("g_rc_state.exec_status=%d\n", g_rc_state.exec_status);
        //堵塞等待B1的"开始运行"消息
        if (g_rc_state.exec_status == 0 || g_rc_state.exec_status == 2)
        {
            cout << "等待开始运行命令" << endl;
            rt_sem_p(&g_rt_sem_StartRun, TM_INFINITE);
            if (g_rc_state.move_mode == 0)//单步模式
            {
                cout << "qqqqqqqqqqqqqqq" << endl;
                g_rc_state.exec_status = 0;
            }
            else if (g_rc_state.move_mode == 1)//连续模式
            {
                g_rc_state.exec_status = 1;
            }
            else if (g_rc_state.move_mode == 2)//单循环模式
            {
                g_rc_state.exec_status = 2;
            }
        }

//        cout<<"加载文件&&编译文件中..."<<endl;
        if (!(g_codeModel.DataSpace.size() > 0 && g_codeModel.StatementSpace.size() > 0))//编译失败
        {
            cout << "加载文件&&编译文件失败" << endl;
            g_rc_state.start = 0;
        }
        else
        {
            /*
            *
            * 编译成功后生成内部指令序列g_codeModel
            */
//            cout << "编译成功后生成内部指令序列g_codeModel" << endl;
            g_rc_state.ready = 1;//程序文件编译成功

            //判断是不是最后的指令
            curLine = g_run_current_lineno;
            sportInstructionLine = currentLine2sportLine(g_codeModel.StatementSpace[curLine]->lineno);
            cout << "$$$$$$$$$$$$$$$$curLine=" << curLine << endl;
            cout << "$$$$$$$$$$$$$$$$sportInstructionLine=" << sportInstructionLine << endl;
            while (curLine<g_codeModel.StatementSpace.size() && g_server_tcp.bAcceptFlag)
            {
                cout<<"==========================================================="<<endl;
                cout << "当前行号=" << g_codeModel.StatementSpace[curLine]->lineno << endl;
                memset(lineBuf, 0, sizeof(lineBuf));
                sprintf(lineBuf, "msg:%d", g_codeModel.StatementSpace[curLine]->lineno);
                writeLen =  g_server_tcp.MyWrite(lineBuf, sizeof(lineBuf));
//                cout << "writeLen=" << writeLen << endl;
                /*
                *执行一条指令
                *（从指令序列中取出一条写入内部指令区）
                *g_codeModel.pc=curLine;
                *g_codeModel.executor();
                */
                cout << "运行一条命令" << endl;
                g_codeModel.pc = curLine;
                g_codeModel.StatementSpace.at(curLine)->excute();
                /*
                *	更新当前程序行号rc_cur_state.cur_linenum
                *	rc_cur_state.cur_linenum=g_codeModel.StatementSpace[g_codeModel.pc]->lineno;
                */
                g_rc_state.cur_linenum = g_codeModel.StatementSpace[g_codeModel.pc]->lineno;
//                cout << "g_codeModel.StatementSpace[g_codeModel.pc]->instType=" <<g_codeModel.StatementSpace[curLine]->instType<<endl;
                cout << "sportInstructionLine=" << sportInstructionLine << endl;
                if (g_codeModel.StatementSpace[g_codeModel.pc]->instType != 0)
                {
                    cout << "_G_instList.size()=" << _G_instList.size() << endl;
//                    printf("_G_instList[%d].instType=%d\n", sportInstructionLine, _G_instList[sportInstructionLine].instType);
                    g_irib.in_rbt_inst = _G_instList[sportInstructionLine];
                    g_irib.instFlag = false;
                    g_rc_plc_share_memory->stat.status_w.bit3 = 1;

                    if (_G_instList[sportInstructionLine].instType == 7)
                    {
                        g_wakeup_b3=0x2;
                    }
                    else if (_G_instList[sportInstructionLine].instType == 5)
                    {
                        g_wakeup_b3=0x4;
                    }
                    else if (_G_instList[sportInstructionLine].instType == 4)
                    {
                        g_wakeup_b3=0x6;
                    }
                    sportInstructionLine++;
                    //向B3发送“启动插补”的消息
                    rt_sem_broadcast(&g_rt_sem);
                    // 阻塞等待B3的插补“完成所有插补”的消息
                    cout << "b2-------阻塞等待b3完成所有插补" << endl;
                    rt_sem_p(&g_rt_sem_B3_to_B2, TM_INFINITE);
                    cout << "b2---------b3完成所有插补" << endl;
                }
                else
                {
                    g_irib.instFlag = true;
                }
                curLine++;//程序行号加一
                g_run_current_lineno = curLine;
                //判断运行模式  0:单步  1：连续
                if (g_rc_state.move_mode == 0)
                {
                    cout << "ppppppppppppppppppppppppppppppppppp" << endl;
                    g_rc_state.exec_status = 0;
                    break;
                }
            }
            if (curLine == g_codeModel.StatementSpace.size())
            {
                curLine = 0;//重复运行
                g_run_current_lineno = curLine;
                sportInstructionLine = 0;
            }
//             usleep(100);
//             g_rc_state.ready=0;
        }
//        cout<<"B2线程......."<<endl;

    }
    return ;
}


void *send_msg_thread(void *arg)
{
    char posBuf[1024];
    while (1)
    {
        if (!g_server_tcp.bAcceptFlag)
        {
            cout << "发送线程等待启动" << endl;
            g_sendthreadsem.Semaphore_op(0, -1, 1);
        }
        memset(posBuf, 0, sizeof (posBuf));
        for (int i = 0; i < 6; i++)
        {
            g_servo_current_data[i].present_p = g_rc_plc_share_memory->servos_stat[i].present_p;//电机当前位置
//                    cout << "g_servo_current_data["<<i<<"].present_p" << g_servo_current_data[i].present_p <<endl;
        }

        sprintf(posBuf, "pos:%lf_%lf_%lf_%lf_%lf_%lf", getAnglePro(g_servo_current_data[0].present_p)
                                                     , getAnglePro(g_servo_current_data[1].present_p)
                                                     , getAnglePro(g_servo_current_data[2].present_p)
                                                     , getAnglePro(g_servo_current_data[3].present_p)
                                                     , getAnglePro(g_servo_current_data[4].present_p)
                                                     , getAnglePro(g_servo_current_data[5].present_p));
        g_server_tcp.MyWrite(posBuf, sizeof (posBuf));

        usleep(1000);
    }
    pthread_exit(NULL);
}



//b1线程
void task_function_first(void *arg)
{
    cout<<"task_function 1"<<endl;

    XMLDocument config, Calibration;
    if (!LoadXml("../xml/configs/config.xml", config))
    {
        PRINTF_ERR_MESSAGE("load config XML file is error!");
        return;
    }

    if (!LoadXml("../xml/configs/calibration.xml", Calibration))
    {
        PRINTF_ERR_MESSAGE("read Calibration XML file is error!");
        return;
    }

    if (!ReadConfigXml(config, g_robot_config, g_servo_config, g_add_ax_config))
    {
        PRINTF_ERR_MESSAGE("read config XML file is error!");
        return;
    }

    /* 暂时用不上，取消注释会出现段错误
    if (ReadCalibrationXml(Calibration, g_calibration_config))
    {
        PRINTF_ERR_MESSAGE("read Calibration XML file is error!");
        return;
    }
    */

    cout<<"name:"<<g_robot_config.name_of_robot<<endl;
    cout << "xmlMaxV=" <<g_robot_config.link_param[0].vel_limit[1]<<endl;
    cout << "xmlMaxAcc="<<g_robot_config.link_param[0].acc_limit[1]<<endl;

#if 0
    strcpy(g_rc_state.cur_project,"../file/program1/program1.tid");
    strcpy(g_rc_state.cur_program,"../file/program1/program1.tip");
#endif

    /*
        根据配置信息初始化机器人模型及插补计算库
    */

    /*
        根据机器人模型及初始化插补计算库
    */

    //初始化 C共享内存和信号量 创建RC/PLC进程

     cout<<"机器人模型创建成功12345！"<<endl;

    if (!g_semaphore.Semaphore_Init("/root", 14, 2))
    {
        PRINTF_ERR_MESSAGE("Semaphore initialize error!");
        return ;
    }

    if (!g_share_memory.share_memory_init("/root", 13, sizeof (RC_PLC_SHARE_BUFF)))
    {
        PRINTF_ERR_MESSAGE("ShareMemory initialize error!");
        return ;
    }
    //清空共享内存里的数据
    g_share_memory.share_memory_clean();

    g_rc_plc_share_memory = (RC_PLC_SHARE_BUFF *)g_share_memory.p_get_share_memory_head();

    g_rc_plc_share_memory->stat.status_w.bit3 = 0;

#if 1//发送位置信息线程和信号量等操作
    //初始化信号量
    g_sendthreadsem.Semaphore_Init("/root", 99, 1);
    //创建线程
    pthread_t sendMsgTid;
    pthread_create(&sendMsgTid, nullptr, send_msg_thread, nullptr);
#endif


    //初始化rc_cur_state结构体（rc_cur_state.start=1）其他可根据实际情况修改
    g_rc_state.start = 1;

    //初始化内部指令缓冲区
    memset(&g_irib, 0, sizeof(In_rbt_inst_buff));
    g_irib.instFlag = true;

    /////////////创建xenomai 信号 用于同步其他任务///////////
    rt_sem_create(&g_rt_sem, "MySemaphore0", 0, S_FIFO); //创建xenomai信号量 用于同步B3
    rt_sem_create(&g_rt_sem_B3_to_B2, "MySemaphore1", 0, S_FIFO); //创建xenomai信号量 用于同步B2
    rt_sem_create(&g_rt_sem_StartRun, "MySemaphore2", 0 ,S_FIFO); //创建xenomai信号量 用于同步B2
    rt_sem_create(&g_rt_sem_B2, "MySemaphore3", 0, S_FIFO); //创建xenomai信号量 用于同步B2

    ///////////////////////启动B2、B3 创建线程/////////////
    XenomaiTask task_second;
    if (!task_second.xeno_task_create("Mytask_second", 0, 30, 0))
    {
        PRINTF_ERR_MESSAGE("create B2 task_first error! ");
        return;
    }
    if (!task_second.xeno_task_start(task_function_second,nullptr))
    {
        PRINTF_ERR_MESSAGE("start B2 task_first error! ");
        return;
    }

    XenomaiTask task_thrid;
    if (!task_second.xeno_task_create("Mytask_thrid", 0, 40, 0))
    {
        PRINTF_ERR_MESSAGE("create B2 task_first error! ");
        return;
    }
    if (!task_second.xeno_task_start(task_function_third,nullptr))
    {
        PRINTF_ERR_MESSAGE("start B2 task_first error! ");
        return;
    }
    ///////////////////////////////////

    //初始化服务器端TCP套接字

    if (!g_server_tcp.MySocket())
    {
        PRINTF_ERR_MESSAGE("network socket error !");
        return ;
    }

    if (!g_server_tcp.MySetsockopt())
    {
        PRINTF_ERR_MESSAGE("network setsockopt error !");
        g_server_tcp.CloseServerFd();
        return ;
    }

    if (!g_server_tcp.MyBind(9999))
    {
        PRINTF_ERR_MESSAGE("network bind error !");
        g_server_tcp.CloseServerFd();
        return ;
    }

    if (!g_server_tcp.MyListen(11))
    {
        PRINTF_ERR_MESSAGE("network list error !");
        g_server_tcp.CloseServerFd();
        return ;
    }

#if 1
    g_rc_state.mode = 1;
    g_rc_state.start = 0;
    g_rc_state.move_mode = 1;
    g_rc_state.ready = 0;
    g_rc_state.exec_status = 0;
#endif

    Send_Ctrl_Info   s_ctrl_info;
    int start_run = 0;

    for (;;)
    {
        if (!g_server_tcp.bAcceptFlag)
        {
            char buf[16] = {0};
            if (!g_server_tcp.MyAccept())
            {

                PRINTF_ERR_MESSAGE("network accept error !");
                g_server_tcp.CloseServerFd();
                return ;
            }
            g_server_tcp.bAcceptFlag = true;
            sprintf(buf, "pos:%d", g_rc_plc_share_memory->servos_stat[0].present_p);
            g_server_tcp.MyWrite(buf, strlen(buf));
            g_sendthreadsem.Semaphore_op(0, 1, 1);
        }


        memset(&s_ctrl_info, 0, sizeof(Send_Ctrl_Info));

        char recv_buf_sum[8] = {0};
        memset(recv_buf_sum, 0, 8);

        if (!g_server_tcp.MyReadSizeData(recv_buf_sum, 8))  //接收八个字节的指令
        {
            PRINTF_INFO_MESSAGE("user disconnecttion network!");
            g_server_tcp.bAcceptFlag = false;
            g_rc_state.ready = 0;
            g_rc_state.start = 0;
            rt_sem_broadcast(&g_rt_sem_StartRun);
            continue;
        }

        s_ctrl_info = *(Send_Ctrl_Info*)recv_buf_sum;
        std::printf("key:	0x%X	\t    0x%X  \n", s_ctrl_info.key, s_ctrl_info.value);
        std::cout<<"------------------------------------"<<endl<<endl;

        if (s_ctrl_info.key == 0x80000008)  //接收到接收文件的指令
        {
            int recv_size = -1;
            PRINTF_INFO_MESSAGE(" 接收文件中");
            file_attr file;
            recv_size = g_server_tcp.MyRead(&file, sizeof (file_attr));

            cout << "recv_size=" << recv_size << endl;
            cout << "file.File_Name=" << file.File_Name <<endl;
            cout << "file.File_Size=" << file.File_Size <<endl;
            if (g_server_tcp.ReceiveFile(file.File_Name, file.File_Size))
            {
                char err[512] = "recv file successful!";

                sprintf(err, "msg:recv %s successful!", file.File_Name);
                g_server_tcp.MyWrite(err, sizeof(err));

                cout<<file.File_Name<<"文件接收成功"<<endl;
                uncompressFile(file.File_Name, "../file");
#if 1
                string fileName = file.File_Name;
                string str = fileName.substr(0, fileName.find("."));
                sprintf(g_rc_state.cur_project, "../file/%s/%s.tid", str.c_str(), str.c_str());
                sprintf(g_rc_state.cur_program, "../file/%s/%s.tip", str.c_str(), str.c_str());
                g_rc_state.ready = 0;
                if (g_rc_state.ready == 0)//判断程序文件是否已经编译
                {
                    cout << "-----------------" << g_rc_state.cur_project << endl;
                    cout << "-----------------" << g_rc_state.cur_program << endl;
                    //清空上个程序
                    cout << "---------loading-----------" << endl;
                    g_codeModel.clear();
                    g_programVisitor.lineno = 0;
                    clearinList();
        //            curLine = 0;
        //            sportInstructionLine = 0;
                    //加载编译数据文件
                    loadDataFile(g_rc_state.cur_project, &g_dataVisitor);
                    //加载编译程序文件
                    loadProgramFile(g_rc_state.cur_program, &g_programVisitor);
                    g_codeModel.executor();
                }
                g_rc_state.exec_status = 0;
#endif
            }
            else
            {
                char err[512] = "recv file successful!";
                sprintf(err, "msg:recv %s failed!", file.File_Name);
                g_server_tcp.MyWrite(err, sizeof (err));
                PRINTF_ERR_MESSAGE("文件接收失败");
            }
        }
        else if (s_ctrl_info.key == 0x80000009)//接收xml文件的指令
        {
            PRINTF_INFO_MESSAGE(" 接收xml文件中");
            file_attr file;
            int recv_size = -1;
            recv_size = g_server_tcp.MyRead(&file, sizeof (file_attr));
            cout << "recv_size=" << recv_size << endl;
            cout << "file.File_Name=" << file.File_Name <<endl;
            cout << "file.File_Size=" << file.File_Size <<endl;

            if (g_server_tcp.ReceiveFile(file.File_Name, file.File_Size))
            {
                char err[512] = "recv file successful!";

                sprintf(err,"msg:recv %s successful!", file.File_Name);
                g_server_tcp.MyWrite(err, sizeof(err));
                cout<<file.File_Name<<"文件接收成功"<<endl;
                uncompressFile(file.File_Name, "../xml");

#if 1
                if (false == LoadXml("../xml/configs/config.xml", config))
                {
                     cout<<"读取XML文件失败"<<endl;
                     return;
                }
                if (false == LoadXml("../xml/configs/calibration.xml", Calibration))
                {
                     cout<<"读取XML文件失败"<<endl;
                     return;
                }
                if (!ReadConfigXml(config, g_robot_config, g_servo_config, g_add_ax_config))
                {
                    PRINTF_ERR_MESSAGE("read config XML file is error!");
                    return;
                }
                cout << "xmlMaxV=" <<g_robot_config.link_param[0].vel_limit[1] <<endl;
                cout << "xmlMaxAcc=" <<g_robot_config.link_param[0].acc_limit[1] <<endl;
#endif
           }
           else
           {
               char err[512] = "recv file successful!";
               sprintf(err, "msg:recv %s failed!", file.File_Name);
               g_server_tcp.MyWrite(err, sizeof (err));
               PRINTF_ERR_MESSAGE("文件接收失败");
           }
        }
        else if (s_ctrl_info.key == 0x80000001)//mode
        {
            printf("g_rc_state.mode=s_ctrl_info.value=%d\n",s_ctrl_info.value);
            g_rc_state.mode = s_ctrl_info.value;
            g_rc_state.start = 1;
            g_rc_state.exec_status = 0;
        }
        else if (s_ctrl_info.key == 0x80000002)//speed
        {
            g_jog_speed_percent = s_ctrl_info.value/100.0;
            std::printf("speed: %d\n", s_ctrl_info.value);
        }
        else if (s_ctrl_info.key == 0x80000003)//start
        {
            g_rc_state.start = s_ctrl_info.value;
            g_rc_state.mode = 1;
        }
        else if (s_ctrl_info.key == 0x80000004)//tool
        {
            std::printf("tool: %d\n", s_ctrl_info.value);
        }
        else if (s_ctrl_info.key == 0x80000005)//usr_coord
        {
            std::printf("usr_coord: %d\n",s_ctrl_info.value);
        }
        else if (s_ctrl_info.key == 0x80000006)//coord
        {
            std::printf("coord: %d\n",s_ctrl_info.value);
        }
        else if (s_ctrl_info.key == 0x80000007)//开始运行
        {
            start_run = s_ctrl_info.value;
            g_run_current_lineno = s_ctrl_info.value;
            printf("g_run_current_lineno=%d\n",g_run_current_lineno);
            rt_sem_broadcast(&g_rt_sem_StartRun);
        }
        else if (s_ctrl_info.key == 0x8000000A)//coord
        {
            g_rc_state.exec_status = s_ctrl_info.value;
            g_rc_state.move_mode = s_ctrl_info.value;
            g_rc_state.start = 1;
        }
        else if (s_ctrl_info.key == 0x00000200)//按键 10-
        {
          g_jog_info.joint = 0;//1轴
          g_jog_info.angle = SINGLE_ANGLE;//10°
          g_jog_info.isForeward = false;//反转
          g_jog_info.isRelease = s_ctrl_info.value;//按键是否释放  按下:1 释放:0
          cout << "g_jog_info.isRelease=" <<g_jog_info.isRelease<<endl;
          g_irib.instFlag = false;
          g_wakeup_b3 = 0x1;

          g_rc_plc_share_memory->stat.status_w.bit3 = 1;

          rt_sem_broadcast(&g_rt_sem);
          std::printf("10 - speed: %d\n",s_ctrl_info.value);
        }
        else if (s_ctrl_info.key == 0x00000400)//按键 11+
        {
            g_jog_info.joint = 0;//1轴
            g_jog_info.angle = SINGLE_ANGLE;//10°
            g_jog_info.isForeward = true;//正转
            g_jog_info.isRelease = s_ctrl_info.value;//按键是否释放  按下:1 释放:0
            cout << "g_jog_info.isRelease=" <<g_jog_info.isRelease<<endl;
            g_irib.instFlag = false;
            g_wakeup_b3 = 0x1;
            g_rc_plc_share_memory->stat.status_w.bit3 = 1;
            rt_sem_broadcast(&g_rt_sem);
            std::printf("11 + speed: %d\n",s_ctrl_info.value);
        }
        else if (s_ctrl_info.key == 0x00000800)//按键 12 -
        {
          g_jog_info.joint = 1;//2轴
          g_jog_info.angle = SINGLE_ANGLE;//10°
          g_jog_info.isForeward = false;//反转
          g_jog_info.isRelease = s_ctrl_info.value;//按键是否释放  按下:1 释放:0
          cout << "g_jog_info.isRelease=" <<g_jog_info.isRelease<<endl;
          g_irib.instFlag = false;
          g_wakeup_b3 = 0x1;
          g_rc_plc_share_memory->stat.status_w.bit3 = 1;
          rt_sem_broadcast(&g_rt_sem);
          std::printf("12 - speed: %d\n",s_ctrl_info.value);
        }
        else if (s_ctrl_info.key == 0x00001000)//按键 13+
        {
          g_jog_info.joint = 1;//2轴
          g_jog_info.angle = SINGLE_ANGLE;//10°
          g_jog_info.isForeward = true;//正转`
          g_jog_info.isRelease = s_ctrl_info.value;//按键是否释放  按下:1 释放:0
          cout << "g_jog_info.isRelease=" <<g_jog_info.isRelease<<endl;
          g_irib.instFlag = false;
          g_wakeup_b3 = 0x1;
          g_rc_plc_share_memory->stat.status_w.bit3 = 1;
          rt_sem_broadcast(&g_rt_sem);
          std::printf("13 + speed: %d\n",s_ctrl_info.value);
        }
        else if (s_ctrl_info.key == 0x00200000)//复位按键
        {
          g_irib.instFlag = false;
          g_jog_info.isRelease = s_ctrl_info.value;//按键是否释放  按下:1 释放:0
          g_wakeup_b3 = 0x3;
          g_rc_plc_share_memory->stat.status_w.bit3 = 1;
          rt_sem_broadcast(&g_rt_sem);
          std::printf("复位按键: %d\n",s_ctrl_info.value);
        }
        else if (s_ctrl_info.key == 0x00000100)//试运行
        {
          memset(&g_program_try_pointData, 0, sizeof (struct Program_PointData));
          g_server_tcp.MyRead(&g_program_try_pointData, sizeof (struct Program_PointData));
          for (int i = 0; i < 6; i++)
          {
              cout << "g_program_try_pointData.joints["<< i << "]=" << g_program_try_pointData.joints[i] <<endl;
          }
          g_irib.instFlag = false;
          g_jog_info.isRelease = s_ctrl_info.value;//按键是否释放  按下:1 释放:0
          g_wakeup_b3 = 0x5;
          g_rc_plc_share_memory->stat.status_w.bit3 = 1;
          rt_sem_broadcast(&g_rt_sem);
          std::printf("试运行按键: %d\n",s_ctrl_info.value);
        }
      #if 0
              //rc_state.mode=rc_c.mode;
              rc_state.start=rc_c.start;
              rc_state.move_mode=rc_c.move_mode;
              rc_state.exec_status=rc_c.exec_status;
              printf("!!!!!!!!!!!!!!!!!!!!rc_state.exec_status=%d\n",rc_state.exec_status);
      #endif
#if 1
        printf("g_rc_state.mode=%d-----g_rc_state.start=%d\n", g_rc_state.mode, g_rc_state.start);
        if (g_rc_state.mode == 1 && g_rc_state.start == 1)
        {
            cout << "b2开始编译文件" << endl;
            //向B2发送消息后阻塞监听示教器
            rt_sem_broadcast(&g_rt_sem_B2);
        }
//        if (start_run == 1)
//        {
////              sleep(1);
//            cout << "b2开始运行" << endl;
//            rt_sem_broadcast(&g_rt_sem_StartRun);
//            start_run = 0;
//        }
#endif
    }
    PRINTF_INFO_MESSAGE("---------------B1线程结束!");
    return ;
}


int main()
{

    //启动线程1
    XenomaiTask task_first;
    if (!task_first.xeno_task_create("Mytask_first", 0, 50, 0))
    {
        PRINTF_ERR_MESSAGE("create B1 task_first error!");
        return -1;
    }
    if (!task_first.xeno_task_start(task_function_first, nullptr))
    {
        PRINTF_ERR_MESSAGE("start B1 task_first error!");
        return -1;
    }

    getchar();
    return 0;
}
