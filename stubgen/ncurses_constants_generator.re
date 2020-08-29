let c_headers = "#include <ncurses.h>";

let () = {
  let fname = Sys.argv[1];
  let oc = open_out_bin(fname);
  let format = Format.formatter_of_out_channel(oc);
  Format.fprintf(format, "%s@\n", c_headers);
  Cstubs.Types.write_c(format, (module Ncurses_constants.Types));
  Format.pp_print_flush(format, ());
  close_out(oc);
};
