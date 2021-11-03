#include "myvisitor.h"


/*************************MyDataVisitor*******************************************/
MyDataVisitor::MyDataVisitor(CodeModel *codeModel)
{
    code=codeModel;
}

antlrcpp::Any MyDataVisitor::visitFile(robDataParser::FileContext *ctx)
{
    cout << __LINE__ << " " << ctx->ID()->toString() << endl;
    cout << __LINE__ << " " << ctx->STRING()->toString() << endl;
    cout << __LINE__ << " " << ctx->INT()->toString() << endl;

    struct InnerData inner;
    string varName=ctx->ID()->toString();
    string str=ctx->STRING()->toString();
    str.erase(0,1);
    str.erase(str.size()-1,1);
    int iVarType=stoi(ctx->INT()->toString());

    inner.type=iVarType;
    cout << __LINE__ << " " << inner.type << endl;
    if(0==iVarType)
    {
        inner.v.value_b=new bool();
        *inner.v.value_b=stoi(str);
        code->DataSpace.push_back(inner);
        code->SymbolTable.insert(pair<string,int>(varName,code->DataSpace.size()-1));
    }
    else if (1==iVarType) {
        inner.v.value_c=new char();
        *inner.v.value_c=*str.c_str();
        code->DataSpace.push_back(inner);
        code->SymbolTable.insert(pair<string,int>(varName,code->DataSpace.size()-1));
    }
    else if (2==iVarType) {
        inner.v.value_i=new int();
        *inner.v.value_i=stoi(str);
        code->DataSpace.push_back(inner);
        code->SymbolTable.insert(pair<string,int>(varName,code->DataSpace.size()-1));
    }
    else if (3==iVarType) {
        inner.v.value_d=new double();
        *inner.v.value_d=stod(str);
        code->DataSpace.push_back(inner);
        code->SymbolTable.insert(pair<string,int>(varName,code->DataSpace.size()-1));
    }
    else if (4==iVarType) {

        inner.v.value_s=new string();
        *inner.v.value_s=str;
        code->DataSpace.push_back(inner);
        code->SymbolTable.insert(pair<string,int>(varName,code->DataSpace.size()-1));
    }
    else if (5==iVarType) {
        double data[12];
        for(int i=0;i<12;i++)
        {
            data[i]=stod(str.substr(0,str.find(",")));
            str.erase(0,str.find(",")+1);
        }
        JointTarget joint;
        joint.robax.J1=data[0];
        joint.robax.J2=data[1];
        joint.robax.J3=data[2];
        joint.robax.J4=data[3];
        joint.robax.J5=data[4];
        joint.robax.J6=data[5];
        joint.extax.e1=data[6];
        joint.extax.e2=data[7];
        joint.extax.e3=data[8];
        joint.extax.e4=data[9];
        joint.extax.e5=data[10];
        joint.extax.e6=data[11];

        inner.v.value_jointt=new JointTarget();
        *inner.v.value_jointt=joint;
        code->DataSpace.push_back(inner);
        code->SymbolTable.insert(pair<string,int>(varName,code->DataSpace.size()-1));
    }
    else if (6==iVarType) {
        double data[5];
        for(int i=0;i<5;i++)
        {
            data[i]=stod(str.substr(0,str.find(",")));
            str.erase(0,str.find(",")+1);
        }

        SpeedData speed;
        speed.j_per=data[0];
        speed.tcp_per=data[1];
        speed.tcp_rot=data[2];
        speed.exj_line=data[3];
        speed.exj_rot=data[4];

        inner.v.value_speed=new SpeedData();
        *inner.v.value_speed=speed;
        code->DataSpace.push_back(inner);
        code->SymbolTable.insert(pair<string,int>(varName,code->DataSpace.size()-1));
    }
    else if (7==iVarType) {
        ZoneData zone;
        zone.distance=stod(str);

        inner.v.value_zone=new ZoneData();
        *inner.v.value_zone=zone;
        code->DataSpace.push_back(inner);
        code->SymbolTable.insert(pair<string,int>(varName,code->DataSpace.size()-1));
    }
    else if (8==iVarType) {
        ToolData tool;
        tool.robhold=stod(str.substr(0,str.find(",")));
        str.erase(0,str.find(",")+1);

        double my_t[16];
        for(int i=0;i<16;i++)
        {
            my_t[i]=stod(str.substr(0,str.find(",")));
            str.erase(0,str.find(",")+1);
        }

        tool.tframe.thans.X=my_t[0];
        tool.tframe.thans.Y=my_t[1];
        tool.tframe.thans.Z=my_t[2];
        tool.tframe.rot.A=my_t[3];
        tool.tframe.rot.B=my_t[4];
        tool.tframe.rot.C=my_t[5];
        tool.tload.mass=my_t[6];
        tool.tload.cog.X=my_t[7];
        tool.tload.cog.Y=my_t[8];
        tool.tload.cog.Z=my_t[9];
        tool.tload.aom.A=my_t[10];
        tool.tload.aom.B=my_t[11];
        tool.tload.aom.C=my_t[12];
        tool.tload.ix=my_t[13];
        tool.tload.iy=my_t[14];
        tool.tload.iz=my_t[15];

        inner.v.value_tool=new ToolData();
        *inner.v.value_tool=tool;
        code->DataSpace.push_back(inner);
        code->SymbolTable.insert(pair<string,int>(varName,code->DataSpace.size()-1));
    }
    else if (9==iVarType) {
        WobjData wobj;
        wobj.robhald=stod(str.substr(0,str.find(",")));
        str.erase(0,str.find(",")+1);
        wobj.ufprog=stod(str.substr(0,str.find(",")));
        str.erase(0,str.find(",")+1);

        double my_w[6];
        for(int i=0;i<6;i++)
        {
           my_w[i]=stod(str.substr(0,str.find(",")));
           str.erase(0,str.find(",")+1);
        }
        wobj.oframe.thans.X=my_w[0];
        wobj.oframe.thans.Y=my_w[1];
        wobj.oframe.thans.Z=my_w[2];
        wobj.oframe.rot.A=my_w[3];
        wobj.oframe.rot.A=my_w[4];
        wobj.oframe.rot.A=my_w[5];
        wobj.ufram_id=stoi(str.substr(0,str.find(",")));

        inner.v.value_wobj=new WobjData();
        *inner.v.value_wobj=wobj;
        code->DataSpace.push_back(inner);
        code->SymbolTable.insert(pair<string,int>(varName,code->DataSpace.size()-1));
    }
    else if (10==iVarType) {
        RobTarget rob;
        double my_r[16];
        for (int i = 0; i < 16; i++) {
            my_r[i]=stod(str.substr(0,str.find(",")));
            str.erase(0,str.find(",")+1);
        }
        rob.trans.X=my_r[0];
        rob.trans.Y=my_r[1];
        rob.trans.Z=my_r[2];
        rob.rot.A=my_r[3];
        rob.rot.B=my_r[4];
        rob.rot.C=my_r[5];
        rob.conf.cf1=my_r[6];
        rob.conf.cf4=my_r[7];
        rob.conf.cf6=my_r[8];
        rob.conf.cfx=my_r[9];
        rob.extax.e1=my_r[10];
        rob.extax.e2=my_r[11];
        rob.extax.e3=my_r[12];
        rob.extax.e4=my_r[13];
        rob.extax.e5=my_r[14];
        rob.extax.e6=my_r[15];

        inner.v.value_rob=new RobTarget();
        *inner.v.value_rob=rob;
        code->DataSpace.push_back(inner);
        code->SymbolTable.insert(pair<string,int>(varName,code->DataSpace.size()-1));
   }


    return visitChildren(ctx);
}


/*************************MyProgramVisitor*******************************************/
MyProgramVisitor::MyProgramVisitor(CodeModel *codeModel)
{
    code=codeModel;
    lineno=0;
}

antlrcpp::Any MyProgramVisitor::visitMovjExpr(robProgramParser::MovjExprContext *ctx)
{
    cout << __LINE__ << " " << ctx->ToPoint()->toString() << endl;
    cout << __LINE__ << " " << ctx->SpeedData()->toString() << endl;
    cout << __LINE__ << " " << ctx->ZoneData()->toString() << endl;
    cout << __LINE__ << " " << ctx->ToolData()->toString() << endl;
    RCStatementMovj *movj=new RCStatementMovj;
    cout << __LINE__ << " " << code->SymbolTable.find(ctx->ToPoint()->toString())->second << endl;
    cout << __LINE__ << " " << code->DataSpace[0].type << endl;
    movj->lineno=lineno;
    movj->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->ToPoint()->toString())->second]);
    movj->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->SpeedData()->toString())->second]);
    movj->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->ZoneData()->toString())->second]);
    movj->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->ToolData()->toString())->second]);
    if(ctx->WobjData()!=NULL)
        movj->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->WobjData()->toString())->second]);
    code->StatementSpace.push_back(movj);
    return visitChildren(ctx);
}

antlrcpp::Any MyProgramVisitor::visitMovlExpr(robProgramParser::MovlExprContext *ctx)
{
    cout << __LINE__ << " " << ctx->ToPoint()->toString() << endl;
    cout << __LINE__ << " " << ctx->SpeedData()->toString() << endl;
    cout << __LINE__ << " " << ctx->ZoneData()->toString() << endl;
    cout << __LINE__ << " " << ctx->ToolData()->toString() << endl;
    RCStatementMovl *movl=new RCStatementMovl();
    movl->lineno=lineno;
    movl->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->ToPoint()->toString())->second]);
    movl->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->SpeedData()->toString())->second]);
    movl->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->ZoneData()->toString())->second]);
    movl->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->ToolData()->toString())->second]);
    if(ctx->WobjData()!=NULL)
        movl->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->WobjData()->toString())->second]);
    code->StatementSpace.push_back(movl);
    return visitChildren(ctx);
}

antlrcpp::Any MyProgramVisitor::visitMovcExpr(robProgramParser::MovcExprContext *ctx)
{
    cout << __LINE__ << " " << ctx->MidPoint()->toString() << endl;
    cout << __LINE__ << " " << ctx->ToPoint()->toString() << endl;
    cout << __LINE__ << " " << ctx->SpeedData()->toString() << endl;
    cout << __LINE__ << " " << ctx->ZoneData()->toString() << endl;
    cout << __LINE__ << " " << ctx->ToolData()->toString() << endl;
    RCStatementMovc *movc=new RCStatementMovc();
    movc->lineno=lineno;
    movc->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->MidPoint()->toString())->second]);
    movc->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->ToPoint()->toString())->second]);
    movc->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->SpeedData()->toString())->second]);
    movc->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->ZoneData()->toString())->second]);
    movc->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->ToolData()->toString())->second]);
    if(ctx->WobjData()!=NULL)
        movc->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->WobjData()->toString())->second]);
    code->StatementSpace.push_back(movc);
    return visitChildren(ctx);
}

antlrcpp::Any MyProgramVisitor::visitMovabsjExpr(robProgramParser::MovabsjExprContext *ctx)
{
    cout << __LINE__ << " " << ctx->ToJointPoint()->toString() << endl;
    cout << __LINE__ << " " << ctx->SpeedData()->toString() << endl;
    cout << __LINE__ << " " << ctx->ZoneData()->toString() << endl;
    cout << __LINE__ << " " << ctx->ToolData()->toString() << endl;
    RCStatementMovabsj *movabsj=new RCStatementMovabsj();
    movabsj->lineno=lineno;
    movabsj->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->ToJointPoint()->toString())->second]);
    movabsj->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->SpeedData()->toString())->second]);
    movabsj->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->ZoneData()->toString())->second]);
    movabsj->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->ToolData()->toString())->second]);
    if(ctx->WobjData()!=NULL)
        movabsj->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->WobjData()->toString())->second]);
    code->StatementSpace.push_back(movabsj);
    return visitChildren(ctx);
}

antlrcpp::Any MyProgramVisitor::visitDelayExpr(robProgramParser::DelayExprContext *ctx)
{
    cout << __LINE__ << " " <<ctx->DelayData()->toString() << endl;

    RCStatementDelay *delay=new RCStatementDelay();
    delay->lineno=lineno;
    delay->pDataSpace->push_back(code->DataSpace[code->SymbolTable.find(ctx->DelayData()->toString())->second]);
    code->StatementSpace.push_back(delay);

    return visitChildren(ctx);
}

antlrcpp::Any MyProgramVisitor::visitNlExpr(robProgramParser::NlExprContext *ctx)
{
    lineno+=1;
    return visitChildren(ctx);
}

/****************************************************************************************/
int getFileSize(const char *filename)
{
    struct stat statbuf;
    stat(filename,&statbuf);
    return statbuf.st_size;
}
void loadDataFile(const char *filename,MyDataVisitor *visitor)
{

    int dataBufSize=getFileSize(filename);
    char *dataBuf=(char *)malloc(dataBufSize);
    int dataFd=open(filename,O_RDONLY);
    if(dataFd<0)
    {
        perror("open data file failed");
        free(dataBuf);
        return ;
    }
    memset(dataBuf,0,dataBufSize);
    int ret=read(dataFd,dataBuf,dataBufSize-1);
    if(ret<0)
    {
        perror("read data file failed");
        free(dataBuf);
        return ;
    }
//    cout << ret << " " << dataBufSize << endl;
//    cout << dataBuf << endl;
    close(dataFd);
    antlr4::ANTLRInputStream dataInput(dataBuf);
    robDataLexer dataLexer(&dataInput);
    antlr4::CommonTokenStream dataToken(&dataLexer);
    robDataParser dataParser(&dataToken);
    antlr4::tree::ParseTree *dataTree=dataParser.data();

 //    cout << dataTree->toStringTree(&dataParser) << endl;

     visitor->visit(dataTree);
     free(dataBuf);
}

void loadProgramFile(const char *filename,MyProgramVisitor *visitor)
{
    int ret;
    int programBufSize=getFileSize(filename);
    char *programBuf=(char *)malloc(programBufSize);
    int programFd=open(filename,O_RDONLY);
    if(programFd<0)
    {
        perror("open program file failed");
        free(programBuf);
        return ;
    }
    memset(programBuf,0,programBufSize);
    ret=read(programFd,programBuf,programBufSize-1);
    if(ret<0)
    {
        perror("read program file failed");
        free(programBuf);
        return ;
    }
    close(programFd);

    antlr4::ANTLRInputStream programInput(programBuf);
    robProgramLexer programLexer(&programInput);
    antlr4::CommonTokenStream programToken(&programLexer);
    robProgramParser programParser(&programToken);
    antlr4::tree::ParseTree *programTree=programParser.program();

//    cout << programTree->toStringTree(&programParser) << endl;
    visitor->visit(programTree);
    free(programBuf);
}

bool loadFile(char *srcFile, const char *distFile,struct stat srcFileStat)
{
    if(strcmp(srcFile,distFile)!=0)
    {
        return true;
    }
    else
    {
        struct stat statbuf;
        stat(distFile,&statbuf);
        if(srcFileStat.st_mtim.tv_sec==statbuf.st_mtim.tv_sec&&srcFileStat.st_mtim.tv_nsec==statbuf.st_mtim.tv_nsec)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

