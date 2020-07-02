#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <windows.h>
#pragma warning(disable : 4996)
using namespace std;
void manageBook1();
//书的结构体

class user
{
public:
	char accout[20]; //账户名
	char password[20]; //账户密码
	int number= 0;

	char bookNam[5][20] = { {'\0'} ,{'\0'} ,{'\0'}, {'\0'} ,{'\0'} };



	void showbill()  //借阅图书展示
	{
		for (int i = 0; i < 5; i++)
		{

			if (*bookNam[i] != '\0')
			{
				cout << "你借的书如下：" << endl;
				cout << bookNam[i] << ' ';
			}
		}
		cout << endl;
	}
};
class manager
{
public:

	char password[20];
};
list<user> us; //存放用户数据的list容器
list<manager> ma;//存放管理员账号数据的list容器
struct book
{
	char isbn[30];
	char book_name[30]; //书名
	char author[30];//作者
	char publicer[30];//出版商
	char dateAdded[30];//日期
	int qcl;//库存量
	double price;//价格
};
//存放书的链表容器
list<book> ob;
//输出 书的数据
ostream& operator<<(ostream& out, book data)
{
	out << "613图书管理系统" << endl;
	out << "\t\t书的资料" << endl;
	out << "ISBN号：" << data.isbn << endl;
	out << "书  名：" << data.book_name << endl;
	out << "作  者：" << data.author << endl;
	out << "出版社：" << data.publicer << endl;
	out << "日  期：" << data.dateAdded << endl;
	out << "库存量：" << data.qcl << endl;
	out << "价  格：" << data.price << endl;
	return out;
}
//输入 书的数据
istream& operator>>(istream& in, book& data)
{
	cout << "请输入图书信息:ISBN,书名，作者，日期，出版社，库存量，价格" << endl;
	in >> data.isbn >> data.book_name >> data.author >> data.dateAdded >> data.publicer >> data.qcl >> data.price;
	return in;
}
//添加 书
void Addbooks() //添加书籍
{
	book temData;
	cin >> temData;
	ob.push_back(temData);
}
//展示所有的书
void Showbooks()
{
	list<book>::iterator it = ob.begin();

	if (ob.empty())

		cout << "库中没有图书，请先添加书籍" << endl;
	else {
		cout << "所有图书" << endl;
		while (it != ob.end())
		{
			cout << *it;
			it++;
		}

	}

}
//删除 书
void Deletebooks()
{
	int flag = 0;
	char bookname[51];
	cout << "请输入你要删除的书名:" << endl;
	cin >> bookname;
	list<book>::iterator it = ob.begin();
	while (it != ob.end() && flag == 0)
	{
		if (!strcmp(bookname, it->book_name))
		{

			ob.erase(it);
			cerr << "删除成功！" << endl;

			break;
		}
		it++;
	}
	if (flag == 0) cout << "没有该书" << endl;
}
// 找 书
void Findbook()
{
	int flag = 0;
	char bookname[51];
	cout << "请输入你要查找的书名:";
	cin >> bookname;
	list<book>::iterator it = ob.begin();
	while (it != ob.end() && flag == 1)
	{
		if (!strcmp(bookname, it->book_name))
		{
			cout << "查找成功！本书库存量为:" << it->qcl << endl;

			flag = 1; break;
		}
		++it;
	}
	if (flag == 0) cout << "没有该书" << endl;


}
//借书
void Borrowbooks(list<user>::iterator ap)
{

	int flag = 0;
	char bookname[51];
	cout << "请输入你要借的书名:" << endl;;
	cin >> bookname;
	list<book>::iterator it = ob.begin();
	while (it != ob.end() && flag == 0)
	{

		if (!strcmp(bookname, it->book_name))
		{

			if (it->qcl >= 1)
			{
				flag = 1;


				if (ap->number >= 5)
				{
					cout << "你所借的书已满5本" << endl;
					system("cls");
					manageBook1();

				}

				else
				{

					cout << "借书成功！" << endl;
					it->qcl--;
					for (int i = 0; i < 5; i++)
					{
						if (*ap->bookNam[i] == '\0')
						{
							strcpy_s(ap->bookNam[i], bookname);
						}
						ap->number++;
						return;
					}
				}


			}
			else
			{
				flag = 1;
				cout << "书的库存量为0" << endl;
				return;
			}


		}
		++it;
	}
	
	if (flag == 0) cout << "没有该书" << endl;

}
//还 书
void Returnbooks(list<user>::iterator ap)
{
	int flag = 0;
	char bookname[51];
	cout << "请输入你要还的书名:" << endl;
	cin >> bookname;
	list<book>::iterator it = ob.begin();
	while (it != ob.end() && flag == 0)
	{
		int i;
		if (!strcmp(bookname, it->book_name))
		{

			for (i = 0; i < 5; i++)
			{
				if (!strcmp(bookname, ap->bookNam[i]))
				{
					*ap->bookNam[i] = '\0';
					ap->number--;
					cout << "还书成功！" << endl;
					it->qcl++;
					return;
				}
			}
			if (i == 5)
			{
				cout << "你没有借过这本书" << endl;
				return;
			}
		}

		it++;
	}

}
//保存到文件
void Savefile()  
{
	list<book>::iterator it = ob.begin();
	ofstream file("D:\\图书管理系统.txt");
	if (!file)
	{
		cout << "文件打开失败" << endl;
	}

	while (it != ob.end())
	{

		file << it->isbn << '$' << it->book_name << '$' << it->author << '$' << it->publicer << '$' << it->dateAdded << '$' << it->qcl << '$' << it->price << '\n' << endl;
		it++;
	}
	cout << "数据保存完毕" << endl;
	file.close();

	list<user>::iterator it1 = us.begin();
	ofstream file1("D:\\用户.txt");
	if (!file1)
	{
		cout << "文件打开失败" << endl;
	}

	while (it1 != us.end())
	{

		file1 << it1->accout << '$' << *it1->password << '$' <<it1->number<< '$' << it1->bookNam[0] << '$' << it1->bookNam[1] << '$' << *it1->bookNam[2] << '$' << *it1->bookNam[3] << '$' << *it1->bookNam[4] << '$' <<  '\n' << endl;
		it++;
	}
	cout << "数据保存完毕" << endl;
	file1.close();
}

//从文件中读取数据
void Readfile()  //从文件读取数据
{
	cout << "从文件读取数据" << endl;
	//读取图书数据
	ifstream ifile("D:\\图书管理系统.txt");
	char ch;
	int i;

	if (!ifile)
	{
		cout << "打开图书文件失败" << endl;
		return;
	}


	for (i = 0; i < 100; i++)
	{
		string isbn;  //编号
		string book_name; //书名
		string author;//作者
		string publicer;//出版商
		string dateAdded;//日期
		string qcl;//库存量
		string price;//价格

		if (!ifile.get(ch))
		{
			cout << "书的文件已读完！" << endl;
			//system("cls");
			ifile.close();
			return;

		}

		while (ch != '$')//读取isbn
		{
			if (ch == ' ')
			{
				ifile.get(ch);
				continue;
			}
			isbn += ch;
			ifile.get(ch);
		}

		ifile.get(ch);
		while (ch != '$')//读取书名
		{
			if (ch == ' ')//跳过空格  
			{
				ifile.get(ch);
				continue;
			}
			book_name += ch;
			ifile.get(ch);
		}

		ifile.get(ch);
		while (ch != '$')//读取作者
		{
			if (ch == ' ')//跳过空格  
			{
				ifile.get(ch);
				continue;
			}
			author += ch;
			ifile.get(ch);
		}
		ifile.get(ch);
		while (ch != '$')//读取出版商
		{
			if (ch == ' ')//跳过空格  
			{
				ifile.get(ch);
				continue;
			}
			publicer += ch;
			ifile.get(ch);
		}
		ifile.get(ch);
		while (ch != '$')//读取日期
		{
			if (ch == ' ')//跳过空格  
			{
				ifile.get(ch);
				continue;
			}
			dateAdded += ch;
			ifile.get(ch);
		}
		ifile.get(ch);
		while (ch != '$')//读取库存量
		{
			if (ch == ' ')//跳过空格  
			{
				ifile.get(ch);
				continue;
			}
			qcl += ch;
			ifile.get(ch);
		}
		ifile.get(ch);

		while (ch != '\n')//读取价格
		{
			if (ch == ' ')//跳过空格  
			{
				ifile.get(ch);
				continue;
			}
			price += ch;
			ifile.get(ch);
		}
		if (!ifile.get(ch))
		{
			cout << "文件已经读完！-------" << endl;
			ifile.close();
			return;
		}

		book temp;
		strcpy(temp.isbn, isbn.c_str());
		strcpy(temp.book_name, book_name.c_str());
		strcpy(temp.author, author.c_str());
		strcpy(temp.publicer, publicer.c_str());
		strcpy(temp.dateAdded, dateAdded.c_str());
		temp.qcl = atoi(qcl.c_str());
		temp.price = strtod(price.c_str(), NULL);
		ob.push_back(temp);
	}



	
}
void Readfile1()
{
	char ch;
	//读取用户数据
	ifstream ifile1("D:\\用户.txt");

	if (!ifile1)
	{
		cout << "打开图书文件失败" << endl;
		return;
	}

	for (int i = 0; i < 10; i++)
	{
		string accout;  //用户名
		string password; //密码
		string number;//借书的数量
		//存
		string bookname1;
		string bookname2;
		string bookname3;
		string bookname4;
		string bookname5;

		cout << '1';

		if (!ifile1.get(ch))
		{
			cout << "用户文件文件已读完！" << endl;
			//system("cls");
			ifile1.close();
			return;
		}


		while (ch != '$')//读取用户名
		{
			if (ch == ' ')
			{
				ifile1.get(ch);
				continue;
			}
			accout += ch;
			ifile1.get(ch);
		}

		ifile1.get(ch);
		while (ch != '$')//读取密码
		{
			if (ch == ' ')//跳过空格  
			{
				ifile1.get(ch);
				continue;
			}
			password += ch;
			ifile1.get(ch);
		}
		cout << '2' << endl;
		ifile1.get(ch);
		while (ch != '$')//读取借书的数量
		{
			if (ch == ' ')//跳过空格  
			{
				ifile1.get(ch);
				continue;
			}
			number += ch;
			ifile1.get(ch);
		}

		ifile1.get(ch);
		while (ch != '$')//读取书名1
		{
			if (ch == ' ')//跳过空格  
			{
				ifile1.get(ch);
				continue;
			}
			bookname1 += ch;
			ifile1.get(ch);
		}
		ifile1.get(ch);
		while (ch != '$')//读取书名2
		{
			if (ch == ' ')//跳过空格  
			{
				ifile1.get(ch);
				continue;
			}
			bookname2 += ch;
			ifile1.get(ch);
		}
		ifile1.get(ch);
		while (ch != '$')//读取书名3
		{
			if (ch == ' ')//跳过空格  
			{
				ifile1.get(ch);
				continue;
			}
			bookname3 += ch;
			ifile1.get(ch);
		}
		ifile1.get(ch);
		while (ch != '$')//读取书名4
		{
			if (ch == ' ')//跳过空格  
			{
				ifile1.get(ch);
				continue;
			}
			bookname4 += ch;
			ifile1.get(ch);
		}


		ifile1.get(ch);

		while (ch != '\n')//读取书名5
		{
			if (ch == ' ')//跳过空格  
			{
				ifile1.get(ch);
				continue;
			}
			bookname5 += ch;
			ifile1.get(ch);
		}

		if (!ifile1.get(ch))
		{
			cout << "文件已经读完！-------" << endl;
			ifile1.close();
			return;
		}

		user User;
		User.number = atoi(number.c_str());
		strcpy_s(User.accout, accout.c_str());
		strcpy_s(User.password, password.c_str());
		strcpy_s(User.bookNam[0], bookname1.c_str());
		strcpy_s(User.bookNam[1], bookname2.c_str());
		strcpy_s(User.bookNam[2], bookname3.c_str());
		strcpy_s(User.bookNam[3], bookname4.c_str());
		strcpy_s(User.bookNam[4], bookname5.c_str());

		us.push_back(User);
	}
	ifile1.close();
}
void Readfile2()
{
	char ch;
	ifstream ifile2("D:\\管理员.txt");

	if (!ifile2)
	{
		cout << "打开图书文件失败" << endl;

		return;
	}

		string password; //密码

		ifile2 >> password;
			//getline(password);

		//if (!ifile2.get(ch))
		//{
		//	cout << "管理员文件已读完！" << endl;
		//	system("cls");
		//	ifile2.close();
		//	return;
		//}
		//while(ifile2.get(ch)!='$')
		//{
		//	password += ch;
		//	ifile2.get(ch);
		//}
		//if (!ifile2.get(ch))
		//{
		//	cout << "文件已经读完！-------" << endl;
		//	ifile2.close();
		//	return;
		//}

		manager Manager;
	
		strcpy_s(Manager.password, password.c_str());


		ma.push_back(Manager);
	
	ifile2.close();
}
//用户操作列表
void manageBook1()
{
	cout << "------------------【用户操作系统】------------------------" << endl;
	cout << "\t\t1.图书列表" << endl;
	cout << "\t\t2.借    书" << endl;
	cout << "\t\t3.还    书" << endl;
	cout << "\t\t4.查找书籍" << endl;
	cout << "\t\t5.个人信息" << endl;
	cout << "\t\t6.退出登录" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "\t\t输入选择（1-6）:";
}
//管理员操作列表
void manageBook2()
{
	cout << "------------------【书库管理系统】------------------------" << endl;
	cout << "\t\t1.图书列表" << endl;
	cout << "\t\t2.添加图书" << endl;
	cout << "\t\t3.删除图书" << endl;
	cout << "\t\t4.修改图书信息" << endl;
	cout << "\t\t5.个人信息" << endl;
	cout << "\t\t6.退出登录" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "\t\t输入选择（1-6）:";
}

//用户信息列表
void userinformenu(list<user>::iterator it)
{

	cout << it->accout << "借书情况：" << endl;
	it->showbill();
}


//用户交涉
int usermanageKeyDown(list<user>::iterator it)
{
	int userKey = 0;
	cin >> userKey;
	system("cls");
	switch (userKey)
	{
	case 1:
		cout << "------------------【图书列表】---------------" << endl;
		Showbooks();
		break;

	case 2:
		cout << "------------------【借    书】---------------" << endl;
		Borrowbooks(it);
		break;
	case 3:
		cout << "------------------【还    书】---------------" << endl;
		Returnbooks(it);
		break;
	case 4:
		cout << "------------------【查找书籍】---------------" << endl;
		Findbook();
		break;

	case 5:
		cout << "------------------【个人信息】---------------" << endl;
		userinformenu(it);
		system("pause");
		system("cls");
		break;
	case 6:
		Savefile();
		break;
	default:
		break;
	}
	return userKey;
}
//管理员交互
int manageBookKeyDown()
{
	int userKey = 0;
	cin >> userKey;
	switch (userKey)
	{
	case 1:
		cout << "------------------【图书列表】---------------" << endl;
		Showbooks();
		break;
	case 2:
		cout << "------------------【添加图书】---------------" << endl;
		Addbooks();
		Savefile();
		break;
	case 3:
		cout << "------------------【删除图书】---------------" << endl;
		Deletebooks();
		Savefile();
		break;
	case 4:
		cout << "------------------【修改图书信息】---------------" << endl;
		Findbook();
		break;

	case 5:
		cout << "------------------【个人信息】---------------" << endl;
		while (1)
		{
			system("cls");
		}
		break;
	case 6:
		Savefile();
		break;
	default:
		break;
	}
	return userKey;
}
//账号登录界面
int accoutmenu()
{
	int a = 0;
	cout << "------------------【图书管理系统登录操作】------------------------" << endl;
	cout << "\t\t1.用户身份登录" << endl;

	cout << "\t\t2.管理员身份登录" << endl;
	cout << "\t\t3.用户身份注册" << endl;

	cout << "\t\t请输入您的选择：";
	cin >> a;
	while (1)
	{
		switch (a)
		{
		case 1:system("cls"); return 1;
		case 2:system("cls"); return 2;
		case 3:system("cls"); return 3;
		default:
			cout << "输入错误，请重新输入:" << endl;
		}
		cin >> a;
	}
	system("cls");

}


//用户操作列表
void userinforBook()
{
	cout << "------------------【用户个人信息】------------------------" << endl;
	cout << "\t\t1.余额查询" << endl;
	cout << "\t\t2.流水查询" << endl;
	cout << "\t\t3.修改密码" << endl;
	cout << "\t\t4.返回菜单" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "\t\t输入选择（1-4）:";
}
//管理员操作列表
void managerinforBook()
{
	cout << "------------------【用户个人信息】------------------------" << endl;
	cout << "\t\t1.余额查询" << endl;
	cout << "\t\t2.流水查询" << endl;
	cout << "\t\t3.修改密码" << endl;
	cout << "\t\t4.返回菜单" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "\t\t输入选择（1-4）:";
}

//用户信息




//账号注册登陆交互
void log(int a)
{
	char accout[20];
	char password[20];
	//user User;
	//manager Man;
	int flag = 0;
	int x = a;
	if (x == 1)
	{
		cout << "请输入您的用户的用户名以及密码:";
		cin >> accout >> password;
		while (1)
		{

			list<user>::iterator it = us.begin();

			while (it != us.end() && flag == 0)
			{
				if (!strcmp(it->accout, accout))
				{
					if (!strcmp(it->password, password))
					{
						cout << "用户" << accout << "登录成功" << endl;
						while (1)
						{
							manageBook1();
							int flag3 = usermanageKeyDown(it);
							if (flag3 == 6)
							{
								system("pause");
								system("cls");
								return;
							}
						}
					}
					else
					{
						while (flag == 0)
						{
							cout << "请重新输入密码:";
							cin >> password;
							if (!strcmp(it->password, password))
							{
								cout << "用户" << accout << "登录成功" << endl;
								while (1)
								{
									manageBook1();
									int flag3 = usermanageKeyDown(it);
									if (flag3 == 6)
									{
										system("pause");
										system("cls");
										return;
									}
								}
							}
							system("cls");
						}
					}
					it++;
				}
			}

			}
		}
	
	else if (x == 2)
	{
		cout << "请输入您的管理员密码:";
		cin >> password;
		list<manager>::iterator it1 = ma.begin();
		while (1)
		{

			while (it1 != ma.end() && flag == 0)
			{
				
				
					if (!strcmp(it1->password, password))
					{
						flag = 1;
					}
					else
					{
						while (flag == 0)
						{
							cout << "请重新输入密码:";
							cin >> password;
							if (!strcmp(it1->password, password))
							{
								flag = 1;
							}
							system("cls");
						}
					}
				
				it1++;
			}
			if (flag == 1)
			{
				cout << "管理员" << accout << "登录成功" << endl;
				while (1)
				{
					manageBook2();
					int flag2 = manageBookKeyDown();
					if (flag2 == 6)
					{
						system("pause");
						system("cls");
						return;
					}
				}
			}
			
			
				
			
		
		}

	}

	else if (x == 3)
	{
		cout << "请输入您要注册的用户名以及密码：" << endl;
		cin >> accout >> password;

		ofstream file("D:\\用户.txt");
		if (!file.is_open())
		{
			cout << "打开文件失败" << endl;
		}

		file << accout << '$' << password << '$' << '0' << '$' << '\0' << '$' << '\0' << '$' << '\0' << '$' << '\0' << '$' << '\0' <<  '\n' << endl;
		file.close();
		user User;

		strcpy_s(User.accout, accout);
		strcpy_s(User.password, password);

		us.push_back(User);
		
		cout << "注册成功" << endl;
		Sleep(1000);
		system("cls");
		return;

	}

	else return;
}

int main()
{
	Readfile();
	Readfile1();
	Readfile2();


	while (1)
	{
		log(accoutmenu());
		system("pause");
		system("cls");
	}

	system("pause");
	return 0;
}
