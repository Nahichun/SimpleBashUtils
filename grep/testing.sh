echo "Test"

echo ""
echo "-e flag"
grep -e "main" s21_grep.c
./s21_grep -e "main" s21_grep.c

echo ""
echo "without flags"
grep "main" s21_grep.c
./s21_grep "main" s21_grep.c

echo ""
echo "-i flag"
grep -i "MaIN" s21_grep.c
./s21_grep -i "MaIN" s21_grep.c

echo ""
echo "-v flag"
grep -v "main" s21_grep.c
./s21_grep -v "main" s21_grep.c

echo ""
echo "-c flag"
grep -c "main" s21_grep.c
./s21_grep -c "main" s21_grep.c

echo ""
echo "-n flag"
grep -n "main" s21_grep.c
./s21_grep -n "main" s21_grep.c

echo ""
echo "many files"
grep -c "main" s21_grep.c test.txt
./s21_grep -c "main" s21_grep.c test.txt