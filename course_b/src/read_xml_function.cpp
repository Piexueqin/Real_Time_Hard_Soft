#include "../include/read_xml_function.h"


#define Printf_info  1  //是否打印调试信息

//加载XML文件名字
bool LoadXml(const char* filename, XMLDocument &doc)
{
    //加载xml文件
    if ( XML_SUCCESS != doc.LoadFile(filename))
    {
         return false;
    }
    return true;
}

//读取xml文件 此函数是根据xml文件的写的参数配置，如xml文件改变了结构，此函数不一定有用
bool ReadConfigXml(XMLDocument &doc, robot_config &Robot_Config, servo_config &Servo_Config, aux_config &Add_ax_config)
{
    XMLElement *config = doc.RootElement(); //加载整个文档到config中
    if (!config)
    {
         return false;
    }
    //  <!-- dh参数类型：mdh = 0，sdh = 1 -->
    XMLElement *robot = config->FirstChildElement("robot_param");
    if (!robot)
    {
        return false;
    }

    Robot_Config.configuration = robot->Attribute("configuration");
    Robot_Config.num_of_links = *robot->Attribute("num_of_links");
    Robot_Config.num_of_tools = *robot->Attribute("num_of_tools");
    Robot_Config.num_of_wobjs = *robot->Attribute("num_of_wobjs");
    Robot_Config.num_of_users = *robot->Attribute("num_of_users");
    Robot_Config.num_of_trajs = *robot->Attribute("num_of_trajs");
    Robot_Config.name_of_robot = robot->Attribute("name_of_robot");
    Robot_Config.dh_type = *robot->Attribute("dh_type");

    //link_param
    XMLElement *link = robot->FirstChildElement();

    for (int i = 0; link; i++)
    {
        Robot_Config.link_param[i].name = link->Attribute("name");
        Robot_Config.link_param[i].id = *link->Attribute("id");
        Robot_Config.link_param[i].joint_type = *link->Attribute("joint_type");
        //dh
        XMLElement *dh = link->FirstChildElement("dh");

        const XMLAttribute *temp = dh->FirstAttribute();  //第一个属性
        for (int j = 0 ; temp; j++)
        {
            Robot_Config.link_param[i].dh[j] = stod(temp->Value());
            temp = temp->Next(); //指向下一个属性
        }

        XMLElement *pos_limit = link->FirstChildElement("pos_limit");
        Robot_Config.link_param[i].pos_limit[0] = stod(pos_limit->Attribute("min"));
        Robot_Config.link_param[i].pos_limit[1] = stod(pos_limit->Attribute("max"));

        XMLElement *vel_limit=link->FirstChildElement("vel_limit");
        Robot_Config.link_param[i].vel_limit[0] = stod(vel_limit->Attribute("min"));
        Robot_Config.link_param[i].vel_limit[1] = stod(vel_limit->Attribute("max"));

        XMLElement *acc_limit=link->FirstChildElement("acc_limit");
        Robot_Config.link_param[i]. acc_limit[0] = stod(acc_limit->Attribute("min"));
        Robot_Config.link_param[i]. acc_limit[1] = stod(acc_limit->Attribute("max"));

        XMLElement *jerk_limit=link->FirstChildElement("jerk_limit");
        Robot_Config.link_param[i]. jerk_limit[0] = stod(jerk_limit->Attribute("min"));
        Robot_Config.link_param[i]. jerk_limit[1] = stod(jerk_limit->Attribute("max"));

        XMLElement *mass = link->FirstChildElement("mass");
        Robot_Config.link_param[i].mass = stod(mass->Attribute("value"));

        XMLElement *cog = link->FirstChildElement("cog");
        Robot_Config.link_param[i].cog[0]=stod(cog->Attribute("x"));
        Robot_Config.link_param[i].cog[1]=stod(cog->Attribute("y"));
        Robot_Config.link_param[i].cog[2]=stod(cog->Attribute("z"));

        XMLElement *inertia = link->FirstChildElement("inertia");
        Robot_Config.link_param[i].inertia[0] = stod(inertia->Attribute("ixx"));
        Robot_Config.link_param[i].inertia[1] = stod(inertia->Attribute("ixy"));
        Robot_Config.link_param[i].inertia[2] = stod(inertia->Attribute("ixz"));
        Robot_Config.link_param[i].inertia[3] = stod(inertia->Attribute("iyy"));
        Robot_Config.link_param[i].inertia[4] = stod(inertia->Attribute("iyz"));
        Robot_Config.link_param[i].inertia[5] = stod(inertia->Attribute("izz"));

        link = link->NextSiblingElement();  //指向下一个兄弟节点
        if (0 == strcmp(link->Value(),"tool_param"))  //检测到tool_param节点退出循环
        {
            break;
        }

    }

    //tool_param
    XMLElement *tool_param = robot->FirstChildElement("tool_param");
    if (!tool_param)
    {
        return false;
    }

    for(int i = 0; tool_param; i++)
    {
        Robot_Config.tool_param[i].name = tool_param->Attribute("name");
        Robot_Config.tool_param[i].id = *tool_param->Attribute("id");

        XMLElement *robhold = tool_param->FirstChildElement("robhold");
        Robot_Config.tool_param[i].robhold = *robhold->Attribute("value");

        XMLElement *pos = tool_param->FirstChildElement("pos");
        Robot_Config.tool_param->pos[0] = stod(pos->Attribute("x"));
        Robot_Config.tool_param->pos[1] = stod(pos->Attribute("y"));
        Robot_Config.tool_param->pos[2] = stod(pos->Attribute("z"));

        XMLElement *orient = tool_param->FirstChildElement("orient");
        Robot_Config.tool_param->orient[0] = stod(orient->Attribute("u"));
        Robot_Config.tool_param->orient[1] = stod(orient->Attribute("v"));
        Robot_Config.tool_param->orient[2] = stod(orient->Attribute("w"));

        XMLElement *mass = tool_param->FirstChildElement("mass");
        Robot_Config.tool_param[i].mass = stod(mass->Attribute("value"));

        XMLElement *cog = tool_param->FirstChildElement("cog");
        Robot_Config.tool_param->cog[0] = stod(cog->Attribute("x"));
        Robot_Config.tool_param->cog[1] = stod(cog->Attribute("y"));
        Robot_Config.tool_param->cog[2] = stod(cog->Attribute("z"));

        XMLElement *inertia = tool_param->FirstChildElement("inertia");
        Robot_Config.tool_param->inertia[0] = stod(inertia->Attribute("ixx"));
        Robot_Config.tool_param->inertia[1] = stod(inertia->Attribute("ixy"));
        Robot_Config.tool_param->inertia[2] = stod(inertia->Attribute("ixz"));

        tool_param = tool_param->NextSiblingElement();  //指向下一个兄弟节点
        if (0 == strcmp(tool_param->Value(),"wobj_param"))  //检测到wobj_param节点退出循环
        {
            break;
        }
    }

    XMLElement *wobj_param = robot->FirstChildElement("wobj_param");
    if (!wobj_param)
    {
        return false;
    }

    for (int i = 0; wobj_param; i++)
    {
        Robot_Config.wobj_param[i].name = wobj_param->Attribute("name");
        Robot_Config.wobj_param[i].id = *wobj_param->Attribute("id");

        XMLElement *pos = wobj_param->FirstChildElement("pos");
        Robot_Config.wobj_param[i].pos[0] = stod(pos->Attribute("x"));
        Robot_Config.wobj_param[i].pos[1] = stod(pos->Attribute("y"));
        Robot_Config.wobj_param[i].pos[2] = stod(pos->Attribute("z"));

        XMLElement *orient = wobj_param->FirstChildElement("orient");
        Robot_Config.wobj_param[i].orient[0] = stod(orient->Attribute("u"));
        Robot_Config.wobj_param[i].orient[1] = stod(orient->Attribute("v"));
        Robot_Config.wobj_param[i].orient[2] = stod(orient->Attribute("w"));
        wobj_param = wobj_param->NextSiblingElement();  //指向下一个兄弟节点
        if (0 == strcmp(wobj_param->Value(), "user_param"))  //检测到user_param节点退出循环
        {
          break;
        }
    }

    XMLElement *user_param = robot->FirstChildElement("user_param");
    if (!user_param)
    {
        return false;
    }

    for( int i = 0; user_param; i++)
    {
        Robot_Config.user_param[i].name = user_param->Attribute("name");
        Robot_Config.user_param[i].id = *user_param->Attribute("id");

        XMLElement *pos = user_param->FirstChildElement("pos");
        Robot_Config.user_param[i].pos[0] = stod(pos->Attribute("x"));
        Robot_Config.user_param[i].pos[1] = stod(pos->Attribute("y"));
        Robot_Config.user_param[i].pos[2] = stod(pos->Attribute("z"));

        XMLElement *orient = user_param->FirstChildElement("orient");
        Robot_Config.user_param[i].orient[0] = stod(orient->Attribute("u"));
        Robot_Config.user_param[i].orient[1] = stod(orient->Attribute("v"));
        Robot_Config.user_param[i].orient[2] = stod(orient->Attribute("w"));

        user_param = user_param->NextSiblingElement();  //指向下一个兄弟节点
        if (0 == strcmp(user_param->Value(),"traj_param"))  //检测到traj_param节点退出循环
        {
        break;
        }
    }

    XMLElement *traj_param = robot->FirstChildElement("traj_param");
    if (!traj_param)
    {
        return false;
    }

    for(int i = 0; traj_param; i++)
    {
        Robot_Config.traj_param[i].type = *traj_param->Attribute("type");

        XMLElement *vel_max = traj_param->FirstChildElement("vel_max");
        Robot_Config.traj_param[i].vel_max = stod(vel_max->Attribute("value"));

        XMLElement *acc_max = traj_param->FirstChildElement("acc_max");
        Robot_Config.traj_param[i].acc_max = stod(acc_max->Attribute("value"));

        XMLElement *jerk_max = traj_param->FirstChildElement("jerk_max");
        Robot_Config.traj_param[i].jerk_max = stod(jerk_max->Attribute("value"));

        XMLElement *Ta = traj_param->FirstChildElement("Ta");
        Robot_Config.traj_param[i].Ta = stod(Ta->Attribute("value"));

        XMLElement *Tj = traj_param->FirstChildElement("Tj");
        Robot_Config.traj_param[i].Tj = stod(Tj->Attribute("value"));

        traj_param = traj_param->NextSiblingElement();  //指向下一个兄弟节点
        //因为没有下个兄弟节点，因此直接退出循环
    }

    //读取servo_param
    XMLElement *servo_param = config->FirstChildElement("servo_param");
    if (!robot)
    {
        return false;
    }

    Servo_Config.num_of_servos = *servo_param->Attribute("num_of_servos");
    Servo_Config.bus_type = *servo_param->Attribute("bus_type");
    Servo_Config.period = stof(servo_param->Attribute("period"));

    XMLElement *servo = servo_param->FirstChildElement("servo");

    for(int i = 0; servo; i++)
    {
        XMLElement *name = servo->FirstChildElement("name");
        Servo_Config.servo_param[i].name = name->Attribute("value");

        XMLElement *dev_id = servo->FirstChildElement("dev_id");
        Servo_Config.servo_param[i].dev_id = *dev_id->Attribute("value");

        XMLElement *link_id = servo->FirstChildElement("link_id");
        Servo_Config.servo_param[i].link_id = *link_id->Attribute("value");

        XMLElement *run_mode = servo->FirstChildElement("run_mode");
        Servo_Config.servo_param[i].run_mode = *run_mode->Attribute("value");

        XMLElement *pos_limit = servo->FirstChildElement("pos_limit");
        Servo_Config.servo_param[i].pos_limit[0] = stod(pos_limit->Attribute("min"));
        Servo_Config.servo_param[i].pos_limit[1] = stod(pos_limit->Attribute("max"));

        XMLElement *ratio = servo->FirstChildElement("ratio");
        Servo_Config.servo_param[i].ratio = stod(ratio->Attribute("value"));

        XMLElement *encoder_bits = servo->FirstChildElement("encoder_bits");
        Servo_Config.servo_param[i].encoder_bits = stoi(encoder_bits->Attribute("value"));

        servo = servo->NextSiblingElement();
    }

    XMLElement *aux_param = config->FirstChildElement("aux_param");
    if (!aux_param)
    {
        return false;
    }

    //附加轴配置
    //aux_param_config Add_ax_config;
    Add_ax_config.num_of_auxs = *aux_param->Attribute("num_of_auxs");

    XMLElement *aux = aux_param->FirstChildElement("aux");
    for (int i = 0; aux; i++)
    {
        XMLElement *name = aux->FirstChildElement("name");
        Add_ax_config.aux_param[i].name = name->Attribute("value");

        XMLElement *type = aux->FirstChildElement("type");
        Add_ax_config.aux_param[i].type = *type->Attribute("value");

        XMLElement *ratio = aux->FirstChildElement("ratio");
        Add_ax_config.aux_param[i].ratio = stod(ratio->Attribute("value"));

        XMLElement *bus_id = aux->FirstChildElement("bus_id");
        Add_ax_config.aux_param[i].bus_id = *bus_id->Attribute("value");

        XMLElement *pos_limit = aux->FirstChildElement("pos_limit");
        Add_ax_config.aux_param[i].pos_limit[0] = stod(pos_limit->Attribute("min"));
        Add_ax_config.aux_param[i].pos_limit[1] = stod(pos_limit->Attribute("max"));

        XMLElement *vel_limit = aux->FirstChildElement("vel_limit");
        Add_ax_config.aux_param[i].vel_limit[0] = stod(vel_limit->Attribute("min"));
        Add_ax_config.aux_param[i].vel_limit[1] = stod(vel_limit->Attribute("max"));

        XMLElement *acc_limit=aux->FirstChildElement("acc_limit");
        Add_ax_config.aux_param[i].acc_limit[0] = stod(acc_limit->Attribute("min"));
        Add_ax_config.aux_param[i].acc_limit[1] = stod(acc_limit->Attribute("max"));

        XMLElement *jerk_limit = aux->FirstChildElement("jerk_limit");
        Add_ax_config.aux_param[i].jerk_limit[0] = stod(jerk_limit->Attribute("min"));
        Add_ax_config.aux_param[i].jerk_limit[1] = stod(jerk_limit->Attribute("max"));

        aux=aux->NextSiblingElement();
    }
    return true;
}

//读取xml文件 此函数是根据xml文件的写的参数配置，如xml文件改变了结构，此函数不一定有用，解析会出现段错误
//此函数功能不全，暂不使用，使用会出现段错误
bool ReadCalibrationXml(XMLDocument &doc, Calibration_Config &calibration_config)
{
    XMLElement *calibration = doc.RootElement();
    if (!calibration)
    {
        return false;
    }

    //robot
    XMLElement *robot = calibration->FirstChildElement("robot");
    if (!robot)
    {
        return false;
    }

    calibration_config.robot_configuration = *robot->Attribute("configuration");//取字符型参数
    calibration_config.robot_name = robot->Attribute("name");//取字符型参数
    calibration_config.link_num = atoi(robot->Attribute("num_of_links"));//取字符型参数
    calibration_config.DH_type = *robot->Attribute("dh_type");//取字符型参数

   // cout<<robot->Value()<<" configuration="<<calibration_config.robot_configuration
    //<<" name="<<calibration_config.robot_name
    //    <<" num_of_links="<<calibration_config.link_num
    //	<<" dh_type="<<calibration_config.DH_type<<endl;

    //link
    XMLElement *Link=robot->FirstChildElement();
    for(int i=0;Link;i++)
    {
        // cout<<"++++++++++++++"<<endl;


         calibration_config.link[i].link_name=Link->Attribute("name");
         calibration_config.link[i].link_id=*Link->Attribute("id");
         calibration_config.link[i].joint_type=*Link->Attribute("joint_type");


        // cout<<Link->Value()<<" name="<<calibration_config.link[i].link_name
        //  <<" id="<< calibration_config.link[i].link_id
         //    <<" joint_type="<< calibration_config.link[i].joint_type<<endl;

         //offset
         XMLElement *offset=Link->FirstChildElement("offset");
         if(!offset)
            return false;
        // cout<<offset->Value()<<endl; //

         //theta_zero
         XMLElement *theta_zero=offset->FirstChildElement("theta_zero");
          calibration_config.link[i].theta_zero=stod(theta_zero->Attribute("value"));

        // cout<<theta_zero->Value()<<" value="<<calibration_config.link[i].theta_zero<<endl;

         //a_zero
         XMLElement *a_zero=offset->FirstChildElement("a_zero");
          calibration_config.link[i].a_zero=stod(a_zero->Attribute("value"));
        // cout<<a_zero->Value()<<" value="<< calibration_config.link[i].a_zero<<endl;

         //theta_zero
         XMLElement *d_zero=offset->FirstChildElement("d_zero");

          calibration_config.link[i].d_zero=stod(d_zero->Attribute("value"));
        // cout<<d_zero->Value()<<" value="<<calibration_config.link[i].d_zero<<endl;

         //theta_zero
         XMLElement *ratio_zero=offset->FirstChildElement("ratio_zero");

         calibration_config.link[i].ratio_zero=stod(ratio_zero->Attribute("value"));
        // cout<<ratio_zero->Value()<<" value="<<calibration_config.link[i].ratio_zero<<endl;

        Link=Link->NextSiblingElement();

        if(0==strcmp(Link->Value(),"tcp_calibration"))  //退出
            break;
    }

    //cout<<"///////////////////////////////////"<<endl;
    //tcp_calibration
    XMLElement *tcp_calibration=robot->FirstChildElement("tcp_calibration");
    if(!tcp_calibration)
        return false;


    calibration_config.tcp_calibration_num=atoi(tcp_calibration->Attribute("num"));

  //  cout<<tcp_calibration->Value()<<" num="<<calibration_config.tcp_calibration_num<<endl;

    XMLElement *tcp=tcp_calibration->FirstChildElement("tcp");
    while(tcp)
    {

        calibration_config.tool_csys.csys_name=tcp->Attribute("name");
        calibration_config.tool_csys.csys_id=*tcp->Attribute("id");

    //   cout<<tcp->Value()<<" name="<<calibration_config.tool_csys.csys_name
                //<<" id="<<calibration_config.tool_csys.csys_id<<endl;


       XMLElement *matrix=tcp->FirstChildElement("matrix");

        const XMLAttribute *tem=matrix->FirstAttribute();

        for(int j=0;j<12;j++)
        {
            calibration_config.tool_csys.csysmatrix[j]=stod(tem->Value());

            //cout<<calibration_config.tool_csys.csysmatrix[j]<<" ";
            tem=tem->Next();
        }

    //	cout<<endl;

       /*
       cout<<matrix->Value()<<" r11="<<stod(matrix->Attribute("r11"))<<" r12="<<stod(matrix->Attribute("r12"))
           <<" r13="<<stod(matrix->Attribute("r13"))<<" r21="<<stod(matrix->Attribute("r21"))
           <<" r22="<<stod(matrix->Attribute("r22"))<<" r23="<<stod(matrix->Attribute("r23"))
           <<" r31="<<stod(matrix->Attribute("r31"))<<" r32="<<stod(matrix->Attribute("r32"))
           <<" r33="<<stod(matrix->Attribute("r33"))<<" x="<<stod(matrix->Attribute("x"))
           <<" y="<<stod(matrix->Attribute("y"))<<" z="<<stod(matrix->Attribute("z"))<<endl;
       */

       tcp=tcp->NextSiblingElement();
    }


    XMLElement *user_coordinate_calibration=robot->FirstChildElement("user_coordinate_calibration");
    if(!user_coordinate_calibration)
        return false;


    calibration_config.user_coordinate_calibration_num=atoi(user_coordinate_calibration->Attribute("num"));

   // cout<<user_coordinate_calibration->Value()<<" num="<<calibration_config.user_coordinate_calibration_num<<endl;


    XMLElement *user_coordinate=user_coordinate_calibration->FirstChildElement("user_coordinate");

    while(user_coordinate)
    {

        calibration_config.user_coordinate.csys_name=user_coordinate->Attribute("name");
        calibration_config.user_coordinate.csys_id=*user_coordinate->Attribute("id");

      // cout<<user_coordinate->Value()<<" name="<<calibration_config.user_coordinate.csys_name
            //	<<" id="<<calibration_config.user_coordinate.csys_id<<endl;

       XMLElement *matrix=user_coordinate->FirstChildElement("matrix");


        const XMLAttribute *tem=matrix->FirstAttribute();

        for(int j=0;j<12;j++)
        {
            calibration_config.user_coordinate.csysmatrix[j]=stod(tem->Value());

            //cout<<calibration_config.user_coordinate.csysmatrix[j]<<" ";
            tem=tem->Next();
        }

    //	cout<<endl;
       user_coordinate=user_coordinate->NextSiblingElement();
    }
    return true;
}



