rm -r build

cmake -S . -B build

cp app build/
rm app