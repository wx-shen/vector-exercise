#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
//c++
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include <algorithm>  

using namespace std;

int i, n, tmp = 0;
typedef struct books_list
{
	string num;/*书目序号*/
	string author; /*作者名*/
	string bookname; /*书名*/
	string publisher; /*出版单位*/
	string pbtime; /*出版时间*/
	string ISBN; /*ISBN号*/
	float price = 0.0;  /*价格*/
	string content; /*内容介绍*/
}BK;

//vector模板类用于存放待保存的数据
vector<BK> bkWrtieBuffer;
vector<BK> bkList;

void updataBkList();
void InsertDoc();//
void printBookDoc(BK _bktmp);
void printBookDoc(vector<BK> _bkList);
void searchBook();
void deleteDoc();
void correctDoc();
void sortDoc();
bool compPrice(const BK& a, const BK& b);
bool compBookname(const BK& a, const BK& b);
bool compISBN(const BK& a, const BK& b);

void readFile();//
void dataInitialize();
void saveFile(vector<BK> _bkList);//
void changeFile(vector<BK> _bkList);

void updataBkList()
{
	bkList.clear();
	readFile();
}

void InsertDoc()
{
	system("cls");
	printf("请输入要录入书籍的个数：\n");
	tmp = bkList.size();
	scanf_s("%d", &n);
	cin.get();
	for (i = tmp; i < n + tmp; i++)
	{
		BK bktmp;
		system("cls");
		printf("请录入第%d本书：\n", i + 1);
		printf("请输入书号：");
		getline(cin, bktmp.num);
		//scanf_s("%s", &bktmp.num,20);
		printf("请输入作者：");
		getline(cin, bktmp.author);
		//scanf_s("%s", &bktmp., 20);
		printf("请输入书名：");
		getline(cin, bktmp.bookname);
		//scanf_s("%s", &bktmp., 20);
		printf("请输入出版单位：");
		getline(cin, bktmp.publisher);
		//scanf_s("%s", &bktmp., 20);
		printf("请输入出版时间：");
		getline(cin, bktmp.pbtime);
		//scanf_s("%s", &bktmp., 20);
		printf("请输入ISBN号：");
		getline(cin, bktmp.ISBN);
		//scanf_s("%s", &bktmp., 10);
		printf("请输入价格：");
		scanf_s("%f", &bktmp.price);
		cin.get();
		printf("请输入内容介绍：");
		getline(cin, bktmp.content);
		//scanf_s("%s", &bktmp., 20);
		printf("数据已存入data.txt.\n");
		bkWrtieBuffer.push_back(bktmp);
		cout << bkWrtieBuffer.size() << endl;
	}
	tmp = n + tmp;//tmp很关键，记录数量避免多次添加，前面数据被覆盖
	saveFile(bkWrtieBuffer);
	updataBkList();
}

void printBookDoc(BK _bktmp)
{
	system("cls");
	printf("————————————————————————————————————————————————\n");
	printf("┃ 书 号 ┃ ISBN号 ┃ 书 名 ┃ 作 者 ┃ 出版单位 ┃ 出版时间 ┃ 内容介绍 ┃ 价格 ┃\n");
	printf("————————————————————————————————————————————————\n");
	printf("┃ %-6.6s┃ %-6.6s┃ %-10.10s┃ %-10.10s┃ %-10.10s┃ %-12.12s┃ %-6.6s┃ %.2f ┃\n", _bktmp.num.c_str(), _bktmp.ISBN.c_str(), _bktmp.bookname.c_str(), _bktmp.author.c_str(), _bktmp.publisher.c_str(), _bktmp.pbtime.c_str(), _bktmp.content.c_str(), _bktmp.price); /*循环输出表格*/
	printf("————————————————————————————————————————————————\n");
	printf("\n");
	getchar();
}

void printBookDoc(vector<BK> _bkList)
{
	system("cls");
	printf("————————————————————————————————————————————————\n");
	printf("┃ 书 号 ┃ ISBN号 ┃ 书 名 ┃ 作 者 ┃ 出版单位 ┃ 出版时间 ┃ 内容介绍 ┃ 价格 ┃\n");
	printf("————————————————————————————————————————————————\n");
	for (auto& _bktmp : _bkList)
	{
		printf("┃ %-6.6s┃ %-6.6s┃ %-10.10s┃ %-10.10s┃ %-10.10s┃ %-12.12s┃ %-6.6s┃ %.2f ┃\n", _bktmp.num.c_str(), _bktmp.ISBN.c_str(), _bktmp.bookname.c_str(), _bktmp.author.c_str(), _bktmp.publisher.c_str(), _bktmp.pbtime.c_str(), _bktmp.content.c_str(), _bktmp.price); /*循环输出表格*/
	}
	printf("————————————————————————————————————————————————\n");
	printf("\n");
	getchar();
}

void searchBook()
{
	system("cls");
	string bknum;
	bool findFlag = false;
	cout << "请输入要查询的书号：";
	cin >> bknum;
	for (auto& bktmp : bkList)
	{
		if (bktmp.num == bknum)
		{
			printBookDoc(bktmp);
			findFlag = true;
			break;
		}
	}
	if (!findFlag)
	{
		cout << "未找到该书籍相关信息\n";
	}
	getchar();//暂停，让用户看清楚结果，按任意键再继续。
}

void deleteDoc()
{
	system("cls");
	string bknum;
	bool findFlag = false;
	cout << "请输入要删除的书号：";
	cin >> bknum;
	vector<BK>::iterator itr = bkList.begin();
	while (itr != bkList.end())
	{
		if (itr->num == bknum)
		{
			itr = bkList.erase(itr);
			cout << "已经删除该书籍信息\n";
			findFlag = true;
		}
		else
			itr++;
	}
	if (!findFlag)
	{
		cout << "未找到该书籍相关信息\n";
	}
	changeFile(bkList);
	updataBkList();
	getchar();//暂停，让用户看清楚结果，按任意键再继续。
}

void correctDoc()
{
	system("cls");
	string bknum;
	bool findFlag = false;
	cout << "请输入要修改的书号：";
	cin >> bknum;
	cin.get();
	vector<BK>::iterator itr = bkList.begin();
	while (itr != bkList.end())
	{
		if (itr->num == bknum)
		{
			printf("请输入书号：");
			getline(cin, itr->num);
			//scanf_s("%s", &bktmp.num,20);
			printf("请输入作者：");
			getline(cin, itr->author);
			//scanf_s("%s", &bktmp., 20);
			printf("请输入书名：");
			getline(cin, itr->bookname);
			//scanf_s("%s", &bktmp., 20);
			printf("请输入出版单位：");
			getline(cin, itr->publisher);
			//scanf_s("%s", &bktmp., 20);
			printf("请输入出版时间：");
			getline(cin, itr->pbtime);
			//scanf_s("%s", &bktmp., 20);
			printf("请输入ISBN号：");
			getline(cin, itr->ISBN);
			//scanf_s("%s", &bktmp., 10);
			printf("请输入价格：");
			scanf_s("%f", &itr->price);
			cin.get();
			printf("请输入内容介绍：");
			getline(cin, itr->content);
			//scanf_s("%s", &bktmp., 20);
			printf("------*已经修改该书籍信息!*------\n");
			findFlag = true;
		}
		else
			itr++;
	}
	if (!findFlag)
	{
		cout << "未找到该书籍相关信息\n";
	}
	changeFile(bkList);
	updataBkList();
}

void sortDoc()
{
	system("cls");
	int choice;
	cout << "------*请选择以下一种排序方法*------\n";
	cout << "[1].价格升序排序\n";
	cout << "[2].书名升序排序\n";
	cout << "[3].ISBN号升序排序\n";
	cout << "Input:";
	cin >> choice;
	//cin.get();
	if (choice != 0)
	{
		switch (choice)
		{
		case 1:
			sort(bkList.begin(), bkList.end(), compPrice);
			break;
		case 2:
			sort(bkList.begin(), bkList.end(), compBookname);
			break;
		case 3:
			sort(bkList.begin(), bkList.end(), compISBN);
			break;
		}
		printBookDoc(bkList);
		//getchar();//暂停，让用户看清楚结果，按任意键再继续。
		//sleep(2);
	}
}

bool compPrice(const BK& a, const BK& b) 
{
	return a.price < b.price;
}

bool compBookname(const BK& a, const BK& b) 
{
	return a.bookname < b.bookname;
}

bool compISBN(const BK& a, const BK& b) 
{
	return a.ISBN < b.ISBN;
}

void readFile()
{
	ifstream fin;
	fin.open("data.txt");
	if (fin.is_open())
	{
		string strTmp;
		while (getline(fin, strTmp))
		{
			if (strTmp.size() != 0)
			{
				vector<string> strTmpSplit;
				string::size_type pos1, pos2;
				pos2 = strTmp.find(' ');
				pos1 = 0;
				while (string::npos != pos2)
				{
					strTmpSplit.push_back(strTmp.substr(pos1, pos2 - pos1));
					pos1 = pos2 + 1;
					pos2 = strTmp.find(' ', pos1);
				}
				if (pos1 != strTmp.length())
				{
					strTmpSplit.push_back(strTmp.substr(pos1));
				}
				//for (auto& str : strTmpSplit)
				//{
				//	cout << str << "\n";
				//}
				//cout << endl;
				BK bktmp{
					strTmpSplit[0],
					strTmpSplit[1],
					strTmpSplit[2],
					strTmpSplit[3],
					strTmpSplit[4],
					strTmpSplit[5],
					atof(strTmpSplit[6].c_str()),
					strTmpSplit[7]};
				bkList.push_back(bktmp);
			}
		}
	}
	else
		dataInitialize();
}

void dataInitialize()
{
	cout << "data.txt not found.Initializing";
	unsigned tmp = 0;
	InsertDoc();
}

void saveFile(vector<BK> _bkList)
{
	ofstream fout("data.txt", ios::out | ios::app);
	for (auto& bktmp : _bkList)
	{
		fout << bktmp.num << " "
			<< bktmp.author << " "
			<< bktmp.bookname << " "
			<< bktmp.publisher << " "
			<< bktmp.pbtime << " "
			<< bktmp.ISBN << " "
			<< bktmp.price << " "
			<< bktmp.content << endl;
	}
	_bkList.clear();
	fout.close();
}

void changeFile(vector<BK> _bkList)
{
	ofstream fout("data.txt", ios::out);
	for (auto& bktmp : _bkList)
	{
		fout << bktmp.num << " "
			<< bktmp.author << " "
			<< bktmp.bookname << " "
			<< bktmp.publisher << " "
			<< bktmp.pbtime << " "
			<< bktmp.ISBN << " "
			<< bktmp.price << " "
			<< bktmp.content << endl;
	}
	_bkList.clear();
	fout.close();
}



int main()
{
	unsigned tmp;
	unsigned choice;

	readFile();
	tmp = bkList.size();
	while (true)
	{
		system("cls");
		printf(" ┏━┓━━━━━━━━━━━━━━━━━━━┓\n");
		printf(" ┃ ┃  图书管理菜单     ┃\n");
		printf(" ┃ ┗━━━━━━━━━━━━━━━━━━━┛ \n");
		printf(" ┃ [1]图书新增 ┃\n");
		printf(" ┃   ┃\n");
		printf(" ┃ [2]图书信息浏览 ┃\n");
		printf(" ┃   ┃\n");
		printf(" ┃ [3]图书信息查询 ┃\n");
		printf(" ┃   ┃\n");
		printf(" ┃ [4]图书信息删除 ┃\n");
		printf(" ┃   ┃\n");
		printf(" ┃ [5]图书书目修改 ┃\n");
		printf(" ┃   ┃\n");
		printf(" ┃ [6]图书书目排序 ┃\n");
		printf(" ┃   ┃\n");
		printf(" ┃ [7]退出程序     ┃\n");
		printf(" ┃   ┃\n");
		printf(" ┗━━━━━━━━━━━━━━━━━━━━━━━┛\n");
		printf("  请选择:");
		fflush(stdin);/*清空输入缓冲区*/
		cin >> choice;
		//switch (switch_on)
		//{
		//default:
		//	break;
		//}
		switch (choice)
		{
		case 1:InsertDoc(); break;
		case 2:printBookDoc(bkList); break;
		case 3:searchBook(); break;
		case 4:deleteDoc(); break;
		case 5:correctDoc(); break;
		case 6:sortDoc(); break;
		case 7:exit(0); break;
		}
		getchar();//暂停，让用户看清楚结果，按任意键再继续
	}
	cout << bkList.size() << endl;
}
