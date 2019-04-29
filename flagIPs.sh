#!/bin/bash
grep IP /etc/log | awk {'print $3'} > tempSources.txt;
sed 's/\.[^.]*$//' tempSources.txt > sources.txt;
grep -v -f trustedIPs sources.txt > flaggedIPs.txt;
rm tempSources.txt sources.txt;
