//
// Created by 王智杰 on 2025/6/14.
//
//41.棋盘覆盖（分治）**
//
//Description
//在一个2k × 2k 个方格组成的棋盘中，恰有一个方格与其他方格不同，称该方格为一特殊方格，且称该棋盘为一特殊棋盘。
//在棋盘覆盖问题中，要用图示的4种不同形态的L型骨牌覆盖给定的棋盘上除特殊方格以外的所有方格，L型骨牌不能旋转，且任何两个L型骨牌不得重叠覆盖。
//1913_1.png
//棋盘和标记为红色的特殊方格                      4种L型骨牌
//Input
//第一行是一个T，表示案例数。对于每一个案例，有三个数K，X，Y分别表示在一个2k × 2k的棋盘中，在第X行第Y列有一个特殊方格。1 ≤ K ≤ 8
//1 ≤ X, Y ≤ 2k
//Output
//输出这个被骨牌覆盖的棋盘，分别用a,b,c,d表示四种骨牌（分别用以下四种字符图形表示），特殊方格用*号表示。
//aa      bb    c      d
//a        b    cc    dd
//具体输出见sample Output
//Sample Input
//2
//2 1 2
//1 1 1
//
//Sample Output
//c*bb
//ccdb
//cddd
//ccdd
//*d
//dd


#include<stdio.h>
#include<math.h>

#define MAX 256
char board[MAX][MAX];
const char tile_char[4] = {'a','b','c','d'};
//象限左上角坐标(tr,tc),tr代表行，tc代表列;特殊方格坐标(dr,dc),dr代表行，dc代表列*****
void ChessBoard(int tr,int tc,int dr,int dc,int size){
    if(size == 1)//如果棋盘大小为1，结束
        return;

    int s = size/2; //将棋盘对半划分四个象限
    //当特殊方格在左上角时
    if(dr < tr + s && dc < tc + s){
        board[tr+s-1][tc+s] = tile_char[3]; //右上角
        board[tr+s][tc+s] = tile_char[3]; //右下角
        board[tr+s][tc+s-1] = tile_char[3]; //左下角

    //递归覆盖四个子棋盘
    ChessBoard(tr,tc,dr,dc,s);//左上角
    ChessBoard(tr,tc+s,tr+s-1,tc+s,s);//右上角
    ChessBoard(tr+s,tc,tr+s,tc+s-1,s);//左下角
    ChessBoard(tr+s,tc+s,tr+s,tc+s,s);//右下角
    }

    //特殊方格在右上角
    if(dr < tr + s && dc > tc + s - 1){
        board[tr+s-1][tc+s-1] = tile_char[2]; //左上角
        board[tr+s][tc+s] = tile_char[2];  //右下角
        board[tr+s][tc+s-1] = tile_char[2];  //左下角

    //递归覆盖四个子棋盘
    ChessBoard(tr,tc,tr+s-1,tc+s-1,s);//左上角
    ChessBoard(tr,tc+s,dr,dc,s);//右上角
    ChessBoard(tr+s,tc,tr+s,tc+s-1,s);//左下角
    ChessBoard(tr+s,tc+s,tr+s,tc+s,s);//右下角
    }

    //特殊方格在左下角
    if(dr > tr + s - 1 && dc < tc + s){
        board[tr+s-1][tc+s] = tile_char[1]; //右上角
        board[tr+s][tc+s] = tile_char[1]; //右下角
        board[tr+s-1][tc+s-1] = tile_char[1];  //左上角

    //递归覆盖四个子棋盘
    ChessBoard(tr,tc,tr+s-1,tc+s-1,s);//左上角
    ChessBoard(tr,tc+s,tr+s-1,tc+s,s);//右上角
    ChessBoard(tr+s,tc,dr,dc,s);//左下角
    ChessBoard(tr+s,tc+s,tr+s,tc+s,s);//右下角
    }

    //特殊方格在右下角
    if(dr > tr + s - 1 && dc > tc + s - 1){
        board[tr+s-1][tc+s] = tile_char[0]; //右上角
        board[tr+s-1][tc+s-1] = tile_char[0]; //左上角
        board[tr+s][tc+s-1] = tile_char[0]; //左下角

    //递归覆盖四个子棋盘
    ChessBoard(tr,tc,tr+s-1,tc+s-1,s);//左上角
    ChessBoard(tr,tc+s,tr+s-1,tc+s,s);//右上角
    ChessBoard(tr+s,tc,tr+s,tc+s-1,s);//左下角
    ChessBoard(tr+s,tc+s,dr,dc,s);//右下角
    }
}

int main(){
    int T;
    scanf("%d",&T);//输入测试用例个数
    while(T--){
        int K,X,Y,size;
        scanf("%d%d%d",&K,&X,&Y);
        size = (int)pow(2,K);//2^K=(int)pow(2,K)
        //初始化棋盘board为空
        for(int i =0;i < size; i++){
            for(int j = 0;j < size;j++){
                board[i][j] = ' '; // 初始化为空格
            }
            board[i][size] = '\0'; //每行末尾添加结束符***
        }
        board[X-1][Y-1] = '*';//初始化特殊方格
        ChessBoard(0,0,X-1,Y-1,size);//调用棋盘函数
        for(int i = 0; i < size; i++)
            printf("%s\n",board[i]);//按行 打印棋盘
    }
    return 0;
}