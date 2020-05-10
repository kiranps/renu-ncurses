module N = Ncurses_bindings.Bindings(Ncurses_generated);
open N;

type nodeType =
  | Div(int, int, int, int);

type dom =
  | Node(list(dom), nodeType)
  | Text(string);

module Div = {
  let createElement = (~x, ~y, ~height, ~width, ~children=[], ()) => {
    Node(children, Div(x, y, height, width));
  };
};

let s = x => Text(x);

let rec renderer = (node, parent) => {
  let (pwin, Div(px, py, ph, pw)) = parent;
  switch (node) {
  | Text(value) =>
    mvwprintw(pwin, 2, 2, value);
    wrefresh(pwin);
  | Node(children, Div(x, y, height, width)) =>
    let win = subwin(pwin, height, width, px + x, py + y);
    box(win, 0, 0);
    wrefresh(win);
    children
    |> List.iter(node => renderer(node, (win, Div(x, y, height, width))));
  | _ => ()
  };
};

let render = app => {
  let main_window = initscr();
  box(main_window, 0, 0);
  refresh();
  let node = app();
  renderer(node, (main_window, Div(0, 0, 0, 0)));
  let _a = getch();
  endwin();
};
