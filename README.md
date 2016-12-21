# smux
My terminal multiplexer.
This project is intended to be a simple clone of tmux with limited functionality.

It works through having a separate thread for each terminal pane with its own pseudoterminal slave and master. The ncurses library is used to display the multiple panes, and interthread communication is done via global variables and pthread conditional variables.
