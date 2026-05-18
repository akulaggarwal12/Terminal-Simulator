#include "aether.hpp"   // Own Header File
#include "raylib.h"     // Base for Graphics
#include <iostream>
#include <filesystem>   // Base for File Management
#include <fstream>      // For File Opening and some other functions
#include <sstream>      // For File Opening and some other functions
#include <vector>       
#include <iomanip>      // For Multiwords file / directory names
#include <string>       
namespace fs = std::filesystem;

// Terminal History Class
class Terminal {
    public:
        std::string text;
        Color color;
};

// Virtual Terminal
void Graphics(fs::path currentpath) {
    
    // Raylib Window
    int screen_width = 1400, screen_height = 800;
    InitWindow(screen_width ,screen_height , "AETHER");
    SetTargetFPS(60);
    
    // Double Press Declarations for Tab Functioning
    double previous_press = 0.0;
    bool double_press = false;
    const double double_press_duration = 0.25;
    
    // For different function results
    int flag = -1;
    
    // For Typing
    int cursor_pos = 0;
    std::string input = "";
    
    // All Necessary Vectors
    std::vector<Terminal> history;
    std::vector<std::string> data_list;
    std::vector<std::string> dir_list;
    std::vector<std::string> file_list;
    std::vector<std::string> cmd_history;
    
    // Scrolling Declarations
    static int maxy = 0;
    bool auto_scroll = false;
    float scroll_offset = 0.0f;
    
    // Background Adjustment
    Image image = LoadImage("Image.png");
    ImageResize(&image,screen_width, screen_height - 40);
    Texture2D background = LoadTextureFromImage(image);
    UnloadImage(image);
    
    // Graphics:
    while (!WindowShouldClose()) {
    
        // Basic Window Details
        screen_width = GetScreenWidth();
        screen_height = GetScreenHeight();
        DrawTexture(background, 0, 40, RAYWHITE);
        
        // For typing, Graphics ordinate and scrolling
        int key = GetCharPressed();
        int y;
        int wheel = (int)GetMouseWheelMove();
        
        // Toggle Full Screen
        if (IsKeyPressed (KEY_F11)) {
        
            ToggleFullscreen();
            screen_width = GetScreenWidth();
            screen_height = GetScreenHeight();
            
            // Reloading Background
            image = LoadImage("Image.png");
            ImageResize(&image,screen_width, screen_height - 40);
            background = LoadTextureFromImage(image);
            UnloadImage(image);
        }
        
        // Tab Key Functioning
        if (IsKeyPressed (KEY_TAB)) {
        
            double current_press = GetTime();
            if (current_press - previous_press <= double_press_duration) {
                double_press = true;
                previous_press = 0;
            }
            else {
                double_press = false;
                previous_press = current_press;
            }
            
            // Calling Function
            flag = aether::tab_func(input, currentpath, double_press, data_list, dir_list, file_list);
            cursor_pos = input.length();
            
            // Function result for listing Data
            if (flag == 6) {
                history.push_back({"user@TechnOS:~ $ " + input, VIOLET});
                for (std::string data : dir_list)
                    history.push_back({data, DARKBLUE});
                for (std::string data : file_list)
                    history.push_back({data, SKYBLUE});
            }
        }
        
        // Active Line (Typing)
        while (key > 0) {
            if (key >= 32 && key <= 125) {
                
                // Inserting text between cursor and initial position
                input.insert(cursor_pos, 1, (char)key);
                cursor_pos ++;
            }
            key = GetCharPressed();
            auto_scroll = true;
        }
        
        // Deleting
        if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) && cursor_pos > 0) {
            
            // Deleting the text btw cursor and initial index
            input.erase(cursor_pos - 1, 1);
            cursor_pos--;
        }
        
        // Cursor Movement
        if ((IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) && cursor_pos > 0)
            cursor_pos--;
        if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) && cursor_pos < input.length())
            cursor_pos++;
            
        
        // Entering
        static int cmd_index;
        if (IsKeyPressed(KEY_ENTER)) {
        
            auto_scroll = true;
            history.push_back({"user@TechnOS:~ $ " + input, VIOLET});
            
            cmd_history.push_back(input);
            std::stringstream ss(input);
            std::string cmd;
            ss >> cmd;
            
            // Command Rule Book
            if (cmd == "touch") {
                flag = aether::touch_file(ss, currentpath);
                std::cout << flag << std::endl;
            }
            else if (cmd == "rename") {
                flag = aether::rename_file(ss, currentpath);
                std::cout << flag << std::endl;
            }
            else if (cmd == "open") {
                flag = aether::open_file(ss, currentpath);
                std::cout << flag << std::endl;
            }
            else if (cmd == "cd") {
                flag = aether::change_dir(ss, &currentpath);
                std::cout << flag << std::endl;
            }
            else if (cmd == "mkdir") {
                flag = aether::make_dir(ss, currentpath);
                std::cout << flag << std::endl;
            }
            else if (cmd == "del") {
                flag = aether::remove(ss, currentpath);
                std::cout << flag << std::endl;
            }
            else if (cmd == "ls") {
                flag = aether::list (currentpath, data_list, dir_list, file_list);
                std::cout << flag << std::endl;
            }
            else if (cmd == "help") {
                flag = 7;
                std::cout << flag << std::endl;
            }
            else if (cmd == "clear") {
                flag = 1;
                history.clear();
            }
            else if (cmd == "gedit") {
                flag = aether::gedit_file(ss, currentpath);
                std::cout << flag << std::endl;
            }
            else if (cmd == "nano") {
                flag = aether::nano_file(ss, currentpath);
                std::cout << flag << std::endl;
            }
            else if (cmd == "move") {
                flag = aether::move_file(ss, currentpath);
                std::cout << flag << std::endl;
            }
            else if (cmd == "copy") {
                flag = aether::copy_file(ss, currentpath);
                std::cout << flag << std::endl;
            }
            else if (cmd == "dup") {
                flag = aether::duplicate_file(ss, currentpath);
                std::cout << flag << std::endl;
            }
            else {
                flag = 8;
                std::cout << flag << std::endl;
            }
            
            // Reset
            input = "";
            cursor_pos = 0;
            cmd_index = cmd_history.size();
            
            
            // History Saving
            if (flag == 0) {
                std::string msg = "(Given File / Directory Already Exists.)";
                history.push_back({msg, WHITE});
            }
            else if (flag == 2) {
                std::string msg = "(Given Command Is Incomplete.)";
                history.push_back({msg, WHITE});
            }
            else if (flag == 3) {
                std::string msg = "(Given File / Directory Doesn't Exists.)";
                history.push_back({msg, WHITE});
            }
            else if (flag == 4) {
                std::string msg = "(New File Name Already Exists.)";
                history.push_back({msg, WHITE});
            }
            else if (flag == 5) {
                std::string msg = "(Items Have Been Deleted)";
                history.push_back({msg, WHITE}); 
            }
            else if (flag == 6) {
                for (std::string data : dir_list)
                    history.push_back({data, DARKBLUE});
                for (std::string data : file_list)
                    history.push_back({data, SKYBLUE});
            }
            else if (flag == 7) {
                std::vector<std::string> msg;
                msg.push_back("Available Commands are: ");
                msg.push_back("1 - touch filename");
                msg.push_back(":: Create the file");
                msg.push_back("2 - rename oldname newname");
                msg.push_back(":: Renaming the file / Folder");
                msg.push_back("3 - open filename");
                msg.push_back(":: Opening the file");
                msg.push_back("4 - gedit filename");
                msg.push_back(":: Opening the file using gedit editor");
                msg.push_back("5 - nano filename");
                msg.push_back(":: Opening the file using nano editor");
                msg.push_back("6 - cd directoryname");
                msg.push_back(":: Change the Directory");
                msg.push_back("7 - mkdir directoryname");
                msg.push_back(":: Create Directory");
                msg.push_back("8 - del name");
                msg.push_back(":: Deleting File / Folder");
                msg.push_back("9 - ls");
                msg.push_back(":: List of files and folders");
                msg.push_back("10 - help");
                msg.push_back(":: Shows all available commands");
                msg.push_back("11 - clear");
                msg.push_back(":: Clear all the previous results");
                msg.push_back("12 - dup name");
                msg.push_back(":: Copy the File or Directory in same Parent path");
                msg.push_back("13 - copy name destination");
                msg.push_back(":: Copies the File or Directory to the destination Path");
                msg.push_back("14 - move name destination");
                msg.push_back(":: Cut the File or Directory to the destination Path");
                for (int i = 0; i < msg.size(); i++)
                    history.push_back({msg[i], YELLOW});
            }
            else if (flag == 8) {
                std::string msg = "(Command Invalid.)";
                history.push_back({msg, WHITE});
            }
        }
        
        
        // Command History
        if (IsKeyPressed(KEY_UP) && cmd_index > 0) {
            cmd_index --;
            auto_scroll = true;
            input = cmd_history[cmd_index];
            cursor_pos = input.length();
        }
        
        if (IsKeyPressed(KEY_DOWN) && cmd_index < cmd_history.size()) {
            cmd_index ++;
            auto_scroll = true;
            
            if (cmd_index == cmd_history.size()) {
                input = "";
                cursor_pos = 0;
            }
            else {
                input = cmd_history[cmd_index];
                cursor_pos = input.length();
            }
        }
        
        //Back Button
        Vector2 mouse_pos = GetMousePosition();
        Vector2 centre = {30.0, 20.0};
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointCircle(mouse_pos, centre, 15.0))
                currentpath = currentpath.parent_path();
        }
        
        // Auto Scrolling
        if (auto_scroll) {
        
            int calc_y = 50; 
            int fontx = 20;
            
            // Calculating the max y ordinate for auto-scrolling offset
            for (int i = 0; i < history.size(); i++) {
                if (ColorToInt(history[i].color) == ColorToInt(SKYBLUE) || ColorToInt(history[i].color) == ColorToInt(DARKBLUE)) {
                    if (i > 0 && ColorToInt(history[i - 1].color) == ColorToInt(VIOLET))
                        fontx = 20;
                    if (fontx > screen_width - 150) {
                        fontx = 20;
                        calc_y += 20;
                    }
                    fontx += 160;
                    if (i + 1 == history.size() || ColorToInt(history[i + 1].color) == ColorToInt(VIOLET))
                        calc_y += 25;
                }
                else if (ColorToInt(history[i].color) == ColorToInt(YELLOW)) {
                    calc_y += 20;
                    for (int j = 1; j <= 28; j += 2)
                        calc_y += 20;
                    
                    i += 28;
                    if (i + 1 == history.size() || ColorToInt(history[i + 1].color) == ColorToInt(VIOLET))
                        calc_y += 5;
                }
                else {
                    if (i + 1 < history.size() && ColorToInt(history[i + 1].color) == ColorToInt(VIOLET))
                        calc_y += 25;
                    else
                        calc_y += 20;
                }
            }
            
            calc_y += 25;
            maxy = calc_y;
            
            // Necessary offset needed until autoscroll ends
            int autoscroll = screen_height - 50 - maxy;
            if (autoscroll < 0) {
                scroll_offset = autoscroll;
            }
            auto_scroll = false;
        }
        
        BeginDrawing();
            ClearBackground(BLACK);
            
            // Scrolling
            int maxscroll = 0;
            int minscroll = screen_height - 50 - maxy;
            if (maxy + 50 > screen_height) {
                scroll_offset += wheel * 40;
                if (scroll_offset > maxscroll)
                    scroll_offset = maxscroll;
                else if (scroll_offset < minscroll)
                    scroll_offset = minscroll;
            }
            else 
                scroll_offset = 0;
            y = scroll_offset + 50;
        
            // Ribbon 
            DrawRectangle(0, 0, screen_width, 40, GRAY);
            DrawText(currentpath.c_str(), 60, 10, 20, BLACK);
            DrawText("Press F11 For Fullscreen Toggle", screen_width - MeasureText("Press F11 For Fullscreen Toggle", 20) - 15, 10, 20, BLACK);
            
            // Back Button
            DrawCircle(30, 20, 15.0, BLACK);
            DrawText("<", 25, 7, 30, LIGHTGRAY);
            
            BeginScissorMode(0, 50, screen_width, screen_height - 50);
            
            // Output Previous Commands and Results
            int fontx = 20;
            for (int i = 0; i < history.size(); i++) {
                int fontsize = (ColorToInt(history[i].color) == ColorToInt(VIOLET)) ? 20 : 15;
                
                // For Listing Files, Folders
                if (ColorToInt(history[i].color) == ColorToInt(SKYBLUE) || ColorToInt(history[i].color) == ColorToInt(DARKBLUE)) {
                    if (ColorToInt(history[i - 1].color) == ColorToInt(VIOLET))
                        fontx = 20;
                    if (fontx > screen_width - 150) {
                        fontx = 20;
                        y += 20;
                    }
                    int fontlen = MeasureText(history[i].text.c_str(), fontsize);
                    
                    if (fontlen < 150)
                        DrawText(history[i].text.c_str(), fontx, y, fontsize, history[i].color);
                    else
                        DrawText(TextFormat("%.*s...", 11, history[i].text.c_str()), fontx, y, fontsize, history[i].color);
                    
                    fontx += 160;
                    if (i + 1 == history.size() || ColorToInt(history[i + 1].color) == ColorToInt(VIOLET))
                        y += 25;
                }
                
                // Help Commands
                else if (ColorToInt(history[i].color) == ColorToInt(YELLOW)) {
                    DrawText(history[i].text.c_str(), 20, y, fontsize, history[i].color);
                    y += 20;
                    for (int j = 1; j <= 28; j += 2) {
                        DrawText(history[i + j].text.c_str(), 20, y, fontsize, history[i + j].color);
                        DrawText(history[i + j + 1].text.c_str(), 300, y, fontsize, history[i + j + 1].color);
                        y += 20;
                    }
                    i += 28;
                    if (i + 1 == history.size() || ColorToInt(history[i + 1].color) == ColorToInt(VIOLET))
                        y += 5;
                }
                else {
                    DrawText(history[i].text.c_str(), 20, y, fontsize, history[i].color);
                    
                    // Command history display
                    if (ColorToInt(history[i + 1].color) == ColorToInt(VIOLET))
                        y += 25;
                    else
                        y += 20;
                }
            }
            
            
            // New Line
            int inputX = 20 + MeasureText("user@TechnOS:~ $ ", 20) + 10;
            DrawText("user@TechnOS:~ $ ", 20, y, 20, ORANGE);
            DrawText(input.c_str(), inputX, y, 20, GREEN);
            
            // Blinking Cursor Logic
            if (((int)(GetTime() * 2)) % 2 == 0) {
                int cursorX = inputX + MeasureText(input.substr(0, cursor_pos).c_str(), 20);
                DrawText("|", cursorX, y, 20, DARKGREEN);
            }
            y += 25;
            maxy = y - (int)scroll_offset;
            
            
        
        EndScissorMode();
        EndDrawing();
    }
    CloseWindow();
}


int main () {
    fs::path root_path = fs::current_path();
    Graphics(root_path);
    return 0;
}
