let c_headers = "#include <ncurses.h>";

let main = () => {
  let ml_out = open_out("ncurses_generated.ml");
  let c_out = open_out("ncurses_stubs.c");
  let c_fmt = Format.formatter_of_out_channel(c_out);
  let ml_fmt = Format.formatter_of_out_channel(ml_out);
  Format.fprintf(c_fmt, "%s@\n", c_headers);
  Cstubs.write_c(c_fmt, ~prefix="ncurses_stub_", (module Ncurses_bindings.Bindings));
  Cstubs.write_ml(ml_fmt, ~prefix="ncurses_stub_", (module Ncurses_bindings.Bindings));
  Format.pp_print_flush(ml_fmt, ());
  Format.pp_print_flush(c_fmt, ());
  close_out(ml_out);
  close_out(c_out);
};

let () = main();
