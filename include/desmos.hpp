#ifndef DESMOS_DESMOS
#define DESMOS_DESMOS

#include <SDL2/SDL.h>
#include <vector>
#include <utility>
#include <stdexcept>
#include <math.h>
#include <algorithm>
#include "line.hpp"

#define PIX_NORMAL_TRUE_SIZE 0.125
#define FINEST_CELL_PIX_SIZE 20
#define AXIS_RGB_1 55
#define AXIS_RGB_2 100
#define EPS 1e-7
#define INF 1e4
#define FPS 60

class desmos
{
private:
    struct dline
    {
        Line line;
        SDL_Color color;
        int thickness;

        dline(const Line& line, const SDL_Color& rgba_color, int thickness);
    };
    int h,w;
    double window_true_w,window_true_h;
    double pix_true_size;
    bool move_window{false};
    bool running{false};
    SDL_Rect win_rect;
    std::pair<Point,double> camera;
    SDL_Window *window{nullptr};
    SDL_Renderer *renderer{nullptr};

    const static inline std::vector<int> grid_color_levels = { 160, 200, 230 };

    std::vector<dline> lines;

    bool point_out_of_bounds(int x, int y);

    void draw_line(int x1, int y1, int x2, int y2, int thickness=1);
    void draw_grid();
    void drawOx(int y);
    void drawOy(int x);
    void update_window_true_dim();
    void on_event(const SDL_Event& event);
    void fill_background();
    void draw_lines();
public:
    desmos(int h, int w);
    void add_line(const Line& line, const SDL_Color& rgba_color, int thickness=1);
    void render();
};

#endif