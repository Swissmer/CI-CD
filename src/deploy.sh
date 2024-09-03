#!/bin/bash

cd cat
scp s21_cat.c swissmer@10.10.0.2:/usr/local/bin/
cd ../grep
scp s21_grep.c swissmer@10.10.0.2:/usr/local/bin/
ssh swissmer@10.10.0.2 ls /usr/local/bin