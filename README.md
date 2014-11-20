PROMPT:

Individually, implement the Shift-Reduce algorithm shown under 4.5.3 LR Parsers in the book (8thand 10th edition, probablyalso 9th), including figure 4.5. Specifically:
 
1. The user should be able to enter any formula that corresponds to the grammar given, in a dialog box or command-line prompt, and it should be possible to enter another formula without ending the program.
2. The non-terminals will be E, T, and F, and the variables (shown as "id" in the grammar) can be a, b, c, or any single lower case letter. Spaces in the formula should be allowed but not required.
3. It should print each step on a separate line on standard output. The line should show which rule was used (R4, S5, etc.), the contents of the stack, and the remaining input.
4. If there is an error, it should give an error message (preferably indicating where) and return to the dialog box for input.

GRAMMAR RULES:
1. E -> E + T
2. E -> T
3. T -> T * F
4. T -> F
5. T -> F
6. F -> id


NOTES:
1) 'id' is represented by 'i' in the program