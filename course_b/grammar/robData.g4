grammar robData;

options{
    language=Cpp;
}

ID          :   [a-zA-Z_][a-zA-Z_0-9]*;
INT         :   [0-9]+;
STRING      :   '"' ('\\'[bntr"\\]|.)*? '"';
WS          :   [ \t\r\n]+ ->skip;

data    :   file+;
file    :   ID ':' STRING ':' INT ';';
