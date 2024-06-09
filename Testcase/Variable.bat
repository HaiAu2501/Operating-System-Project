set_env TRUE 1
print_env TRUE
set_env FALSE 0
print_env FALSE
if (1 + 1 == 2): print_env TRUE else print_env FALSE
if ((1 + 1)*2 == 4): print_env TRUE else print_env FALSE
if ((1 + 1 + (1 + 1)*2)*2 == 12): print_env TRUE else print_env FALSE
if ((TRUE + TRUE)*2 == 4): print_env TRUE else print_env FALSE
if ((TRUE + TRUE + (TRUE + TRUE)*2)*2 == 12): print_env TRUE else print_env FALSE
if ((TRUE + TRUE*2 + TRUE*3 + TRUE*4)*FALSE == 0): print_env TRUE else print_env FALSE
unset_env TRUE
print_env TRUE
unset_env FALSE
print_env FALSE