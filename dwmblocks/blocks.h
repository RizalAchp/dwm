// if not defined the scripts use default
#ifndef SCRIPTDIR
#define CPU "cpu"
#define MEMORY "memory"
#define INTERNET "internet"
#define VOLUME "volume"
#define CLOCK "clock"
#endif

// Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
    /*Icon*/ /*Command*/ /*Update Interval*/ /*Update Signal*/

    {" 🌡  ", CPU,                 100, 1},
    {" 💻 ", MEMORY,              60, 1},
    {" 🌐 ", INTERNET,            60, 0},
    {" 🔊 ", VOLUME,              0, 10},
    {" 📅 ", CLOCK,               60, 0},

};

// sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim = ' ';
