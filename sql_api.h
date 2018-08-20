#ifndef __MYSQL_HANDLER_H__
#define __MYSQL_HANDLER_H__

typedef enum {false = 0, true = !false} bool;

bool ConnectDatabase();     //函数声明
void FreeConnect();
bool QueryDatabase();  //查询
bool InsertData();
bool ModifyData();
bool DeleteData();

#endif

