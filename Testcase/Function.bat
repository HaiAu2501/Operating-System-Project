function f(x, y, z) = x*y*z
set_env a = 2
set_env b = 3
set_env c = 4
evaluate f 2 3 4
evaluate f a b c
evaluate f a 3 4
set_env m = 10
function g(x) = x*(m + 1)
evaluate g 5
evaluate g a
evaluate g m
unset_env m 
evaluate g 5
set_env x = 5
function h(x) = x + x*x
evaluate h 3
evaluate h x
unset_env a
unset_env b
unset_env c
unset_env x