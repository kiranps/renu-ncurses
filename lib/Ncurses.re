module N = Ncurses_bindings.Bindings(Ncurses_generated);
open N;
open Ctypes;
open Styling.Constants;
open Styling;

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

module Screen = {
  let createElement = (~x, ~y, ~height, ~width, ~children=[], ()) => {
    Node(children, Div(x, y, height, width));
  };
};

let s = x => Text(x);

let rec renderer = (~node, ~parentWindow=?, ()) => {
  switch (node) {
  | Text(value) =>
    switch (parentWindow) {
    | Some((pwin, _)) =>
      mvwprintw(pwin, 2, 2, value);
      wrefresh(pwin);
    | None => mvprintw(2, 2, value)
    }
  | Node(children, Div(x, y, height, width)) =>
    switch (parentWindow) {
    | Some((pwin, Div(px, py, ph, pw))) =>
      let win = subwin(pwin, height, width, px + x, py + y);
      box(win, 0, 0);
      wrefresh(win);
      children
      |> List.iter(node =>
           renderer(
             ~node,
             ~parentWindow=(win, Div(x, y, height, width)),
             (),
           )
         );
    | None =>
      let win = newwin(height, width, x, y);
      box(win, 0, 0);
      wrefresh(win);
      children
      |> List.iter(node =>
           renderer(
             ~node,
             ~parentWindow=(win, Div(x, y, height, width)),
             (),
           )
         );
    }
  | _ => ()
  };
  ();
};

let render = app => {
  let main_window = initscr();
  box(main_window, 0, 0);
  refresh();
  let node = app();
  renderer(~node, ());
  let _a = getch();
  endwin();
};
