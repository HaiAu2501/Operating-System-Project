set_env a = 1
set_env b = 1
loop 10 set_env c = a + b & set_env a = b & set_env b = c
print_env c
unset_env a
unset_env b
unset_env c
print_env a
print_env b
print_env c