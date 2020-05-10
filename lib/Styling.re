module N = Ncurses_bindings.Bindings(Ncurses_generated);
open N;

module Constants = {
  let normal = 0;
  let attributes = 2147483392;
  let chartext = 255;
  let color = 65280;
  let standout = 65536;
  let underline = 131072;
  let reverse = 262144;
  let blink = 524288;
  let dim = 1048576;
  let bold = 2097152;
  let altcharset = 4194304;
  let invis = 8388608;
  let protect = 16777216;
  let horizontal = 33554432;
  let left = 67108864;
  let low = 134217728;
  let right = 268435456;
  let top = 536870912;
  let vertical = 1073741824;
  let combine = List.fold_left((lor), 0);
  let color_pair = n => n lsl 8 land color;
  let pair_number = a => (a land color) lsr 8;
};

module Color = {
  let black = 0;
  let red = 1;
  let green = 2;
  let yellow = 3;
  let blue = 4;
  let magenta = 5;
  let cyan = 6;
  let white = 7;
};

type rule =
  | D(string, int);

let create_pair = (~foreground=Color.white, ~background=Color.black) => {
  init_pair(1, foreground, background);
};

let init_all_pairs = () => {
  let order = ref(0);
  Array.iter(
    i => {
      Array.iter(j => init_pair(order^, i, j), Tablecloth.Array.range(8));
      order := order^ + 1;
    },
    Tablecloth.Array.range(8),
  );
};

let backgroundColor = color => D("backgroundColor", color);
let color = color => D("color", color);

let applyStyles = rules => {
  let fg = 7;
  let bg = 0;

  List.iter(
    rule => {
      switch (rule) {
      | D("backgroundColor", color) =>
        let bg = color;
        ();
      | D("color", color) =>
        let fg = color;
        ();
      | _ => ()
      }
    },
    rules,
  );
};

let className = [backgroundColor(Color.red), color(Color.green)];
