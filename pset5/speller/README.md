# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

the maximum length of word example in dictionary.h

## According to its man page, what does `getrusage` do?

The function examine the resource usage by a process and declared in sys/resource.h
Function: ```int getrusage(int processes, struct rusage *rusage)```
- Data type: struct rusage, has various statistics
## Per that same man page, how many members are in a variable of type `struct rusage`?

15

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?



## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

the for loop is going to read the file character from character until it reaches the EOF, andif the character is alphabet, then it will start to put into word according to the index counter, it will keep doing that, until the next c is not digit and alpha and if index is greater than zero, it will insert '\0' to the end of word. meanwhile, if the index is at zero and fgetc got a digit, it will enter another while loop to discard all the alphabet and number after the digit until the isalnum condition doesnt satisfy and break out of the while loop

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fscanf cant identify which word contain number, which should not be included. since fscanf read subsequent characters until whitespace, that meaning punctuation like colon will be include in words too 

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

We dont want to modify the variable from which the pointer point to
