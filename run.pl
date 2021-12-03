#!/usr/bin/env perl
#lance cmake
$cmake = system("cmake -DCMAKE_BUILD_TYPE=Debug -GNinja .");
if($cmake != 0){print("Ereur Premake\n"); exit;}
#compile
$ninja = system("ninja");
if($ninja != 0){print("Ereur Ninja (compilation)\n"); exit;}

#lance 
system("./CB")