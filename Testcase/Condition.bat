set_env TRUE = 1
print_env TRUE
set_env FALSE = 0
print_env FALSE
set_env x = 1
print_env x
set_env y = 2
print_env y
set_env z = 3
print_env z
if (x + y == z): print_env TRUE else print_env FALSE
if (x + y == 3): print_env TRUE else print_env FALSE
if (1 + y == z): print_env TRUE else print_env FALSE
if (x + 2 == z): print_env TRUE else print_env FALSE
if (x + y != z): print_env TRUE else print_env FALSE
if (x + y > z): print_env TRUE else print_env FALSE
if (x + y >= z): print_env TRUE else print_env FALSE
if (x + y < z): print_env TRUE else print_env FALSE
if (x + y <= z): print_env TRUE else print_env FALSE
unset_env x
print_env x
unset_env y
print_env y
unset_env z
print_env z
unset_env TRUE
print_env TRUE
unset_env FALSE
print_env FALSE