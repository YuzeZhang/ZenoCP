#include "public.h"
#include "Connection.h"

// ��ʼ�����ݿ�����
Connection::Connection()
{
    _conn = mysql_init(nullptr);
}

// �ͷ����ݿ�������Դ
Connection::~Connection()
{
    if (_conn != nullptr)
        mysql_close(_conn);
}

// �������ݿ�
bool Connection::connect(string ip,
                         unsigned short port,
                         string username,
                         string password,
                         string dbname)
{
    MYSQL *p = mysql_real_connect(_conn, ip.c_str(), username.c_str(),
                                  password.c_str(), dbname.c_str(),
                                  port, nullptr, 0);

    //mysql_query(_conn, "set interactive_timeout=24*3600");

    return p != nullptr;
}

// ���²��� insert��delete��update
bool Connection::update(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG("����ʧ�ܣ�" + sql + "\nmysql_error:" + mysql_error(_conn));
        return false;
    }
    return true;
}

// ��ѯ���� select
MYSQL_RES *Connection::query(string sql)
{
    // ��ѯ���� select
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG("��ѯʧ��" + sql + "\nmysql_error:" + mysql_error(_conn));
        return nullptr;
    }
    return mysql_use_result(_conn);
}

// ˢ�����ӵ���ʼ����ʱ��
void Connection::refreshAliveTime()
{
    _alivetime = clock();
}

// �������ӿ��е�ʱ��
clock_t Connection::getAliveTime()
{
    return clock() - _alivetime;
}

