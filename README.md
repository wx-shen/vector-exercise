# vector��ϰ

ʹ��vectorʵ����һ���򵥵�ͼ�����ϵͳ���鼮�����Ϣ�����data.txt�У�ͬһ��Ŀ�Ĳ�ͬ����֮���ÿո������

�����˽ṹBK������7��string�����Ժ�һ��float���ԡ�

����ȫ�ֱ���`vector<BK> bkWriteBuffer`��`vector<BK> bkList`������ʱδ��ʼ����С����������ʱ��ͨ��`push_back()`�������Ԫ�ء�

�ļ��Ķ�дʹ��`ifstream`���`ofstream`�ࡣ�ڶ�ȡ�ļ�����ʱ�����ж�ȡ�ļ������ݣ��洢���ֲ�����`strTmp`�У�����ʹ��`' '` �ָ�`strTmp`�����ָ���д��`vector<string> strTmpSplit`�С���ʼ���ṹ`bktmp`����`vector<string> strTmpSplit`�е�����ת��Ϊ�ṹ`bktmp`����ŵ�ȫ�ֱ���`vector<BK> bkList`�У�����鼮��Ϣ�Ķ�ȡ��

���������ô���Ƭ�ξ������һ����ϰ�����������⣬�Լ������˼·��

## �ַ����ָ�

```c++
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
```

`strTmp`��ʾ���ָ��string��`vector<string> strTmpSplit`��ʾ�ָ��Ľ����

## ɾ��vector�е�ĳ��Ԫ��

```c++
string bknum;
bool findFlag = false;
cout << "������Ҫɾ������ţ�";
cin >> bknum;
vector<BK>::iterator itr = bkList.begin();
while (itr != bkList.end())
{
    if (itr->num == bknum)
    {
        itr = bkList.erase(itr);
        cout << "�Ѿ�ɾ�����鼮��Ϣ\n";
        findFlag = true;
    }
    else
        itr++;
}
if (!findFlag)
{
    cout << "δ�ҵ����鼮�����Ϣ\n";
}
```

���ȴӱ�׼�����ж�ȡ`bknum`����Ϊ��ɾ���鼮��������~~�������ѡ����ISBN������������~~���������`itr`����ʼ��Ϊ`bkList`�ĵ�һ��Ԫ�ء�����whileѭ����������`bkList`��ע�⣬��Ϊ������`bkList`��Ԫ���ǽṹ���ǻ����������ͣ�������Ҫʹ��`itr->num`��`->`����ȡ��������ֵ��������������ʹ��`*itr`���ɡ������У�`num`��`bknum`����`string`���ͣ���˿���ֱ��ʹ��`==`���бȽϡ�

### `erase()`����

`erase()`����ɾ������Ԫ��ʱ�ķ���ֵ�Ǳ�ɾ��Ԫ�صĺ�һ��Ԫ�ص�ָ�롣

���˻�˵����Ҫɾ��`bkList[8]`������`erase(bkList[8])`�᷵��ԭ����`bkList[9]`��������ɾ��ʱ����ʹ��`erase(bkList[8])`�Ǵ���ģ������һ��Ұָ�롣������Ҫʹ��`itr`���շ���ֵ�����⣬����`erase()`�ķ���ֵ����һ��Ԫ�أ����Ա���ѭ���ڣ�`itr`����Ҫ�Լӡ�

`findFlag`���ڱ�ʶ�Ƿ��ҵ���Ӧ���鼮��������������׸����

## ʹ��`sort()`����

������Ҫ˵�����ǣ�ʹ��`sort()`��Ҫ����ͷ�ļ�`#include<algorithm>`��ĳ��С��Ų���û�е��룬�����Լ�������һ��`sort()`�����������ڴ���д��ͷͷ�ǵ����﷨��ȷ��һ�ȣ������Ǳ��벻������������

���������������һ��`sort()`��ʹ�÷�����`sort()`������������������������

### ����������������

easy game����ñ߽磬�����Լ��š�

```c++
std::vector<int> myvector (myints, myints+8);
```

### �Զ���������������

```c++
int choice;
cout << "------*��ѡ������һ�����򷽷�*------\n";
cout << "[1].�۸���������\n";
cout << "[2].������������\n";
cout << "[3].ISBN����������\n";
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
    //getchar();//��ͣ�����û�������������������ټ�����
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
```

����ǰ����������ñ߽����⣬����Ҫ����������ָ������ʽ��

�����б�д����������ʽ�������۸����򡰡����������򡰡���ISBN���򡰡��������`compPrice`�������ú���ͨ���ṹ���е�`price`���ԱȽ������ṹ��Ĵ�С��`price`�ߵ���Ϊ���ڡ�

## �ļ���ȡ

```c++
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
				//splitStrTmp()
				BK bktmp{strTmpSplit[0],
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
```

���ȳ��Զ�ȡ�ļ������`data.txt`�����ڣ������`dataInitialize()`���г�ʼ����

`fin`���Ʊ�׼�������е�`cin`��ӵ����`cin`��ͬ�ķ��������Կ���ͨ��`getline(fin, strTmp)`�������ж�ȡ����ȡ����ַ���ͨ��`' '`�ָ�õ�8���Ӵ���ÿ���ִ���Ӧ�ṹ��`BK`�ص�һ�����ԡ����Դ˴�ͨ����Щ�ִ�����ʼ���ֲ�����`bktmp`��������ʱ��Ŵ���һ���ж�ȡ������Ϣ����`bktmp`д��ȫ�ֱ���`bkList`�������һ����Ϣ�Ķ�ȡ��

~~д��`bkList`��ֲ�����bktmpӦ�����ٵģ��ܸо������ڴ�����ķ��ա�~~

## �ļ�д��

```c++
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
```

�ڴ���`fout`ʱ������Ҫ�����ļ��Ĵ򿪷�ʽ��

�����У�`ios::out`��ʾд����Ϣ��`ios::app`��ʾ׷��д�롣

## �ܽ�

��˵�Ķ�˵�Ĳ���ˣ���ϰ��һ��`vector`�����ԣ���������������˽��������ˡ�

д�ĺܿ��ġ�~~�����Ƕ����˿��������ҾͲ�֪���ˣ�~~