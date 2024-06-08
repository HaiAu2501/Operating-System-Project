set_env TRUE 1
print_env TRUE
set_env FALSE 0
print_env FALSE
if (1 + 1 == 2): print_env TRUE else print_env FALSE
if (1 + 1 == 3): print_env TRUE else print_env FALSE
unset_env TRUE
print_env TRUE
unset_env FALSE
print_env FALSE