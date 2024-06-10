create "Parent\Child\Grandchild"
list_tree Parent
cd Parent\
cd Child\
cd Grandchild\
write_file "Hello World from Grandchild" "Hello.txt"
read_file "Hello.txt"
cd ..\..\..
pwd
cd Parent
create "AnotherChild"
cd AnotherChild
create "AnotherGrandchild"
cd ..
pwd
cd ..
list_tree Parent
copy "Parent\Child" "Parent\Child (Copy)"
copy "Parent\Child\Grandchild" "Parent\Child\Grandchild (Copy)"
copy "Parent\AnotherChild" "Parent\AnotherChild (Copy)"
copy "Parent\AnotherChild\AnotherGrandchild" "Parent\AnotherChild\AnotherGrandchild (Copy)"
list_tree Parent
delete "Parent"