#include <ncurses.h>
#include <string.h>

#define DEFAULT_Y (25)
#define DEFAULT_X (80)

#define BORDER_SIZE (2)

#define OFFSET (1)

int main(void)
{
    initscr(); // start ncurses

    const int size_y = DEFAULT_Y + BORDER_SIZE;
    const int size_x = DEFAULT_X + BORDER_SIZE;

    const int physical_y = LINES; // <- this variable contains physical y size
    const int physical_x = COLS;  // <- this variable contains physical x size

    const int centered_y = (physical_y - size_y) / 2;
    const int centered_x = (physical_x - size_x) / 2;

    //                         size
    //                   ..............
    WINDOW *win = newwin(size_y, size_x, centered_y, centered_x);
    //                                   ......................     
    //                                   position on the screen

    // TRUE and FALSE can be used !
    //             v
    nodelay(win, true); // user input doesn't stop the program

    // noecho();     <- user input isn't displayed on the screen
    // curs_set(0);  <- hides cursor

    box(win, 0, 0); // border
                    
    int y = 0;
    int x = 0;


    wmove(win, OFFSET + y, OFFSET + x);
    wprintw(win, "current frame is: ");

    //   ^
    //  same
    //   v
    // wmvprintw(wim, OFFSET + y, OFFSET + x, "current frame is:");


    // NOT IMPORTANT:
    {
        const int cols_taken_by_string = strlen("Press 'q' to exit");

        int string_centered_y = size_y / 2;
        int string_centered_x = (size_x - cols_taken_by_string)  / 2;


        wmove(win, string_centered_y, string_centered_x);
        wprintw(win, "Press 'q' to exit");
    }

    unsigned int counter = 0;
    int input = 0;  

    int string_length = strlen("current frame is: ");

    do
    {
        //    refreshes the screen
        //           v
        input = wgetch(win);

        //            moving cursor here
        //                     v         
        //  "current frame is: "
        //
        wmove(win, OFFSET + y, OFFSET + x + string_length);
        wprintw(win, "%u", counter);

        counter++;
    }
    while(input != 'q');

    delwin(win); // clear before exiting

    endwin(); // end ncurses
    return 0;
}
