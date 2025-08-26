#include "raylib.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <memory>
#include <random>

// 游戏常量
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const float BALL_RADIUS = 20.0f;
const float PADDLE_WIDTH = 15.0f;
const float PADDLE_HEIGHT = 80.0f;
const float BALL_SPEED = 300.0f;
const float PADDLE_SPEED = 400.0f;

// 颜色主题
const Color THEME_BACKGROUND = {15, 15, 35, 255};
const Color THEME_FOREGROUND = {255, 255, 255, 255};
const Color THEME_ACCENT = {100, 200, 255, 255};
const Color THEME_SUCCESS = {100, 255, 100, 255};
const Color THEME_DANGER = {255, 100, 100, 255};

// 游戏状态枚举
enum class GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

// 粒子系统
struct Particle {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float life;
    float max_life;
    
    Particle(Vector2 pos, Vector2 vel, Color col, float lifetime) 
        : position(pos), velocity(vel), color(col), life(lifetime), max_life(lifetime) {}
    
    void update(float dt) {
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        life -= dt;
        
        // 淡出效果
        float alpha = life / max_life;
        color.a = (unsigned char)(255 * alpha);
    }
    
    bool is_alive() const {
        return life > 0;
    }
    
    void draw() const {
        if (is_alive()) {
            DrawCircleV(position, 3.0f, color);
        }
    }
};

// 粒子系统管理器
class ParticleSystem {
private:
    std::vector<Particle> particles;
    
public:
    void emit(Vector2 position, int count, Color base_color) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> speed_dist(50.0f, 200.0f);
        std::uniform_real_distribution<float> angle_dist(0.0f, 2.0f * PI);
        std::uniform_real_distribution<float> life_dist(0.5f, 2.0f);
        
        for (int i = 0; i < count; ++i) {
            float angle = angle_dist(gen);
            float speed = speed_dist(gen);
            
            Vector2 velocity = {
                std::cos(angle) * speed,
                std::sin(angle) * speed
            };
            
            particles.emplace_back(position, velocity, base_color, life_dist(gen));
        }
    }
    
    void update(float dt) {
        for (auto& particle : particles) {
            particle.update(dt);
        }
        
        // 移除死亡的粒子
        particles.erase(
            std::remove_if(particles.begin(), particles.end(),
                          [](const Particle& p) { return !p.is_alive(); }),
            particles.end());
    }
    
    void draw() const {
        for (const auto& particle : particles) {
            particle.draw();
        }
    }
    
    size_t get_count() const {
        return particles.size();
    }
};

// 游戏球类
class Ball {
public:
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
    
    Ball(Vector2 pos, float r) : position(pos), radius(r), color(THEME_FOREGROUND) {
        reset_velocity();
    }
    
    void reset_velocity() {
        // 随机初始方向
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> angle_dist(-PI/4, PI/4);
        std::uniform_int_distribution<int> direction_dist(0, 1);
        
        float angle = angle_dist(gen);
        int direction = direction_dist(gen) ? 1 : -1;
        
        velocity.x = std::cos(angle) * BALL_SPEED * direction;
        velocity.y = std::sin(angle) * BALL_SPEED;
    }
    
    void update(float dt) {
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        
        // 上下边界碰撞
        if (position.y - radius <= 0 || position.y + radius >= SCREEN_HEIGHT) {
            velocity.y = -velocity.y;
            position.y = std::max(radius, std::min((float)SCREEN_HEIGHT - radius, position.y));
        }
    }
    
    void draw() const {
        DrawCircleV(position, radius, color);
        
        // 添加发光效果
        DrawCircleV(position, radius + 2, Fade(color, 0.3f));
        DrawCircleV(position, radius + 4, Fade(color, 0.1f));
    }
    
    Rectangle get_bounds() const {
        return {
            position.x - radius,
            position.y - radius,
            radius * 2,
            radius * 2
        };
    }
};

// 游戏板类
class Paddle {
public:
    Vector2 position;
    Vector2 size;
    Color color;
    float speed;
    bool is_ai;
    
    Paddle(Vector2 pos, bool ai = false) 
        : position(pos), size{PADDLE_WIDTH, PADDLE_HEIGHT}, 
          color(THEME_FOREGROUND), speed(PADDLE_SPEED), is_ai(ai) {}
    
    void update(float dt, const Ball& ball) {
        if (is_ai) {
            // AI逻辑：跟踪球
            float target_y = ball.position.y - size.y / 2;
            float diff = target_y - position.y;
            
            if (std::abs(diff) > 5.0f) {
                float move_direction = diff > 0 ? 1.0f : -1.0f;
                position.y += move_direction * speed * dt * 0.8f; // AI稍微慢一点
            }
        } else {
            // 玩家控制
            if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
                position.y -= speed * dt;
            }
            if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
                position.y += speed * dt;
            }
        }
        
        // 边界检查
        position.y = std::max(0.0f, std::min((float)SCREEN_HEIGHT - size.y, position.y));
    }
    
    void draw() const {
        Rectangle paddle_rect = {position.x, position.y, size.x, size.y};
        DrawRectangleRec(paddle_rect, color);
        
        // 添加边框效果
        DrawRectangleLinesEx(paddle_rect, 2, THEME_ACCENT);
    }
    
    Rectangle get_bounds() const {
        return {position.x, position.y, size.x, size.y};
    }
};

// 主游戏类
class PongGame {
private:
    GameState state;
    std::unique_ptr<Ball> ball;
    std::unique_ptr<Paddle> left_paddle;
    std::unique_ptr<Paddle> right_paddle;
    ParticleSystem particles;
    
    int left_score;
    int right_score;
    const int winning_score = 5;
    
    float game_time;
    std::string winner_message;
    
public:
    PongGame() : state(GameState::MENU), left_score(0), right_score(0), game_time(0.0f) {
        initialize_game();
    }
    
    void initialize_game() {
        // 创建游戏对象
        ball = std::make_unique<Ball>(
            Vector2{SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f}, 
            BALL_RADIUS
        );
        
        left_paddle = std::make_unique<Paddle>(
            Vector2{50, SCREEN_HEIGHT / 2.0f - PADDLE_HEIGHT / 2.0f},
            false // 玩家控制
        );
        
        right_paddle = std::make_unique<Paddle>(
            Vector2{SCREEN_WIDTH - 50 - PADDLE_WIDTH, SCREEN_HEIGHT / 2.0f - PADDLE_HEIGHT / 2.0f},
            true // AI控制
        );
    }
    
    void handle_input() {
        switch (state) {
            case GameState::MENU:
                if (IsKeyPressed(KEY_SPACE)) {
                    state = GameState::PLAYING;
                    reset_game();
                }
                if (IsKeyPressed(KEY_ESCAPE)) {
                    state = GameState::GAME_OVER;
                }
                break;
                
            case GameState::PLAYING:
                if (IsKeyPressed(KEY_ESCAPE)) {
                    state = GameState::PAUSED;
                }
                break;
                
            case GameState::PAUSED:
                if (IsKeyPressed(KEY_SPACE)) {
                    state = GameState::PLAYING;
                }
                if (IsKeyPressed(KEY_ESCAPE)) {
                    state = GameState::MENU;
                }
                break;
                
            case GameState::GAME_OVER:
                if (IsKeyPressed(KEY_SPACE)) {
                    state = GameState::MENU;
                }
                if (IsKeyPressed(KEY_ESCAPE)) {
                    // 退出游戏
                }
                break;
        }
    }
    
    void update(float dt) {
        game_time += dt;
        particles.update(dt);
        
        if (state == GameState::PLAYING) {
            // 更新游戏对象
            ball->update(dt);
            left_paddle->update(dt, *ball);
            right_paddle->update(dt, *ball);
            
            // 碰撞检测
            check_collisions();
            
            // 检查得分
            check_scoring();
            
            // 检查游戏结束条件
            if (left_score >= winning_score || right_score >= winning_score) {
                winner_message = (left_score >= winning_score) ? "玩家获胜!" : "AI获胜!";
                state = GameState::GAME_OVER;
            }
        }
    }
    
    void check_collisions() {
        Rectangle ball_rect = ball->get_bounds();
        
        // 左挡板碰撞
        if (CheckCollisionRecs(ball_rect, left_paddle->get_bounds()) && ball->velocity.x < 0) {
            ball->velocity.x = -ball->velocity.x;
            
            // 根据击中位置调整角度
            float hit_pos = (ball->position.y - left_paddle->position.y) / left_paddle->size.y - 0.5f;
            ball->velocity.y += hit_pos * 200.0f;
            
            // 生成粒子效果
            particles.emit(ball->position, 10, THEME_ACCENT);
        }
        
        // 右挡板碰撞
        if (CheckCollisionRecs(ball_rect, right_paddle->get_bounds()) && ball->velocity.x > 0) {
            ball->velocity.x = -ball->velocity.x;
            
            float hit_pos = (ball->position.y - right_paddle->position.y) / right_paddle->size.y - 0.5f;
            ball->velocity.y += hit_pos * 200.0f;
            
            particles.emit(ball->position, 10, THEME_ACCENT);
        }
    }
    
    void check_scoring() {
        // 左边得分 (球出右边界)
        if (ball->position.x > SCREEN_WIDTH) {
            left_score++;
            particles.emit(Vector2{SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2}, 20, THEME_SUCCESS);
            reset_ball();
        }
        
        // 右边得分 (球出左边界)
        if (ball->position.x < 0) {
            right_score++;
            particles.emit(Vector2{50, SCREEN_HEIGHT / 2}, 20, THEME_DANGER);
            reset_ball();
        }
    }
    
    void reset_ball() {
        ball->position = Vector2{SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
        ball->reset_velocity();
    }
    
    void reset_game() {
        left_score = 0;
        right_score = 0;
        game_time = 0.0f;
        reset_ball();
    }
    
    void draw() {
        BeginDrawing();
        
        ClearBackground(THEME_BACKGROUND);
        
        switch (state) {
            case GameState::MENU:
                draw_menu();
                break;
                
            case GameState::PLAYING:
            case GameState::PAUSED:
                draw_game();
                if (state == GameState::PAUSED) {
                    draw_pause_overlay();
                }
                break;
                
            case GameState::GAME_OVER:
                draw_game();
                draw_game_over();
                break;
        }
        
        // 绘制粒子效果
        particles.draw();
        
        // FPS显示
        DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, THEME_ACCENT);
        DrawText(TextFormat("Particles: %zu", particles.get_count()), 10, 35, 16, THEME_ACCENT);
        
        EndDrawing();
    }
    
    void draw_menu() {
        const char* title = "RAYLIB PONG";
        const char* subtitle = "现代C++游戏演示";
        const char* instructions[] = {
            "SPACE - 开始游戏",
            "↑/↓ 或 W/S - 移动挡板",
            "ESC - 暂停/退出",
            "",
            "使用raylib游戏引擎",
            "集成现代C++特性"
        };
        
        int title_width = MeasureText(title, 60);
        int subtitle_width = MeasureText(subtitle, 30);
        
        DrawText(title, (SCREEN_WIDTH - title_width) / 2, SCREEN_HEIGHT / 2 - 100, 60, THEME_FOREGROUND);
        DrawText(subtitle, (SCREEN_WIDTH - subtitle_width) / 2, SCREEN_HEIGHT / 2 - 40, 30, THEME_ACCENT);
        
        for (size_t i = 0; i < sizeof(instructions) / sizeof(instructions[0]); ++i) {
            int text_width = MeasureText(instructions[i], 20);
            DrawText(instructions[i], (SCREEN_WIDTH - text_width) / 2, 
                    SCREEN_HEIGHT / 2 + 20 + i * 25, 20, THEME_FOREGROUND);
        }
        
        // 闪烁提示
        if (((int)(game_time * 2)) % 2 == 0) {
            const char* prompt = "按 SPACE 开始";
            int prompt_width = MeasureText(prompt, 24);
            DrawText(prompt, (SCREEN_WIDTH - prompt_width) / 2, 
                    SCREEN_HEIGHT - 100, 24, THEME_SUCCESS);
        }
    }
    
    void draw_game() {
        // 绘制中线
        for (int y = 0; y < SCREEN_HEIGHT; y += 20) {
            DrawRectangle(SCREEN_WIDTH / 2 - 2, y, 4, 10, THEME_ACCENT);
        }
        
        // 绘制游戏对象
        ball->draw();
        left_paddle->draw();
        right_paddle->draw();
        
        // 绘制分数
        std::string left_score_text = std::to_string(left_score);
        std::string right_score_text = std::to_string(right_score);
        
        DrawText(left_score_text.c_str(), SCREEN_WIDTH / 4, 50, 48, THEME_FOREGROUND);
        DrawText(right_score_text.c_str(), 3 * SCREEN_WIDTH / 4, 50, 48, THEME_FOREGROUND);
        
        // 绘制标签
        DrawText("玩家", SCREEN_WIDTH / 4 - 30, 110, 20, THEME_ACCENT);
        DrawText("AI", 3 * SCREEN_WIDTH / 4 - 10, 110, 20, THEME_ACCENT);
        
        // 游戏时间
        std::string time_text = "时间: " + std::to_string((int)game_time) + "s";
        DrawText(time_text.c_str(), SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT - 30, 20, THEME_ACCENT);
    }
    
    void draw_pause_overlay() {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.7f));
        
        const char* pause_text = "游戏暂停";
        const char* resume_text = "按 SPACE 继续";
        const char* menu_text = "按 ESC 返回菜单";
        
        int pause_width = MeasureText(pause_text, 48);
        int resume_width = MeasureText(resume_text, 24);
        int menu_width = MeasureText(menu_text, 24);
        
        DrawText(pause_text, (SCREEN_WIDTH - pause_width) / 2, SCREEN_HEIGHT / 2 - 50, 48, THEME_FOREGROUND);
        DrawText(resume_text, (SCREEN_WIDTH - resume_width) / 2, SCREEN_HEIGHT / 2 + 20, 24, THEME_ACCENT);
        DrawText(menu_text, (SCREEN_WIDTH - menu_width) / 2, SCREEN_HEIGHT / 2 + 50, 24, THEME_ACCENT);
    }
    
    void draw_game_over() {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.8f));
        
        const char* game_over_text = "游戏结束";
        const char* restart_text = "按 SPACE 重新开始";
        
        int game_over_width = MeasureText(game_over_text, 48);
        int winner_width = MeasureText(winner_message.c_str(), 36);
        int restart_width = MeasureText(restart_text, 24);
        
        DrawText(game_over_text, (SCREEN_WIDTH - game_over_width) / 2, SCREEN_HEIGHT / 2 - 80, 48, THEME_DANGER);
        DrawText(winner_message.c_str(), (SCREEN_WIDTH - winner_width) / 2, SCREEN_HEIGHT / 2 - 20, 36, THEME_SUCCESS);
        DrawText(restart_text, (SCREEN_WIDTH - restart_width) / 2, SCREEN_HEIGHT / 2 + 40, 24, THEME_ACCENT);
        
        // 最终分数
        std::string final_score = "最终比分: " + std::to_string(left_score) + " - " + std::to_string(right_score);
        int score_width = MeasureText(final_score.c_str(), 20);
        DrawText(final_score.c_str(), (SCREEN_WIDTH - score_width) / 2, SCREEN_HEIGHT / 2 + 80, 20, THEME_FOREGROUND);
    }
    
    bool should_close() const {
        return WindowShouldClose();
    }
};

int main() {
    std::cout << "🎮 Raylib 现代C++游戏开发演示\\n";
    std::cout << "===============================\\n";
    std::cout << "启动 Pong 游戏...\\n\\n";
    
    // 初始化raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib C++ Demo - Modern Pong Game");
    
    // 设置目标FPS
    SetTargetFPS(60);
    
    try {
        // 创建游戏实例
        PongGame game;
        
        std::cout << "📚 游戏特性:\\n";
        std::cout << "  • 现代C++类设计和RAII\\n";
        std::cout << "  • 智能指针管理内存\\n";
        std::cout << "  • 粒子系统视觉效果\\n";
        std::cout << "  • 碰撞检测和物理模拟\\n";
        std::cout << "  • AI对手\\n";
        std::cout << "  • 状态机管理\\n";
        std::cout << "  • 实时FPS显示\\n\\n";
        
        std::cout << "🎯 控制说明:\\n";
        std::cout << "  • ↑/↓ 或 W/S: 移动挡板\\n";
        std::cout << "  • SPACE: 开始/继续游戏\\n";
        std::cout << "  • ESC: 暂停/返回菜单\\n\\n";
        
        // 游戏主循环
        while (!game.should_close()) {
            float deltaTime = GetFrameTime();
            
            game.handle_input();
            game.update(deltaTime);
            game.draw();
        }
        
    } catch (const std::exception& e) {
        std::cerr << "❌ 游戏错误: " << e.what() << std::endl;
        CloseWindow();
        return 1;
    }
    
    // 清理资源
    CloseWindow();
    
    std::cout << "✅ Raylib 演示完成!\\n";
    std::cout << "\\n📚 Raylib 主要特性:\\n";
    std::cout << "  • 简单易用的游戏开发API\\n";
    std::cout << "  • 跨平台支持 (Windows, Linux, macOS)\\n";
    std::cout << "  • 2D/3D图形渲染\\n";
    std::cout << "  • 音频播放和处理\\n";
    std::cout << "  • 输入处理 (键盘, 鼠标, 游戏手柄)\\n";
    std::cout << "  • 文本渲染和字体支持\\n";
    std::cout << "  • 纹理和着色器支持\\n";
    std::cout << "  • C语言编写，C++友好\\n";
    
    return 0;
}
