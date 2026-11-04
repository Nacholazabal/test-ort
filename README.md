# Práctica 7 - Pruebas y CI

Drivers de LED y potenciómetro de la Práctica 4, con pruebas unitarias en Unity, análisis estático con Cppcheck, formato con clang-format y un workflow de GitHub Actions que corre todo en cada push y en cada pull request.

## Comandos

Desde la raíz del repositorio:

```
clang-format --dry-run --Werror src/*.c include/*.h test/*.c
cppcheck --enable=warning,style --error-exitcode=1 -I include src
gcc -Wall -Wextra -Werror -Iinclude -Isrc -Itest/unity test/test_potenciometro.c test/unity/unity.c -o build/test_potenciometro.exe
```

Unity (`test/unity/`) es de ThrowTheSwitch, versión 2.7.0, con licencia MIT (`test/unity/LICENSE.txt`).
