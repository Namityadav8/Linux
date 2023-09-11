#!/bin/bash

echo "Prime Numbers:"


read -p "Enter an upper limit: " limit

for ((num = 2; num <= limit; num++)); do
    is_prime=true

    for ((divisor = 2; divisor * divisor <= num; divisor++)); do
        ((num % divisor == 0)) && { is_prime=false; break; }
    done

    $is_prime && echo $num
done
