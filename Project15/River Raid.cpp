#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ConsoleHelper.h"
#include "MediaPlayer.h"

using namespace System;

int main()
{

	srand(time(NULL));


	Console::SetWindowSize(128, 48);
	Console::SetBufferSize(128, 48);
	Console::CursorVisible = false;
	ConsoleKeyInfo tecla;

	int velocidade = 1;
	int combustivel = 10;
	int frames = 0;
	int tempo = 1;
	int score = 0;

	int posx = 20;//Coordenadas do jogador
	int posy = 31;

	int inimigox;
	int inimigoy = 2;//Coordenadas do Inimigo

	int tiroy;
	int tirox;

	int comby;
	int combx;

	int ilhay = 7;
	int mapay = 0;

	bool inimigo = false;//inimigo no jogo
	bool sair = false;
	bool tiro = false;
	bool obstaculo = false;//ilhas no meio do mapa
	bool obstaculo2 = false;
	bool comb = false;


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
			frames = 0;
			tempo = 0;
			ilhay = 7;
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

			if (velocidade == 1) { frames++; }
			else if (velocidade == 2) { frames += 2; }

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
					posx -= 2;
					Console::Beep(200, 25);
					Console::Beep(240, 25);


				}
				else if (tecla.Key == ConsoleKey::RightArrow && posx != 54)
				{
					posx += 2;
					Console::Beep(200, 25);
					Console::Beep(240, 25);


				}
				else if (tecla.Key == ConsoleKey::UpArrow) { velocidade = 2; }
				else if (tecla.Key == ConsoleKey::DownArrow) { velocidade = 1; }
				else if (tecla.Key == ConsoleKey::Spacebar)
				{
					tiro = true;
					ConsoleHelper::ImprimirASCIIExtended(posx + 1, posy - 1, "Û");
					Console::Beep(1000, 25);

					Console::Beep(2000, 25);
					tirox = posx + 1;
					tiroy = posy - 1;

				}
				
			}


			//Funcionalidades do inimigo. (Spawn, velocidade e Respawn)
			if (inimigo == false)
			{
				inimigox = rand() % 43 + 7;
				inimigoy = 1;

				ConsoleHelper::ImprimirASCIIExtended(inimigox, inimigoy, ConsoleColor::Blue, ConsoleColor::Black, "ÜÛÛÛÜ");

				inimigo = true;
			}
			else if (inimigoy <= 31 && inimigo == true)
			{
				inimigoy += velocidade;

				ConsoleHelper::ImprimirASCIIExtended(inimigox, inimigoy, ConsoleColor::Blue, ConsoleColor::DarkRed, "ÜÛÛÛÜ");


			}
			else { inimigo = false; }
			//checagem do tiro após a movimentação do inimigo
			if (tiro == true && (tiroy == inimigoy || tiroy == inimigoy - 1) && (tirox >= inimigox && (inimigox + 4) >= tirox))
			{
				Console::Beep(250, 55);
				score += 30;
				inimigo = false;
				tiro = false;
			}


			//Funcionalidades do tiro.
			if (tiro == true && tiroy > 0)
			{
				tiroy -= velocidade;
				ConsoleHelper::ImprimirASCIIExtended(tirox, tiroy, "Û");
			}
			else if (tiro == 1) { tiro = false; }


			//checagem de colisão após a movimentação do tiro
			if (tiro == true && (tiroy == inimigoy || tiroy == inimigoy - 1) && (tirox >= inimigox && ((inimigox + 4) >= tirox)))
			{
				score += 30;
				Console::Beep(250, 55);
				inimigo = false;
				tiro = false;
			}


			//Ilhas no meio do mapa
			if ((tempo % 7 == 0) && obstaculo2 == false) { obstaculo = true; }
			if (obstaculo == true && ilhay <= 40)
			{
				ConsoleHelper::ImprimirASCIIExtended(23, ilhay - 7, ConsoleColor::Blue, ConsoleColor::DarkGreen, " ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(23, ilhay - 6, ConsoleColor::Blue, ConsoleColor::DarkGreen, " ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(23, ilhay - 5, ConsoleColor::Blue, ConsoleColor::DarkGreen, " ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(23, ilhay - 4, ConsoleColor::Blue, ConsoleColor::DarkGreen, " ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(23, ilhay - 3, ConsoleColor::Blue, ConsoleColor::DarkGreen, " ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(23, ilhay - 2, ConsoleColor::Blue, ConsoleColor::DarkGreen, " ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(23, ilhay - 1, ConsoleColor::Blue, ConsoleColor::DarkGreen, "  ÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(23, ilhay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "   ÛÛÛÛÛÛÛÛÛÛÛ");
				ilhay += velocidade;
				//Checagem de colisão entre a nave e as ilhas centrais
				if ((ilhay >= posy) && ((ilhay - 7) <= posy) && (posx <= 38 && posx >= 23))
					ESTADO_JOGO = GAMEOVER;

			}

			//Ilhas nas bordas do mapa
			if ((tempo % 11 == 0) && obstaculo == false) { obstaculo2 = true; }
			if (obstaculo2 == true && ilhay <= 40)
			{
				ConsoleHelper::ImprimirASCIIExtended(7, ilhay - 7, ConsoleColor::Blue, ConsoleColor::DarkGreen, "ÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(7, ilhay - 6, ConsoleColor::Blue, ConsoleColor::DarkGreen, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(7, ilhay - 5, ConsoleColor::Blue, ConsoleColor::DarkGreen, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(7, ilhay - 4, ConsoleColor::Blue, ConsoleColor::DarkGreen, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(7, ilhay - 3, ConsoleColor::Blue, ConsoleColor::DarkGreen, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(7, ilhay - 2, ConsoleColor::Blue, ConsoleColor::DarkGreen, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(7, ilhay - 1, ConsoleColor::Blue, ConsoleColor::DarkGreen, "ÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(7, ilhay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "ÛÛÛÛÛÛÛÛÛÛÛÛÛ");

				ConsoleHelper::ImprimirASCIIExtended(41, ilhay - 7, ConsoleColor::Blue, ConsoleColor::DarkGreen, "   ÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(41, ilhay - 6, ConsoleColor::Blue, ConsoleColor::DarkGreen, "  ÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(41, ilhay - 5, ConsoleColor::Blue, ConsoleColor::DarkGreen, " ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(41, ilhay - 4, ConsoleColor::Blue, ConsoleColor::DarkGreen, " ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(41, ilhay - 3, ConsoleColor::Blue, ConsoleColor::DarkGreen, " ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(41, ilhay - 2, ConsoleColor::Blue, ConsoleColor::DarkGreen, " ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(41, ilhay - 1, ConsoleColor::Blue, ConsoleColor::DarkGreen, "  ÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(41, ilhay, ConsoleColor::Blue, ConsoleColor::DarkGreen, "   ÛÛÛÛÛÛÛÛÛÛÛÛÛ");
				ilhay += velocidade;
				//Checagem de colisão entre a nave e as ilhas das bordas
				if ((ilhay >= posy) && ((ilhay - 7) <= posy) && ((posx >= 41 && posx <= 56) || (posx >= 7 && posx <= 21)))
					ESTADO_JOGO = GAMEOVER;

			}
			else if (ilhay > 40) { obstaculo = false; obstaculo2 = false; ilhay = 7; }

			//Combustivel
			if (combustivel == 0){ ESTADO_JOGO = GAMEOVER; }
			if (tempo % 5 && !comb) { comb = true; combx = rand() % 43 + 7; comby = 6; }
			if (comb && comby <= 40)
			{
				//Abastece a nave
				if (comby >= posy && comby - 5 <= posy && combx - 1 <= posx && combx + 3 >= posx)
				{
					Console::Beep(600, 40);
					combustivel++;

				}

				ConsoleHelper::ImprimirASCIIExtended(combx, comby - 5, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÜÛÜ");
				ConsoleHelper::ImprimirASCIIExtended(combx, comby - 4, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÛFÛ");
				ConsoleHelper::ImprimirASCIIExtended(combx, comby - 3, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÛUÛ");
				ConsoleHelper::ImprimirASCIIExtended(combx, comby - 2, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÛEÛ");
				ConsoleHelper::ImprimirASCIIExtended(combx, comby - 1, ConsoleColor::Blue, ConsoleColor::DarkGray, "ÛLÛ");
				ConsoleHelper::ImprimirASCIIExtended(combx, comby, ConsoleColor::Blue, ConsoleColor::DarkGray, "ßßß");
				comby += velocidade;
			}
			else { comb = false; }

			//Cria a nave, atualizando sua posição a cada frame.
			ConsoleHelper::ImprimirASCIIExtended(posx, posy, ConsoleColor::Blue, ConsoleColor::DarkYellow, " Û ");
			ConsoleHelper::ImprimirASCIIExtended(posx, posy + 1, ConsoleColor::Blue, ConsoleColor::DarkYellow, "ÛÛÛ");
			ConsoleHelper::ImprimirASCIIExtended(posx, posy + 2, ConsoleColor::Blue, ConsoleColor::DarkYellow, " Û ");
			ConsoleHelper::ImprimirASCIIExtended(posx, posy + 3, ConsoleColor::Blue, ConsoleColor::DarkYellow, "Û Û");

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
				if (combustivel == 10)
				{
					ConsoleHelper::ImprimirASCIIExtended(0, 38, ConsoleColor::DarkGray, ConsoleColor::Black, "                                                                ");
					ConsoleHelper::ImprimirASCIIExtended(0, 39, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ÉÍÍÍÍÍÍÍÍÍÍÍ»                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º          ³º                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 41, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ºE    «   F º                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 42, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ÈÍÍÍÍÍÍÍÍÍÍÍ¼                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 43, ConsoleColor::DarkGray, ConsoleColor::Black, "                                                                ");
				}
				else if (combustivel == 9)
				{
					ConsoleHelper::ImprimirASCIIExtended(0, 38, ConsoleColor::DarkGray, ConsoleColor::Black, "                                                                ");
					ConsoleHelper::ImprimirASCIIExtended(0, 39, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ÉÍÍÍÍÍÍÍÍÍÍÍ»                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º         ³ º                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 41, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ºE    «   F º                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 42, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ÈÍÍÍÍÍÍÍÍÍÍÍ¼                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 43, ConsoleColor::DarkGray, ConsoleColor::Black, "                                                                ");
				}
				else if (combustivel == 8)
				{
					ConsoleHelper::ImprimirASCIIExtended(0, 38, ConsoleColor::DarkGray, ConsoleColor::Black, "                                                                ");
					ConsoleHelper::ImprimirASCIIExtended(0, 39, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ÉÍÍÍÍÍÍÍÍÍÍÍ»                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º        ³  º                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 41, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ºE    «   F º                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 42, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ÈÍÍÍÍÍÍÍÍÍÍÍ¼                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 43, ConsoleColor::DarkGray, ConsoleColor::Black, "                                                                ");
				}
				else if (combustivel == 7)
				{
					ConsoleHelper::ImprimirASCIIExtended(0, 38, ConsoleColor::DarkGray, ConsoleColor::Black, "                                                                ");
					ConsoleHelper::ImprimirASCIIExtended(0, 39, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ÉÍÍÍÍÍÍÍÍÍÍÍ»                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º       ³   º                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 41, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ºE    «   F º                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 42, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ÈÍÍÍÍÍÍÍÍÍÍÍ¼                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 43, ConsoleColor::DarkGray, ConsoleColor::Black, "                                                                ");
				}
				else if (combustivel == 6)
				{
					ConsoleHelper::ImprimirASCIIExtended(0, 38, ConsoleColor::DarkGray, ConsoleColor::Black, "                                                                ");
					ConsoleHelper::ImprimirASCIIExtended(0, 39, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ÉÍÍÍÍÍÍÍÍÍÍÍ»                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º      ³    º                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 41, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ºE    «   F º                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 42, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ÈÍÍÍÍÍÍÍÍÍÍÍ¼                         ");
					ConsoleHelper::ImprimirASCIIExtended(0, 43, ConsoleColor::DarkGray, ConsoleColor::Black, "                                                                ");
				}
				else if (combustivel = 5)
				{
					ConsoleHelper::ImprimirASCIIExtended(0, 38, ConsoleColor::DarkGray, ConsoleColor::Black, "                                                                ");
					ConsoleHelper::ImprimirASCIIExtended(0, 39, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ÉÍÍÍÍÍÍÍÍÍ»                           ");
					ConsoleHelper::ImprimirASCIIExtended(0, 40, ConsoleColor::DarkGray, ConsoleColor::Black, "                          º³        º                           ");
					ConsoleHelper::ImprimirASCIIExtended(0, 41, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ºE   «   Fº                           ");
					ConsoleHelper::ImprimirASCIIExtended(0, 42, ConsoleColor::DarkGray, ConsoleColor::Black, "                          ÈÍÍÍÍÍÍÍÍÍ¼                           ");
					ConsoleHelper::ImprimirASCIIExtended(0, 43, ConsoleColor::DarkGray, ConsoleColor::Black, "                                                                ");
				}
			}
			Console::BackgroundColor = ConsoleColor::Blue;
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