#include <stdio.h>
#include "graphics.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

int CreatePrimeNumber(){
		int number, i = 2, count = 0;
		srand(time(NULL));
		while (count == 0){
			number = (rand() % 50) + 100;
			count = 1;
			for (i = 2; i < number; i++)
			{
				if (number%i == 0){
					count = 0;
					break;
				}
			}
		}
		return number;
	}

int CreateE(int Phi){//phi ile aralarýnda asal E sayýsý üretecek.(gcd function)
		srand(time(NULL));
		int E, i, count = 0;
		while (count == 0){
			E = (rand() % (Phi - 3)) + 2;//phiden küçük 2 ve üzeri rakam random atýyor
			count = 1;
			for (i = 2; i < Phi; i++)
			{
				if ((Phi%i == 0) && (E%i == 0))//sýrayla denior 2 den baslayarak aralarýnda asalmý diye. eðer ikiside bir sayýya bölünürse count 0 kalýyor ve yeniden random atýp deniyor eðer bulamazsa count 1 kalýyor random sayý phi ile aralarýnda asaldýr
				{
					count = 0;
					break;
				}
			}
		}
		return E;
	}

int CreateD(int PHIn, int E){
		int i;

		for (i = 2; i < PHIn; i++)
		{
			if ((E * i) % PHIn == 1)// E*x= 1 mod(PHI(N)) --> mod phi(N)'de 1 sonucunu verecek E*X sayýsý olsun.Bulunabilecek en küçük X sayýsýna E sayýsýnýn mod(phi(n))'de ki tersi deniliyor.
			{
				//printf("E tamsayisinin mod PHI(N)'de tersi yani D sayisi:%d\n", i);
				return i;
			}
		}
		return i;
	}

int encrypt(int E, int M, int N){

		int i, C = 1;
		for (i = 0; i<E; i++)
			C = C*M%N;

		return C%N;
	}

int decrypt(int D, int C, int N){

		int i, DC = 1;
		for (i = 0; i<D; i++)
			DC = DC*C%N;

		return DC%N;
}

int main(){
		int i, N, P, Q, PHIn, E, D, M;
		int C[100], DC[100];
		char message[100], Ormsg[100];

		int x=60, y=30;
		char Bigtext[10][30];
		initwindow(800, 600, "RSA");

		settextstyle(3, 1, 1);
		settextjustify(1, 3);
		setcolor(7);

			char tempchar[2];
			char texta = '0';
			int a = 0,waitt=0;
		
		while (1){

			//cleardevice();
			outtextxy(10, 75, "Enter a message:");
			readimagefile("exit.jpg", 600, 525, 750, 575);
			readimagefile("sender.jpg", 175, 60, 250, 160);//sender    
			readimagefile("receiver.jpg", 525, 60, 600, 160);//receiver  
			while (1){
				waitt = 0;
				if (kbhit())waitt = 1;

				if (waitt==1)
				{
					fflush(stdin);
					texta = getch();//karakteri texta nýn içerisine alýyor
					fflush(stdin);
					message[a] = texta;//message degiskenine biriktiriyor girilen harfleri
					message[a + 1] = NULL;
					outtextxy(10, 75, "Enter a message:");

					if (texta == 8||texta==27)//silme ve esc tusu pasif
					{
						continue;
					}
					if (texta == 13){ break; }
					sprintf(tempchar, "%c", texta);
					outtextxy(10 + (a * 13), 100, tempchar);//ekrana basýyor. Her harf için a * 9 pixel ileri gidiyor
					printf("text2:%s - text1:%s\n", tempchar, message);
					a++;
					waitt = 0;
				}
			
					if (ismouseclick(WM_LBUTTONDOWN))
					{
						getmouseclick(WM_LBUTTONDOWN, x, y);

					}
					if (x > 600 && x < 775 && y>525 && y < 575) //exit
					{
						exit(-1);
					}
			}
			cleardevice();
			outtextxy(10, 75, "Enter a message:");
			readimagefile("exit.jpg", 600, 525, 750, 575);
			readimagefile("sender.jpg", 175, 60, 250, 160);//sender    
			readimagefile("receiver.jpg", 525, 60, 600, 160);//receiver  



			readimagefile("securitypro.jpg",350, 300, 450, 400);//security provider  
			delay(200);

			P = CreatePrimeNumber();
			Q = CreatePrimeNumber();
			while (P == Q){
				Q = CreatePrimeNumber();
			}
			N = P*Q;
			PHIn = (P - 1)*(Q - 1);
			E = CreateE(PHIn);//phi deðerini ile aralarýnda asal oalcak þekilde bir E sayýsý oluþturulacak.
			D = CreateD(PHIn, E);

			for (i = 0; i < strlen(message); i++)
			{
				M = message[i];
				C[i] = encrypt(E, M, N);
			}
			for (i = 0; i <strlen(message); i++)
			{
				DC[i] = decrypt(D, C[i], N);
				Ormsg[i] = DC[i];
			}



			sprintf(Bigtext[1], "P : %d     ", P);
			sprintf(Bigtext[2], "Q : %d     ", Q);
			sprintf(Bigtext[3], "N : %d     ", N);

			sprintf(Bigtext[4], "Phi(N) : %d     ", PHIn);
			sprintf(Bigtext[5], "E : %d     ", E);
			sprintf(Bigtext[6], "D : %d     ", D);

			sprintf(Bigtext[7], "Public Key : (%d,%d)   ", N, E);
			sprintf(Bigtext[8], "Private Key : (%d,%d)   ", N, D);



			outtextxy(50, 430, Bigtext[1]); delay(50);
			outtextxy(50, 450, Bigtext[2]); delay(50);
			outtextxy(50, 470, Bigtext[3]); delay(50);
			outtextxy(50, 490, Bigtext[4]); delay(50);
			outtextxy(50, 510, Bigtext[5]); delay(50);
			outtextxy(50, 530, Bigtext[6]); delay(50);


			delay(1000);

			outtextxy(130, 400, Bigtext[7]);
			delay(500);
			readimagefile("arrowleft.jpg", 225, 170, 275, 350);//sol arrow
			delay(500);


			outtextxy(310, 150, "Encrypted Message:"); 
			for (i = 0; i < a; i++){
				sprintf(tempchar, "%c", C[i]);
				outtextxy(310 + (i * 13), 170, tempchar);
			}

			readimagefile("arrow1.jpg", 300, 60, 325, 120);//orta
			delay(400);
			readimagefile("arrow2.jpg", 350, 60, 375, 120);//orta
			delay(400);
			readimagefile("arrow3.jpg", 400, 60, 425, 120);//orta
			delay(400);
			readimagefile("arrow4.jpg", 450, 60, 475, 120);//orta
			delay(400);




			outtextxy(500, 400, Bigtext[8]);
			delay(500);
			readimagefile("arrowright.jpg", 525, 170, 575, 350);//sað arrow

			outtextxy(610, 75, "Descrypted Message:");
			delay(1000);
			for (i = 0; i < a; i++){
				sprintf(tempchar, "%c", Ormsg[i]); delay(10);
				outtextxy(610+(i*10), 100, tempchar);
			}



		
		//showerrorbox("Sample of an Error Box");
			for (i = 0; i < strlen(message); i++)
			{
				message[i] = { NULL };
				Ormsg[i] = { NULL };
			}
				getmouseclick(WM_LBUTTONDOWN, x, y);

			
			if (x > 600 && x < 775 && y>525 && y < 575) //exit
			{
				exit(-1);
			}
			a = 0; 
		}
		closegraph();
		return 0;
}
