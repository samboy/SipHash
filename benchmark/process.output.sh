#!/bin/sh

awk '{
		if(/lun/){name = $1}
		if(/real/){sub(/.*m/,"");sub(/s/,"");bench[name] += $0}
      }
      END{
		for(b in bench){print b " " bench[b]}
      }'
