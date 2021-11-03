#ifndef MYCOMMAND_H
#define MYCOMMAND_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unistd.h>
#include <./include/robot_datastruct.h>

using namespace std;

extern vector<struct In_rbt_inst> _G_instList;

void displayData(vector<struct InnerData> data);

class RCStatementBase{
public:
    RCStatementBase();
    virtual ~RCStatementBase();
    virtual void excute()=0;

    int lineno;
    vector<struct InnerData> *pDataSpace;
    bool bInsertedList;
    int instType;
};

class CodeModel{
public:
    CodeModel();
    ~CodeModel();
    virtual void executor();
    void clear();

    vector<struct InnerData> DataSpace;
    vector<RCStatementBase*> StatementSpace;
    unordered_map<string,int> SymbolTable;
    int pc;
    int lineno;
};


class RCStatementMovj : public RCStatementBase{
public:
    RCStatementMovj();
    ~RCStatementMovj();
    virtual void excute() override;

    int endPoint;
    int speed;
    int posLevel;

};
class RCStatementMovc : public RCStatementBase{
public:
    RCStatementMovc();
    ~RCStatementMovc();
    virtual void excute() override;

    int endPoint;
    int speed;
    int posLevel;

};
class RCStatementMovl : public RCStatementBase{
public:
    RCStatementMovl();
    ~RCStatementMovl();
    virtual void excute() override;

    int endPoint;
    int speed;
    int posLevel;

};
class RCStatementMovabsj : public RCStatementBase{
public:
    RCStatementMovabsj();
    ~RCStatementMovabsj();
    virtual void excute() override;

    int endPoint;
    int speed;
    int posLevel;

};
class RCStatementDelay : public RCStatementBase{
public:
    RCStatementDelay();
    ~RCStatementDelay();
    virtual void excute() override;

    int endPoint;
    int speed;
    int posLevel;

};

void clearinList();

#endif // MYCOMMAND_H
