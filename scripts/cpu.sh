#!/usr/bin/bash
CPU="$(top -bn 1 | grep '%Cpu' | tr -d 'usy,' | awk '{print "user " $2 ", sys " $3}')"
echo -e "$CPU "
