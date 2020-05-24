type stylesheet = {
  x: option(int),
  y: option(int),
  height: option(int),
  width: option(int),
};

type rule =
  | X(int)
  | Y(int)
  | Height(int)
  | Width(int);

let height = x => Height(x);
let width = x => Width(x);
let x = x => X(x);
let y = x => Y(x);

let renderDiv = style => {};

let style = x => {
  let rec gen = (x, style) => {
    switch (x) {
    | [head, ...tail] =>
      switch (head) {
      | X(x) => gen(tail, {...style, x: Some(x)})
      | Y(x) => gen(tail, {...style, y: Some(x)})
      | Height(x) => gen(tail, {...style, height: Some(x)})
      | Width(x) => gen(tail, {...style, width: Some(x)})
      }
    | [] => style
    };
  };
  gen(x, {x: None, y: None, height: None, width: None});
};
