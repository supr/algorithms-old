#!/bin/bash

for filename in *.txt; do
  #foo=${filename%.foo}
  #mv $filename "$foo.txt" 
  

  mv $filename ${filename%.txt}.foo

  #foo=$( awk -F '.foo' '{print $1}' )
  #echo $filename
  #mv $filename.{foo} $filename.txt
done
