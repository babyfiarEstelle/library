
// cgi_select.cpp : �������̨Ӧ�ó������ڵ㡣

//


//#include "stdafx.h"
#include<iostream>
#include <Windows.h>

#include <mysql.h>

#pragma comment(lib,"libmysql.lib")

using namespace std;

void start_meun()
{
	cout << "Connection to SQL\n";
	printf(" ---------------------------------------------------\n");
	printf("                 ��ӭʹ��ͼ�����ϵͳ               \n");
	printf(" ---------------------------------------------------\n");
	printf("      [1].����ͼ�����ϵͳ       [0].�˳�ϵͳ:");
}

void end_meun(MYSQL  *sock)
{

	mysql_close(sock);

	printf(" --------------------------------------------------\n");
	printf("       -=  ��лʹ�ã��ټ��� =-           \n");
	printf(" --------------------------------------------------\n");
	system("pause");
	exit(0);
}

void login_meun()
{
	printf(" ---------------------------------------------------\n");
	printf("                ѡ���û����͵�¼ϵͳ                \n");
	printf("    [1].����Ա��½		[2].���ߵ�½		[0]�˳�ϵͳ    \n");
	printf(" ---------------------------------------------------\n");
}

void reader_meun()
{
	printf(" ----------------------------------------------------------------------\n");
	printf("                                      ѡ�����                \n");
	printf("    [1].��ѯͼ��	[2].����	[3].����		[0].�˳�ϵͳ    \n");
	printf("    [4].����ϵͳ	[5].����ϵͳ	[6].�޸�����       \n");
	printf(" ----------------------------------------------------------------------\n");
}

void admin_meun()
{
	printf(" --------------------------------------------------------------------\n");
	printf("                               ѡ�����                \n");
	printf("    [1].��ѯͼ��	[2].���ͼ��	[3].ɾ��ͼ��       \n");
	printf("    [4].��ѯ�û�	[5].����û�	[6].ɾ���û�	[0].�˳�ϵͳ    \n");
	printf(" --------------------------------------------------------------------\n");
}

void admin_op(MYSQL *sock, char *admin_id)
{
	while (1)
	{
		admin_meun();
		int a_op = 0;
		cin >> a_op;
		if (!a_op)
		{
			end_meun(sock);
		}
		else if (a_op == 1)
		{
			char sqlbuf[200] = "SELECT * FROM book";
			if (mysql_query(sock, sqlbuf))
			{
				printf("���ݻ�ȡʧ��!:%s", mysql_error(sock));
				return;
			}

			MYSQL_RES *result;
			unsigned uLine = 0, uField = 0;
			MYSQL_ROW row;
			MYSQL_FIELD *pField(NULL);

			if (!(result = mysql_store_result(sock)))
			{
				printf("�����ȡʧ��!:%s", mysql_error(sock));
				return;
			}

			//�������  
			uLine = (unsigned)mysql_num_rows(result);

			//����ֶ���  
			uField = (unsigned)mysql_num_fields(result);

			//������� 
			cout << "�鱾���	�鱾����	�鱾����	�鱾�۸�	�鱾������	�鱾����	�鱾״̬\n";
			for (int i = 0; i < (int)uLine; i++)
			{
				//���һ������  
				row = mysql_fetch_row(result);
				for (int j = 0; j < (int)uField; j++)
				{
					printf("|%-10s", row[j]);
					printf("	");
				}
				printf("\n");

			}
			mysql_free_result(result);
		}
		else if (a_op == 2)
		{
			char new_book_id[20], new_book_name[20], new_book_type[20], new_book_publisher[20], new_book_writer[20];
			char new_book_price[20], new_book_status[20];

			cout << "�����鱾id:";
			cin >> new_book_id;
			cout << "�����鱾����:";
			cin >> new_book_name;
			cout << "�����鱾����:";
			cin >> new_book_type;
			cout << "�鱾�۸�:";
			cin >> new_book_price;
			cout << "�����鱾������:";
			cin >> new_book_publisher;
			cout << "�����鱾����:";
			cin >> new_book_writer;
			cout << "�����鱾״̬(����1Ϊ�У�0Ϊ�ޣ�:";
			cin >> new_book_status;

			char sqlbuf[200] = "INSERT INTO book VALUES(";

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, new_book_id);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ",");

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, new_book_name);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ",");

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, new_book_type);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ",");

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, new_book_price);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ",");

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, new_book_publisher);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ",");

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, new_book_writer);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ",");

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, new_book_status);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ")");

			//cout << sqlbuf << endl;
			if (mysql_query(sock, sqlbuf))
			{
				printf("���ݻ�ȡʧ��!:%s", mysql_error(sock));
				return;
			}
			mysql_commit(sock);
			cout << "��ӳɹ�!" << endl;
		}
		else if (a_op == 3)
		{
			char new_book_id[20];

			cout << "����Ҫɾ���鱾��id:";
			cin >> new_book_id;

			char sqlbuf[200] = "DELETE FROM book WHERE book_id=";

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, new_book_id);
			strcat_s(sqlbuf, "\"");

			if (mysql_query(sock, sqlbuf))
			{
				printf("���ݻ�ȡʧ��!:%s", mysql_error(sock));
				return;
			}
			mysql_commit(sock);
			cout << "ɾ���ɹ�!" << endl;
		}
		else if (a_op == 4)
		{
			char sqlbuf[200] = "SELECT * FROM reader";
			if (mysql_query(sock, sqlbuf))
			{
				printf("���ݻ�ȡʧ��!:%s", mysql_error(sock));
				return;
			}

			MYSQL_RES *result;
			unsigned uLine = 0, uField = 0;
			MYSQL_ROW row;
			MYSQL_FIELD *pField(NULL);

			if (!(result = mysql_store_result(sock)))
			{
				printf("�����ȡʧ��!:%s", mysql_error(sock));
				return;
			}

			//�������  
			uLine = (unsigned)mysql_num_rows(result);

			//����ֶ���  
			uField = (unsigned)mysql_num_fields(result);

			//�������  
			cout << "�û�id    �û�����    �û�����   �绰    \n";
			for (int i = 0; i < (int)uLine; i++)
			{
				//���һ������  
				row = mysql_fetch_row(result);
				for (int j = 0; j < (int)uField; j++)
				{
					printf("|%-10s", row[j]);
				}
				printf("\n");

			}
			mysql_free_result(result);
		}
		else if (a_op == 5)
		{
		char new_reader_id[20], new_reader_name[20], new_reader_pass[20], new_reader_number[20];

			cout << "�������id:";
			cin >> new_reader_id;
			cout << "�����������:";
			cin >> new_reader_name;
			cout << "������ߵ绰:";
			cin >> new_reader_number;

			new_reader_pass[0] = '1';
			new_reader_pass[1] = '2';
			new_reader_pass[2] = '3';
			new_reader_pass[3] = '\0';

			char sqlbuf[200] = "INSERT INTO reader(reader_id,reader_name,reader_pass,reader_number) VALUES(";

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, new_reader_id);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ",");

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, new_reader_name);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ",");

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, new_reader_pass);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ",");

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, new_reader_number);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ")");

			//cout << sqlbuf << endl;
			if (mysql_query(sock, sqlbuf))
			{
				printf("���ݻ�ȡʧ��!:%s", mysql_error(sock));
				return;
			}
			mysql_commit(sock);
			cout << "��ӳɹ�!" << endl;
		}
		else if (a_op == 6)
		{
			char new_reader_id[20];

			cout << "����Ҫɾ�����ߵ�id:";
			cin >> new_reader_id;

			char sqlbuf[200] = "DELETE FROM reader WHERE reader_id=";

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, new_reader_id);
			strcat_s(sqlbuf, "\"");

			if (mysql_query(sock, sqlbuf))
			{
				printf("���ݻ�ȡʧ��!:%s", mysql_error(sock));
				return;
			}
			mysql_commit(sock);
			cout << "ɾ���ɹ�!" << endl;
		}
	}
}

void reader_op(MYSQL *sock, char * reader_id)
{
	while (1)
	{
		reader_meun();
		int r_op = 0;
		cin >> r_op;

		if (!r_op)
		{
			end_meun(sock);
		}

		if (r_op == 1)
		{
			char sqlbuf[200] = "SELECT * FROM book";
			if (mysql_query(sock, sqlbuf))
			{
				printf("���ݻ�ȡʧ��!:%s", mysql_error(sock));
				return;
			}

			MYSQL_RES *result;
			unsigned uLine = 0, uField = 0;
			MYSQL_ROW row;
			MYSQL_FIELD *pField(NULL);

			if (!(result = mysql_store_result(sock)))
			{
				printf("�����ȡʧ��!:%s", mysql_error(sock));
				return;
			}

			//�������  
			uLine = (unsigned)mysql_num_rows(result);

			//����ֶ���  
			uField = (unsigned)mysql_num_fields(result);

			//�������  
			cout << "�鱾���	�鱾����	�鱾����	�鱾�۸�	�鱾������	�鱾����	�鱾״̬ \n";
			for (int i = 0; i < (int)uLine; i++)
			{
				//���һ������  
				row = mysql_fetch_row(result);
				for (int j = 0; j < (int)uField; j++)
				{
					printf("|%-10s", row[j]);
					printf("	");
				}
				printf("\n");

			}
			mysql_free_result(result);
		}
		else if (r_op == 2)
		{
			char borrow_name[20], borrow_book[20], borrow_time[20];

			cout << "���������������";
			cin >> borrow_name;
			cout << "�����鱾���ƣ�";
			cin >> borrow_book;
			cout << "�������ʱ�䣺";
			cin >> borrow_time;

			char sqlbuf[200] = "INSERT INTO borrow VALUES(";
			
			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, borrow_name);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ",");

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, borrow_book);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ",");

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, borrow_time);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ")");


			if (mysql_query(sock, sqlbuf))
			{
				printf("���ݻ�ȡʧ��!:%s", mysql_error(sock));
				return;
			}	
			char str[200] = "UPDATE book borrow SET book_status = \"0\" where book_name = \"";
			strcat_s(str, borrow_book);
			strcat_s(str, "\"");
			if (mysql_query(sock, str))
			{
				printf("���ݻ�ȡʧ��!:%s", mysql_error(sock));
				return;
			}
			cout << "�鱾���³ɹ�" << endl;
			mysql_commit(sock);
			cout << "����ɹ�" << endl;
		}
		else if (r_op == 3)
		{
			char returns_name[20], returns_book[20], returns_time[20];
			cout << "������������";
			cin >> returns_name;
			cout << "�黹���鱾���ƣ�";
			cin >> returns_book;
			cout << "�黹ʱ�䣻";
			cin >> returns_time;

			char sqlbuf[200] = "INSERT INTO returns VALUES(";
			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, returns_name);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ",");

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, returns_book);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ",");

			strcat_s(sqlbuf, "\"");
			strcat_s(sqlbuf, returns_time);
			strcat_s(sqlbuf, "\"");

			strcat_s(sqlbuf, ")");

			if (mysql_query(sock, sqlbuf))
			{
				printf("���ݻ�ȡʧ��!:%s", mysql_error(sock));
				return;
			}
			char str[200] = "UPDATE book borrow SET book_status = \"1\" where book_name = \"";
			strcat_s(str, returns_book);
			strcat_s(str, "\"");
			if (mysql_query(sock, str))
			{
				printf("���ݻ�ȡʧ��!:%s", mysql_error(sock));
				return;
			}
			cout << "�鱾���³ɹ�" << endl;
			mysql_commit(sock);
			cout << "�黹�ɹ�" << endl;

		}
		else if (r_op == 4)
		{
			char sqlbuf[200] = "SELECT * FROM borrow";
			if (mysql_query(sock, sqlbuf))
			{
				printf("���ݻ�ȡʧ��!:%s", mysql_error(sock));
				return;
			}

			MYSQL_RES *result;
			unsigned uLine = 0, uField = 0;
			MYSQL_ROW row;
			MYSQL_FIELD *pField(NULL);

			if (!(result = mysql_store_result(sock)))
			{
				printf("�����ȡʧ��!:%s", mysql_error(sock));
				return;
			}

			//�������  
			uLine = (unsigned)mysql_num_rows(result);

			//����ֶ���  
			uField = (unsigned)mysql_num_fields(result);

			//�������  
			cout << "������		�鱾����	���ʱ�� \n";
			for (int i = 0; i < (int)uLine; i++)
			{
				//���һ������  
				row = mysql_fetch_row(result);
				for (int j = 0; j < (int)uField; j++)
				{
					printf("|%-10s", row[j]);
					printf("	");
				}
				printf("\n");

			}
			mysql_free_result(result);
			}
		else if (r_op == 5)
		{
			char sqlbuf[200] = "SELECT * FROM returns";
			if (mysql_query(sock, sqlbuf))
			{
				printf("���ݻ�ȡʧ��!:%s", mysql_error(sock));
				return;
			}

			MYSQL_RES *result;
			unsigned uLine = 0, uField = 0;
			MYSQL_ROW row;
			MYSQL_FIELD *pField(NULL);

			if (!(result = mysql_store_result(sock)))
			{
				printf("�����ȡʧ��!:%s", mysql_error(sock));
				return;
			}

			//�������  
			uLine = (unsigned)mysql_num_rows(result);

			//����ֶ���  
			uField = (unsigned)mysql_num_fields(result);

			//�������  
			cout << "�黹������	�鱾����	�黹���� \n";
			for (int i = 0; i < (int)uLine; i++)
			{
				//���һ������  
				row = mysql_fetch_row(result);
				for (int j = 0; j < (int)uField; j++)
				{
					printf("|%-10s", row[j]);
					printf("	");
				}
				printf("\n");

			}
			mysql_free_result(result);
			}
		else if (r_op == 6)
		{
			//mysql_autocommit(sock, 0);
			char r_newpass[50];
			cout << "�����µ�����:";
			cin >> r_newpass;
			char sqlbuf[200] = "update reader set reader_pass=\"";
			strcat_s(sqlbuf, r_newpass);
			strcat_s(sqlbuf, "\" where reader_name = \"");
			strcat_s(sqlbuf, reader_id);
			strcat_s(sqlbuf, "\"");
			if (mysql_query(sock, sqlbuf))
			{
				printf("���ݸ���ʧ��!:%s", mysql_error(sock));
				return;
			}
			mysql_commit(sock);
			//mysql_autocommit(sock, 1);
			cout << "���³ɹ�!" << endl;
		}
		else return;
	}

}

void admin(MYSQL *sock)
{
	while (1)
	{
		char admin_id[50];
		char admin_pass[50];

		cout << "�������˺�:";
		cin >> admin_id;
		cout << "����������:";
		cin >> admin_pass;

		char sqlbuf[200] = "SELECT * FROM admin";
		if (mysql_query(sock, sqlbuf))
		{
			printf("���ݻ�ȡʧ��!:%s", mysql_error(sock));
			return;
		}

		MYSQL_RES *result;
		unsigned uLine = 0, uField = 0;
		MYSQL_ROW row;
		MYSQL_FIELD *pField(NULL);

		if (!(result = mysql_store_result(sock)))
		{
			printf("�����ȡʧ��!:%s", mysql_error(sock));
			return;
		}

		//�������  
		uLine = (unsigned)mysql_num_rows(result);

		//����ֶ���  
		uField = (unsigned)mysql_num_fields(result);

		pField = mysql_fetch_fields(result);

		bool succ = 0;
		//�������  
		for (int i = 0; i < (int)uLine; i++)
		{
			//���һ������  
			row = mysql_fetch_row(result);
			//cout << row[0] << " " << row[1] << endl;
			//cout << admin_id << " " << admin_pass << endl;
			//cout << strcmp((char*)row[0], admin_id) << endl;
			if (!strcmp((char*)row[0], admin_id) && !strcmp((char*)row[1], admin_pass))
			{
				succ = 1;
				break;
			}
		}

		mysql_free_result(result);

		if (succ)
		{
			cout << "�ɹ���½!" << endl;
			admin_op(sock, admin_id);
			break;
		}
		else
		{
			cout << "�˺Ż��������!����������" << endl;
			continue;
		}

	}
}

void reader(MYSQL *sock)
{
	while (1)
	{
		char reader_name[50];
		char reader_pass[50];

		cout << "�������˺�(����):";
		cin >> reader_name;
		cout << "����������:";
		cin >> reader_pass;

		char sqlbuf[200] = "SELECT * FROM reader";
		if (mysql_query(sock, sqlbuf))
		{
			printf("���ݻ�ȡʧ��!:%s", mysql_error(sock));
			return;
		}

		MYSQL_RES *result;
		unsigned uLine = 0, uField = 0;
		MYSQL_ROW row;
		MYSQL_FIELD *pField(NULL);

		if (!(result = mysql_store_result(sock)))
		{
			printf("�����ȡʧ��!:%s", mysql_error(sock));
			return;
		}

		//�������  
		uLine = (unsigned)mysql_num_rows(result);

		//����ֶ���  
		uField = (unsigned)mysql_num_fields(result);

		pField = mysql_fetch_fields(result);

		bool succ = 0;
		//�������  
		for (int i = 0; i < (int)uLine; i++)
		{
			//���һ������  
			row = mysql_fetch_row(result);
			if (!strcmp((char*)row[1], reader_name) && !strcmp((char*)row[2], reader_pass))
			{
				succ = 1;
				break;
			}
		}

		mysql_free_result(result);

		if (succ)
		{
			cout << "�ɹ���½!" << endl;
			reader_op(sock, reader_name);
			break;
		}
		else
		{
			cout << "�˺Ż��������!����������" << endl;
			continue;
		}

	}
}

void main()
{
	MYSQL mysql, *sock;
	mysql_init(&mysql);
	if (!(sock = mysql_real_connect(&mysql, "localhost", "root", "123456", "library", 3306, NULL, 0)))
	{
		printf("Cannot connect to database:%s\n", mysql_error(sock));
		return;
	}
	mysql_query(&mysql, "set names gbk");//�������

	mysql_autocommit(sock, 0);

	int select_num;
	int login_num;

	start_meun();

	while (1)
	{
		cin >> select_num;
		switch (select_num)
		{
		case 1: break;
		case 0:
		{
			// �ر����ݿ�  
			end_meun(sock);

		}
		default:printf("�����������������:"); continue;
		}
		break;
	}


	while (1)
	{
		login_meun();
		int login_num = 0;
		cin >> login_num;
		switch (login_num)
		{
		case 1:admin(sock); break;
		case 2:reader(sock); break;
		case 0:
		{
			// �ر����ݿ�  
			end_meun(sock);

		}
		default:printf("�����������������:"); continue;
		}
	}

	mysql_close(&mysql);

}



