# Compiler-C_Analyzer
A C++ Program for C Syntax Processing

# Examples
Input a C source code, for example
```
int main()
{
  int a,b;
  a=10.3211;
  a+=20; if (b==15) break; 
  float fa=3.141592653; 
  char s='z';
}
```
It should work like this
```
---- Analyzing ----
Line 1, Keyword	   int
Line 1, Keyword	   main
Line 1, Bracket	   (
Line 1, Bracket	   )
Line 2, Bracket	   {
Line 3, Keyword	   int
Line 3, Symbol	   a
Line 3, Comma	   ,
Line 3, Symbol	   b
Line 3, Semicol	   ;
Line 4, Symbol	   a
Line 4, Equal	   =
Line 4, Float	   10.3211
Line 4, Semicol	   ;
Line 5, Symbol	   a
Line 5, EqIncre	   +=
Line 5, Integer	   10100
Line 5, Semicol	   ;
Line 5, Keyword	   if
Line 5, Bracket	   (
Line 5, Symbol	   b
Line 5, Compare	   ==
Line 5, Integer	   1111
Line 5, Bracket	   )
Line 5, Keyword	   break
Line 5, Semicol	   ;
Line 6, Keyword	   float
Line 6, Symbol	   fa
Line 6, Equal	   =
Line 6, Float	   3.141592653
Line 6, Semicol	   ;
Line 7, Keyword	   char
Line 7, Symbol	   s
Line 7, Equal	   =
Line 7, Char	   z
Line 7, Semicol	   ;
Line 8, Bracket	   }
```
