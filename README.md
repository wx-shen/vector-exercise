# vector练习

使用vector实现了一个简单的图书馆里系统。书籍相关信息存放在data.txt中，同一条目的不同属性之间用空格隔开。

定义了结构BK，包括7个string型属性和一个float属性。

定义全局变量`vector<BK> bkWriteBuffer`和`vector<BK> bkList`。定义时未初始化大小，后续操作时，通过`push_back()`方法添加元素。

文件的读写使用`ifstream`类和`ofstream`类。在读取文件内容时，逐行读取文件的内容，存储到局部变量`strTmp`中，并且使用`' '` 分割`strTmp`，将分割结果写入`vector<string> strTmpSplit`中。初始化结构`bktmp`，把`vector<string> strTmpSplit`中的内容转换为结构`bktmp`，存放到全局变量`vector<BK> bkList`中，完成书籍信息的读取。

接下来，用代码片段具体介绍一下练习中遇到的问题，以及解决的思路。

## 字符串分割

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

`strTmp`表示待分割的string，`vector<string> strTmpSplit`表示分割后的结果。

## 删除vector中的某个元素

```c++
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
```

首先从标准输入中读取`bknum`，作为待删除书籍的索引。~~更合理的选择是ISBN，但是我懒。~~定义迭代器`itr`，初始化为`bkList`的第一个元素。随后的while循环遍历整个`bkList`，注意，因为本例中`bkList`的元素是结构而非基本数据类型，所以需要使用`itr->num`即`->`来获取迭代器的值。基本数据类型使用`*itr`即可。本例中，`num`和`bknum`都是`string`类型，因此可以直接使用`==`进行比较。

### `erase()`方法

`erase()`方法删除单个元素时的返回值是被删除元素的后一个元素的指针。

用人话说，我要删除`bkList[8]`，调用`erase(bkList[8])`会返回原来的`bkList[9]`。所以在删除时，仅使用`erase(bkList[8])`是错误的，会产生一个野指针。所以需要使用`itr`接收返回值。此外，由于`erase()`的返回值是下一个元素，所以本次循环内，`itr`不需要自加。

`findFlag`用于标识是否找到相应的书籍，基本操作不再赘述。

## 使用`sort()`排序

首先需要说明的是，使用`sort()`需要导入头文件`#include<algorithm>`。某个小天才不但没有导入，而且自己定义了一个`sort()`函数，以至于代码写的头头是道，语法正确的一比，但就是编译不过，罪过罪过。

接下来，具体介绍一下`sort()`的使用方法。`sort()`方法接收两个或三个参数。

### 基本数据类型排序

easy game，框好边界，让它自己排。

```c++
std::vector<int> myvector (myints, myints+8);
```

### 自定义数据类型排序

```c++
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

除了前两个参数框好边界以外，还需要第三个参数指定排序方式。

本例中编写了三个排序方式，即”价格升序“、”书名升序“、”ISBN升序“。具体解析`compPrice`函数，该函数通过结构体中的`price`属性比较两个结构体的大小，`price`高的视为大于。

## 文件读取

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

首先尝试读取文件，如果`data.txt`不存在，则调用`dataInitialize()`进行初始化。

`fin`类似标准输入流中的`cin`，拥有与`cin`相同的方法。所以可以通过`getline(fin, strTmp)`进行逐行读取。读取后的字符串通过`' '`分割，得到8个子串，每个字串对应结构体`BK`重的一个属性。所以此处通过这些字串，初始化局部变量`bktmp`，用于临时存放从这一行中读取到的信息。将`bktmp`写入全局变量`bkList`，完成这一行信息的读取。

~~写入`bkList`后局部变量bktmp应该销毁的，总感觉会有内存溢出的风险。~~

## 文件写入

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

在创建`fout`时，还需要留意文件的打开方式。

本例中，`ios::out`表示写入信息，`ios::app`表示追加写入。

## 总结

该说的都说的差不多了，复习了一遍`vector`的特性，对输入输出流的了解更加深刻了。

写的很开心。~~（但是读的人开不开心我就不知道了）~~