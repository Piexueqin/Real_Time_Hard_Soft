#ifndef READ_XML_FUNCTION_H
#define READ_XML_FUNCTION_H

#include <iostream>
using namespace std;
#include "tinyxml2.h"
using namespace tinyxml2;
#include "robot_datastruct.h"

/*****************
 *
 * 此文件函数需要根据相应文件里的内容格式解析，解析错误，出现段错误
 * 此文件根据文件里相应的变量名解析，如变量名改变，请在相应函数里改变相应名
 *
 ******************/



//加载xml文件，生成 doc
bool LoadXml(const char* filename, XMLDocument &doc);
//解析configxml文件，将变量赋值给相应的结构体
bool ReadConfigXml(XMLDocument &doc, robot_config &Robot_Config, servo_config &Servo_Config, aux_config &Add_ax_config);

//暂未使用，需根据calibration xml文件来修改功能
bool ReadCalibrationXml( XMLDocument &doc, Calibration_Config &calibration_config);

#endif // READ_XML_FUNCTION_H
