//
// Written by JoyWonderful.
// ColorfulToDisplay
//

/**
 * @file clrftodsp.h
 * @author JoyWonderful
 * ColorfulToDisplay.
 * 模拟一个人正在输入，删除字。
 * 若要输出中文，请执行 init() 函数。
 * 包含头文件编译，请将 #include "clrftodsp.h" 添置代码头部，将你写的文件和我写的头文件放在一起，再编译。注意，不是 <> 而是 "" 。
*/

#include <windows.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;


/**
 * @brief  一个一个地输出字符。（默认换行） \n Output the characters one by one.(default line break)
 * @param  _str    一个字符串，这是你想要输出的字符串。 \n A string, which is the string you want to output.
 * @param  _time   一个整数，这是每个字符输出之后你想要停顿的时间。 \n An integer, that is the time you want to pause after each character output.
 * @return 无。 \n Nothing.
*/
void write_word(string _str, int _time)
{
    for(int i = 0; i < _str.length(); i ++)
    {
        cout << _str[i] ;
        Sleep(_time) ;
    }
    cout << endl ;
}

/**
 * @brief  一个一个地输出字符。 \n Output the characters one by one.
 * @param  _str    一个字符串，这是你想要输出的字符串。 \n A string, which is the string you want to output.
 * @param  _time   一个整数，这是每个字符输出之后你想要停顿的时间。 \n An integer, that is the time you want to pause after each character output.
 * @param  _isend  一个布尔值，这是你想不想换行的表示。 \n A boolean value, which is an indication of whether you want to break the line or not.
 * @return 无。 \n Nothing.
*/
void write_word(string _str, int _time, bool _isend)
{
    for(int i = 0; i < _str.length(); i ++)
    {
        cout << _str[i] ;
        Sleep(_time) ;
    }
    if(_isend) cout << endl ;
}

/**
 * @brief  一个一个地输出字符。（默认换行、随机时间） \n Output the characters one by one.(default line break, random time)
 * @param  _str    一个字符串，这是你想要输出的字符串。 \n A string, which is the string you want to output.
 * @param  _ltime  一个整数，这是每个字符输出之后你想要停顿的时间左边界。 \n An integer, that is the left boundary of the time you want to pause after each character output.
 * @param  _rtime  一个整数，这是每个字符输出之后你想要停顿的时间右边界。 \n An integer, that is the right boundary of the time you want to pause after each character output.
 * @return 无。 \n Nothing.
*/
void write_word(string _str, int _ltime, int _rtime)
{
    for(int i = 0; i < _str.length(); i ++)
    {
        cout << _str[i] ;
        srand((unsigned)time(NULL)) ;
        int sleep_time = _ltime + (int)_rtime * rand() / (RAND_MAX + 1) ;
        // cout << "sleep seconds:" << sleep_time << endl ;
        Sleep(sleep_time) ;
    }
    cout << endl ;
}

/**
 * @brief  一个一个地输出字符。（随机时间） \n Output the characters one by one.(random time)
 * @param  _str    一个字符串，这是你想要输出的字符串。 \n A string, which is the string you want to output.
 * @param  _ltime  一个整数，这是每个字符输出之后你想要停顿的时间左边界。 \n An integer, that is the left boundary of the time you want to pause after each character output.
 * @param  _rtime  一个整数，这是每个字符输出之后你想要停顿的时间右边界。 \n An integer, that is the right boundary of the time you want to pause after each character output.
 * @param  _isend  一个布尔值，这是你想不想换行的表示。 \n A boolean value, which is an indication of whether you want to break the line or not.
 * @return 无。 \n Nothing.
*/
void write_word(string _str, int _ltime, int _rtime, bool _isend)
{
    for(int i = 0; i < _str.length(); i ++)
    {
        cout << _str[i] ;
        srand((unsigned)time(NULL)) ;
        int sleep_time = _ltime + (int)_rtime * rand() / (RAND_MAX + 1) ;
        // cout << "sleep seconds:" << sleep_time << endl ;
        Sleep(sleep_time) ;
    }
    if(_isend) cout << endl ;
}


/**
 * @brief  清除当前行的所有字符。 \n Clears all characters for the current line.
 * @note
 *  不显示光标，没有时间停顿，这是一个功能而已，不是拿来吸引观众的。若你想清除 `write_word()` 输出的内容， \n 
 *  请将 `_isend` 改为 `false`。  \n \n
 *  No cursor, no time to pause, this is just a feature, not to attract the audience. If you want \n
 *  to clear the `write_word()` output, change `_isend` to 'false'.
 * @return  无。 \n Nothing.
*/
void clearline()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
    CONSOLE_SCREEN_BUFFER_INFO bInfo ;
    GetConsoleScreenBufferInfo(hOut, &bInfo) ;
    int my_y = bInfo.dwCursorPosition.Y ;
    // cout << my_y ;
    CONSOLE_CURSOR_INFO mycursorinfo ;
    mycursorinfo.bVisible = FALSE ;
    mycursorinfo.dwSize = 1;
    SetConsoleCursorInfo(hOut, &mycursorinfo) ;
    for(int i = bInfo.srWindow.Right; i >= 0; i --)
    {
        COORD pos = {i, my_y} ;
        // cout << bInfo.dwCursorPosition.Y << endl ;
        SetConsoleCursorPosition(hOut, pos) ;
        cout << " " ;
    }
    mycursorinfo.bVisible = TRUE ;
    mycursorinfo.dwSize = 1;
    SetConsoleCursorInfo(hOut, &mycursorinfo) ;
}

/**
 * @brief  清除当前行的字符。 \n Clears the characters of the specified line.
 * @param  _issleep 一个布尔值，表示是否在清除一个字符后停顿3毫秒。 \n A Boolean value that indicates whether to pause for 3 milliseconds after clearing a character.
 * @return 无。 \n Nothing.
*/
void clearline(bool _issleep)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
    CONSOLE_SCREEN_BUFFER_INFO bInfo ;
    GetConsoleScreenBufferInfo(hOut, &bInfo) ;
    int my_y = bInfo.dwCursorPosition.Y ;
    // cout << my_y ;
    CONSOLE_CURSOR_INFO mycursorinfo ;
    mycursorinfo.bVisible = FALSE ;
    mycursorinfo.dwSize = 1;
    SetConsoleCursorInfo(hOut, &mycursorinfo) ;
    for(int i = bInfo.srWindow.Right; i >= 0; i --)
    {
        COORD pos = {i, my_y} ;
        // cout << bInfo.dwCursorPosition.Y << endl ;
        SetConsoleCursorPosition(hOut, pos) ;
        cout << " " ;
        if(_issleep) Sleep(3) ;
    }
    mycursorinfo.bVisible = TRUE ;
    mycursorinfo.dwSize = 1;
    SetConsoleCursorInfo(hOut, &mycursorinfo) ;
    COORD pos = {0, my_y} ;
    SetConsoleCursorPosition(hOut, pos) ;
}

/**
 * @brief  清除指定行的字符。 \n Clears the characters of the specified line.
 * @param  _lineid  一个整数，表示你想清除的行的行号。（从1开始） \n An integer that represents the line number of the row you want to clear. (from 1)
 * @param  _issleep 一个布尔值，表示是否在清除一个字符后停顿3毫秒。 \n A Boolean value that indicates whether to pause for 3 milliseconds after clearing a character.
 * @return 无。 \n Nothing.
*/
void clearline(int _lineid, bool _issleep)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
    CONSOLE_SCREEN_BUFFER_INFO bInfo ;
    GetConsoleScreenBufferInfo(hOut, &bInfo) ;
    for(int i = bInfo.srWindow.Right; i >= 0; i --)
    {
        COORD pos = {i, _lineid - 1} ;
        SetConsoleCursorPosition(hOut, pos) ;
        cout << " " ;
        if(_issleep) Sleep(3) ;
    }
    COORD pos = {0, _lineid - 1} ;
    SetConsoleCursorPosition(hOut, pos) ;
}

/**
 * @brief  清除指定行的字符。 \n Clears the characters of the specified line.
 * @param  _lineid  一个整数，表示你想清除的行的行号。（从1开始） \n An integer that represents the line number of the row you want to clear. (from 1)
 * @param  _issleep 一个布尔值，表示是否在清除一个字符后停顿3毫秒。 \n A Boolean value that indicates whether to pause for 3 milliseconds after clearing a character.
 * @param  _ishide  一个布尔值，表示你是否想隐藏光标。 \n A Boolean value that indicates whether you want to hide the cursor.
 * @return 无。 \n Nothing.
*/
void clearline(int _lineid, bool _issleep, bool _ishide)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
    CONSOLE_SCREEN_BUFFER_INFO bInfo ;
    GetConsoleScreenBufferInfo(hOut, &bInfo) ;
    CONSOLE_CURSOR_INFO mycursorinfo ;
    mycursorinfo.bVisible = FALSE ;
    mycursorinfo.dwSize = 1;
    if(_ishide) SetConsoleCursorInfo(hOut, &mycursorinfo) ;
    for(int i = bInfo.srWindow.Right; i >= 0; i --)
    {
        COORD pos = {i, _lineid - 1} ;
        SetConsoleCursorPosition(hOut, pos) ;
        cout << " " ;
        if(_issleep) Sleep(3) ;
    }
    mycursorinfo.bVisible = TRUE ;
    mycursorinfo.dwSize = 1;
    SetConsoleCursorInfo(hOut, &mycursorinfo) ;
    COORD pos = {0, _lineid - 1} ;
    SetConsoleCursorPosition(hOut, pos) ;
}

/**
 * @brief  清除全部字符。若不想要停顿，直接在代码中插入`system("cls")`即可，它只是拿来美化用的。 \n Clear all characters.
 * @attention
 *  清除之后，光标将回到(0, 0)，即控制台窗口的左上角。 \n Once cleared, the cursor will return to (0, 0), which is the upper-left corner of the console window.
 * @return 无。 \n Nothing.
*/
void clear_all()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
    CONSOLE_SCREEN_BUFFER_INFO bInfo ;
    GetConsoleScreenBufferInfo(hOut, &bInfo) ;
    for(int i = bInfo.dwCursorPosition.Y; i >= 0; i --)
    {
        for(int j = bInfo.srWindow.Right; j >= 0; j --)
        {
            COORD pos = {j, i} ;
            SetConsoleCursorPosition(hOut, pos) ;
            cout << " " ;
            Sleep(1) ;
        }
    }
    COORD pos = {0, 0} ;
    SetConsoleCursorPosition(hOut, pos) ;
}


/**
 * @brief  在指定行滚动字符。 \n Scrolling characters on the specified line.
 * @param  _str    一个字符串，表示你想滚动的字符。 \n A string that represents the character you want to scroll.
 * @param  _lineid 一个整数，表示你想滚动字符行的行号。 \n An integer that represents the line number of the character line you want to scroll.
 * @return 无。Nothing.
*/
void scroll_word(string _str, int _lineid)
{
    int chs = 0 ;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
    CONSOLE_SCREEN_BUFFER_INFO bInfo ;
    GetConsoleScreenBufferInfo(hOut, &bInfo) ;
    CONSOLE_CURSOR_INFO mycursorinfo ;
    mycursorinfo.bVisible = FALSE ;
    mycursorinfo.dwSize = 1;
    SetConsoleCursorInfo(hOut, &mycursorinfo) ;
    // for(int i = 0; i < _str.length(); i ++)
    // {
    //     if(include_chinese(_str)) continue ;
    //     else chs ++ ;
    // }
    // chs /= 2 ;
    // cout << "chs: " << chs << endl ;
    // Sleep(3000) ;
    for(int i = 0; i < bInfo.srWindow.Right + 1 - _str.length() + chs; i ++)
    {
        clearline(_lineid, false) ;
        for(int j = 0; j < i; j ++) cout << " " ;
        cout << _str << endl ;
        Sleep(30) ;
    }
    mycursorinfo.bVisible = TRUE ;
    mycursorinfo.dwSize = 1;
    SetConsoleCursorInfo(hOut, &mycursorinfo) ;
}

/**
 * @brief  在指定行滚动字符。 \n Scrolling characters on the specified line.
 * @param  _lineid 一个整数，表示你想滚动字符行的行号。 \n An integer that represents the line number of the character line you want to scroll.
 * @return 无 \n Nothing.
*/
void scroll_word(string _str)
{
    int chs = 0 ;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
    CONSOLE_SCREEN_BUFFER_INFO bInfo ;
    GetConsoleScreenBufferInfo(hOut, &bInfo) ;
    CONSOLE_CURSOR_INFO mycursorinfo ;
    mycursorinfo.bVisible = FALSE ;
    mycursorinfo.dwSize = 1;
    SetConsoleCursorInfo(hOut, &mycursorinfo) ;
    // for(int i = 0; i < _str.length(); i ++)
    // {
    //     if(include_chinese(_str)) continue ;
    //     else chs ++ ;
    // }
    // chs /= 2 ;
    // cout << "chs: " << chs << endl ;
    // Sleep(3000) ;
    for(int i = 0; i < bInfo.srWindow.Right + 1 - _str.length() + chs; i ++)
    {
        clearline() ;
        for(int j = 0; j < i; j ++) cout << " " ;
        cout << _str ;
        Sleep(30) ;
    }
    mycursorinfo.bVisible = TRUE ;
    mycursorinfo.dwSize = 1;
    SetConsoleCursorInfo(hOut, &mycursorinfo) ;
}


/**
 * @brief  设置输出字符的前景色和后景色。 \n Sets the foreground and back colors of the output characters.
 * @param  _color 一个十六进制的数字。 \n 请以 `0x` 开头。格式为 `0x[前景色][背景色]` 。 \n 其中 0=黑色 1=蓝色 2=绿色 3=浅绿色 4=红色 5=紫色 6=黄色 7=白色 8=灰色 9=淡蓝色 A=淡绿色 B=淡浅绿色 C=淡红色 D=淡紫色 E=淡黄色 F=亮白色。更多信息，请打开命令行(cmd.exe)键入 `color /?` 回车。例如：0xfc 会在亮白色上产生淡红色。 \n \n A hexadecimal number. \n Please start with '0x'. The format is '0x[foreground color][background color]'. \n where 0=black 1=blue 2=green 3=light green 4=red 5=purple 6=yellow 7=white 8=gray 9=light blue A=pale green B=light light green C=pale red D=lilac E=pale yellow F=bright white. For more information, open the command line (cmd.exe) and type 'color /?' carriage enter. For example: 0xfc produces a reddish tinge on bright white.
 * @return 无。 \n Nothing.
*/
void setcolor(unsigned short _color)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
    WORD wr1 = _color ;
    SetConsoleTextAttribute(hOut, wr1) ;
}


/**
 * @brief  当你要输出中文时，建议你使用这个函数。否则可能会输出乱码。 \n When you want to output Chinese, it is recommended that you use this function. Otherwise, garbled characters may be output.
 * @return 无。 \n Nothing.
*/
void init()
{
    system("@echo off") ; 
    system("chcp 65001") ;
    setcolor(0x0f) ;
    system("cls") ;
}
