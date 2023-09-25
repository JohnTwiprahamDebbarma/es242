#!/bin/bash

compile_c_program() {
    file_name="$1"
    file_name_length=$((${#file_name} - 2))
    output_name=""

    for ((i = 0; i <= file_name_length; i++)); do
        output_name="${output_name}${file_name:$i:1}"
    done

    output_file_name="${PWD}/${output_name}.exe"
    gcc "${PWD}/${file_name}" -o "$output_file_name"
}

alias make='compile_c_program'
