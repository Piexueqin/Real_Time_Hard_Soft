grammar robProgram;

options{
    language=Cpp;
}

//数据格式
ToPoint         :   ID+ 'ToPoint';
MidPoint        :   ID+ 'MidPoint';
ToJointPoint    :   ID+ 'ToJointPoint';
SpeedData       :   ID+ 'Speed';
ZoneData        :   ID+ 'Zone';
ToolData        :   ID+ 'Tool';
WobjData        :   ID+ 'Wobj';
DelayData       :   ID+ 'Delay';


ID          :   [a-zA-Z_][a-zA-Z_0-9]*;
NUM         :   '-'? [0-9]+ ('.' [0-9]+)?;
STRING      :   '"' ('\\'[bntr"\\]|.)*? '"';
WS          :   [ \t]+ ->skip;
NEWLINE     :   '\r'? '\n';
LINECOMMENT :   '//' .*? '\n' ->skip;   //单行注释
MULTCOMMENT :   '/*' .*? '*/' ->skip;   //多行注释

program :   file+;
file    :   routine_stat nlExpr
        |   robot_stat nlExpr
        |   signal_stat nlExpr
        |   nlExpr
        ;
routine_stat    :   'PROC' ID '(' ')'     #mainExpr
                |   'ENDPROC'      #endExpr
                ;

robot_stat      :   movjExpr
                |   movlExpr
                |   movcExpr
                |   movabsjExpr
                ;
movjExpr        :   'MOVJ' ToPoint ',' SpeedData ',' ZoneData ',' ToolData (',' WobjData)? ;
movlExpr        :   'MOVL' ToPoint ',' SpeedData ',' ZoneData ',' ToolData (',' WobjData)? ;
movcExpr        :   'MOVC' MidPoint ',' ToPoint ',' SpeedData ',' ZoneData ',' ToolData (',' WobjData)? ;
movabsjExpr     :   'MOVABSJ' ToJointPoint ',' SpeedData ',' ZoneData ',' ToolData (',' WobjData)? ;

signal_stat     :   delayExpr;
delayExpr       :   'DELAY' DelayData ;

nlExpr          :   NEWLINE;
