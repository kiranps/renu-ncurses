module N = Ncurses_bindings.Bindings(Ncurses_generated);
open N;
open Styling;
open Tablecloth;

type element =
  | Div(stylesheet);

type dom =
  | Node(list(dom), element)
  | Text(string);

module Div = {
  let createElement = (~children=[], ~style, ()) => {
    Node(children, Div(style));
  };
};

let s = x => Text(x);

let text = (win, x, y, value) => {
  mvwprintw(win, x, y, value);
  wrefresh(win);
};

let div = (pwin, x, y, height, width) => {
  let win = subwin(pwin, height, width, x, y);
  box(win, 0, 0);
  wrefresh(win);
  win;
};

let rec renderer = (node, parent) => {
  let (pwin, Div(style')) = parent;

  switch (node) {
  | Text(value) => text(pwin, 1, 1, value)
  | Node(children, Div(style)) =>
    let {x, y, height, width} = style;
    let {x: px, y: py, height: h', width: w'} = style';

    let x' = Option.getExn(px) + Option.getExn(x);
    let y' = Option.getExn(py) + Option.getExn(y);
    let height' = Option.getExn(height);
    let width' = Option.getExn(width);
    let win = div(pwin, x', y', height', width');

    children |> List.iter(~f=n => renderer(n, (win, Div(style))));
  | _ => ()
  };
};

let st = {x: Some(0), y: Some(0), height: Some(0), width: Some(0)};

let render = app => {
  let main_window = initscr();
  box(main_window, 0, 0);
  refresh();
  let node = app();
  renderer(node, (main_window, Div(st)));
  let _a = getch();
  endwin();
};
