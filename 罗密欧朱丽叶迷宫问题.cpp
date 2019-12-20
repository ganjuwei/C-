
#include<iostream>
#include<fstream>

using namespace std;

int Num_Hang;							//����Num_Hang �ǵ�ͼ����					��������������
int Num_Lie;							//����Num_Lie �ǵ�ͼ����					��������������
int Num_StopRoom;						//����Num_StopRoom �ǵ�ͼ�ϰ��ĸ���			��������������


int Array_Map[105][105];			    //����Array_Map �ǵ�ͼ��С105 105			����������
int Array_Path[105 * 105];			    //����Array_Path  ���ߵ�·���ķ���			����������
int Array_Best[105 * 105];				//����Array_Best  ���ߵ�·��������·��			����������

//��Dir_x[0] Dir_y[0]��ʾ�ߵ��ǵ�ǰ��������ĸ���
//��Dir_x[1] Dir_y[1]��ʾ�ߵ��ǵ�ǰ��������ĸ���
int Dir_x[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
int Dir_y[] = { 1, -1, 0, 0, 1, -1, -1, 1 };//�˸����� ��������  ��Ҫб�ŵĶԽ��� 

//������� Start_Pos        �յ�End_Pos     ��������������
int Start_Pos_x, Start_Pos_y, End_Pos_x, End_Pos_y;

//������Сת����� Minturn       һ���м����ߵ�������·��num     ��������������
int Minturn = 99999;//�涨һ�������
int num = 0;		//�涨һ���м����ߵ����ŵ�·��

int StopPosx[50];//��ʱ���������50���ϰ��㣬x
int StopPosy[50];//��ʱ���������50���ϰ��㣬y   -1��ʾû��

void backtrack(int x, int y, int cur)//�ӵ�ǰ���ӣ�x��y�����������߹��ĵ�cur�䷿�� 
{
	cout << "������ing\n";
	//��ǰ���������ߵķ��� �����Ͽ��ȥ����ֹ�ߵķ��ӣ������3x3����շ�����1  ��ô������8������û�ߵ�Ŀ�ĵأ���������·��ʧ����
	if (cur >= Num_Hang*Num_Lie - Num_StopRoom)//���Ѿ��߱������еķ��� ����Ե���Juliet���� 
	{
		if (x != End_Pos_x || y != End_Pos_y)
		{
			return;//���Ŀ�ĵز���  Julietʧ��
		}
		int turn = 0;								//��ʼ��һ����ʱ����  ��С��ת�����turn


		for (int i = 2; i < cur; i++)//�����path��¼���Ƿ��� �����ǰһ������ͬ�Ļ� ��ת��+1  ��һ������ת�򡣴�2��ʼ
		{
			if (Array_Path[i] != Array_Path[i - 1])//�ж�·�� �����ڶ����ߵ�·���ķ����һ��ʼ�Ĳ�һ����֤��ת����
			{
				turn++;		//��ʱת�������һ
			}
		}
		//���ת��Ĵ�������֮ǰ�Ķ�ҪС������϶����������·���ˣ���ʼ��99999����ֹ��ͼ�ܴ�
		//��Сת��·�������99999+10 ����ô��һ���жϾ� ���������Գ�ʼ��������һ�㡣

		//һ.����֮ǰ������ת��Minturn��7�� ��һ������ʱת��turn5��  ��ô��Ҫ
		//1.������������ 
		//2.��������·������ 
		//3.��������·���������� 
		if (turn < Minturn)
		{
			Minturn = turn;
			memcpy(Array_Best, Array_Path, sizeof(Array_Path));//��path��ֵȫ����ֵ��best  
			num = 1;
			//�����һ������·����7 �����5 ��ô���ŵ���·������������Ϊ1��numֻ��¼�������·��������
		}
		//��.����֮ǰ������ת��Minturn��5�� ��һ������ʱת��turn5��  ��ô��Ҫ
		//1.��������·���������� ��һ�ξͺ���
		else if (turn == Minturn)   num++;
		//��.����֮ǰ������ת��Minturn��5�� ��һ������ʱת��turn6��  ��ô��Ҫ
		//1.ʲô�����ɷ���
		return;
	}

	//��������һ������
	//˼·��
	//1.�����ж������߿��Բ������ߣ�����������谭�����������Ե��֤��������򲻿����ߣ�
	//2.��������ߣ����Ҿͽ�ȥ�����ж���һ����ģ����Ͽ��Բ������ߣ���������ߣ����Ҿ��ߣ���������ԣ����Ҿͷ���������һ������Ϊ0
	for (int i = 0; i < 8; i++)
	{
		int xx = x + Dir_x[i];
		int yy = y + Dir_y[i];
		if (Array_Map[xx][yy] == -1)  continue;//����һ����յķ��ӣ����������� ���ҿ�����������ɲ������� 
		if (xx<1 || xx>Num_Hang || yy<1 || yy>Num_Lie)  continue;//һ��Լ�� ���˵�ͼ�ı�Ե�ˣ����������� ���ҿ�����������ɲ������� 
		Array_Path[cur] = i;//��¼��ǰ�ڵ�����һ�������� 
		Array_Map[xx][yy] = -1;//�߹���λ�ñ��Ϊ-1 
		backtrack(xx, yy, cur + 1);//�ӵ�ǰ��㣨xx��yy�����������ǵ�cur���� 
		Array_Map[xx][yy] = 0;//����֮�� ���Ȳ�����䷿�� ��Ϊ0 
	}
}

void path_solve()//�������߹���·���ķ���Ѱ�ҵ����ߵķ������ 
{
	int x = Start_Pos_x, y = Start_Pos_y;//��ʼ��
	Array_Map[Start_Pos_x][Start_Pos_y] = 1;//���ÿ�ʼ����1
	for (int i = 1; i < Num_Hang*Num_Lie - Num_StopRoom; i++)
	{
		int xx = x + Dir_x[Array_Best[i]];//���ÿ�ʼ����Ͽ�ʼ���ߵ�·�������x��ֵ
		int yy = y + Dir_y[Array_Best[i]];//���ÿ�ʼ����Ͽ�ʼ���ߵ�·�������y��ֵ
		Array_Map[xx][yy] = Array_Map[x][y] + 1;//���õڶ����ߵĵ�Ϊ2
		x = xx;//�ѵڶ������������óɿ�ʼ��x
		y = yy;//�ѵڶ������������óɿ�ʼ��y
	}
}
void TextFileWriteinput(const char* FileName, int hang, int lie, int stop, int Startposx, int Startposy, int Endtposx, int Endtposy)//�ļ�����
{

	//int StopPosx[50] = { -1 };//��ʱ���������50���ϰ��㣬x
	//int StopPosy[50] = { -1 };//��ʱ���������50���ϰ��㣬y   -1��ʾû��
	ofstream out;
	out.open(FileName);//iso::trunc��ʾ�ڴ��ļ�ǰ���ļ���գ�������д�룬�ļ��������򴴽�
	out << hang << "��" << "\n" << lie << "��" << "\n" << stop << "��շ������" << "\n";
	for (int i = 0; i < 50; i++)
	{
		if (StopPosx[i] != -1)
		{
			out << StopPosx[i] << "\t" << StopPosy[i] << "��շ����λ��" << "\n";
		}

	}
	out << Startposx << "\t" << Startposy << "��ʼ��" << "\n" << Endtposx << "\t" << Endtposy << "������" << "\n";
	out.close();
}
void TextFileWriteoutput(const char* FileName)//�ļ�����
{

	ofstream out;
	out.open(FileName);//iso::trunc��ʾ�ڴ��ļ�ǰ���ļ���գ�������д�룬�ļ��������򴴽�
	out << Minturn << "����ת�����" << "\t" << num << "�м���·��" << "\n";
	//��ӡ����·��ʾ��ͼ
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

	for (int qq = 0; qq < 50; qq++)//��ʼ��ȫ�����ó�-1
	{
		StopPosx[qq] = -1;
		StopPosy[qq] = -1;
	}
	//�Ƽ�3x3̫���̫������
	//�����ͼ����  ��  �����ϰ���
	cout << "�����ͼ����  ��  �����ϰ���\n";
	scanf("%d%d%d", &Num_Hang, &Num_Lie, &Num_StopRoom);

	for (int i = 0; i < Num_StopRoom; i++)
	{
		int x, y;
		//����ڼ����ϰ���ĵ�
		cout << "����ڼ����ϰ���ĵ�\n";
		scanf("%d%d", &x, &y);
		Array_Map[x][y] = -1;
		StopPosx[i] = x;//�ѵ�������Ȼ�д�뵽txt��Ҫ�õ�
		StopPosy[i] = y;
	}
	//���뿪ʼ��   ���������
	cout << "���뿪ʼ��   ���������\n";
	scanf("%d%d%d%d", &Start_Pos_x, &Start_Pos_y, &End_Pos_x, &End_Pos_y);

	TextFileWriteinput("input.txt", Num_Hang, Num_Lie, Num_StopRoom, Start_Pos_x, Start_Pos_y, End_Pos_x, End_Pos_y);

	Array_Map[Start_Pos_x][Start_Pos_y] = -1;
	backtrack(Start_Pos_x, Start_Pos_y, 1);;
	path_solve();
	//��ӡ��Сת���������ӡһ���м���ת�������·������
	printf("%d\n%d\n", Minturn, num);

	if (num == 0)
	{
		cout << "û�ҵ�\n";
	}
	//��ӡ����·��ʾ��ͼ
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
