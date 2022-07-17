#!/bin/bash
# xset s 500 &
xautolock -time 5 -locker "slock" -notify 30 -notifier "notify-send.sh 'Locker' 'Locking screen in 30 seconds'" -killtime 5 -killer "systemctl suspend"
