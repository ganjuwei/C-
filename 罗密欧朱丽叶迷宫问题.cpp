
#include<iostream>
#include<fstream>

using namespace std;

int Num_Hang;							//定义Num_Hang 是地图的行					类型是数字类型
int Num_Lie;							//定义Num_Lie 是地图的列					类型是数字类型
int Num_StopRoom;						//定义Num_StopRoom 是地图障碍的个数			类型是数字类型


int Array_Map[105][105];			    //定义Array_Map 是地图大小105 105			类型是数组
int Array_Path[105 * 105];			    //定义Array_Path  是走的路径的方向			类型是数组
int Array_Best[105 * 105];				//定义Array_Best  是走的路径的最优路径			类型是数组

//当Dir_x[0] Dir_y[0]表示走的是当前格子上面的格子
//当Dir_x[1] Dir_y[1]表示走的是当前格子下面的格子
int Dir_x[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
int Dir_y[] = { 1, -1, 0, 0, 1, -1, -1, 1 };//八个方向 上下左右  还要斜着的对角线 

//定义起点 Start_Pos        终点End_Pos     类型是数字类型
int Start_Pos_x, Start_Pos_y, End_Pos_x, End_Pos_y;

//定义最小转弯次数 Minturn       一共有几种走到的最优路线num     类型是数字类型
int Minturn = 99999;//规定一个最大数
int num = 0;		//规定一共有几种走到最优的路线

int StopPosx[50];//暂时定义最多有50个障碍点，x
int StopPosy[50];//暂时定义最多有50个障碍点，y   -1表示没有

void backtrack(int x, int y, int cur)//从当前房子（x，y）出发，所走过的第cur间房子 
{
	cout << "正在找ing\n";
	//当前房间最大可走的房子 长乘上宽减去被禁止走的房子，如果是3x3被封闭房子是1  那么我走了8步还是没走到目的地，那这条线路就失败了
	if (cur >= Num_Hang*Num_Lie - Num_StopRoom)//我已经走遍了所有的房子 则可以到达Juliet了吗 
	{
		if (x != End_Pos_x || y != End_Pos_y)
		{
			return;//如果目的地不是  Juliet失败
		}
		int turn = 0;								//初始化一个临时变量  最小的转弯次数turn


		for (int i = 2; i < cur; i++)//我这个path记录的是方向 如果和前一个不相同的话 就转向+1  第一步不算转向。从2开始
		{
			if (Array_Path[i] != Array_Path[i - 1])//判断路径 如果最第二步走的路径的方向和一开始的不一样，证明转向了
			{
				turn++;		//临时转向变量加一
			}
		}
		//如果转向的次数比我之前的都要小，那你肯定是最优秀的路径了，初始化99999，防止地图很大，
		//最小转弯路径如果是99999+10 。那么第一次判断就 不成立所以初始化尽量大一点。

		//一.假设之前最优是转弯Minturn是7次 这一次是临时转弯turn5次  那么就要
		//1.更新最优数据 
		//2.更新最优路径数据 
		//3.更新最优路径条数数据 
		if (turn < Minturn)
		{
			Minturn = turn;
			memcpy(Array_Best, Array_Path, sizeof(Array_Path));//将path的值全部赋值给best  
			num = 1;
			//如果上一次最优路径是7 这次是5 那么最优到达路径就重新设置为1，num只记录最优秀的路径次数，
		}
		//二.假设之前最优是转弯Minturn是5次 这一次是临时转弯turn5次  那么就要
		//1.更新最优路径条数数据 加一次就好了
		else if (turn == Minturn)   num++;
		//三.假设之前最优是转弯Minturn是5次 这一次是临时转弯turn6次  那么就要
		//1.什么都不干返回
		return;
	}

	//假设我在一个点了
	//思路，
	//1.我先判断向上走可以不可以走，（如果遇到阻碍，如果遇到边缘就证明这个方向不可以走）
	//2.如果可以走，那我就进去，在判断下一个点的，向上可以不可以走，如果可以走，那我就走，如果不可以，那我就返回来，上一个点标记为0
	for (int i = 0; i < 8; i++)
	{
		int xx = x + Dir_x[i];
		int yy = y + Dir_y[i];
		if (Array_Map[xx][yy] == -1)  continue;//到了一个封闭的房子，不可以走了 ，我看看其他方向可不可以走 
		if (xx<1 || xx>Num_Hang || yy<1 || yy>Num_Lie)  continue;//一个约束 到了地图的边缘了，不可以走了 ，我看看其他方向可不可以走 
		Array_Path[cur] = i;//记录当前节点往哪一个方向走 
		Array_Map[xx][yy] = -1;//走过的位置标记为-1 
		backtrack(xx, yy, cur + 1);//从当前结点（xx，yy）出发，这是第cur个点 
		Array_Map[xx][yy] = 0;//返回之后 我先不走这间房子 则为0 
	}
}

void path_solve()//根据我走过的路径的方向，寻找到我走的房间序号 
{
	int x = Start_Pos_x, y = Start_Pos_y;//开始点
	Array_Map[Start_Pos_x][Start_Pos_y] = 1;//设置开始点是1
	for (int i = 1; i < Num_Hang*Num_Lie - Num_StopRoom; i++)
	{
		int xx = x + Dir_x[Array_Best[i]];//设置开始点加上开始点走的路径方向的x的值
		int yy = y + Dir_y[Array_Best[i]];//设置开始点加上开始点走的路径方向的y的值
		Array_Map[xx][yy] = Array_Map[x][y] + 1;//设置第二步走的点为2
		x = xx;//把第二个点重新设置成开始点x
		y = yy;//把第二个点重新设置成开始点y
	}
}
void TextFileWriteinput(const char* FileName, int hang, int lie, int stop, int Startposx, int Startposy, int Endtposx, int Endtposy)//文件名字
{

	//int StopPosx[50] = { -1 };//暂时定义最多有50个障碍点，x
	//int StopPosy[50] = { -1 };//暂时定义最多有50个障碍点，y   -1表示没有
	ofstream out;
	out.open(FileName);//iso::trunc表示在打开文件前将文件清空，由于是写入，文件不存在则创建
	out << hang << "行" << "\n" << lie << "列" << "\n" << stop << "封闭房间个数" << "\n";
	for (int i = 0; i < 50; i++)
	{
		if (StopPosx[i] != -1)
		{
			out << StopPosx[i] << "\t" << StopPosy[i] << "封闭房间的位置" << "\n";
		}

	}
	out << Startposx << "\t" << Startposy << "开始点" << "\n" << Endtposx << "\t" << Endtposy << "结束点" << "\n";
	out.close();
}
void TextFileWriteoutput(const char* FileName)//文件名字
{

	ofstream out;
	out.open(FileName);//iso::trunc表示在打开文件前将文件清空，由于是写入，文件不存在则创建
	out << Minturn << "最少转弯次数" << "\t" << num << "有几条路径" << "\n";
	//打印最优路径示意图
	for (int ii = 1; ii <= Num_Hang; ii++)
	{
		for (int j = 1; j <= Num_Lie; j++)
		{
			if (j != 1)  out << "    ";
			out << Array_Map[ii][j];
		}
		out << "\n";
	}
	out.close();
}

int main()
{

	for (int qq = 0; qq < 50; qq++)//初始化全部设置成-1
	{
		StopPosx[qq] = -1;
		StopPosy[qq] = -1;
	}
	//推荐3x3太大的太难找了
	//输入地图的行  列  几个障碍物
	cout << "输入地图的行  列  几个障碍物\n";
	scanf("%d%d%d", &Num_Hang, &Num_Lie, &Num_StopRoom);

	for (int i = 0; i < Num_StopRoom; i++)
	{
		int x, y;
		//输入第几个障碍物的点
		cout << "输入第几个障碍物的点\n";
		scanf("%d%d", &x, &y);
		Array_Map[x][y] = -1;
		StopPosx[i] = x;//把点存起来等会写入到txt需要用到
		StopPosy[i] = y;
	}
	//输入开始点   输入结束点
	cout << "输入开始点   输入结束点\n";
	scanf("%d%d%d%d", &Start_Pos_x, &Start_Pos_y, &End_Pos_x, &End_Pos_y);

	TextFileWriteinput("input.txt", Num_Hang, Num_Lie, Num_StopRoom, Start_Pos_x, Start_Pos_y, End_Pos_x, End_Pos_y);

	Array_Map[Start_Pos_x][Start_Pos_y] = -1;
	backtrack(Start_Pos_x, Start_Pos_y, 1);;
	path_solve();
	//打印最小转弯次数，打印一共有几个转弯次数的路径条数
	printf("%d\n%d\n", Minturn, num);

	if (num == 0)
	{
		cout << "没找到\n";
	}
	//打印最优路径示意图
	for (int ii = 1; ii <= Num_Hang; ii++)
	{
		for (int j = 1; j <= Num_Lie; j++)
		{
			if (j != 1)   printf("   ");
			printf("%d", Array_Map[ii][j]);
		}
		printf("\n");
	}
	TextFileWriteoutput("output.txt");

	system("pause");
	return 0;
}
