s/"\([^"]*\)"/“\1”/g
s/`\([^`']*\)'/‘\1’/g
s/ '\([^`']*\)' / ‘\1’ /g
s/ '\([^`']*\)'$/ ‘\1’/g
s/^'\([^`']*\)' /‘\1’ /g
s/“”/""/g
s/“/“[1m/g
s/”/[0m”/g
s/‘/‘[1m/g
s/’/[0m’/g
