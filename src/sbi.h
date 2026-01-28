/*
  Struct containing the return status of OpenSBI.
  https://github.com/riscv-non-isa/riscv-sbi-doc/blob/master/src/binary-encoding.adoc
 */
struct SbiRet {
  long error;
  long value;
};


struct SbiRet debug_print(char *message, int len);

struct SbiRet set_timer_in_near_future();
