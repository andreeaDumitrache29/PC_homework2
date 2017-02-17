#/bin/bash
file=$1
sed -i -e 's/-/!/g' $file
sed -i -e 's/:/7/g' $file
sed -i -e 's/;/?/g' $file
sed -i -e 's/\./\"/g' $file
sed -i -e 's/a/A/g' $file
sed -i -e 's/i/,/g' $file
sed -i -e 's/e/,/g' $file
