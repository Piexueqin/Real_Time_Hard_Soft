#include "./include/mycommand.h"

/**************************RCStatementBase*******************************************/
RCStatementBase::RCStatementBase()
{
    pDataSpace=new vector<struct InnerData>();
    bInsertedList=false;
    instType=0;
}
RCStatementBase::~RCStatementBase()
{
    delete pDataSpace;
}

/***************************CodeModel********************************************/
CodeModel::CodeModel()
{

}
CodeModel::~CodeModel()
{

}
void CodeModel::executor()
{
//    cout << "pc=" << pc << endl;
//    cout << "lineno=" << StatementSpace.at(pc)->lineno << endl;
//    StatementSpace.at(pc)->excute();
//    lineno=StatementSpace.at(pc)->lineno;
    for (int i = 0; i < StatementSpace.size(); i++)
    {
        StatementSpace.at(i)->excute();
    }
}
void CodeModel::clear()
{
    cout << "void CodeModel::clear()" << endl;
    if(StatementSpace.size()>0)
    {
        for(int i=0;i<StatementSpace.size();i++)
        {
            delete StatementSpace[i];
            StatementSpace[i]=NULL;
        }
    }
    StatementSpace.clear();
    if(DataSpace.size()>0)
    {
        for(int i=0;i<DataSpace.size();i++)
        {
            switch (DataSpace.at(i).type) {
            case 0:
                delete DataSpace.at(i).v.value_b;
                DataSpace.at(i).v.value_b=NULL;
                break;
            case 1:
                delete DataSpace.at(i).v.value_c;
                DataSpace.at(i).v.value_c=NULL;
                break;
            case 2:
                delete DataSpace.at(i).v.value_i;
                DataSpace.at(i).v.value_i=NULL;
                break;
            case 3:
                delete DataSpace.at(i).v.value_d;
                DataSpace.at(i).v.value_d=NULL;
                break;
            case 4:
                delete DataSpace.at(i).v.value_s;
                DataSpace.at(i).v.value_s=NULL;
                break;
            case 5:
                delete DataSpace.at(i).v.value_jointt;
                DataSpace.at(i).v.value_jointt=NULL;
                break;
            case 6:
                delete DataSpace.at(i).v.value_speed;
                DataSpace.at(i).v.value_speed=NULL;
                break;
            case 7:
                delete DataSpace.at(i).v.value_zone;
                DataSpace.at(i).v.value_zone=NULL;
                break;
            case 8:
                delete DataSpace.at(i).v.value_tool;
                DataSpace.at(i).v.value_tool=NULL;
                break;
            case 9:
                delete DataSpace.at(i).v.value_wobj;
                DataSpace.at(i).v.value_wobj=NULL;
                break;
            case 10:
                delete DataSpace.at(i).v.value_rob;
                DataSpace.at(i).v.value_rob=NULL;
                break;
            }
        }
    }
    DataSpace.clear();
    SymbolTable.clear();
}
/**************************RCStatementMovj********************************************/
RCStatementMovj::RCStatementMovj()
{
    instType = 4;
}
RCStatementMovj::~RCStatementMovj()
{
    cout << "~RCStatementMovj()" << endl;

}
void RCStatementMovj::excute()
{
    cout << "RCStatementMovj" << endl;
//    displayData(*pDataSpace);
    //将命令写入指令内存缓冲区
    if(!bInsertedList)
    {
        cout << "_G_instList.push_back(inner);" << endl;
        bInsertedList = true;
        struct In_rbt_inst inner;
        inner.instType = instType;
        inner.movParam.MOVJ = new MOVJParam();
        inner.movParam.MOVJ->ToPoint = *pDataSpace->at(0).v.value_rob;
        inner.movParam.MOVJ->Speed = *pDataSpace->at(1).v.value_speed;
        inner.movParam.MOVJ->Zone = *pDataSpace->at(2).v.value_zone;
        inner.movParam.MOVJ->Tool = *pDataSpace->at(3).v.value_tool;

        _G_instList.push_back(inner);
    }

}

/*************************RCStatementMovc*******************************************/
RCStatementMovc::RCStatementMovc()
{
    instType = 6;
}
RCStatementMovc::~RCStatementMovc()
{

}
void RCStatementMovc::excute()
{
    cout << "RCStatementMovc" << endl;
    displayData(*pDataSpace);
    //将命令写入指令内存缓冲区
    if(!bInsertedList)
    {
        cout << "_G_instList.push_back(inner);" << endl;
        bInsertedList = true;
        struct In_rbt_inst inner;
        inner.instType = instType;
        inner.movParam.MOVC = new MOVCParam();
        inner.movParam.MOVC->MidPoint = *pDataSpace->at(0).v.value_rob;
        inner.movParam.MOVC->ToPoint = *pDataSpace->at(1).v.value_rob;
        inner.movParam.MOVC->Speed = *pDataSpace->at(2).v.value_speed;
        inner.movParam.MOVC->Zone = *pDataSpace->at(3).v.value_zone;
        inner.movParam.MOVC->Tool = *pDataSpace->at(4).v.value_tool;

        _G_instList.push_back(inner);
    }
}

/**************************RCStatementMovl*****************************************/
RCStatementMovl::RCStatementMovl()
{
    instType=5;
}
RCStatementMovl::~RCStatementMovl()
{

}
void RCStatementMovl::excute()
{
    cout << "RCStatementMovl::excute()" << endl;
//    displayData(*pDataSpace);
    //将命令写入指令内存缓冲区
    if(!bInsertedList)
    {
        cout << "_G_instList.push_back(inner);" << endl;
        bInsertedList=true;
        struct In_rbt_inst inner;
        inner.instType=instType;
        inner.movParam.MOVL=new MOVLParam();
        inner.movParam.MOVL->ToPoint=*pDataSpace->at(0).v.value_rob;
        inner.movParam.MOVL->Speed=*pDataSpace->at(1).v.value_speed;
        inner.movParam.MOVL->Zone=*pDataSpace->at(2).v.value_zone;
        inner.movParam.MOVL->Tool=*pDataSpace->at(3).v.value_tool;

        _G_instList.push_back(inner);
    }

}

/*************************RCStatementMovabsj******************************************/
RCStatementMovabsj::RCStatementMovabsj()
{
    instType=7;
}
RCStatementMovabsj::~RCStatementMovabsj()
{

}
void RCStatementMovabsj::excute()
{
    cout << "RCStatementMovabsj::excute()" << endl;
//    displayData(*pDataSpace);
    //将命令写入指令内存缓冲区
    if(!bInsertedList)
    {
        cout << "_G_instList.push_back(inner);" << endl;
        bInsertedList=true;
        struct In_rbt_inst inner;
        inner.instType=instType;
        inner.movParam.MOVABSJ=new MOVABSJParam();
        inner.movParam.MOVABSJ->ToJointPoint=*pDataSpace->at(0).v.value_jointt;
        inner.movParam.MOVABSJ->Speed=*pDataSpace->at(1).v.value_speed;
        inner.movParam.MOVABSJ->Zone=*pDataSpace->at(2).v.value_zone;
        inner.movParam.MOVABSJ->Tool=*pDataSpace->at(3).v.value_tool;

        _G_instList.push_back(inner);
    }

}

/******************************************************************************************/
RCStatementDelay::RCStatementDelay()
{

}
RCStatementDelay::~RCStatementDelay()
{

}
void RCStatementDelay::excute(){
    cout << "RCStatementDelay" << endl;
//    displayData(*pDataSpace);
    //延时
    if(!bInsertedList)
    {
        bInsertedList=true;
    }
    else
    {
        sleep(*pDataSpace->at(0).v.value_d);
    }

}





/**************************************************************************/
void displayData(vector<struct InnerData> data)
{
    cout << "11111111111111" << endl;
    for(int i=0;i<data.size();i++)
    {
        switch (data.at(i).type) {
        case 0:
            cout << __LINE__ << " bool " << *data.at(i).v.value_b << endl;
            break;
        case 1:
            cout << __LINE__ << " char " << *data.at(i).v.value_c << endl;
            break;
        case 2:
            cout << __LINE__ << " int " << *data.at(i).v.value_i << endl;
            break;
        case 3:
            cout << __LINE__ << " double " << *data.at(i).v.value_d << endl;
            break;
        case 4:
            cout << __LINE__ << " string " << *data.at(i).v.value_s << endl;
            break;
        case 5:
            cout << "2222222222222222222" << endl;
            cout << __LINE__ << " jointtarget " << data.at(i).v.value_jointt->robax.J1 << " "
                                                << data.at(i).v.value_jointt->robax.J2 << " "
                                                << data.at(i).v.value_jointt->robax.J3 << " "
                                                << data.at(i).v.value_jointt->robax.J4 << " "
                                                << data.at(i).v.value_jointt->robax.J5 << " "
                                                << data.at(i).v.value_jointt->robax.J6 << " "
                                                << data.at(i).v.value_jointt->extax.e1 << " "
                                                << data.at(i).v.value_jointt->extax.e2 << " "
                                                << data.at(i).v.value_jointt->extax.e3 << " "
                                                << data.at(i).v.value_jointt->extax.e4 << " "
                                                << data.at(i).v.value_jointt->extax.e5 << " "
                                                << data.at(i).v.value_jointt->extax.e6 << endl;

            break;
        case 6:
            cout << __LINE__ << " speeddata " << data.at(i).v.value_speed->j_per << " "
                                                << data.at(i).v.value_speed->tcp_per << " "
                                                << data.at(i).v.value_speed->tcp_rot << " "
                                                << data.at(i).v.value_speed->exj_line << " "
                                                << data.at(i).v.value_speed->exj_rot << endl;
            break;
        case 7:
            cout << __LINE__ << " zonedata " << data.at(i).v.value_zone->distance << endl;
            break;
        case 8:
            cout << __LINE__ << " tooldata " << data.at(i).v.value_tool->robhold << " "
                                             << data.at(i).v.value_tool->tframe.thans.X << " "
                                             << data.at(i).v.value_tool->tframe.thans.Y << " "
                                             << data.at(i).v.value_tool->tframe.thans.Z << " "
                                             << data.at(i).v.value_tool->tframe.rot.A << " "
                                             << data.at(i).v.value_tool->tframe.rot.B << " "
                                             << data.at(i).v.value_tool->tframe.rot.C << " "
                                             << data.at(i).v.value_tool->tload.mass << " "
                                             << data.at(i).v.value_tool->tload.cog.X << " "
                                             << data.at(i).v.value_tool->tload.cog.Y << " "
                                             << data.at(i).v.value_tool->tload.cog.Z << " "
                                             << data.at(i).v.value_tool->tload.aom.A << " "
                                             << data.at(i).v.value_tool->tload.aom.B << " "
                                             << data.at(i).v.value_tool->tload.aom.C << " "
                                             << data.at(i).v.value_tool->tload.ix << " "
                                             << data.at(i).v.value_tool->tload.iy << " "
                                             << data.at(i).v.value_tool->tload.iz << endl;
            break;
        case 9:
            cout << __LINE__ << " wobjdata " << data.at(i).v.value_wobj->robhald << " "
                                             << data.at(i).v.value_wobj->ufprog << " "
                                             << data.at(i).v.value_wobj->oframe.thans.X << " "
                                             << data.at(i).v.value_wobj->oframe.thans.Y << " "
                                             << data.at(i).v.value_wobj->oframe.thans.Z << " "
                                             << data.at(i).v.value_wobj->oframe.rot.A << " "
                                             << data.at(i).v.value_wobj->oframe.rot.B << " "
                                             << data.at(i).v.value_wobj->oframe.rot.C << " "
                                             << data.at(i).v.value_wobj->ufram_id << endl;
            break;
        default:
            break;
        }
    }
}

//清空在MOVABSJ等类的execute函数中new出来的插补类型结构体，切换程序时使用
void clearinList()
{
    for(int i=0;i<_G_instList.size();i++)
    {
        if(_G_instList.at(i).instType==7)
        {
            delete _G_instList.at(i).movParam.MOVABSJ;
            _G_instList.at(i).movParam.MOVABSJ=NULL;
        }
        else if(_G_instList.at(i).instType==5)
        {
            delete _G_instList.at(i).movParam.MOVL;
            _G_instList.at(i).movParam.MOVL=NULL;
        }
    }
    _G_instList.clear();
}





