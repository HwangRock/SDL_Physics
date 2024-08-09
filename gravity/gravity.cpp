#include <SDL.h>
#include <iostream>

// 물체의 위치와 속도를 나타내는 구조체
struct Object {
    float x, y;     // 위치
    float vx, vy;   // 속도

    Object(float x, float y) : x(x), y(y), vx(0.0f), vy(0.0f) {}//생성자
};

// 화면 크기
const int screen_x = 800, screen_y = 600;

//공의 반지름
const int radius = 10;

// 공의 초기 위치
const float start_x = screen_x / 2, start_y = screen_y - 30;

// 중력 가속도
const float gravity = 0.098f;

// 점프 초기 속도
const float jump_speed = -3.5f;

int main(int argc, char* argv[]) {

    // SDL 윈도우 생성
    SDL_Window* window = SDL_CreateWindow("gravity", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_x, screen_y, SDL_WINDOW_SHOWN);

    // SDL 렌더러 생성
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // 물체 생성
    Object obj(start_x, start_y);

    // 이벤트 처리 루프
    bool g_flag_running = false;
    bool jumping = false;
    while (!g_flag_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                g_flag_running = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE && !jumping) {
                    obj.vy = jump_speed;
                    jumping = true;
                }
                else if (event.key.keysym.sym == SDLK_LEFT) {
                    obj.vx = -1.0f;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT) {
                   obj.vx = 1.0f;
                }
            }
            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) {
                    obj.vx = 0.0f;
                }
            }
        }

        // 중력 적용
        obj.vy += gravity;

        // 물체 이동
        if (obj.vx < 0 and obj.x > 10) {
            obj.x += obj.vx;
        }
        else if (obj.vx > 0 and obj.x < screen_x - 10) {
            obj.x += obj.vx;
        }
        obj.y += obj.vy;
        
        // 물체가 지면에 도달하면 점프 상태 해제
        if (obj.y >= start_y) {
            obj.y = start_y;
            obj.vy = 0.0f;
            jumping = false;
        }

        // 화면 지우기
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 땅 그리기
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_Rect groundRect = { 0, screen_y - 20, screen_x, 20 };
        SDL_RenderFillRect(renderer, &groundRect);

        // 공 그리기
        SDL_SetRenderDrawColor(renderer, 50, 150, 10, 255);
        for (int dy = -radius; dy <= radius; dy++) {
            for (int dx = -radius; dx <= radius; dx++) {
                if (dx * dx + dy * dy <= radius * radius) {
                    SDL_RenderDrawPoint(renderer, static_cast<int>(obj.x) + dx, static_cast<int>(obj.y) + dy);
                }
            }
        }


        // 화면 업데이트
        SDL_RenderPresent(renderer);

        // 짧은 지연 시간 추가
        SDL_Delay(10);
    }

    // SDL 종료
    SDL_DestroyRenderer;
    return 0;
}
