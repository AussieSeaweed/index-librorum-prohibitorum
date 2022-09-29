def print_(n):
    print(n)


Code = type(foo.__code__)
code = foo.__code__

foo.__code__ = Code(
    code.co_argcount,
    code.co_kwonlyargcount,
    code.co_nlocals,
    code.co_stacksize,
    code.co_flags,
    code.co_code,
    code.co_consts[:-2] + (print_.__code__,) + code.co_consts[-1:],
    code.co_names,
    code.co_varnames,
    code.co_filename,
    code.co_name,
    code.co_firstlineno,
    code.co_lnotab,
    code.co_freevars,
    code.co_cellvars,
)

foo()