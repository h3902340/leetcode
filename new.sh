cp template.txt $1.cpp
sed -i '' "s/xxxx/$1/g" $1.cpp
touch testcases/${1}_in.txt
touch testcases/${1}_out.txt