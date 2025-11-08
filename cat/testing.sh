#!/bin/bash


echo "Test"
echo "test line" > test1.txt
echo "test line 2" > test2.txt
echo ""

echo "one file"
./s21_cat test1.txt
echo ""

echo "more files"
./s21_cat test1.txt test2.txt
echo ""

echo "not found"
./s21_cat secretS21.txt
echo ""

echo "Is a directory"
./s21_cat /etc/
echo ""



echo "n flag"
echo "line" > test_n.txt
echo "" >> test_n.txt
echo "lineline" >> test_n.txt
./s21_cat -n test_n.txt

echo "Regular:"
cat -n test_n.txt

echo ""
echo "--number flag"
./s21_cat --number test_n.txt
echo "Regular:"
cat --number test_n.txt
echo ""

echo "b flag"
echo "line1" > test_b.txt
echo "" >> test_b.txt
echo "" >> test_b.txt
echo "line2" >> test_b.txt

./s21_cat -b test_b.txt
echo "Refular:"
cat -b test_b.txt

echo ""
echo "--number-nonblank"
./s21_cat --number-nonblank test_b.txt
echo "Regular:"
cat --number-nonblank test_b.txt
echo ""


echo "s flag"
echo "line1" > test_s.txt
echo "" >> test_s.txt
echo "" >> test_s.txt
echo "line4" >> test_s.txt
echo "" >> test_s.txt
echo "" >> test_s.txt
echo "" >> test_s.txt
echo "" >> test_s.txt
echo "" >> test_s.txt
echo "line" >> test_s.txt

./s21_cat -s test_s.txt
echo "Regular:"
cat -s test_s.txt

echo ""
echo "--squeeze-blank"
./s21_cat --squeeze-blank test_s.txt
echo "Regular:"
cat --squeeze-blank test_s.txt
echo ""


echo -e "hello\t\tworld" > test_spec.txt
echo -e "line2\a" >> test_spec.txt
echo -e "line3" >> test_spec.txt

echo "e flag"
./s21_cat -e test_spec.txt
echo "Regular:"
cat -e test_spec.txt

echo ""

echo "E flag"
./s21_cat -E test_spec.txt
echo "Regular:"
cat -E test_spec.txt

echo ""

echo "t flag"
./s21_cat -t test_spec.txt
echo "Regular:"
cat -t test_spec.txt

echo ""

echo "T flag"
./s21_cat -T test_spec.txt
echo "Regular:"
cat -T test_spec.txt