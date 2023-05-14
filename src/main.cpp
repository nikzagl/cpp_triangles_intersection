#include "GUI.hpp"
#include "triangle.hpp"
#include <gtest/gtest.h>
int main(){
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
    UserInterface window;
    window.Run();
    //check correct data

}