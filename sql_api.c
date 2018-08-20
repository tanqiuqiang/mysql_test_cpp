#include"mysql/mysql.h"
#include<string.h>
#include<stdio.h>
#include"sql_api.h"



MYSQL mysql; //mysql连接
char query[150]; //查询语句
 

int main(int argc,char **argv)
{
	
    ConnectDatabase();
	sprintf(query, "select * from APP_CLIENT_INFO");
	QueryDatabase(query);

    return 0;
}
//连接数据库
bool ConnectDatabase()
{
	//连接配置
    char *host = "192.168.1.189";
    char *user = "root";
    char *passwd = "root";
    char *db = "CDMC";
    int  port = 3306;
    //初始化mysql
    mysql_init(&mysql);  //连接mysql，数据库
 
    //返回false则连接失败，返回true则连接成功
    if(!mysql_real_connect(&mysql, host, user, passwd, db, port, NULL, CLIENT_FOUND_ROWS)) //中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等），可以先写成参数再传进去
    {
        printf( "Error connecting to database:%s\n",mysql_error(&mysql));
        return false;
    }
    else
    {
        printf("Connected Success...\n");
        return true;
    }
}
//释放资源
void FreeConnect()
{
    //释放资源
    //mysql_free_result(res);
    mysql_close(&mysql);
}
/***************************数据库操作***********************************/
//其实所有的数据库操作都是先写个sql语句，然后用mysql_query(&mysql,query)来完成，包括创建数据库或表，增删改查
//查询数据

bool QueryDatabase(char *sql)
{
	MYSQL_RES *res; //这个结构代表返回行的一个查询结果集
	MYSQL_ROW column; //一个行数据的类型安全(type-safe)的表示，表示数据行的列
	MYSQL_FIELD *fd;  //字段列数组
	char field[32][32];  //存字段名二维数组
	
    mysql_query(&mysql,"set names gbk");
    //返回0 查询成功，返回1查询失败
    if(mysql_query(&mysql, sql))        //执行SQL语句
    {
        printf("Query failed (%s)\n",mysql_error(&mysql));
        return false;
    }
    else
    {
        printf("query success\n");
    }
    res=mysql_store_result(&mysql);
    for(int i=0;fd=mysql_fetch_field(res);i++)  //获取字段名
        strcpy(field[i],fd->name);
    int j=mysql_num_fields(res);  // 获取列数
    //打印数据行数,字段数
    printf("number of dataline: %d and field: %d,\n",mysql_affected_rows(&mysql),j);	
    for(int i=0;i<j;i++)  //打印字段
        printf("%10s\t",field[i]);
    printf("\n");
    while(column=mysql_fetch_row(res))
    {
        for(int i=0;i<j;i++)
            printf("%10s\t",column[i]);
        printf("\n");
    }
	mysql_free_result(res);//free
    return true;
}
//插入数据
bool InsertData(char *sql)
{
    if(mysql_query(&mysql, sql))        //执行SQL语句
    {
        printf("Query failed (%s)\n",mysql_error(&mysql));
        return false;
    }
    else
    {
        printf("Insert success\n");
        return true;
    }
}
//修改数据
bool ModifyData(char *sql)
{
    //sprintf(query, "update user set email='lilei325@163.com' where name='Lilei'");
    if(mysql_query(&mysql, sql))        //执行SQL语句
    {
        printf("Query failed (%s)\n",mysql_error(&mysql));
        return false;
    }
    else
    {
        printf("Insert success\n");
        return true;
    }
}
//删除数据
bool DeleteData(char *sql)
{
    /*sprintf(query, "delete from user where id=6");*/
    if(mysql_query(&mysql, sql))        //执行SQL语句
    {
        printf("Query failed (%s)\n",mysql_error(&mysql));
        return false;
    }
    else
    {
        printf("Insert success\n");
        return true;
    }
}