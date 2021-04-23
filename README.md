# nm_otool

`nm_otool` is clone project of `nm` and `otool` command, specifically working with mach-o file.
`nm` shows symbol table with virtual address, type and name.
`otool` shows hex dump of `__text` section of `__TEXT` segment.

<br/><br/>

## Requirements

`nm_otool` use [libft](https://github.com/jebae/libft), [ft_printf](https://github.com/jebae/ft_printf.git)

```
# download libft
git clone https://github.com/jebae/libft.git

# download ft_printf
git clone https://github.com/jebae/ft_printf.git

# directory structure
root/
 libs/
  libft
  ft_print
```

<br/><br/>

## Install

```
# for both nm and otool
make

# for nm only
make nm

# for otool only
make otool
```

<br/><br/>

## Usage

>💡 `nm` and `otool` uses several function as shared library from `./shared/shared.so`.
> Don't forget to set environment variable before execute program.
> `DYLD_LIBRARY_PATH=<shared.so path> ./ft_nm ...`
> `DYLD_LIBRARY_PATH=<shared.so path> ./ft_otool ...`

<br/>

### nm

```
nm [mach-o file name | archive file name]

# execute file
./ft_nm a.out

# object file
./ft_nm obj.o

# shared library
./ft_nm dylib.so

# archive file
./ft_nm libft.a

# multiple argument
./ft_nm libft.a a.out dylib.so

e.g.
$> DYLD_LIBRARY_PATH=shared ./nm/ft_nm ./nm/objs/sym_list.o
00000000000002f0 t _cmp
00000000000000b0 T _free_sym_list
                 U _ft_memalloc
                 U _ft_memcpy
                 U _ft_memdel
                 U _ft_strcmp
0000000000000130 T _get_sym_list
0000000000000000 T _get_symtab_command
00000000000002c0 t _handle_err
                 U _quick_sort
```

<br/>

### otool

```
otool [mach-o file name | archive file name]

# execute file
./otool a.out

# object file
./otool obj.o

# shared library
./otool dylib.so

# archive file
./otool libft.a

# multiple argument
./otool libft.a a.out dylib.so

e.g.
$> DYLD_LIBRARY_PATH=shared ./otool/ft_otool ./otool/objs/main.o
./otool/objs/main.o:
Contents of (__TEXT, __text) section
0000000000000000        55 48 89 e5 48 83 ec 20 c7 45 fc 00 00 00 00 89
0000000000000010        7d f8 48 89 75 f0 83 7d f8 01 0f 8f 1a 00 00 00
0000000000000020        48 8d 3d 6a 00 00 00 b0 00 e8 00 00 00 00 c7 45
0000000000000030        fc 01 00 00 00 e9 4e 00 00 00 c7 45 ec 01 00 00
0000000000000040        00 8b 45 ec 3b 45 f8 0f 8d 34 00 00 00 48 8b 45
0000000000000050        f0 48 63 4d ec 48 8b 3c c8 e8 00 00 00 00 83 f8
0000000000000060        ff 0f 85 0c 00 00 00 c7 45 fc 01 00 00 00 e9 15
0000000000000070        00 00 00 8b 45 ec 83 c0 01 89 45 ec e9 c0 ff ff
0000000000000080        ff c7 45 fc 00 00 00 00 8b 45 fc 48 83 c4 20 5d
0000000000000090        c3
```
