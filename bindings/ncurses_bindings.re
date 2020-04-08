open Ctypes;

type window = ptr(unit);

let window: typ(window) = ptr(void);

module Bindings = (F: Ctypes.FOREIGN) => {
  open F;
  let initscr = foreign("initscr", void @-> returning(window));
  let endwin = foreign("endwin", void @-> returning(void));
  let refresh = foreign("refresh", void @-> returning(void));
  let wrefresh = foreign("wrefresh", window @-> returning(void));
  let newwin =
    foreign("newwin", int @-> int @-> int @-> int @-> returning(window));
  let addch = foreign("addch", char @-> returning(void));
  let mvwaddch =
    foreign("mvwaddch", window @-> int @-> int @-> char @-> returning(void));
  let addstr = foreign("addstr", string @-> returning(void));
  let mvwaddstr =
    foreign(
      "mvwaddstr",
      window @-> int @-> int @-> string @-> returning(void),
    );
  let box = foreign("box", window @-> int @-> int @-> returning(void));
  let cbreak = foreign("cbreak", void @-> returning(void));
  let keypad = foreign("keypad", window @-> bool @-> returning(void));
  let getch = foreign("getch", void @-> returning(void));
  let wgetch = foreign("wgetch", window @-> returning(int));
  let getstr = foreign("getstr", ptr(char) @-> returning(void));
  let mvprintw =
    foreign(
      "mvprintw",
      int @-> int @-> string @-> ptr(char) @-> returning(void),
    );
};
