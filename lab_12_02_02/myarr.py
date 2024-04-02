import ctypes

lib = ctypes.CDLL("out/libmyarr.so")

#void fill_by_fib(int64_t *arr, size_t size)
_fill_by_fib = lib.fill_by_fib
_fill_by_fib.argtypes = (ctypes.POINTER(ctypes.c_int64), ctypes.c_size_t)
_fill_by_fib.restype = None

def fill_by_fib(n: int):
    new_arr = (ctypes.c_int64 * n)()
    _fill_by_fib(new_arr, n)
    return list(new_arr)

#pos_first_found(int64_t *dst, int64_t *arr, size_t size)
_pos_first_found = lib.pos_first_found
_pos_first_found.argtypes = (ctypes.POINTER(ctypes.c_int64), ctypes.POINTER(ctypes.c_int64), ctypes.c_size_t)
_pos_first_found.restype = None

def pos_first_found(arr: list):
    n = len(arr)
    new_arr = (ctypes.c_int64 * n)(*arr)
    res = (ctypes.c_int64 * n)()
    _pos_first_found(res, new_arr, n)
    return list(res)