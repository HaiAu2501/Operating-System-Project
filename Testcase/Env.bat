save_env ENV
read_file ENV
set_env a 1
set_env b 2
print_env a
print_env b
save_env ENV
read_file ENV
write_file c=3 ENV
read_file ENV
print_env c
unset_env a
unset_env b
delete ENV