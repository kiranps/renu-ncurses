module N = Ncurses_bindings.Bindings(Ncurses_generated);
open N;
open Ctypes;

type wstr =
  | String(string);

module TextN = {
  let createElement = (~x, ~y, ~win, ~value, ~children as _, ()) =>
    mvwaddstr(win, x, y, value);
};

module Text = {
  let createElement = (~value, ~children as _, ()) => String(value);
};

module Window = {
  let rec renderChildren = (win, children) => {
    switch (children) {
    | [String(value), ...tail] =>
      mvwaddstr(win, 1, 2, value);
      renderChildren(win, tail);
    | [] => ()
    };
  };

  let createElement = (~x, ~y, ~height, ~width, ~children=?, ()) => {
    let win = newwin(height, width, x, y);
    box(win, 0, 0);
    switch (children) {
    | Some(values) => renderChildren(win, values)
    | None => ()
    };
    win;
  };
};

module Input = {
  let createElement = (~children as _, ()) => {
    let win = <Window x=1 y=1 height=3 width=50 />;
    let data = allocate_n(char, ~count=80);
    getstr(data);
    /*keypad(win, true);*/
    /*let c = wgetch(win);*/
    /*if (c == 106) {*/
    /*mvwaddstr(win, 1, 2, "you typed " ++  );*/
    mvprintw(1, 2, "you typed  %s", data);
    /*};*/
    win;
  };
};

module MainWindow = {
  let createElement = (~children, ()) => {
    List.iter(x => wrefresh(x), children);
  };
};

let render = children => {
  let main_window = initscr();
  ignore(cbreak());
  box(main_window, 0, 0);
  refresh();
  children();
  let _a = getch();
  endwin();
};
