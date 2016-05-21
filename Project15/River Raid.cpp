#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ConsoleHelper.h"
#include "MediaPlayer.h"

using namespace System;
using namespace Threading;

struct Barco {

};

int main()
{

	srand(time(NULL));


	Console::SetWindowSize(128, 48);
	Console::SetBufferSize(128, 48);
	Console::CursorVisible = false;
	ConsoleKeyInfo tecla;

	//velocidades do jogo de 1 a 3
	int velocidade = 1;
	//combustivel
	int combustivel = 10;
	//temporizador
	int frames = 0;
	int tempo = 1;
	//score
	int score = 0;

	//Coordenadas do jogador
	int posx = 20;
	int posy = 31;

	//Coordenadas do Inimigo
	int inimigox;
	int inimigoy = 2;
	int direção;

    //Coordenadas do tiro
	int tiroy;
	int tirox;

	//Coordenadas do combustivel
	int comby;
	int combx;

	//variaveis para as ilhas
	int ilhay = 1;
	int limite;
	int mapay = 0;

	//inimigo no jogo
	bool inimigo = false;
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
	//combustivel
	bool comb = false;
	//sprite da explosão
	bool explosao = false;
	bool explosaob = false;
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
			velocidade = 1;
			frames = 0;
			tempo = 0;
			ilhay = 1;
			combustivel = 10;
			obstaculo = false;
			obstaculo2 = false;
			comb = false;
			tiro = false;
			inimigo = false;
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
			if (frames >= 20)
			{
				frames = 0;
				tempo++;
				combustivel--;
			}

			Console::SetWindowSize(64, 44);
			Console::SetBufferSize(64, 44);
			Console::Clear();

			mapay = 0;//Variavel para "descer" as bordas do mapa.

					  //Cria as bordas do mapa.
			while (mapay <= 35)
			{
				ConsoleHelper::ImprimirASCIIExtended(0, mapay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "Û");
				ConsoleHelper::ImprimirASCIIExtended(1, mapay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "Û");
				ConsoleHelper::ImprimirASCIIExtended(2, mapay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "Û");
				ConsoleHelper::ImprimirASCIIExtended(3, mapay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "Û");
				ConsoleHelper::ImprimirASCIIExtended(4, mapay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "Û");
				ConsoleHelper::ImprimirASCIIExtended(5, mapay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "Û");
				ConsoleHelper::ImprimirASCIIExtended(6, mapay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "Û");


				ConsoleHelper::ImprimirASCIIExtended(57, mapay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "Û");
				ConsoleHelper::ImprimirASCIIExtended(58, mapay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "Û");
				ConsoleHelper::ImprimirASCIIExtended(59, mapay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "Û");
				ConsoleHelper::ImprimirASCIIExtended(60, mapay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "Û");
				ConsoleHelper::ImprimirASCIIExtended(61, mapay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "Û");
				ConsoleHelper::ImprimirASCIIExtended(62, mapay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "Û");
				ConsoleHelper::ImprimirASCIIExtended(63, mapay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "Û");

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
					Console::Beep(1000, 25);
					Console::Beep(2000, 25);
					tirox = posx + 1;
					tiroy = posy - 1;
				}

			}


			//Funcionalidades do inimigo. (Spawn, velocidade e Respawn)
			if (inimigo == false)
			{
				//define a direção a qual o inimigo ira se movimentar
				direção = rand() % 2;
				//gera um x aleatório ao inimigo e coloca sua posição no Y = 2
				inimigox = rand() % 43 + 7;
				inimigoy = 2;
				//Caso o x do inimigo seja o mesmo x de uma ilha, um novo x será gerado ao inimigo
				if (obstaculo)
				{
					for (;(ilhay >= inimigoy + 4) && ((ilhay - limite) <= inimigoy) && (inimigox <= 37 && inimigox >= 19);)
					{
						inimigox = rand() % 43 + 7;
					}
				}
				if (obstaculo2)
				{
					for (;(ilhay >= inimigoy + 4) && ((ilhay - limite) <= inimigoy) && ((inimigox >= 36 && inimigox <= 56) || (inimigox >= 7 && inimigox <= 21));)
					{
						inimigox = rand() % 43 + 7;
					}
				}				
				//Evita que o inimigo apreça dentro da ponte
				if (ponte)
				{
					inimigoy -= 8;
				}
				inimigo = true;
			}
			else if (inimigoy <= 36 && inimigo == true)
			{
				
				//movimentação para a direita
				if (direção % 2 && inimigox > 7 && inimigox < 52 && posy - inimigoy <= 12)
				{
					//movimentação sem ilhas
					if (!(obstaculo || obstaculo2))
					{
						inimigox++;
						if (inimigox == 8 || inimigox == 51)
							direção++;
					}
					//movimentação com ilhas no meio do mapa
					else if (obstaculo && ilhay >= inimigoy && (limite - ilhay) <= inimigoy && (inimigox <= 21 || inimigox >= 41))
					{
						inimigox++;
						if (inimigox == 8 || inimigox == 51 || inimigox == 22 || inimigox == 40)
							direção++;
					}
					//movimentação com ilhas nas bordas
					else if (obstaculo2 && ilhay >= inimigoy && (limite - ilhay) <= inimigoy && inimigox >= 23 && inimigox <= 35)
					{
						inimigox++;
						if (inimigox == 23 || inimigox == 35)
							direção++;
					}
		
				}

				//movimentação para a esquerda
			    if (!direção % 2 && inimigox > 7 && inimigox < 52 && posy - inimigoy <= 12)
				{
					//movimentação sem ilhas
					if (!(obstaculo || obstaculo2))
					{
						inimigox--;
						if (inimigox == 8 || inimigox == 51)
							direção++;
					}
					//movimentação com ilhas no meio do mapa
					else if (obstaculo && ilhay >= inimigoy && (limite - ilhay) <= inimigoy && (inimigox <= 21 || inimigox >= 41))
					{
						inimigox--;
						if (inimigox == 8 || inimigox == 51 || inimigox == 22 || inimigox == 40)
							direção++;
					}
					//movimentação com ilhas nas bordas do mapa
					else if (obstaculo2 && ilhay >= inimigoy && (limite - ilhay) <= inimigoy && inimigox >= 23 && inimigox <= 35)
					{
						inimigox--;
						if (inimigox == 23 || inimigox == 35)
							direção++;
					}
				}
				
				
				if (inimigoy > 1 && inimigoy - 1 < 36) { ConsoleHelper::ImprimirASCIIExtended(inimigox, inimigoy - 1, ConsoleColor::Blue, ConsoleColor::DarkRed, " ÜÜÜ "); }
				if (inimigoy > 0 && inimigoy < 36) { ConsoleHelper::ImprimirASCIIExtended(inimigox, inimigoy, ConsoleColor::Blue, ConsoleColor::Black, "ßÛÛÛß"); }
				inimigoy += velocidade;


			}
			else { inimigo = false; }
			//checagem do tiro após a movimentação do inimigo
			if (tiro == true && (tiroy <= inimigoy && tiroy >= inimigoy - 3) && (tirox >= inimigox && (inimigox + 4) >= tirox))
			{
				Console::Beep(250, 55);
				score += 30;
				inimigo = false;
				tiro = false;
				explosao = true;
			}


			//Funcionalidades do tiro.
			if (tiro == true && tiroy > 3)
			{
				tiroy -= 3;
				ConsoleHelper::ImprimirASCIIExtended(tirox, tiroy, ConsoleColor::Blue, ConsoleColor::DarkYellow, "Ý");
			}
			else if (tiro == 1) { tiro = false; }


			//checagem de colisão após a movimentação do tiro
			if (tiro == true && (tiroy <= inimigoy && tiroy >= inimigoy - 3) && (tirox >= inimigox && ((inimigox + 4) >= tirox)))
			{
				score += 30;
				Console::Beep(250, 55);
				inimigo = false;
				tiro = false;
				explosao = true;
			}

			//Ilhas no meio do mapa
			if ((tempo % 7 == 0) && !obstaculo2 && !obstaculo) { obstaculo = true; limite = rand() % 20 + 30; }
			if (obstaculo)
			{				
				if (ilhay > 0 && ilhay <= 36) { ConsoleHelper::ImprimirASCIIExtended(23, ilhay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "   ÛÛÛÛÛÛÛÛÛÛÛ"); }
				if (ilhay > 1 && ilhay <= 36) { ConsoleHelper::ImprimirASCIIExtended(23, ilhay - 1, ConsoleColor::Blue, ConsoleColor::DarkGreen, "  ÛÛÛÛÛÛÛÛÛÛÛÛÛ"); }				
				if (ilhay > 2)
				{
					for (int i = 2; limite > i; i++)
					{				
						if (ilhay > i && ilhay - i <= 36) { ConsoleHelper::ImprimirASCIIExtended(23, ilhay - i, ConsoleColor::Blue, ConsoleColor::DarkGreen, " ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ"); }
						else if (ilhay - limite > 36) { obstaculo = false; ilhay = 1; }
					}			
				} 
				ilhay += velocidade;
				//Checagem de colisão entre a nave e as ilhas centrais
				if ((ilhay >= posy) && ((ilhay - limite) <= posy) && (posx <= 38 && posx >= 23))
				{
					ESTADO_JOGO = GAMEOVER;
				}
			}		

			//Ilhas nas bordas do mapa
			if ((tempo % 5 == 0) && !obstaculo && !obstaculo2) { obstaculo2 = true; limite = rand() % 20 + 30; }
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
						else if (ilhay - limite > 36) { obstaculo2 = false; ilhay = 1; }
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
				}
				ilhay += velocidade;
				//Checagem de colisão entre a nave e as ilhas das bordas
				if ((ilhay >= posy) && ((ilhay - limite) <= posy) && ((posx >= 41 && posx <= 56) || (posx >= 7 && posx <= 21)))
					ESTADO_JOGO = GAMEOVER;

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
			if (combustivel <= 3) { Console::Beep(350, 30); }
			if (combustivel == 0) { ESTADO_JOGO = GAMEOVER; }
			if (tempo % 3 && !comb)
			{
				comb = true;
				combx = rand() % 43 + 7;				
				comby = 6;
				//Caso o x do combustivel seja o mesmo de uma ilha, um novo x é gerado ao combustivel
				if(obstaculo)
				{
					for (;(ilhay >= comby) && ((ilhay - limite) <= comby) && (combx <= 37 && combx >= 22);)
					{
						combx = rand() % 43 + 7;
					}
				}
				if (obstaculo2)
				{
					for (;(ilhay >= comby) && ((ilhay - limite) <= comby) && ((combx >= 40 && combx <= 56) || (combx >= 7 && combx <= 21));)
					{
						combx = rand() % 43 + 7;
					}
				}
				//Evita que o combustivel apareça dentro da ponte
				if (ponte)
				{
					comby -= 16;
				}
			}
			if (comb && comby <= 40)
			{
				//Abastece a nave
				if (combustivel < 10 && comby >= posy && comby - 5 <= posy && combx - 1 <= posx && combx + 3 >= posx)
				{
					velocidade = 1;
					Console::Beep(600, 40);
					combustivel++;

				}

				//desenha o combustivel conforme sua altura
				if (comby > 6 && comby - 6 < 36) { ConsoleHelper::ImprimirASCIIExtended(combx, comby - 5, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÜÛÜ"); }			
				if (comby > 5 && comby - 5 < 36) { ConsoleHelper::ImprimirASCIIExtended(combx, comby - 4, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÛFÛ"); }
				if (comby > 4 && comby - 4 < 36) { ConsoleHelper::ImprimirASCIIExtended(combx, comby - 3, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÛUÛ"); }
				if (comby > 3 && comby - 3 < 36) { ConsoleHelper::ImprimirASCIIExtended(combx, comby - 2, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÛEÛ"); }
				if (comby > 2 && comby - 2 < 36) { ConsoleHelper::ImprimirASCIIExtended(combx, comby - 1, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÛLÛ"); }
				if (comby > 1 && comby - 1 < 36) { ConsoleHelper::ImprimirASCIIExtended(combx, comby, ConsoleColor::Blue, ConsoleColor::DarkGray, "ßßß"); }
				comby += velocidade;

				//Colisão entre o tiro e o combustivel
				if (comby >= tiroy && comby - 5 <= tiroy && combx - 1 <= tirox && combx + 3 >= tirox && tiro)
				{
					Console::Beep(250, 55);
					score += 80;
					tiro = false;
					comb = false;
					explosao = true;
				}

			}
			else { comb = false; }

			//Cria a nave, atualizando sua posição a cada frame.
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

			//Sprite da explosão
			if (explosao)
			{
				ConsoleHelper::ImprimirASCIIExtended(tirox - 3, tiroy - 2, ConsoleColor::Blue, ConsoleColor::Red, "     °");
				ConsoleHelper::ImprimirASCIIExtended(tirox - 3, tiroy - 1, ConsoleColor::Blue, ConsoleColor::Red, " ° °  ");
				ConsoleHelper::ImprimirASCIIExtended(tirox - 3, tiroy, ConsoleColor::Blue, ConsoleColor::Red, "° ° ° ");
				ConsoleHelper::ImprimirASCIIExtended(tirox - 3, tiroy + 1, ConsoleColor::Blue, ConsoleColor::Red, " ° °  ");
				ConsoleHelper::ImprimirASCIIExtended(tirox - 3, tiroy + 2, ConsoleColor::Blue, ConsoleColor::Red, "° ° ° ");
				ConsoleHelper::ImprimirASCIIExtended(tirox - 3, tiroy + 3, ConsoleColor::Blue, ConsoleColor::Red, " °    ");
				explosao = false;
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
				ConsoleHelper::ImprimirASCIIExtended(0, 41, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ºE    «    Fº                          ");
				ConsoleHelper::ImprimirASCIIExtended(0, 42, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ÈÍÍÍÍÍÍÍÍÍÍÍ¼                         ");
				ConsoleHelper::ImprimirASCIIExtended(0, 43, ConsoleColor::DarkGray, ConsoleColor::Black, "                                                                ");



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