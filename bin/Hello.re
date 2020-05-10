open Lib.Ncurses;
open Lib.Styling;
module N = Ncurses_bindings.Bindings(Ncurses_generated);
open N;

let app = () =>
  <Div x=2 y=8 height=40 width=80>
    <Div x=1 y=2 height=10 width=20> {s("window 1")} </Div>
    <Div x=1 y=23 height=10 width=20> {s("window 2")} </Div>
  </Div>;

render(app);
