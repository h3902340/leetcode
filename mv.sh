mv $1.cpp $2.cpp
sed -i '' "s/$1/$2/g" $2.cpp
mv testcases/${1}_in.txt testcases/${2}_in.txt
mv testcases/${1}_out.txt testcases/${2}_out.txt