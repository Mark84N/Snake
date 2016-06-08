#pragma comment(lib, "user32.lib")
#include <field.h>

#include <Windows.h>
#include <chrono>
#include <thread>

int main(int argc, char *argv[]){

    Field f;
    f.showField();

    while (true) {
            system("cls");

            DIRECTIONS defaultDir = f.getSnakeDirection();

            if (GetAsyncKeyState(VK_RIGHT)){
                keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
                defaultDir = DIRECTIONS::RIGHT;

                f.makeStep(DIRECTIONS::RIGHT);

            }
            else if (GetAsyncKeyState(VK_LEFT)){
                keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
                defaultDir = DIRECTIONS::LEFT;

                f.makeStep(DIRECTIONS::LEFT);

            }
            else if (GetAsyncKeyState(VK_UP)){
                keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);
                defaultDir = DIRECTIONS::UP;

                f.makeStep(DIRECTIONS::UP);
            }
            else if (GetAsyncKeyState(VK_DOWN)){
                keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
                defaultDir = DIRECTIONS::DOWN;

                f.makeStep(DIRECTIONS::DOWN);
            }
            else
                f.makeStep(defaultDir);

            f.showField();
            std::this_thread::sleep_for(std::chrono::milliseconds(f.getCurrLevel()));
        }

    return 0;
}
