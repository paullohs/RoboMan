#include "CMD.hpp"

CMD::CMD() {
}

CMD::CMD(CMD &cpy) {
  coords = cpy.coords;
  command = cpy.command;
  val = cpy.val;
  value = cpy.value;
}

CMD::CMD(CMD_ENUM &e, BOOL &b) : command(e), val(b) {
}

CMD::CMD(CMD_ENUM &e, VEC &v) : command(e), coords(v) {
}

CMD::CMD(CMD_ENUM &e, NUM &n) : command(e), value(n) {
}

CMD::~CMD() {
}
