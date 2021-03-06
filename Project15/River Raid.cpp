#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ConsoleHelper.h"
#include "MediaPlayer.h"

using namespace System;
using namespace Threading;

struct inimigo {
	int inimigox;
	int inimigoy;
	int direção;
	bool nojogo = false;
};

struct objeto {
	int combx;
	int comby;
	bool comb = false;
};

int main(void)
{
	SomWork^ tiroSom = gcnew SomWork(500, 30);
	SomWork^ AbastecerSom = gcnew SomWork(600, 40);
	SomWork^ DestruicaoSom = gcnew SomWork(300, 55);
	SomWork^ CombustivelSom = gcnew SomWork(350, 60);
	
	srand(time(NULL));


	Console::SetWindowSize(128, 48);
	Console::SetBufferSize(128, 48);
	Console::CursorVisible = false;
	ConsoleKeyInfo tecla;

	//velocidades do jogo de 1 a 3
	int velocidade = 2;

	//combustivel
	int combustivel = 10;

	//Vida
	int vida = 3;

	//temporizador
	int frames = 0;
	int tempo = 1;

	//score
	int score = 0;

	//Coordenadas do jogador
	int posx = 29;
	int posy = 31;

    //Coordenadas do tiro
	int tiroy;
	int tirox;

	//Declaração do combustivel
	objeto Combus[3];
	   //não permite que os combustiveis comecem todos ao mesmo tempo
	int combjogo = 0;

	//variaveis para as ilhas
	int ilhay = 1;
	int limite;
	int mapay = 0;

	//Declaração do inimigo e quatidade
	inimigo Barco[2];
	inimigo Heli[2];
	inimigo Aviao;
	  //não permite que os inimigos comecem todos ao mesmo tempo
	int barcojogo = 0;
	int helijogo = 0;

	//sair do jogo
	bool sair = false;

	//tiro no jogo
	bool tiro = false;

	//ilhas no meio do mapa
	bool obstaculo = false;
	bool obstaculo2 = false;

	//animações da nave
	bool virandoE = false;
	bool virandoD = false;

	//sprite da explosão
	bool explosao = false;
	bool explosaob = false;

	//destruição da nave
	bool destruido = false;

	//pontes
	bool ponte = false;

	const int MENU = 0;//Estados do jogo.
	const int GAMEPLAY = 1;
	const int GAMEOVER = 2;

	int ESTADO_JOGO = MENU;//jogo começa no menu

	while (sair == false)
	{
		Thread::Sleep(48);



		switch (ESTADO_JOGO)
		{
		case MENU:
			//reset das variaveis
			vida = 3;
			velocidade = 2;
			frames = 0;
			tempo = 1;
			ilhay = 1;
			combustivel = 10;
			score = 0;
			barcojogo = 0;
			helijogo = 0;
			combjogo = 0;
			obstaculo = false;
			obstaculo2 = false;		
			tiro = false;
			for (int i = 0; i < 3; i++) {
				Barco[i].nojogo = false;
			}
			for (int i = 0; i < 3; i++) {
				Combus[i].comb = false;
			}
			
			ConsoleHelper::ImprimirASCIIExtended(10, 10, ConsoleColor::Black, ConsoleColor::Red, "    .----------------.  .----------------.  .----------------.  .----------------.  .----------------. ");
			ConsoleHelper::ImprimirASCIIExtended(10, 11, ConsoleColor::Black, ConsoleColor::Red, "   | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |");
			ConsoleHelper::ImprimirASCIIExtended(10, 12, ConsoleColor::Black, ConsoleColor::Red, "   | |  _______     | || |     _____    | || | ____   ____  | || |  _________   | || |  _______     | |");
			ConsoleHelper::ImprimirASCIIExtended(10, 13, ConsoleColor::Black, ConsoleColor::Red, "   | | |_   __ \\    | || |    |_   _|   | || ||_  _| |_  _| | || | |_   ___  |  | || | |_   __ \\    | |");
			ConsoleHelper::ImprimirASCIIExtended(10, 14, ConsoleColor::Black, ConsoleColor::Red, "   | |   | |__) |   | || |      | |     | || |  \\ \\   / /   | || |   | |_  \\_|  | || |   | |__) |   | |");
			ConsoleHelper::ImprimirASCIIExtended(10, 15, ConsoleColor::Black, ConsoleColor::Red, "   | |   |  __ /    | || |      | |     | || |   \\ \\ / /    | || |   |  _|  _   | || |   |  __ /    | |");
			ConsoleHelper::ImprimirASCIIExtended(10, 16, ConsoleColor::Black, ConsoleColor::Red, "   | |  _| |  \\ \\_  | || |     _| |_    | || |    \\ ' /     | || |  _| |___/ |  | || |  _| |  \\ \\_  | |");
			ConsoleHelper::ImprimirASCIIExtended(10, 17, ConsoleColor::Black, ConsoleColor::Red, "   | | |____| |___| | || |    |_____|   | || |     \\_/      | || | |_________|  | || | |____| |___| | |");
			ConsoleHelper::ImprimirASCIIExtended(10, 18, ConsoleColor::Black, ConsoleColor::Red, "   | |              | || |              | || |              | || |              | || |              | |");
			ConsoleHelper::ImprimirASCIIExtended(10, 19, ConsoleColor::Black, ConsoleColor::Red, "   | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |");
			ConsoleHelper::ImprimirASCIIExtended(10, 20, ConsoleColor::Black, ConsoleColor::Red, "    '----------------'  '----------------'  '----------------'  '----------------'  '----------------' ");
			ConsoleHelper::ImprimirASCIIExtended(10, 21, ConsoleColor::Black, ConsoleColor::Red, "            .----------------.  .----------------.  .----------------.  .----------------.             ");
			ConsoleHelper::ImprimirASCIIExtended(10, 22, ConsoleColor::Black, ConsoleColor::Red, "           | .--------------. || .--------------. || .--------------. || .--------------. |            ");
			ConsoleHelper::ImprimirASCIIExtended(10, 23, ConsoleColor::Black, ConsoleColor::Red, "           | |  _______     | || |      __      | || |     _____    | || |  ________    | |            ");
			ConsoleHelper::ImprimirASCIIExtended(10, 24, ConsoleColor::Black, ConsoleColor::Red, "           | | |_   __ \\    | || |     /  \\     | || |    |_   _|   | || | |_   ___ `.  | |            ");
			ConsoleHelper::ImprimirASCIIExtended(10, 25, ConsoleColor::Black, ConsoleColor::Red, "           | |   | |__) |   | || |    / /\\ \\    | || |      | |     | || |   | |   `. \\ | |            ");
			ConsoleHelper::ImprimirASCIIExtended(10, 26, ConsoleColor::Black, ConsoleColor::Red, "           | |   |  __ /    | || |   / ____ \\   | || |      | |     | || |   | |    | | | |            ");
			ConsoleHelper::ImprimirASCIIExtended(10, 27, ConsoleColor::Black, ConsoleColor::Red, "           | |  _| |  \\ \\_  | || | _/ /    \\ \\_ | || |     _| |_    | || |  _| |___.' / | |            ");
			ConsoleHelper::ImprimirASCIIExtended(10, 28, ConsoleColor::Black, ConsoleColor::Red, "           | | |____| |___| | || ||____|  |____|| || |    |_____|   | || | |________.'  | |            ");
			ConsoleHelper::ImprimirASCIIExtended(10, 29, ConsoleColor::Black, ConsoleColor::Red, "           | |              | || |              | || |              | || |              | |            ");
			ConsoleHelper::ImprimirASCIIExtended(10, 30, ConsoleColor::Black, ConsoleColor::Red, "           | '--------------' || '--------------' || '--------------' || '--------------' |            ");
			ConsoleHelper::ImprimirASCIIExtended(10, 31, ConsoleColor::Black, ConsoleColor::Red, "            '----------------'  '----------------'  '----------------'  '----------------'             ");

			ConsoleHelper::ImprimirASCIIExtended(50, 37, ConsoleColor::Black, ConsoleColor::White, "PRESSIONE ENTER PARA JOGAR");
			if (Console::KeyAvailable)
			{
				tecla = Console::ReadKey(true);
				if (tecla.Key == ConsoleKey::Enter)
				{
					ESTADO_JOGO = GAMEPLAY;

					Console::Clear();
				}

			}
			break;


		case GAMEPLAY:


			if (velocidade == 1) { frames++; }//velocidades
			else if (velocidade == 2) { frames += 2; }
			else if (velocidade == 3) { frames += 3; }

			//Temporizador
			if (frames >= 20) {
				frames = 0;
				tempo++;
				combustivel--;
				velocidade = 2;
				//"solta" os objetos
				helijogo < 2 ? helijogo++ : helijogo;
				barcojogo < 2 ? barcojogo++ : barcojogo;
				combjogo < 3 ? combjogo++ : combjogo;

				if (combustivel < 5) {
					CombustivelSom->Iniciar();
				}
			}
			

			Console::SetWindowSize(64, 44);
			Console::SetBufferSize(64, 44);
			Console::Clear();

			mapay = 0;//Variavel para "descer" as bordas do mapa.

		    //Cria as bordas do mapa.
	 		while (mapay <= 35)
			{
				ConsoleHelper::ImprimirASCIIExtended(0, mapay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "ÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(57, mapay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "ÛÛÛÛÛÛÛ");		
				mapay++;
			}

			//Identificação de telcas.
			if (Console::KeyAvailable)
			{
				tecla = Console::ReadKey(true);
				if (tecla.Key == ConsoleKey::LeftArrow && posx != 8)
				{
					posx--;
					Console::Beep(200, 25);
					Console::Beep(240, 25);
					virandoE = true;

				}
				else if (tecla.Key == ConsoleKey::RightArrow && posx != 54)
				{
					posx++;
					Console::Beep(200, 25);
					Console::Beep(240, 25);
					virandoD = true;

				}
				else if (tecla.Key == ConsoleKey::UpArrow && velocidade < 3) { velocidade++; }
				else if (tecla.Key == ConsoleKey::DownArrow && velocidade > 1) { velocidade--; }
				else if (tecla.Key == ConsoleKey::Spacebar && !tiro)
				{
					tiro = true;
					tiroSom->Iniciar();
					tirox = posx + 1;
					tiroy = posy - 1;
				}

			}

			//Funcionalidades do Barco(spawn, velicidade e colisão com o tiro)    
			for (int i = 0; i < barcojogo; i++) {
				if (!Barco[i].nojogo)
				{
					//define a direção a qual o inimigo ira se movimentar
					Barco[i].direção = rand() % 2;
					//gera um x aleatório ao inimigo e coloca sua posição no Y = 2
					Barco[i].inimigox = rand() % 43 + 7;
					Barco[i].inimigoy = 2;
					//Caso o x do inimigo seja o mesmo x de uma ilha, um novo x será gerado ao inimigo
					if (obstaculo)
					{
						for (;(ilhay + 2 >= Barco[i].inimigoy) && ((ilhay - limite) <= Barco[i].inimigoy) && (Barco[i].inimigox <= 37 && Barco[i].inimigox >= 18);)
						{
							Barco[i].inimigox = rand() % 43 + 7;
						}
					}
					if (obstaculo2)
					{
						for (;(ilhay + 2 >= Barco[i].inimigoy) && ((ilhay - limite) <= Barco[i].inimigoy) && ((Barco[i].inimigox <= 22 || Barco[i].inimigox >= 37));)
						{
							Barco[i].inimigox = rand() % 43 + 7;
						}
					}
					//Evita que o inimigo apreça dentro da ponte
					if (ponte)
					{
						Barco[i].inimigoy -= 8;
					}
					Barco[i].nojogo = true;
				}
				else if (Barco[i].inimigoy <= 36 && Barco[i].nojogo == true)
				{

					//movimentação para a direita
					if ((Barco[i].direção % 2) && Barco[i].inimigox > 7 && Barco[i].inimigox < 52 && posy - Barco[i].inimigoy <= 12)
					{
						//movimentação sem ilhas
						if (!(obstaculo || obstaculo2))
						{
							Barco[i].inimigox++;
							if (Barco[i].inimigox == 8 || Barco[i].inimigox == 51)
								Barco[i].direção++;
						}
						//movimentação com ilhas no meio do mapa
						else if (obstaculo && ilhay >= Barco[i].inimigoy && (limite - ilhay) <= Barco[i].inimigoy && (Barco[i].inimigox <= 19 || Barco[i].inimigox >= 41))
						{
							Barco[i].inimigox++;
							if (Barco[i].inimigox == 8 || Barco[i].inimigox == 51 || Barco[i].inimigox == 22 || Barco[i].inimigox == 40)
								Barco[i].direção++;
						}
						//movimentação com ilhas nas bordas
						else if (obstaculo2 && ilhay >= Barco[i].inimigoy && (limite - ilhay) <= Barco[i].inimigoy && Barco[i].inimigox >= 23 && Barco[i].inimigox <= 35)
						{
							Barco[i].inimigox++;
							if (Barco[i].inimigox == 23 || Barco[i].inimigox == 36)
								Barco[i].direção++;
						}

					}

					//movimentação para a esquerda
					if (!(Barco[i].direção % 2) && Barco[i].inimigox > 7 && Barco[i].inimigox < 52 && posy - Barco[i].inimigoy <= 12)
					{
						//movimentação sem ilhas
						if (!(obstaculo || obstaculo2))
						{
							Barco[i].inimigox--;
							if (Barco[i].inimigox == 8 || Barco[i].inimigox == 51)
								Barco[i].direção++;
						}
						//movimentação com ilhas no meio do mapa
						else if (obstaculo && ilhay >= Barco[i].inimigoy && (limite - ilhay) <= Barco[i].inimigoy && (Barco[i].inimigox <= 21 || Barco[i].inimigox >= 41))
						{
							Barco[i].inimigox--;
							if (Barco[i].inimigox == 8 || Barco[i].inimigox == 51 || Barco[i].inimigox == 22 || Barco[i].inimigox == 40)
								Barco[i].direção++;
						}
						//movimentação com ilhas nas bordas do mapa
						else if (obstaculo2 && ilhay >= Barco[i].inimigoy && (limite - ilhay) <= Barco[i].inimigoy && Barco[i].inimigox >= 23 && Barco[i].inimigox <= 35)
						{
							Barco[i].inimigox--;
							if (Barco[i].inimigox == 23 || Barco[i].inimigox == 36)
								Barco[i].direção++;
						}
					}


					if (Barco[i].inimigoy > 1 && Barco[i].inimigoy - 1 < 36) {
						ConsoleHelper::ImprimirASCIIExtended(Barco[i].inimigox, Barco[i].inimigoy - 1, ConsoleColor::Blue, ConsoleColor::DarkRed, " ÜÜÜ ");
					}
					if (Barco[i].inimigoy > 0 && Barco[i].inimigoy < 36) {
						ConsoleHelper::ImprimirASCIIExtended(Barco[i].inimigox, Barco[i].inimigoy, ConsoleColor::Blue, ConsoleColor::Black, "ßÛÛÛÛ");
					}
					Barco[i].inimigoy += velocidade;

					//checagem de colisão entre barco e nave
					if (Barco[i].inimigoy >= posy + 2 && Barco[i].inimigox - 1 <= posx && Barco[i].inimigox + 4 >= posx) {
						destruido = true;
					}
				}
				else { Barco[i].nojogo = false; }

				//checagem do tiro após a movimentação do inimigo
				if (tiro == true && (tiroy <= Barco[i].inimigoy && tiroy >= Barco[i].inimigoy - 3) && (tirox >= Barco[i].inimigox && (Barco[i].inimigox + 4) >= tirox))
				{
					score += 30;
					Barco[i].nojogo = false;
					tiro = false;
					explosao = true;
				}
			}

			//Funcionalidades do Helicoptero
			for (int i = 0; i < helijogo; i++) {
				if (!Heli[i].nojogo)
				{
					//define a direção a qual o inimigo ira se movimentar
					Heli[i].direção = rand() % 2;
					//gera um x aleatório ao inimigo e coloca sua posição no Y = 2
					Heli[i].inimigox = rand() % 43 + 7;
					Heli[i].inimigoy = 2;
					//Caso o x do inimigo seja o mesmo x de uma ilha, um novo x será gerado ao inimigo
					if (obstaculo)
					{
						for (;(ilhay + 2 >= Heli[i].inimigoy) && ((ilhay - limite) <= Heli[i].inimigoy) && (Heli[i].inimigox <= 39 && Heli[i].inimigox >= 18);)
						{
							Heli[i].inimigox = rand() % 43 + 7;
						}
					}
					if (obstaculo2)
					{
						for (;(ilhay + 2 >= Heli[i].inimigoy) && ((ilhay - limite) <= Heli[i].inimigoy) && ((Heli[i].inimigox <= 22 || Heli[i].inimigox >= 37));)
						{
							Heli[i].inimigox = rand() % 43 + 7;
						}
					}
					//Evita que o inimigo apreça dentro da ponte
					if (ponte)
					{
						Heli[i].inimigoy -= 8;
					}
					Heli[i].nojogo = true;
				}
				else if (Heli[i].inimigoy <= 36 && Heli[i].nojogo == true)
				{

					//movimentação para a direita
					if ((Heli[i].direção % 2) && Heli[i].inimigox > 7 && Heli[i].inimigox < 52 && posy - Heli[i].inimigoy <= 12)
					{
						//movimentação sem ilhas
						if (!(obstaculo || obstaculo2))
						{
							Heli[i].inimigox++;
							if (Heli[i].inimigox == 8 || Heli[i].inimigox == 51)
								Heli[i].direção++;
						}
						//movimentação com ilhas no meio do mapa
						else if (obstaculo && ilhay >= Heli[i].inimigoy && (limite - ilhay) <= Heli[i].inimigoy && (Heli[i].inimigox <= 19 || Heli[i].inimigox >= 41))
						{
							Heli[i].inimigox++;
							if (Heli[i].inimigox == 8 || Heli[i].inimigox == 51 || Heli[i].inimigox == 22 || Heli[i].inimigox == 40)
								Barco[i].direção++;
						}
						//movimentação com ilhas nas bordas
						else if (obstaculo2 && ilhay >= Heli[i].inimigoy && (limite - ilhay) <= Heli[i].inimigoy && Heli[i].inimigox >= 23 && Heli[i].inimigox <= 35)
						{
							Heli[i].inimigox++;
							if (Heli[i].inimigox == 23 || Heli[i].inimigox == 36)
								Heli[i].direção++;
						}

					}

					//movimentação para a esquerda
					if (!(Heli[i].direção % 2) && Heli[i].inimigox > 7 && Heli[i].inimigox < 52 && posy - Heli[i].inimigoy <= 12)
					{
						//movimentação sem ilhas
						if (!(obstaculo || obstaculo2))
						{
							Heli[i].inimigox--;
							if (Heli[i].inimigox == 8 || Heli[i].inimigox == 51)
								Heli[i].direção++;
						}
						//movimentação com ilhas no meio do mapa
						else if (obstaculo && ilhay >= Heli[i].inimigoy && (limite - ilhay) <= Heli[i].inimigoy && (Heli[i].inimigox <= 21 || Heli[i].inimigox >= 41))
						{
							Heli[i].inimigox--;
							if (Heli[i].inimigox == 8 || Heli[i].inimigox == 51 || Heli[i].inimigox == 22 || Heli[i].inimigox == 40)
								Heli[i].direção++;
						}
						//movimentação com ilhas nas bordas do mapa
						else if (obstaculo2 && ilhay >= Heli[i].inimigoy && (limite - ilhay) <= Heli[i].inimigoy && Heli[i].inimigox >= 23 && Heli[i].inimigox <= 35)
						{
							Heli[i].inimigox--;
							if (Heli[i].inimigox == 23 || Heli[i].inimigox == 36)
								Heli[i].direção++;
						}
					}
					if (Heli[i].inimigoy > 2 && Heli[i].inimigoy - 2 < 36) {
						ConsoleHelper::ImprimirASCIIExtended(Heli[i].inimigox, Heli[i].inimigoy - 2, ConsoleColor::Blue, ConsoleColor::DarkRed, "ÍËÍ ");
					}
					if (Heli[i].inimigoy > 1 && Heli[i].inimigoy - 1 < 36) {
						ConsoleHelper::ImprimirASCIIExtended(Heli[i].inimigox, Heli[i].inimigoy - 1, ConsoleColor::Blue, ConsoleColor::DarkBlue, "ÛÛßß");
					}
					if (Heli[i].inimigoy > 0 && Heli[i].inimigoy < 36) {
						ConsoleHelper::ImprimirASCIIExtended(Heli[i].inimigox, Heli[i].inimigoy, ConsoleColor::Blue, ConsoleColor::DarkGreen, "ßß  ");
					}
					Heli[i].inimigoy += velocidade;

					//checagem de colisão entre barco e nave
					if (Heli[i].inimigoy >= posy + 2 && Heli[i].inimigox - 1 <= posx && Heli[i].inimigox + 4 >= posx) {
						destruido = true;
					}

				}
				else { Heli[i].nojogo = false; }

				//checagem do tiro após a movimentação do inimigo
				if (tiro == true && (tiroy <= Heli[i].inimigoy && tiroy >= Heli[i].inimigoy - 3) && (tirox >= Heli[i].inimigox && (Heli[i].inimigox + 5) >= tirox))
				{
					Console::Beep(250, 55);
					score += 30;
					Heli[i].nojogo = false;
					tiro = false;
					explosao = true;
				}
			}

			//Funcionalidades do tiro.
			if (tiro == true && tiroy > 3)
			{
				tiroy -= 3;
				ConsoleHelper::ImprimirASCIIExtended(tirox, tiroy, ConsoleColor::Blue, ConsoleColor::DarkYellow, "Ý");
			}
			else if (tiro == 1) { tiro = false; }


			///checagem de colisão após a movimentação do tiro
			//Barco
			for (int i = 0; i < 3; i++) {
				if (Barco[i].nojogo && tiro && (tiroy <= Barco[i].inimigoy && tiroy >= Barco[i].inimigoy - 3) && (tirox >= Barco[i].inimigox && ((Barco[i].inimigox + 4) >= tirox)))
				{
					score += 30;
					Barco[i].nojogo = false;
					tiro = false;
					explosao = true;
				}
			}
			
			//Helicoptero
			for (int i = 0; i < 3; i++) {
				if (Heli[i].nojogo && tiro && (tiroy <= Heli[i].inimigoy && tiroy >= Heli[i].inimigoy - 3) && (tirox >= Heli[i].inimigox && ((Heli[i].inimigox + 5) >= tirox)))
				{
					score += 30;
					Heli[i].nojogo = false;
					tiro = false;
					explosao = true;
				}
			}

			//Ilhas no meio do mapa
			if ((tempo % 7 == 0) && !obstaculo2 && !obstaculo) { obstaculo = true; limite = rand() % 20 + 30; }
			if (obstaculo)
			{				
				if (ilhay > 0 && ilhay <= 36) {
					ConsoleHelper::ImprimirASCIIExtended(23, ilhay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "   ÛÛÛÛÛÛÛÛÛÛÛ"); 
				}
				if (ilhay > 1 && ilhay <= 36) {
					ConsoleHelper::ImprimirASCIIExtended(23, ilhay - 1, ConsoleColor::Blue, ConsoleColor::DarkGreen, "  ÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				}				
				if (ilhay > 2)
				{
					for (int i = 2; limite > i; i++)
					{				
						if (ilhay > i && ilhay - i <= 36) { 
							ConsoleHelper::ImprimirASCIIExtended(23, ilhay - i, ConsoleColor::Blue, ConsoleColor::DarkGreen, " ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ"); 
						}
						else if (ilhay - limite > 36) {
							obstaculo = false; 
							ilhay = 1;
						}
					}			
				} 
				ilhay += velocidade;
				//Checagem de colisão entre a nave e as ilhas centrais
				if ((ilhay >= posy) && ((ilhay - limite) <= posy) && (posx <= 38 && posx >= 21)) {
					destruido = true;
				}

				//Checagem de colisão entre o tiro e as ilhas centrais
				if ((ilhay >= tiroy) && ((ilhay - limite) <= tiroy) && (tirox <= 38 && tirox >= 21)) {
					tiro = false;
				}
			}		

			//Ilhas nas bordas do mapa
			if ((tempo % 5 == 0) && !obstaculo && !obstaculo2) { 
				obstaculo2 = true; 
				limite = rand() % 20 + 30; 
			}
			if (obstaculo2)
			{

				if (ilhay > 0 && ilhay <= 36)
				{
					ConsoleHelper::ImprimirASCIIExtended(7, ilhay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "ÛÛÛÛÛÛÛÛÛÛÛÛÛ");
					ConsoleHelper::ImprimirASCIIExtended(41, ilhay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "   ÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				}
				if (ilhay > 1 && ilhay <= 36)
				{
					ConsoleHelper::ImprimirASCIIExtended(7, ilhay - 1, ConsoleColor::Blue, ConsoleColor::DarkGreen, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
					ConsoleHelper::ImprimirASCIIExtended(41, ilhay - 1, ConsoleColor::Blue, ConsoleColor::DarkGreen, "  ÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				}
				if (ilhay > 2)
				{
					for (int i = 2; limite > i; i++)
					{

						if (ilhay > i && ilhay - i <= 36) 
						{
							ConsoleHelper::ImprimirASCIIExtended(7, ilhay - i, ConsoleColor::Blue, ConsoleColor::DarkGreen, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
							ConsoleHelper::ImprimirASCIIExtended(41, ilhay - i, ConsoleColor::Blue, ConsoleColor::DarkGreen, " ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
						}
						else if (ilhay - limite > 36) {
							obstaculo2 = false; 
							ilhay = 1; 
						}
					}

				}
				//Criação da ponte
				if (ilhay >= 7 && ilhay <=10) { ponte = true; }
				if (ponte)
				{
					if (ilhay > 10 && ilhay - 11 < 36)
						ConsoleHelper::ImprimirASCIIExtended(21, ilhay - 10, ConsoleColor::Blue, ConsoleColor::DarkRed, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
					if (ilhay > 11 && ilhay - 12 < 36)
						ConsoleHelper::ImprimirASCIIExtended(21, ilhay - 11, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
					if (ilhay > 12 && ilhay - 13 < 36)
						ConsoleHelper::ImprimirASCIIExtended(21, ilhay - 12, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
					if (ilhay > 13 && ilhay - 14 < 36)
						ConsoleHelper::ImprimirASCIIExtended(21, ilhay - 13, ConsoleColor::Blue, ConsoleColor::DarkYellow, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
					if (ilhay > 14 && ilhay - 15 < 36)
						ConsoleHelper::ImprimirASCIIExtended(21, ilhay - 14, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
					if (ilhay > 15 && ilhay - 16 < 36)
						ConsoleHelper::ImprimirASCIIExtended(21, ilhay - 15, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
					if (ilhay > 16 && ilhay - 17 < 36)
						ConsoleHelper::ImprimirASCIIExtended(21, ilhay - 16, ConsoleColor::Blue, ConsoleColor::DarkRed, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");

					if (ilhay - 10 >= posy) {
						destruido = true;
					}

				}
				ilhay += velocidade;

				//Checagem de colisão entre a nave e as ilhas das bordas
				if ((ilhay >= posy) && ((ilhay - limite) <= posy) && ((posx >= 41 && posx <= 56) || (posx >= 7 && posx <= 21))) {
					destruido = true;
				}

				//Checagem de colisão entre o tiro e as ilhs nas bordas
				if ((ilhay >= tiroy) && ((ilhay - limite) <= tiroy) && ((tirox >= 41 && tirox <= 56) || (tirox >= 7 && tirox <= 21))) {
					tiro = false;
				}

					
				//Checagem da colisão do tiro com a ponte
				if (tiro && ponte && tirox >= 22 && tirox <= 43 && tiroy <= ilhay - 11 && tiroy >= ilhay - 17)
				{
					score += 500;
					explosaob = true;
					explosao = true;
					ponte = false;
					tiro = false;

				}

			}
			
			//Combustivel	    
			if (combustivel == 0) { 
				destruido = true;		
			}
			for (int i = 0; i < combjogo; i++) {
				if (!Combus[i].comb)
				{
					Combus[i].comb = true;
					Combus[i].combx = rand() % 43 + 7;
					Combus[i].comby = 6;
					//Caso o x do combustivel seja o mesmo de uma ilha, um novo x é gerado ao combustivel
					if (obstaculo)
					{
						for (;(ilhay >= Combus[i].comby) && ((ilhay - limite) <= Combus[i].comby) && (Combus[i].combx <= 37 && Combus[i].combx >= 22);)
						{
							Combus[i].combx = rand() % 43 + 7;
						}
					}
					if (obstaculo2)
					{
						for (;(ilhay >= Combus[i].comby) && ((ilhay - limite) <= Combus[i].comby) && ((Combus[i].combx >= 40 && Combus[i].combx <= 56) || (Combus[i].combx >= 7 && Combus[i].combx <= 21));)
						{
							Combus[i].combx = rand() % 43 + 7;
						}
					}
					//Evita que o combustivel apareça dentro da ponte
					if (ponte)
					{
						Combus[i].comby -= 16;
					}
				}
				if (Combus[i].comb && Combus[i].comby <= 40)
				{
					//Abastece a nave
					if (combustivel < 10 && Combus[i].comby >= posy && Combus[i].comby - 5 <= posy && Combus[i].combx - 1 <= posx && Combus[i].combx + 3 >= posx)
					{
						velocidade = 1;
						AbastecerSom->Iniciar();
						combustivel++;

					}

					//desenha o combustivel conforme sua altura
					if (Combus[i].comby > 6 && Combus[i].comby - 6 < 36) { ConsoleHelper::ImprimirASCIIExtended(Combus[i].combx, Combus[i].comby - 5, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÜÛÜ"); }
					if (Combus[i].comby > 5 && Combus[i].comby - 5 < 36) { ConsoleHelper::ImprimirASCIIExtended(Combus[i].combx, Combus[i].comby - 4, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÛFÛ"); }
					if (Combus[i].comby > 4 && Combus[i].comby - 4 < 36) { ConsoleHelper::ImprimirASCIIExtended(Combus[i].combx, Combus[i].comby - 3, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÛUÛ"); }
					if (Combus[i].comby > 3 && Combus[i].comby - 3 < 36) { ConsoleHelper::ImprimirASCIIExtended(Combus[i].combx, Combus[i].comby - 2, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÛEÛ"); }
					if (Combus[i].comby > 2 && Combus[i].comby - 2 < 36) { ConsoleHelper::ImprimirASCIIExtended(Combus[i].combx, Combus[i].comby - 1, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÛLÛ"); }
					if (Combus[i].comby > 1 && Combus[i].comby - 1 < 36) { ConsoleHelper::ImprimirASCIIExtended(Combus[i].combx, Combus[i].comby, ConsoleColor::Blue, ConsoleColor::DarkGray, "ßßß"); }
					Combus[i].comby += velocidade;

					//Colisão entre o tiro e o combustivel
					if (Combus[i].comby >= tiroy && Combus[i].comby - 5 <= tiroy && Combus[i].combx - 1 <= tirox && Combus[i].combx + 3 >= tirox && tiro)
					{
						score += 80;
						tiro = false;
						Combus[i].comb = false;
						explosao = true;
					}

				}
				else { Combus[i].comb = false; }
			}

			///Cria a nave, atualizando sua posição a cada frame.
			if (!virandoE && !virandoD)
			{
				ConsoleHelper::ImprimirASCIIExtended(posx, posy, ConsoleColor::Blue, ConsoleColor::DarkYellow, " Û ");
				ConsoleHelper::ImprimirASCIIExtended(posx, posy + 1, ConsoleColor::Blue, ConsoleColor::DarkYellow, "ÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(posx, posy + 2, ConsoleColor::Blue, ConsoleColor::DarkYellow, " Û ");
				ConsoleHelper::ImprimirASCIIExtended(posx, posy + 3, ConsoleColor::Blue, ConsoleColor::DarkYellow, "Û Û");
			}
			//Animação para a esquerda
			else if (virandoE && !virandoD)
			{
				ConsoleHelper::ImprimirASCIIExtended(posx, posy, ConsoleColor::Blue, ConsoleColor::DarkYellow, " ÛÜ");
				ConsoleHelper::ImprimirASCIIExtended(posx, posy + 1, ConsoleColor::Blue, ConsoleColor::DarkYellow, "ÛÛß");
				ConsoleHelper::ImprimirASCIIExtended(posx, posy + 2, ConsoleColor::Blue, ConsoleColor::DarkYellow, " ÛÜ");
				ConsoleHelper::ImprimirASCIIExtended(posx, posy + 3, ConsoleColor::Blue, ConsoleColor::DarkYellow, "Û ß");
				posx--;
				virandoE = false;
			}
			//Animação para a direita
			else if (virandoD && !virandoE)
			{
				ConsoleHelper::ImprimirASCIIExtended(posx, posy, ConsoleColor::Blue, ConsoleColor::DarkYellow, "ÜÛ ");
				ConsoleHelper::ImprimirASCIIExtended(posx, posy + 1, ConsoleColor::Blue, ConsoleColor::DarkYellow, "ßÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(posx, posy + 2, ConsoleColor::Blue, ConsoleColor::DarkYellow, "ÜÛ ");
				ConsoleHelper::ImprimirASCIIExtended(posx, posy + 3, ConsoleColor::Blue, ConsoleColor::DarkYellow, "ß Û");
				posx++;
				virandoD = false;
			}

			//Avião
			if (tempo % 5 && !Aviao.nojogo) {
				Aviao.nojogo = true;
				Aviao.inimigoy = 2;
				Aviao.direção = rand() % 2;
				if (Aviao.direção % 2) {
					Aviao.inimigox = 1;
				}
				else {
					Aviao.inimigox = 62;
				}
			}
			else if (Aviao.nojogo && Aviao.inimigoy <= 36) {
				if (Aviao.direção % 2) {
					ConsoleHelper::ImprimirASCIIExtended(Aviao.inimigox, Aviao.inimigoy, ConsoleColor::Blue, ConsoleColor::DarkGray, "Ü   ");
					ConsoleHelper::ImprimirASCIIExtended(Aviao.inimigox, Aviao.inimigoy + 1, ConsoleColor::Blue, ConsoleColor::DarkGray, "ßÛÛß");
					Aviao.inimigox++;
				}
				else {
					ConsoleHelper::ImprimirASCIIExtended(Aviao.inimigox, Aviao.inimigoy, ConsoleColor::Blue, ConsoleColor::DarkGray, "   Ü");
					ConsoleHelper::ImprimirASCIIExtended(Aviao.inimigox, Aviao.inimigoy + 1, ConsoleColor::Blue, ConsoleColor::DarkGray, "ßÛÛß");
					Aviao.inimigox--;
				}
				Aviao.inimigoy += velocidade;

				if (Aviao.nojogo && tiro && (tiroy <= Aviao.inimigoy && tiroy >= Aviao.inimigoy - 3) && (tirox >= Aviao.inimigox && ((Aviao.inimigox + 4) >= tirox)))
				{
					score += 30;
					Aviao.nojogo = false;
					tiro = false;
					explosao = true;
				}

				//checagem de colisão entre avião e nave
				if (Aviao.inimigoy >= posy && Aviao.inimigox - 1 <= posx && Aviao.inimigox + 4 >= posx) {
					destruido = true;
				}

			}
			else {
				Aviao.nojogo = false;
			}

			//Sprite da explosão
			if (explosao)
			{
				DestruicaoSom->Iniciar();
				ConsoleHelper::ImprimirASCIIExtended(tirox - 3, tiroy - 2, ConsoleColor::Blue, ConsoleColor::Red, "     °");
				ConsoleHelper::ImprimirASCIIExtended(tirox - 3, tiroy - 1, ConsoleColor::Blue, ConsoleColor::Red, " ° °  ");
				ConsoleHelper::ImprimirASCIIExtended(tirox - 3, tiroy, ConsoleColor::Blue, ConsoleColor::Red, "° ° ° ");
				ConsoleHelper::ImprimirASCIIExtended(tirox - 3, tiroy + 1, ConsoleColor::Blue, ConsoleColor::Red, " ° °  ");
				ConsoleHelper::ImprimirASCIIExtended(tirox - 3, tiroy + 2, ConsoleColor::Blue, ConsoleColor::Red, "° ° ° ");
				ConsoleHelper::ImprimirASCIIExtended(tirox - 3, tiroy + 3, ConsoleColor::Blue, ConsoleColor::Red, " °    ");
  				explosao = false;
			}

			//Destruição da nave
			if (destruido) {
				DestruicaoSom->Iniciar();
				ConsoleHelper::ImprimirASCIIExtended(posx - 3, posy - 2, ConsoleColor::Blue, ConsoleColor::Red, "     °");
				ConsoleHelper::ImprimirASCIIExtended(posx - 3, posy - 1, ConsoleColor::Blue, ConsoleColor::Red, " ° °  ");
				ConsoleHelper::ImprimirASCIIExtended(posx - 3, posy, ConsoleColor::Blue, ConsoleColor::Red, "° ° ° ");
				ConsoleHelper::ImprimirASCIIExtended(posx - 3, posy + 1, ConsoleColor::Blue, ConsoleColor::Red, " ° °  ");
				ConsoleHelper::ImprimirASCIIExtended(posx - 3, posy + 2, ConsoleColor::Blue, ConsoleColor::Red, "° ° ° ");
				ConsoleHelper::ImprimirASCIIExtended(posx - 3, posy + 3, ConsoleColor::Blue, ConsoleColor::Red, " °    ");
				Thread::Sleep(1000);
				posx = 29;
				vida--;
				velocidade = 2;
				frames = 0;
				tempo = 0;
				ilhay = 1;
				combustivel = 10;
				barcojogo = 0;
				helijogo = 0;
				combjogo = 0;
				obstaculo = false;
				obstaculo2 = false;
				ponte = false;
				tiro = false;
				Aviao.nojogo = false;
				for (int i = 0; i < 3; i++) {
					Barco[i].nojogo = false;
				}
				for (int i = 0; i < 3; i++) {
					Combus[i].comb = false;
				}
				destruido = false;
			}

			//GameOver
			if (vida <= 0) {
				ESTADO_JOGO = GAMEOVER;
			}

			//HUD
			if (true)
			{

				Console::BackgroundColor = ConsoleColor::DarkGray;
				Console::ForegroundColor = ConsoleColor::Yellow;
				Console::SetCursorPosition(0, 36);
				Console::Write("                                                                ");
				//HUD com variaveis.

				//entre 0 e 9
				if (score < 10)
				{
					Console::SetCursorPosition(0, 37);
					Console::Write("                         SCORE:");
					Console::SetCursorPosition(31, 37);
					Console::Write(score);
					Console::SetCursorPosition(32, 37);
					Console::Write("                                ");
				}
				//entre 10 e 99
				else if (score >= 10 && score < 100)
				{
					Console::SetCursorPosition(0, 37);
					Console::Write("                         SCORE:");
					Console::SetCursorPosition(31, 37);
					Console::Write(score);
					Console::SetCursorPosition(33, 37);
					Console::Write("                                         ");
				}
				//entre 100 e 999
				else if (score >= 100 && score < 1000)
				{
					Console::SetCursorPosition(0, 37);
					Console::Write("                         score:");
					Console::SetCursorPosition(31, 37);
					Console::Write(score);
					Console::SetCursorPosition(34, 37);
					Console::Write("                                       ");
				}
				//entre 1.000 e 9.999
				else if (score >= 1000 && score < 10000)
				{
					Console::SetCursorPosition(0, 37);
					Console::Write("                         SCORE:");
					Console::SetCursorPosition(31, 37);
					Console::Write(score);
					Console::SetCursorPosition(35, 37);
					Console::Write("                                      ");
				}
				//entre 10.000 e 99.999
				else if (score >= 10000 && score < 100000)
				{
					Console::SetCursorPosition(0, 37);
					Console::Write("                         SCORE:");
					Console::SetCursorPosition(31, 37);
					Console::Write(score);
					Console::SetCursorPosition(36, 37);
					Console::Write("                                     ");
				}
				//entre 100.000 e 1.000.000
				else if (score >= 100000 && score < 1000000)
				{
					Console::SetCursorPosition(0, 37);
					Console::Write("                         SCORE:");
					Console::SetCursorPosition(31, 37);
					Console::Write(score);
					Console::SetCursorPosition(37, 37);
					Console::Write("                                    ");
				}
				//acima de 1.000.000
				else
				{
					Console::SetCursorPosition(0, 37);
					Console::Write("                         SCORE:");
					Console::SetCursorPosition(31, 37);
					Console::Write(score);
					Console::SetCursorPosition(38, 37);
					Console::Write("                                   ");
				}

				//HUD de combustivel
				ConsoleHelper::ImprimirASCIIExtended(0, 38, ConsoleColor::DarkGray, ConsoleColor::Black, "                                                                ");
				ConsoleHelper::ImprimirASCIIExtended(0, 39, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ÉÍÍÍÍÍÍÍÍÍÍÍ»                         ");
				if (combustivel == 10) { ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º          ³º                         "); }
				else if (combustivel == 9) { ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º         ³ º                         "); }
 		    	else if (combustivel == 8) { ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º        ³  º                         "); }
				else if (combustivel == 7) { ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º       ³   º                         "); }
				else if (combustivel == 6) { ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º      ³    º                         "); }
				else if (combustivel == 5) { ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º     ³     º                         "); }
				else if (combustivel == 4) { ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º    ³      º                         "); }
				else if (combustivel == 3) { ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º   ³       º                         "); }
				else if (combustivel == 2) { ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º  ³        º                         "); }
				else if (combustivel == 1) { ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º ³         º                         "); }
				else if (combustivel == 0) { ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º³          º                         "); }
				if (vida == 3) { ConsoleHelper::ImprimirASCIIExtended(0, 41, ConsoleColor::DarkGray, ConsoleColor::Black, "                       3  ºE    «    Fº                         "); }
				else if (vida == 2) { ConsoleHelper::ImprimirASCIIExtended(0, 41, ConsoleColor::DarkGray, ConsoleColor::Black, "                       2  ºE    «    Fº                         "); }
				else if (vida == 1) { ConsoleHelper::ImprimirASCIIExtended(0, 41, ConsoleColor::DarkGray, ConsoleColor::Black, "                       1  ºE    «    Fº                         "); }
				else if (vida == 0) { ConsoleHelper::ImprimirASCIIExtended(0, 41, ConsoleColor::DarkGray, ConsoleColor::Black, "                         ºE    «    Fº                          "); }
				ConsoleHelper::ImprimirASCIIExtended(0, 42, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ÈÍÍÍÍÍÍÍÍÍÍÍ¼                         ");
				ConsoleHelper::ImprimirASCIIExtended(0, 43, ConsoleColor::DarkGray, ConsoleColor::Yellow, "                          Ricardovision                         ");
			}

			Console::BackgroundColor = ConsoleColor::Blue;
			if (explosaob)
			{
				Console::BackgroundColor = ConsoleColor::DarkRed;
				explosaob = false;
			}
			break;

		case GAMEOVER://Tela de gameover
			Console::SetWindowSize(128, 48);
			Console::SetBufferSize(128, 48);
			Console::Clear();

			ConsoleHelper::ImprimirASCIIExtended(32, 14, ConsoleColor::Black, ConsoleColor::White, " _____   ___  ___  ___ _____   _____  _   _ ___________ ");
			ConsoleHelper::ImprimirASCIIExtended(32, 15, ConsoleColor::Black, ConsoleColor::White, "|  __ \\ / _ \\ |  \\/  ||  ___| |  _  || | | |  ___| ___ \\ ");
			ConsoleHelper::ImprimirASCIIExtended(32, 16, ConsoleColor::Black, ConsoleColor::White, "| |  \\// /_\\ \\| .  . || |__   | | | || | | | |__ | |_/ /");
			ConsoleHelper::ImprimirASCIIExtended(32, 17, ConsoleColor::Black, ConsoleColor::White, "| | __ |  _  || |\\/| ||  __|  | | | || | | |  __||    / ");
			ConsoleHelper::ImprimirASCIIExtended(32, 18, ConsoleColor::Black, ConsoleColor::White, "| |_\\ \\| | | || |  | || |___  \\ \\_/ /\\ \\_/ / |___| |\\ \\ ");
			ConsoleHelper::ImprimirASCIIExtended(32, 19, ConsoleColor::Black, ConsoleColor::White, " \\____/\\_| |_/\\_|  |_/\\____/   \\___/  \\___/\\____/\\_| \\_|");

			ConsoleHelper::ImprimirASCIIExtended(44, 27, ConsoleColor::Black, ConsoleColor::White, "PRESSIONE ENTER PARA JOGAR NOVAMENTE");
			ConsoleHelper::ImprimirASCIIExtended(52, 28, ConsoleColor::Black, ConsoleColor::White, "OU ESC PARA SAIR.");

			//continuar ou sair do jogo
			if (Console::KeyAvailable)
			{
				tecla = Console::ReadKey(true);
				//continuar no jogo
				if (tecla.Key == ConsoleKey::Enter)
				{
					ESTADO_JOGO = MENU;

					Console::Clear();
				}
				//sair do jogo
				else if (tecla.Key == ConsoleKey::Escape) { sair = true; }
			}
		}
	}
	return 0;
}