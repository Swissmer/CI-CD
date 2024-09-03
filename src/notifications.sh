#!/bin/bash

TELEGRAM_BOT_TOKEN=6684029645:AAEiljuAn0tIKxtz2ElrgoTMQ-TiqldynMQ
TELEGRAM_USER_ID=909047753
TIME=10
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="===============%0ADeploy status: $1%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG%0AStatus:+$CI_JOB_STATUS"

curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null