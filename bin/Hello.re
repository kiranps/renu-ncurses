open Lib.Ncurses;
open Lib.Styling;

let container = style([height(40), width(80), x(2), y(4)]);
let box1 = style([height(10), width(20), x(1), y(2)]);
let box2 = style([height(10), width(20), x(1), y(23)]);

let app = () =>
  <Div style=container>
    <Div style=box1> {s("window 1")} </Div>
    <Div style=box2> {s("window 2")} </Div>
  </Div>;

render(app);
