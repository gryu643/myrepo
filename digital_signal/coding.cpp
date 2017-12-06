#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

int ctoi(char *c)
{
	if(strcmp(c, "0")==0)
	{
		return 0;
	}
	else if(strcmp(c, "1")==0)
	{
		return 1;
	}
	else if(strcmp(c, "2")==0)
	{
		return 2;
	}
	else if(strcmp(c, "3")==0)
	{
		return 3;
	}
	else if(strcmp(c, "4")==0)
	{
		return 4;
	}
	else if(strcmp(c, "5")==0)
	{
		return 5;
	}
	else if(strcmp(c, "6")==0)
	{
		return 6;
	}
	else if(strcmp(c, "7")==0)
	{
		return 7;
	}
	else if(strcmp(c, "8")==0)
	{
		return 8;
	}
	else if(strcmp(c, "9")==0)
	{
		return 9;
	}
}

int main(int argc, char* argv[])
{
	int D1=0;
	int D2=0;
	int O1=0;
	int O2=0;
	int i=0;
	int len=0;
	char *tp;
	char *infname = argv[1];
	char *outfname = argv[2];
	int input[128];
	char str[512];

	//ファイルオープン
	ifstream ifs(infname);//ファイル入力ストリーム
	ofstream ofs(outfname);//ファイル出力ストリーム

	if(ifs.fail()){
		cout << infname << "ファイルが開けません" << "\n";
		return -1;
	}

	//行取得
	ifs.getline(str, sizeof str - 1);
	
	//,で文字列を分解、received[]に受信系列を格納
	tp = strtok(str, ",");
	while(tp != NULL){
		input[i] = ctoi(tp);
		tp = strtok(NULL, ",");
		i++;
	}

	//受信系列の長さ
	len = i;

	for(i=0;i<len-1;i++)
	{
		//出力系列の書き込み
		O1 = (input[i]+D1+D2)%2;
		O2 = (input[i]+D2)%2;
		ofs << O1 << O2 <<",";
		D2 = D1;
		D1 = input[i];
	}
	O1 = (input[i]+D1+D2)%2;
	O2 = (input[i]+D2)%2;
	ofs << O1 << O2;
	
	return 0;
}