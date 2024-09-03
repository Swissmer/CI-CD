#!/bin/bash

SUCCESS=300
FAIL=0
COUNTER=300

sleep 2

echo "\033[31mFAIL: $FAIL\033[0m"
echo "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"

if [ $FAIL -gt 0 ]; then
  exit 1  # Завершаем скрипт с кодом ошибки
fi