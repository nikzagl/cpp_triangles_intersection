#include "../include/desmos.hpp"
#include <iostream>

desmos::dline::dline(const Line& line, const SDL_Color& rgba_color, int thickness) : line(line), color(rgba_color), thickness(thickness) {}

desmos::desmos(int h, int w) : h(h), w(w)
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        throw std::runtime_error("Failed to initialize SDL.");
    this->window = SDL_CreateWindow("desmos",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w+1,h+1,SDL_WINDOW_SHOWN);
    if(!this->window)
        throw std::runtime_error("Failed to create SDL window.");
    this->win_rect.x = 0;
    this->win_rect.y = 0;
    this->win_rect.w = w+1;
    this->win_rect.h = h+1;
    this->camera.second = 1;
    this->camera.first.x = -25.25;
    this->camera.first.y = 10;
    this->renderer = SDL_CreateRenderer(this->window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!this->renderer)
        throw std::runtime_error("Failed to create SDL window.");
}

bool desmos::point_out_of_bounds(int x, int y) { return x < 0 or x > this->w or y < 0 or y > this->h; }

void desmos::draw_line(int x1, int y1, int x2, int y2, int thickness)
{
    /*
    if(this->point_out_of_bounds(x1,y1) and this->point_out_of_bounds(x2,y2))
        return;
    else if(this->point_out_of_bounds(x1,y1))
    {
        std::swap(x1,x2);
        std::swap(y1,y2);
    }
    */
    double angle = (x2-x1) == 0 ? (y2-y1) < 0 ? 270 : 90 : atan(double(y2-y1)/double(x2-x1))/M_PI*180 + ((x2 - x1) < 0 ? 180 : 0);
    y1 += thickness/2;

    SDL_Rect rect;
    rect.x = x1;
    rect.y = y1;
    rect.w = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
    rect.h = thickness;

    SDL_Texture *texture = SDL_CreateTexture(this->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,1,1);
    SDL_SetRenderTarget(this->renderer,texture);
    SDL_RenderDrawPoint(this->renderer,0,0);
    SDL_SetRenderTarget(this->renderer,NULL);

    SDL_Point center = {0,-thickness/2};
    SDL_RenderCopyEx(this->renderer,texture,NULL,&rect,angle,&center,SDL_FLIP_NONE);
}

void desmos::add_line(const Line& line, const SDL_Color& rgba_color, int thickness)
{
    this->lines.push_back(dline(line,rgba_color,thickness));
}

void desmos::drawOx(int y)
{
    SDL_SetRenderDrawColor(this->renderer,AXIS_RGB_1,AXIS_RGB_1,AXIS_RGB_1,255);
    SDL_RenderDrawLine(this->renderer,0,y,this->w-1,y);
    SDL_SetRenderDrawColor(this->renderer,AXIS_RGB_2,AXIS_RGB_2,AXIS_RGB_2,255);
    SDL_RenderDrawLine(this->renderer,0,y+1,this->w-1,y+1);
}

void desmos::drawOy(int x)
{
    SDL_SetRenderDrawColor(this->renderer,AXIS_RGB_1,AXIS_RGB_1,AXIS_RGB_1,255);
    SDL_RenderDrawLine(this->renderer,x,0,x,this->h-1);
    SDL_SetRenderDrawColor(this->renderer,AXIS_RGB_2,AXIS_RGB_2,AXIS_RGB_2,255);
    SDL_RenderDrawLine(this->renderer,x+1,0,x+1,this->h-1);
}

template<typename T>
double log5(T x) { return log(x)/log(5); }

int get_granularity(double x, int min_log5, int max_log5)
{
    for(int curr_log5 = max_log5; curr_log5 >= min_log5; --curr_log5)
    {
        double grain = pow(5,curr_log5);
        if(std::abs(round(x/grain)-x/grain) < EPS)
            return curr_log5;
    }
    throw std::invalid_argument("BUG. Failed to get granularity.");
}

void desmos::draw_grid()
{
    SDL_SetRenderDrawColor(this->renderer,171,157,144,150);
    this->update_window_true_dim();
    int max_cell_true_size_log = ceil(log5(std::min(window_true_h,window_true_w)));
    double max_cell_true_size = pow(5,max_cell_true_size_log);
    int min_cell_true_size_log = ceil(log5(FINEST_CELL_PIX_SIZE*pix_true_size));
    double min_cell_true_size = pow(5,min_cell_true_size_log);
    int min_cell_pix_size = min_cell_true_size/pix_true_size;
    double left_most_vert_line_true = (this->camera.first.x < 0 ? floor(this->camera.first.x/min_cell_true_size) : ceil(this->camera.first.x/min_cell_true_size))*min_cell_true_size;
    double left_most_vert_line_pix = std::abs(this->camera.first.x-left_most_vert_line_true)/pix_true_size;
    for(double curr_vert_line_true = left_most_vert_line_true; curr_vert_line_true < this->camera.first.x+window_true_w; curr_vert_line_true += min_cell_true_size)
    {
        int curr_vert_line_pix = (curr_vert_line_true-this->camera.first.x)/pix_true_size;
        int curr_granularity = get_granularity(curr_vert_line_true,min_cell_true_size_log,max_cell_true_size_log);
        int curr_rgb = this->grid_color_levels[std::min((int)this->grid_color_levels.size()-1,max_cell_true_size_log-curr_granularity)];
        SDL_SetRenderDrawColor(this->renderer,curr_rgb,curr_rgb,curr_rgb,255);
        this->draw_line(curr_vert_line_pix,0,curr_vert_line_pix,this->h-1);
    }

    double up_most_hor_line_true = (this->camera.first.y < 0 ? floor(this->camera.first.y/min_cell_true_size) : ceil(this->camera.first.y/min_cell_true_size))*min_cell_true_size;
    double up_most_hor_line_pix = std::abs(this->camera.first.y-up_most_hor_line_true)/pix_true_size;
    for(double curr_hor_line_true = up_most_hor_line_true; curr_hor_line_true > this->camera.first.y-window_true_h; curr_hor_line_true -= min_cell_true_size)
    {
        int curr_hor_line_pix = (this->camera.first.y-curr_hor_line_true)/pix_true_size;
        int curr_granularity = get_granularity(curr_hor_line_true,min_cell_true_size_log,max_cell_true_size_log);
        int curr_rgb = this->grid_color_levels[std::min((int)this->grid_color_levels.size()-1,max_cell_true_size_log-curr_granularity)];
        SDL_SetRenderDrawColor(this->renderer,curr_rgb,curr_rgb,curr_rgb,255);
        this->draw_line(0,curr_hor_line_pix,this->w-1,curr_hor_line_pix);
    }
    if(this->camera.first.x < 0 and this->camera.first.x > -window_true_w)
    {
        int oy_pix = -this->camera.first.x/pix_true_size;
        this->drawOy(oy_pix);
    }
    if(this->camera.first.y > 0 and this->camera.first.y < window_true_h)
    {
        int ox_pix = this->camera.first.y/pix_true_size;
        this->drawOx(ox_pix);
    }
}

void desmos::update_window_true_dim()
{
    this->pix_true_size = (PIX_NORMAL_TRUE_SIZE*this->camera.second);
    this->window_true_h = (double)this->h*pix_true_size;
    this->window_true_w = (double)this->w*pix_true_size;
}

void desmos::on_event(const SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT)
                this->move_window = true;
            break;
        case SDL_MOUSEBUTTONUP:
            if(event.button.button == SDL_BUTTON_LEFT)
                this->move_window = false;
            break;
        case SDL_MOUSEMOTION:
            if(move_window)
            {
                this->update_window_true_dim();
                this->camera.first.x -= (double)event.motion.xrel/this->w*window_true_w;
                this->camera.first.y += (double)event.motion.yrel/this->h*window_true_h;
            }
            break;
        case SDL_MOUSEWHEEL:
            this->camera.second -= (double)event.wheel.y*this->camera.second*0.125;
            break;
        case SDL_QUIT:
            this->running = false;
            break;
    }
}

void desmos::fill_background()
{
    SDL_SetRenderDrawColor(this->renderer,253,239,226,255);
    SDL_RenderFillRect(this->renderer,&this->win_rect);
}

void desmos::draw_lines()
{
    this->update_window_true_dim();
    for(const auto& line : this->lines)
    {
        SDL_SetRenderDrawColor(this->renderer,line.color.r,line.color.g,line.color.b,line.color.a);
        int line_x1_pix = (line.line.first_point().x-this->camera.first.x)/this->pix_true_size;
        int line_y1_pix = (this->camera.first.y-line.line.first_point().y)/this->pix_true_size;
        int line_x2_pix = (line.line.second_point().x-this->camera.first.x)/this->pix_true_size;
        int line_y2_pix = (this->camera.first.y-line.line.second_point().y)/this->pix_true_size;
        this->draw_line(line_x1_pix,line_y1_pix,line_x2_pix,line_y2_pix,line.thickness);
    }
}

void desmos::render()
{
    SDL_Event event;
    this->running = true;
    while(this->running)
    {
        while(SDL_PollEvent(&event))
            this->on_event(event);

        this->fill_background();
        this->draw_grid();
        this->draw_lines();

        SDL_RenderPresent(this->renderer);
        SDL_Delay(1000/FPS);
    }
}