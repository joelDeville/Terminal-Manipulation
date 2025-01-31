# Terminal-Manipulation
Personal project toying with terminal manipulation for Valentine's Day

This project uses a branching approach depending on if it is running on a windows or linux system.
The largest difference is the usage of Ascii art for the acceptance message.
- In Windows, this will be a rotating single-line message
- In Linux, this will be a rotating ASCII art piece with the same message

I used curses for the implementation of the rotating ASCII art on Linux.
Also, many props to this text to Ascii art generator I found, which greatly sped up the process: https://patorjk.com/software/taag/

Notable features of this program:
- Input checking and variable responses for different length/types of messages
- Terminal manipulation with rewriting over prior printed lines
- Linux/Windows compatibility using branching logic
- Usage of system commands (such as fflush and nanosleep) to messages are printed when they should be
- Fun Ascii art
