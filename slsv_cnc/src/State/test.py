import slsv_state

core = slsv_state.riscv()
core.addHART()
core.addMemory()
core.addNHSV()
a = core.Memory[0].get_word(0)
print(a[1]);
a = core.Memory[0].get_word(0)