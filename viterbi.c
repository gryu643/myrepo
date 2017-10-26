#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int len=0;
int flag = 0;

struct _state{
	char now_state[4];
	int pre_addr;
	int hamming;
	int jouhoukeiretsu;
	char soushinkeiretsu[4];
};

struct _state queue[1024];

int Torerisu(char *r, int start, int end){
	int h=0;
	int i=0;
	int w=0;
	int addr0=0;
	int addr1=0;
	int addr2=0;
	int addr3=0;
	
	for(i=start;i<=end;i++){
		if(strcmp(queue[i].now_state, "00")==0){
			//ハミング距離の計算
			h = abs((r[0] - '0') - 0);
			h += abs((r[1] - '0') - 0);
			queue[end+w+1].hamming = h + queue[i].hamming;
			//前状態のアドレスを格納
			queue[end+w+1].pre_addr = i;
			//次状態を格納
			strcpy(queue[end+w+1].now_state, "00");
			//情報系列を格納
			queue[end+w+1].jouhoukeiretsu = 0;
			//送信系列を格納
			strcpy(queue[end+w+1].soushinkeiretsu, "00");

			//00状態を以前に生成していない場合、書き込み先を更新
			if(addr0==0){
				addr0 = end+w+1;
				w++;
			}
			else{
				if(queue[addr0].hamming>=queue[end+w+1].hamming){
					//次状態が2つある場合、ハミング距離が短い方を格納
					queue[addr0].hamming = queue[end+w+1].hamming;
					queue[addr0].pre_addr = queue[end+w+1].pre_addr;
					queue[addr0].jouhoukeiretsu = queue[end+w+1].jouhoukeiretsu;
					strcpy(queue[addr0].soushinkeiretsu, queue[end+w+1].soushinkeiretsu);
				}
			}

			if(flag==0){
				h = abs((r[0] - '0') - 1);
				h += abs((r[1] - '0') - 1);
				queue[end+w+1].hamming = h + queue[i].hamming;
				queue[end+w+1].pre_addr = i;
				strcpy(queue[end+w+1].now_state, "10");
				//情報系列を格納
				queue[end+w+1].jouhoukeiretsu = 1;
				//送信系列を格納
				strcpy(queue[end+w+1].soushinkeiretsu, "11");
					
				if(addr2==0){
					addr2 = end+w+1;
					w++;
				}
				else{
					if(queue[addr2].hamming>=queue[end+w+1].hamming){
						queue[addr2].hamming = queue[end+w+1].hamming;
						queue[addr2].pre_addr = queue[end+w+1].pre_addr;
						queue[addr2].jouhoukeiretsu = queue[end+w+1].jouhoukeiretsu;
						strcpy(queue[addr2].soushinkeiretsu, queue[end+w+1].soushinkeiretsu);
					}
				}
			}
		}
		else if(strcmp(queue[i].now_state, "01")==0){
			h = abs((r[0] - '0') - 1);
			h += abs((r[1] - '0') - 1);
			queue[end+w+1].hamming = h + queue[i].hamming;
			queue[end+w+1].pre_addr = i;
			strcpy(queue[end+w+1].now_state, "00");
			//情報系列を格納
			queue[end+w+1].jouhoukeiretsu = 0;
			//送信系列を格納
			strcpy(queue[end+w+1].soushinkeiretsu, "11");
			
			if(addr0==0){
				addr0 = end+w+1;
				w++;
			}
			else{
				if(queue[addr0].hamming>=queue[end+w+1].hamming){
					queue[addr0].hamming = queue[end+w+1].hamming;
					queue[addr0].pre_addr = queue[end+w+1].pre_addr;
					queue[addr0].jouhoukeiretsu = queue[end+w+1].jouhoukeiretsu;
					strcpy(queue[addr0].soushinkeiretsu, queue[end+w+1].soushinkeiretsu);
				}
			}

			if(flag==0){
				h = abs((r[0] - '0') - 0);
				h += abs((r[1] - '0') - 0);
				queue[end+w+1].hamming = h + queue[i].hamming;
				queue[end+w+1].pre_addr = i;
				strcpy(queue[end+w+1].now_state, "10");
				//情報系列を格納
				queue[end+w+1].jouhoukeiretsu = 1;
				//送信系列を格納
				strcpy(queue[end+w+1].soushinkeiretsu, "00");
				
				if(addr2==0){
					addr2 = end+w+1;
					w++;
				}
				else{
					if(queue[addr2].hamming>=queue[end+w+1].hamming){
						queue[addr2].hamming = queue[end+w+1].hamming;
						queue[addr2].pre_addr = queue[end+w+1].pre_addr;
						queue[addr2].jouhoukeiretsu = queue[end+w+1].jouhoukeiretsu;
						strcpy(queue[addr2].soushinkeiretsu, queue[end+w+1].soushinkeiretsu);
					}
				}
			}
		}
		else if(strcmp(queue[i].now_state, "10")==0){
			h = abs((r[0] - '0') - 1);
			h += abs((r[1] - '0') - 0);
			queue[end+w+1].hamming = h + queue[i].hamming;
			queue[end+w+1].pre_addr = i;
			strcpy(queue[end+w+1].now_state, "01");
			//情報系列を格納
			queue[end+w+1].jouhoukeiretsu = 0;
			//送信系列を格納
			strcpy(queue[end+w+1].soushinkeiretsu, "10");
			
			if(addr1==0){
				addr1 = end+w+1;
				w++;
			}
			else{
				if(queue[addr1].hamming>=queue[end+w+1].hamming){
					queue[addr1].hamming = queue[end+w+1].hamming;
					queue[addr1].pre_addr = queue[end+w+1].pre_addr;
					queue[addr1].jouhoukeiretsu = queue[end+w+1].jouhoukeiretsu;
					strcpy(queue[addr1].soushinkeiretsu, queue[end+w+1].soushinkeiretsu);
				}
			}

			if(flag==0){
				h = abs((r[0] - '0') - 0);
				h += abs((r[1] - '0') - 1);
				queue[end+w+1].hamming = h + queue[i].hamming;
				queue[end+w+1].pre_addr = i;
				strcpy(queue[end+w+1].now_state, "11");
				//情報系列を格納
				queue[end+w+1].jouhoukeiretsu = 1;
				//送信系列を格納
				strcpy(queue[end+w+1].soushinkeiretsu, "01");
				
				if(addr3==0){
					addr3 = end+w+1;
					w++;
				}
				else{
					if(queue[addr3].hamming>=queue[end+w+1].hamming){
						queue[addr3].hamming = queue[end+w+1].hamming;
						queue[addr3].pre_addr = queue[end+w+1].pre_addr;
						queue[addr3].jouhoukeiretsu = queue[end+w+1].jouhoukeiretsu;
						strcpy(queue[addr3].soushinkeiretsu, queue[end+w+1].soushinkeiretsu);
					}
				}
			}
		}
		else if(strcmp(queue[i].now_state, "11")==0){
			h = abs((r[0] - '0') - 0);
			h += abs((r[1] - '0') - 1);
			queue[end+w+1].hamming = h + queue[i].hamming;
			queue[end+w+1].pre_addr = i;
			strcpy(queue[end+w+1].now_state, "01");
			//情報系列を格納
			queue[end+w+1].jouhoukeiretsu = 0;
			//送信系列を格納
			strcpy(queue[end+w+1].soushinkeiretsu, "01");
			
			if(addr1==0){
				addr1 = end+w+1;
				w++;
			}
			else{
				if(queue[addr1].hamming>=queue[end+w+1].hamming){
					queue[addr1].hamming = queue[end+w+1].hamming;
					queue[addr1].pre_addr = queue[end+w+1].pre_addr;
					queue[addr1].jouhoukeiretsu = queue[end+w+1].jouhoukeiretsu;
					strcpy(queue[addr1].soushinkeiretsu, queue[end+w+1].soushinkeiretsu);
				}
			}

			if(flag==0){
				h = abs((r[0] - '0') - 1);
				h += abs((r[1] - '0') - 0);
				queue[end+w+1].hamming = h + queue[i].hamming;
				queue[end+w+1].pre_addr = i;
				strcpy(queue[end+w+1].now_state, "11");
				//情報系列を格納
				queue[end+w+1].jouhoukeiretsu = 1;
				//送信系列を格納
				strcpy(queue[end+w+1].soushinkeiretsu, "10");
				
				if(addr3==0){
					addr3 = end+w+1;
					w++;
				}
				else{
					if(queue[addr3].hamming>=queue[end+w+1].hamming){
						queue[addr3].hamming = queue[end+w+1].hamming;
						queue[addr3].pre_addr = queue[end+w+1].pre_addr;
						queue[addr3].jouhoukeiretsu = queue[end+w+1].jouhoukeiretsu;
						strcpy(queue[addr3].soushinkeiretsu, queue[end+w+1].soushinkeiretsu);
					}
				}
			}
		}
	}
	//printf("gen_num=%d\n", w);
	return w;
}

int main(int arvc, char *argv[]){
	FILE *fp;
	char *fname = argv[1];
	char *tp;
	char str[512];
	char *received[128];
	int i=0,j=0;
	int start=0,end=0;
	int state_num=0;
	int tmp=0;

	//ファイルオープン
	fp = fopen(fname, "r");
	if(fp == NULL){
		printf("%sファイルが開けません\n", fname);
		return -1;
	}

	//行取得
	fgets(str, sizeof str, fp);
	
	//,で文字列を分解、received[]に受信系列を格納
	tp = strtok(str, ",");
	while(tp != NULL){
		received[i] = tp;
		tp = strtok(NULL, ",");
		i++;
	}

	//受信系列の長さ
	len = i;
	int state_addr[len];

	//ファイルクローズ
	fclose(fp);

	//初期状態
	strcpy(queue[0].now_state, "00");
	queue[0].pre_addr = 0;
	queue[0].hamming = 0;

	//状態生成
	for(j=0;j<i;j++){
		if((len-j)<=2){
			flag = 1;
		}
		state_num = Torerisu(received[j], start, end);
		start = end + 1;
		end += state_num;
	}

	//ハミング距離最短となる状態のアドレスをstate_addrに格納
	tmp = start;
	for(i=0;i<len;i++){
		state_addr[len-i-1] = tmp;
		tmp = queue[tmp].pre_addr;
	}

	printf("情報系列：");
	for(i=0;i<len-2;i++){
		printf("%d ", queue[state_addr[i]].jouhoukeiretsu);
	}
	printf("\n");

	printf("送信系列：");
	for(i=0;i<len;i++){
		printf("%s ", queue[state_addr[i]].soushinkeiretsu);
	}
	printf("\n");
	
	return 0;
}