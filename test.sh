#!/bin/bash

# Fonction de test
run_test() {
    echo "TEST: $1"
    ./a.out "$1"
    echo "--------------------------------"
}

run_test "ls -l"
run_test "ls|wc"
run_test "cat<in>out"
run_test "echo '   espaces   '"
run_test "echo \"| > <\""
run_test "ls >> out"
run_test "" # Vide
run_test "echo \"unclosed"