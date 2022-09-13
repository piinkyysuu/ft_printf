# ft_printf
ft_printf goal is to reproduce libc printf functionality. This is an exellent project to learn about dispatcher table via the use  of an array of function’s pointers.

### Prototype:
```
int		ft_printf(const char *format, ...)
```

### Compile:
```
make
```

### Functionality:

**Pattern:**

```
%[flags][width][.precision][length]specifier
```

| flags * |  width * | .precision * | length * | specifier |
|:-------:|:--------:|:------------:|:--------:|:---------:|
|    -    | (number) |   (.number)  |  (none)  |     d     |
|    +    |          |              |    hh    |     i     |
| (space) |          |              |     h    |     o     |
|    #    |          |              |     l    |     u     |
|    0    |          |              |    ll    |     x     |
|         |          |              |     L    |     X     |
|         |          |              |          |     f     |

*Optional


























