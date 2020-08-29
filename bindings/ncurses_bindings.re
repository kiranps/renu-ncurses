open Ctypes;

type window = ptr(unit);

let window: typ(window) = ptr(void);

module Bindings = (F: Ctypes.FOREIGN) => {
  open F;
  let initscr = foreign("initscr", void @-> returning(window));
  let endwin = foreign("endwin", void @-> returning(void));

  let cbreak = foreign("cbreak", void @-> returning(void));
  let echo = foreign("echo", void @-> returning(void));
  let noecho = foreign("noecho", void @-> returning(void));

  let refresh = foreign("refresh", void @-> returning(void));
  let wrefresh = foreign("wrefresh", window @-> returning(void));
  let newwin =
    foreign("newwin", int @-> int @-> int @-> int @-> returning(window));

  let subwin =
    foreign(
      "subwin",
      window @-> int @-> int @-> int @-> int @-> returning(window),
    );

  let addch = foreign("addch", char @-> returning(void));
  let addstr = foreign("addstr", string @-> returning(void));
  let mvwaddstr =
    foreign(
      "mvwaddstr",
      window @-> int @-> int @-> string @-> returning(void),
    );
  let box = foreign("box", window @-> int @-> int @-> returning(void));
  let keypad = foreign("keypad", window @-> bool @-> returning(void));
  let getch = foreign("getch", void @-> returning(void));
  let wgetch = foreign("wgetch", window @-> returning(int));
  let getstr = foreign("getstr", ptr(char) @-> returning(void));
  let mvprintw =
    foreign("mvprintw", int @-> int @-> string @-> returning(void));

  let wmove = foreign("wmove", window @-> int @-> int @-> returning(void));
  let mvwprintw =
    foreign(
      "mvwprintw",
      window @-> int @-> int @-> string @-> returning(void),
    );

  let mvwscanw =
    foreign(
      "mvwscanw",
      window @-> int @-> int @-> ptr(char) @-> returning(void),
    );

  let attron = foreign("attron", int @-> returning(void));
  let attroff = foreign("attroff", int @-> returning(void));

  let wattron = foreign("wattron", window @-> int @-> returning(void));
  let wattroff = foreign("wattroff", window @-> int @-> returning(void));

  let bkgd = foreign("bkgd", int @-> returning(void));
  let wbkgd = foreign("wbkgd", window @-> int @-> returning(void));

  let bkgdset = foreign("bkgdset", int @-> returning(void));
  let wbkgdset = foreign("wbkgdset", window @-> int @-> returning(void));

  /* Color */

  let start_color = foreign("start_color", void @-> returning(void));
  let can_change_color =
    foreign("can_change_color", void @-> returning(bool));
  let init_pair =
    foreign("init_pair", int @-> int @-> int @-> returning(void));

  let mvwhline =
    foreign(
      "mvwhline",
      window @-> int @-> int @-> int @-> int @-> returning(void),
    );
  let mvwvline =
    foreign(
      "mvwvline",
      window @-> int @-> int @-> int @-> int @-> returning(void),
    );

  let mvwaddch =
    foreign("mvwaddch", window @-> int @-> int @-> int @-> returning(void));

  let mvwaddch1 =
    foreign("mvwaddch", window @-> int @-> int @-> char @-> returning(void));
};
