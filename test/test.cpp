#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
#include <windows.h>

using namespace std;

// 文字の色を変更する関数
void SetConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main() {
    const int FRAME_RATE = 60;
    const double FRAME_TIME = 1.0 / FRAME_RATE;

    double deltaTime = 0.0;
    chrono::high_resolution_clock::time_point prevTime = chrono::high_resolution_clock::now();

    int playerPosition = 0;
    bool isJumping = false;
    int jumpFrames = 0;

    int obstaclePosition = 10;

    while (true) {
        chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
        chrono::duration<double> timeSpan = chrono::duration_cast<chrono::duration<double>>(currentTime - prevTime);
        deltaTime = timeSpan.count();
        prevTime = currentTime;

        if (_kbhit()) {
            char key = _getch();
            if (key == 'a' && playerPosition > 0) {
                playerPosition--;
            }
            else if (key == 'd' && playerPosition < 19) {
                playerPosition++;
            }
            else if (key == ' ') {
                if (!isJumping) {
                    isJumping = true;
                    jumpFrames = 10;
                }
            }
        }

        if (isJumping) {
            jumpFrames--;
            if (jumpFrames <= 0) {
                isJumping = false;
            }
        }

        obstaclePosition--;
        if (obstaclePosition < 0) {
            obstaclePosition = 19;
        }

        if (playerPosition == obstaclePosition && !isJumping) {
            cout << "Game Over!" << endl;
            break;
        }

        system("cls");

        for (int i = 0; i < 20; i++) {
            if (i == playerPosition && isJumping) {
                SetConsoleColor(10);  // プレイヤーのジャンプ中の色 (緑色)
                cout << "P";
                SetConsoleColor(7);   // デフォルトの文字色に戻す
            }
            else {
                cout << ".";
            }
        }
        cout << endl;

        for (int i = 0; i < 20; i++) {
            if (i == playerPosition && !isJumping) {
                SetConsoleColor(12);  // プレイヤーの通常時の色 (赤色)
                cout << "P";
                SetConsoleColor(7);   // デフォルトの文字色に戻す
            }
            else if (i == obstaclePosition) {
                cout << "X";
            }
            else {
                cout << ".";
            }
        }
        cout << endl;

        double remainingTime = FRAME_TIME - deltaTime;
        if (remainingTime > 0) {
            this_thread::sleep_for(chrono::duration<double>(remainingTime));
        }
    }

    return 0;
}