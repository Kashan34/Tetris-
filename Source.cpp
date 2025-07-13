#include <iostream>
#include <conio.h>
#include <thread>
#include<string>
#include <vector>
#include <fstream>  // Add fstream library for file I/O
using namespace std;
#include <stdio.h>
#include <windows.h>

const int nScreenWidth = 120;
const int nScreenHeight = 30;
wstring tetromino[7];
const int nFieldWidth = 12;
const int nFieldHeight = 18;
unsigned char* pField = nullptr;

int Rotate(int px, int py, int r)
{
	int pi = 0;
	switch (r % 4)
	{
	case 0:
		pi = py * 4 + px;
		break;
	case 1:
		pi = 12 + py - (px * 4);
		break;
	case 2:
		pi = 15 - (py * 4) - px;
		break;
	case 3:
		pi = 3 - py + (px * 4);
		break;
	}
	return pi;
}


bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++)
		{
			int pi = Rotate(px, py, nRotation);
			int fi = (nPosY + py) * nFieldWidth + (nPosX + px);
			if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
			{
				if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
				{
					if (tetromino[nTetromino][pi] == L'X' && pField[fi] != 0)
						return false;
				}
			}
		}
	return true;
}

int main()
{

	string strName;
	int nScore = 0;

	struct Player {
		string strName;
		int nScore;
	};
	
	// Initialize tetromino shapes
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");

	tetromino[1].append(L"..X.");
	tetromino[1].append(L".XX.");
	tetromino[1].append(L".X..");
	tetromino[1].append(L"....");

	tetromino[2].append(L".X.");
	tetromino[2].append(L".XX.");
	tetromino[2].append(L"..X.");
	tetromino[2].append(L"....");

	tetromino[3].append(L"....");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L"....");

	tetromino[4].append(L"..X.");
	tetromino[4].append(L".XX.");
	tetromino[4].append(L"..X.");
	tetromino[4].append(L"....");

	tetromino[5].append(L"....");
	tetromino[5].append(L".XX.");
	tetromino[5].append(L"..X.");
	tetromino[5].append(L"..X.");

	tetromino[6].append(L"....");
	tetromino[6].append(L"..X.");
	tetromino[6].append(L".XX.");
	tetromino[6].append(L"..X.");


	pField = new unsigned char[nFieldWidth * nFieldHeight];
	for (int x = 0; x < nFieldWidth; x++)
		for (int y = 0; y < nFieldHeight; y++)
			pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

	// Main menu loop
	while (true)
	{
		
		// Display main menu options
	  cout << "\nTTTTTTT   EEEEEE  TTTTTTT  RRRRRR   IIIIII   SSSSS  " << endl;
		cout << "   T      E          T     R    R     I     S     S " << endl;
		cout << "   T      E          T     R    R     I     S     " << endl;
		cout << "   T      EEEEEE     T     RRRRRR     I      SSSSS  " << endl;
		cout << "   T      E          T     R   R      I           S " << endl;
		cout << "   T      E          T     R    R     I     S     S " << endl;
		cout << "   T      EEEEEE     T     R     R  IIIIII   SSSSS\n" << endl;
		cout << "1. Start game" << endl;
		cout << "2. Previous Scores" << endl;
		cout << "3. View rules" << endl;
		cout << "4. Quit\n\n" << endl;

		// Get input from player
		int nSelection = _getch();

		// Start game
		if (nSelection == '1')
		{
			// Get player name
			cout << "Enter your name: ";
			cin >> strName;
			cout << endl;
			
			Player player;
			player.strName = strName;
			player.nScore = 0;

			// Initialize game variables
			
			int nCurrentPiece = rand() % 7;
			int nCurrentRotation = 0;
			int nCurrentX = nFieldWidth / 2;
			int nCurrentY = 0;

			// Game loop
			while (true)
			{
				wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
				for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
				HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
				SetConsoleActiveScreenBuffer(hConsole);
				DWORD dwBytesWritten = 0;
				bool bGameOver = false;
				int nCurrentPiece = 0;
				int nCurrentRotation = 0;
				int nCurrentX = nFieldWidth / 2;
				int nCurrentY = 0;
				bool bKey[4];
				bool bRotateHold = false;
				int nSpeed = 20;
				int nSpeedCounter = 0;
				bool bForceDown = false;
				int nPieceCount = 0;
				
				vector<int> vLines;
				while (!bGameOver)
				{
					this_thread::sleep_for(50ms);
					nSpeedCounter++;
					bForceDown = (nSpeedCounter == nSpeed);
					for (int k = 0; k < 4; k++)
						bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;
					if (bKey[1])
					{
						if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY))
						{
							nCurrentX = nCurrentX - 1;
						}
					}
					if (bKey[0])
					{
						if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY))
						{
							nCurrentX = nCurrentX + 1;
						}
					}
					if (bKey[2])
					{
						if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
						{
							nCurrentY = nCurrentY + 1;
						}
					}
					if (bKey[3])
					{
						nCurrentRotation += (!bRotateHold && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY));
						bRotateHold = true;
					}
					else
						bRotateHold = false;
					if (bForceDown)
					{
						if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
							nCurrentY++;
						else
						{
							for (int px = 0; px < 4; px++)
								for (int py = 0; py < 4; py++)
									if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
										pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;
							nPieceCount++;
							if (nPieceCount % 10 == 0)
								if (nSpeed >= 10) nSpeed--;
							for (int py = 0; py < 4; py++)
								if (nCurrentY + py < nFieldHeight - 1)
								{
									bool bline = true;
									for (int px = 1; px < nFieldWidth - 1; px++)
										bline &= (pField[(nCurrentY + py) * nFieldWidth + px]) != 0;
									if (bline)
									{
										for (int px = 1; px < nFieldWidth - 1; px++)
											pField[(nCurrentY + py) * nFieldWidth + px] = 8;
										vLines.push_back(nCurrentY + py);
									}
								}
							player.nScore += 25;
							if (!vLines.empty()) player.nScore += (1 << vLines.size()) * 100;
							nCurrentX = nFieldWidth / 2;
							nCurrentY = 0;
							nCurrentRotation = 0;
							nCurrentPiece = rand() % 7;
							bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
						}
						nSpeedCounter = 0;
					}
					for (int x = 0; x < nFieldWidth; x++)
						for (int y = 0; y < nFieldHeight; y++)
							screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];
					for (int px = 0; px < 4; px++)
						for (int py = 0; py < 4; py++)
							if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
								screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;
					swprintf_s(&screen[nScreenWidth + nFieldWidth + 8], 16, L"SCORE: %8d", player.nScore);
					if (!vLines.empty())
					{
						WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
						this_thread::sleep_for(400ms);
						for (auto& v : vLines)
							for (int px = 1; px < nFieldWidth - 1; px++)
							{
								for (int py = v; py > 0; py--)
									pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
								pField[px] = 0;
							}
						vLines.clear();
					}
					WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
				}
				CloseHandle(hConsole);
				cout << " GGGGG    AAAA   M     M  EEEEEE         OOOOOO   V     V  EEEEEE  RRRRRR " << endl;
				cout << "G     G  A    A  MM   MM  E             O      O  V     V  E       R     R" << endl;
				cout << "G        A    A  M M M M  E             O      O  V     V  E       R     R" << endl;
				cout << "G        A    A  M M M M  EEEEE         O      O  V     V  EEEEE   RRRRRR " << endl;
				cout << "G   GGG  AAAAAA  M  M  M  E             O      O  V     V  E       R   R  " << endl;
				cout << "G    GG  A    A  M     M  E             O      O   V   V   E       R    R " << endl;
				cout << " GGGGG   A    A  M     M  EEEEEE         OOOOOO     VVV    EEEEEE  R     R" << endl;
				cout << "\n\n\nSCORE: " << nScore << endl;
				cout << "\n\n\n\n" << endl;
				system("pause");
				break;

			}
			ofstream outFile;
			outFile.open("scores.txt", ios::app);
			outFile << player.strName << " " << player.nScore << endl;
			outFile.close();
			break;
		}

		// View high scores
		else if (nSelection == '2')
		{
			// Open high scores file
			fstream fileScores("scores.txt", ios::in);

			// Read and display high scores
			
			while (fileScores >> strName >> nScore)
			{
				cout << strName << ": " << nScore << endl;
			}

			// Close high scores file
			fileScores.close();
		}
		// View rules
		else if (nSelection == '3')
		{
			// Display game rules
			cout << "Tetris is a puzzle game where the player must rotate and place falling tetromino blocks to create complete rows." << endl;
			cout << "If a row is completed, it is cleared and the player scores points. The game ends when the blocks reach the top of the field." << endl;
			cout << "Controls: Arrow keys to move, Space to rotate, P to pause." << endl;
			cout << endl;
		}
		// Quit game
		else if (nSelection == '4')
		{
			break;
		}
	}

	return 0;
}