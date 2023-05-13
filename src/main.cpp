#include "GUI.hpp"
#include "triangle.hpp"
int main(){
    Triangle tr1 = Triangle({{{0, 0},{2, 3},{4,0}}});
    Triangle tr2 = Triangle({{{0,2},{2,-1},{4,2}}});
    std::vector<Point> intersections = tr1.get_intersection(tr2);
    UserInterface window;
    window.Run();
    //check correct data

}