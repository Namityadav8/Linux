#!/bin/bash

echo "Enter first number:"
read num1

echo "Enter second number:"
read num2

echo "Choose an operation:"
echo "1. Addition"
echo "2. Subtraction"
echo "3. Multiplication"
echo "4. Division"
read operation

case $operation in
    1) result=$((num1 + num2));;
    2) result=$((num1 - num2));;
    3) result=$((num1 * num2));;
    4) result=$(echo "scale=2; $num1 / $num2" | bc);;
    *) echo "Invalid operation."
       exit 1
       ;;
esac

echo "Result: $result"